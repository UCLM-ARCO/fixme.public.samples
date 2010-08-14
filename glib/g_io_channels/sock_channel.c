#include <sock_channel.h>
#include <glib/gmessages.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


#define ACCEPTOR_BACKLOG 8

struct slave_data {
  GIOCondition cond;
  GIOFunc func;
  gpointer data;
  GFunc init;
  GDestroyNotify notify;
  guint prio;
};

/* Abre un socket maestro atendiendo el servicio (o puerto)
   especificado y utilizando protocolo "tcp" o "udp".
 */
GIOChannel* 
g_io_channel_acceptor_new (const char* service, const char* protocol)
{
    struct servent *pse;
    struct protoent *ppe;
    struct sockaddr_in sin;
    int	s, type, yes = 1;

    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((pse = getservbyname(service, protocol)) != NULL) {
	sin.sin_port = pse->s_port;
    }
    else if ((sin.sin_port = htons(atoi(service))) == 0) {
	return NULL;
    }
    if ((ppe = getprotobyname(protocol)) == 0) {
	return NULL;
    }
    type = (strcmp(protocol, "udp") == 0)? SOCK_DGRAM: SOCK_STREAM;
    if ((s = socket(PF_INET, SOCK_STREAM, ppe->p_proto)) < 0) {
	return NULL;
    }
    setsockopt (s, SOL_SOCKET, SO_REUSEADDR, (char*)&yes, sizeof(yes));
    setsockopt (s, SOL_SOCKET, SO_KEEPALIVE, (char*)&yes, sizeof(yes));
    if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
	close (s);
	return NULL;
    }
    if (type == SOCK_STREAM && listen(s, ACCEPTOR_BACKLOG) < 0) {
	close (s);
	return NULL;
    }
    //g_message("New acceptor socket: %d\n", s);
    return g_io_channel_unix_new (s);
}

/* Abre un socket con el destino especificado.  El servicio puede
   también ser un puerto, y el protocolo "udp" o cualquier otro
   orientado a conexión (e.g. "tcp").  ¡Ojo! si es orientado a
   conexión se quedará bloqueado en el connect durante un buen rato.
 */
GIOChannel* 
g_io_channel_connector_new (const char* host, const char* service, const char* protocol)
{
    struct hostent *phe;
    struct servent *pse;
    struct protoent *ppe;
    struct sockaddr_in sin;
    int s, type;

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    if ((pse = getservbyname(service, protocol)) != NULL) {
	sin.sin_port = pse->s_port;
    }
    else if ((sin.sin_port = htons(atoi(service))) == 0) {
	return NULL;
    }
    if ((phe = gethostbyname(host)) != NULL) {
	memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
    }
    else if ((sin.sin_addr.s_addr = inet_addr(host)) == -1) {
	return NULL;
    }
    if ((ppe = getprotobyname(protocol)) == NULL) {
	return NULL;
    }
    type = (strcmp(protocol, "udp") == 0)? SOCK_DGRAM: SOCK_STREAM;
    if ((s = socket(PF_INET, type, ppe->p_proto)) < 0) {
	return NULL;
    }
    if (type != SOCK_DGRAM) {
	if (connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
	    close (s);
	    return NULL;
	}
    }
    else {
	if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
	    close (s);
	    return NULL;
	}
    }
    //g_message("New connector socket: %d\n", s);
    return g_io_channel_unix_new (s);
}

/* Accepts an external connection
 */
GIOChannel*
g_io_channel_acceptor_accept (GIOChannel* src)
{
  int fd;

  fd = accept (g_io_channel_unix_get_fd(src), NULL, NULL);
  if (fd > 0) {
    GIOChannel* slave;

    slave = g_io_channel_unix_new (fd);
    g_io_channel_set_encoding(slave, g_io_channel_get_encoding(src), NULL);
    if (FALSE == g_io_channel_get_buffered(src))
      g_io_channel_set_buffered(slave, FALSE);
    //g_message("Conection in socket: %d, data: %p, slave data: %p\n", fd, sd, sd->data);
    return slave;
  }
  return NULL;
}

/* Handler correspondiente a un socket maestro orientado a conexión.
 */
static gboolean
acceptor_master_handle (GIOChannel* src, GIOCondition c, gpointer data)
{
  GIOChannel* slave = g_io_channel_acceptor_accept(src);
  if (slave != NULL) {
    struct slave_data* sd = (struct slave_data*) data;
    if (NULL != sd->init)
      sd->init(slave, sd->data);
    g_io_add_watch_full(slave, sd->prio, sd->cond, sd->func, sd->data, sd->notify);
  }
  return TRUE;
}

/* Funcion similar a g_io_add_watch para sockets orientados a
   conexión, en los que la GIOFunc debe procesar datos de los socket
   esclavos, no del maestro. Tiene que ser utilizado con canales que
   acepten conexiones (SOCK_STREAM, SOCK_SEQPACKET, SOCK_RDM)
 */
guint
g_io_add_acceptor(GIOChannel* ch, GIOCondition c, GIOFunc func, gpointer data)
{
  return g_io_add_acceptor_full(ch, G_PRIORITY_DEFAULT, c, func, data, NULL, NULL);
}

/* Funcion similar a g_io_add_watch_full para sockets orientados a
   conexión, en los que la GIOFunc debe procesar datos de los socket
   esclavos, no del maestro. Tiene que ser utilizado con canales que
   acepten conexiones (SOCK_STREAM, SOCK_SEQPACKET, SOCK_RDM). La
   función "init" se invoca cuando se crea un nuevo canal esclavo y se
   le pasan el canal nuevo y el puntero data.
 */
guint
g_io_add_acceptor_full(GIOChannel* ch, guint prio, GIOCondition c, GIOFunc func, gpointer data, GFunc init, GDestroyNotify notify)
{
  struct slave_data* sd = g_new(struct slave_data, 1);
  sd->cond = c;
  sd->func = func;
  sd->data = data;
  sd->init = init;
  sd->notify = notify;
  sd->prio = prio;
  //g_message("Accepting conections in %d, data: %p, slave data: %p\n", g_io_channel_unix_get_fd(ch), sd, sd->data);
  return g_io_add_watch_full(ch, prio, G_IO_IN, acceptor_master_handle, sd, g_free);
}


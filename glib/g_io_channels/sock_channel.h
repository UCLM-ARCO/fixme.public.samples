#ifndef SOCK_CHANNEL_H
#define SOCK_CHANNEL_H

#include <glib/giochannel.h>

/* Abre un socket maestro atendiendo el servicio (o puerto)
   especificado y utilizando protocolo "tcp" o "udp".
 */
GIOChannel* 
g_io_channel_acceptor_new (const char* service, const char* protocol);

/* Abre un socket con el destino especificado.  El servicio puede
   también ser un puerto, y el protocolo "udp" o cualquier otro
   orientado a conexión (e.g. "tcp").  ¡Ojo! si es orientado a
   conexión se quedará bloqueado en el connect durante un buen rato.
 */
GIOChannel* 
g_io_channel_connector_new (const char* host, const char* service, const char* protocol);

/* Devuelve el socket escalvo correspondiente a la siguiente conexión (o NULL)
 */
GIOChannel*
g_io_channel_acceptor_accept (GIOChannel* src);

/* Funcion similar a g_io_add_watch para sockets orientados a
   conexión, en los que la GIOFunc debe procesar datos de los socket
   esclavos, no del maestro. Tiene que ser utilizado con canales que
   acepten conexiones (SOCK_STREAM, SOCK_SEQPACKET, SOCK_RDM)
 */
guint
g_io_add_acceptor(GIOChannel* ch, GIOCondition c, GIOFunc func, gpointer data);

/* Funcion similar a g_io_add_watch_full para sockets orientados a
   conexión, en los que la GIOFunc debe procesar datos de los socket
   esclavos, no del maestro. Tiene que ser utilizado con canales que
   acepten conexiones (SOCK_STREAM, SOCK_SEQPACKET, SOCK_RDM)
 */
guint
g_io_add_acceptor_full(GIOChannel* ch, guint prio, GIOCondition c, GIOFunc func, gpointer data, GFunc init, GDestroyNotify notify);

#endif


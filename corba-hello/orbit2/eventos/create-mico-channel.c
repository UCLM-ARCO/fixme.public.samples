#include <stdlib.h>
#include <stdio.h>
#include "CosEventChannel.h"
#include "SimpleEventChannelAdmin.h"

CORBA_ORB orb = NULL;

/* Tratamiento de excepciones */
void Exception( CORBA_Environment *ev)
{
  switch (ev->_major)
    {
    case CORBA_NO_EXCEPTION: return;
    case CORBA_SYSTEM_EXCEPTION:
      g_printerr ("CORBA system exception.\n");
      exit (1);
    case CORBA_USER_EXCEPTION:
      g_printerr (CORBA_exception_id(ev));
      exit(1);
    default :
      g_printerr ("Unknown value for major exception !!!\n");
      exit(1);
    }
}


/* Crea un canal de eventos utilizando una factoria de canales de mico */
CosEventChannelAdmin_EventChannel
create_channel(CORBA_Object factory, CORBA_Environment* ev)
{
  CosEventChannelAdmin_EventChannel retval;

  /* crear un canal */
  retval = SimpleEventChannelAdmin_EventChannelFactory_create_eventchannel(factory, ev);
    
  Exception (ev);
  g_printerr("canal\n");

  return retval;
}

int
main(int argc, char* argv[])
{
  PortableServer_POA poa;
  CORBA_Environment ev;
  CosEventChannelAdmin_EventChannel channel;
  CORBA_Object factory;
  char *ior;


  CORBA_exception_init(&ev);
  orb = CORBA_ORB_init(&argc, argv, "orbit-local-orb", &ev);

  if(argc < 2) {
    g_printerr("Necesito el IOR de la factoria de canales de eventos como argumento\n");
    return 1;
  }

  factory = CORBA_ORB_string_to_object(orb, argv[1], &ev);

  Exception (&ev);
  if (CORBA_Object_is_nil(factory, &ev)) {
    printf("No puedo conectar con %s\n", argv[1]);
    return 1;
  }
  g_printerr("factoria\n");

  channel = create_channel(factory, &ev);

  if (CORBA_Object_is_nil(channel, &ev)) {
    printf("No se pudo crear el canal");
    return 1;
  }

  ior = CORBA_ORB_object_to_string(orb, channel, &ev);
  printf("%s\n", ior); fflush(stderr);
  CORBA_free(ior);

  Exception (&ev);
  return 0;
}


#include <stdio.h>
#include "CosEventChannel.h"

/*
 * Tratamiento de excepciones
 */
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

int
main(int argc, char* argv[])
{
  CORBA_ORB orb = NULL;
  PortableServer_POA poa;
  CORBA_Environment ev;
  CosEventChannelAdmin_EventChannel channel;
  CosEventChannelAdmin_EventChannelFactory factory;
  char *ior;


  CORBA_exception_init(&ev);
  orb = CORBA_ORB_init(&argc, argv, "orbit-local-orb", &ev);
  poa = (PortableServer_POA)CORBA_ORB_resolve_initial_references(orb, "RootPOA", &ev);
  PortableServer_POAManager_activate(PortableServer_POA__get_the_POAManager(poa, &ev), &ev);

  if(argc < 2) {
	 printf("Necesito el IOR del servidor de eventos como argv[1]\n");
	 return 1;
  }
  
  /* Instaciamos el servidor de eventos  */
  factory = CORBA_ORB_string_to_object(orb, argv[1], &ev);
  Exception (&ev);
  if (CORBA_Object_is_nil(factory, &ev)) {
	 printf("No puedo conectar con %s\n", argv[1]);
	 return 1;
  }

  channel = CosEventChannelAdmin_EventChannelFactory_new_event_channel(factory, &ev);
  Exception (&ev);

  if (CORBA_Object_is_nil(channel, &ev)) {
	 printf("No puedo crear el canal\n");
	 return 1;
  }

  ior = CORBA_ORB_object_to_string(orb, channel, &ev);
  fprintf(stderr,"%s\n", ior); fflush(stderr);
  CORBA_free(ior);
  CORBA_ORB_run(orb, &ev);

  Exception (&ev);
  return 0;
}

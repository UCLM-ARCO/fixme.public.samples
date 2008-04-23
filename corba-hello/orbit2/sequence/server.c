#include "hello.h"

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>


int
main (int argc, char *argv[])
{
    PortableServer_POA poa;
    CORBA_Environment ev;
    CORBA_ORB orb;
   
    HelloModule_hello hello_client;    /* El objeto cliente */
    char* ior;

    signal(SIGINT, exit);
    signal(SIGTERM, exit);

    CORBA_exception_init(&ev);
    orb = CORBA_ORB_init(&argc, argv, "orbit-local-orb", &ev);
    poa = (PortableServer_POA)
        CORBA_ORB_resolve_initial_references(orb, "RootPOA", &ev);
    PortableServer_POAManager_activate
        (PortableServer_POA__get_the_POAManager(poa, &ev), &ev);

    hello_client = (HelloModule_hello)impl_HelloModule_hello__create(poa, &ev);
    if (CORBA_Object_is_nil(hello_client, &ev)) {
        printf("No puedo obtener una referencia\n");
        return 1;
    }  

    ior = CORBA_ORB_object_to_string(orb, hello_client, &ev);
    fprintf(stderr,"%s\n", ior); fflush(stderr);
    CORBA_free(ior);
    CORBA_ORB_run(orb, &ev);
    return 0;
}
/* fin parte editada */

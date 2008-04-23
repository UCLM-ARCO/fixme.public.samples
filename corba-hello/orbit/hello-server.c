#include "hello.h"

/*** App-specific servant structures ***/
typedef struct
{
   POA_hello servant;
   PortableServer_POA poa;

}
impl_POA_hello;

/*** Implementation stub prototypes ***/
static void impl_hello__destroy(impl_POA_hello * servant,
				CORBA_Environment * ev);
static void
impl_hello_puts(impl_POA_hello * servant,
		CORBA_char * str, CORBA_Environment * ev);

/*** epv structures ***/
static PortableServer_ServantBase__epv impl_hello_base_epv = {
   NULL,			/* _private data */
   NULL,			/* finalize routine */
   NULL,			/* default_POA routine */
};
static POA_hello__epv impl_hello_epv = {
   NULL,			/* _private */
   (gpointer) & impl_hello_puts,

};

/*** vepv structures ***/
static POA_hello__vepv impl_hello_vepv = {
   &impl_hello_base_epv,
   &impl_hello_epv,
};

/*** Stub implementations ***/
static hello
impl_hello__create(PortableServer_POA poa, CORBA_Environment * ev)
{
   hello retval;
   impl_POA_hello *newservant;
   PortableServer_ObjectId *objid;

   newservant = g_new0(impl_POA_hello, 1);
   newservant->servant.vepv = &impl_hello_vepv;
   newservant->poa = poa;
   POA_hello__init((PortableServer_Servant) newservant, ev);
   objid = PortableServer_POA_activate_object(poa, newservant, ev);
   CORBA_free(objid);
   retval = PortableServer_POA_servant_to_reference(poa, newservant, ev);

   return retval;
}

static void
impl_hello__destroy(impl_POA_hello * servant, CORBA_Environment * ev)
{
   PortableServer_ObjectId *objid;

   objid = PortableServer_POA_servant_to_id(servant->poa, servant, ev);
   PortableServer_POA_deactivate_object(servant->poa, objid, ev);
   CORBA_free(objid);

   POA_hello__fini((PortableServer_Servant) servant, ev);
   g_free(servant);
}

static void
impl_hello_puts(impl_POA_hello * servant,
		CORBA_char * str, CORBA_Environment * ev)
{
/* principio parte editada */
   puts("Servidor Hello ORBit:");
   puts(str);
}
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int
main (int argc, char *argv[])
{
    PortableServer_POA poa;
    CORBA_Environment ev;
    CORBA_ORB orb;
    hello hello_client;    /* El objeto cliente */
    char* ior;

    signal(SIGINT, exit);
    signal(SIGTERM, exit);

    CORBA_exception_init(&ev);
    orb = CORBA_ORB_init(&argc, argv, "orbit-local-orb", &ev);
    poa = (PortableServer_POA)
        CORBA_ORB_resolve_initial_references(orb, "RootPOA", &ev);
    PortableServer_POAManager_activate
        (PortableServer_POA__get_the_POAManager(poa, &ev), &ev);
    hello_client = impl_hello__create(poa, &ev);
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

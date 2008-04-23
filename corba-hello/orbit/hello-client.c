#include <stdio.h>
#include "hello.h"     /* Generado por orbit-idl */

int
main (int argc, char *argv[])
{
    CORBA_Environment ev;
    CORBA_ORB orb;
    hello hello_client;    /* El objeto cliente */

    /* inicializacion */
    CORBA_exception_init(&ev);
    orb = CORBA_ORB_init(&argc, argv, "orbit-local-orb", &ev);
    if(argc < 2) {
        printf("Necesito el IOR del servidor como argv[1]\n");
        return 1;
    }
    /* conexion con servidor */
    hello_client = CORBA_ORB_string_to_object(orb, argv[1], &ev);
    if (CORBA_Object_is_nil(hello_client, &ev)) {
        printf("No puedo conectar con %s\n", argv[1]);
        return 1;
    }
    /* invocar metodo */
    hello_puts(hello_client, "Cliente ORBit: Hello, World!\n", &ev);
    if(ev._major != CORBA_NO_EXCEPTION) {
        printf("Recibi excepcion %d!\n", ev._major);
        return 1;
    }
    /* liberar recursos */
    CORBA_Object_release((CORBA_Object)hello_client, &ev);
    CORBA_Object_release((CORBA_Object)orb, &ev);
    return 0;
}

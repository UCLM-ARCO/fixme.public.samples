#include <stdio.h>
#include "hello.h"     /* Generado por orbit-idl */



#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int
main (int argc, char *argv[])
{
    CORBA_Environment ev;
    CORBA_ORB orb;
    HelloModule_hello hello_client;    /* El objeto cliente */
    
    
    //.......................................
    HelloModule_frame *framec;
    static char *cadena = "hello Server";

    //:::::::::::::::::::::::::::::::::::::::
    
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
    /*.........Metodo Puts..................*/

    framec = HelloModule_frame__alloc();
    framec->_buffer = HelloModule_frame_allocbuf(13);
    memcpy(framec->_buffer, cadena, 13);
    framec->_maximum = 13;//tamaño del buffer disponible.
    framec->_length  = 13;//número de datos enviados.
    framec->_release = CORBA_TRUE;

    HelloModule_hello_puts(hello_client, framec, &ev);
    /*:::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

    /*.............. Metodo Gets ...................*/
    framec = HelloModule_hello_gets(hello_client, &ev);
    printf("EL SERVIDOR DICE: %s\n",framec->_buffer);
    /*::::::::::::::::::::::::::::::::::::::::::::::*/
   
      
    if(ev._major != CORBA_NO_EXCEPTION) {
        printf("Recibi excepcion %d!\n", ev._major);
        return 1;
    }
    /* liberar recursos */
    CORBA_Object_release((CORBA_Object)hello_client, &ev);

    return 0;
}

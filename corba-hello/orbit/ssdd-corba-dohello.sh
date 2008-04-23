#!/bin/bash

help() {
	echo "Usage: $0 [OPTION]..."
	echo " Live ORBit tutorial (hello world)"
	echo
	echo "  -?, --help 		display this help and exit"
	echo "      --ayuda		the same in spanish"
	echo "      --polite		be politically correct"
	echo "      --clean		remove created files"
	echo "      --no-clean		do not remove created files"
}

ayuda() {
	echo "Uso: $0 [OPCION]..."
	echo " Tutorial en vivo de como usar ORBit (hello world)"
	echo
	echo "  -?, --ayuda 		muestra esta ayuda y sale"
	echo "      --help		idem, pero en yanki"
	echo "      --educado		utiliza usted en lugar de tu"
	echo "      --limpia		solo limpia el directorio"
	echo "      --no-limpia		no limpia el directorio"
}

clean() {
	if test $CLEAN = yes; then
		rm hello* Makefile
	fi
}

enter() {
	if test $QUIET = no; then
		echo "Presion$A enter para continuar..."; read i
	fi
}

comp() {
	echo "Puede$S comprobarlo $TU mismo ahora (en otra ventana/consola)."
}

TU=tu
S=s
A=a
CLEAN=yes
QUIET=no

while test $# -gt 0; do
	case "$1" in
	"--educado"|"--polite")
		TU=usted
		S=""
		A=e
		;;
	"--ayuda"|"-?")
		ayuda
		exit 0;
		;;
	"--help")
		help
		exit 0;
		;;
	"--limpia"|"--clean")
		clean
		exit 0;
		;;
	"--no-limpia"|"--no-clean")
		CLEAN=no
		;;
	"-q")
		QUIET=yes
		;;
	*)
		echo "Opcion desconocida: $1" 1>&2
		ayuda
		exit 1
		;;
	esac
	shift
done

echo "Paso 1. Crear el interfaz IDL"
echo
echo "En este caso el interfaz es muy simple:"
echo
cat << EOF | tee hello.idl
interface hello {
        void puts(in string str);
};
EOF
echo
echo "Ese interfaz se acaba de meter en el fichero hello.idl"
comp
enter
echo
echo "Paso 2. Ejecutar orbit-idl para generar los esqueletos"
echo
echo "Ejecutando... orbit-idl --skeleton-impl hello.idl"
orbit-idl --skeleton-impl hello.idl
echo
echo "Ahora hay 5 ficheros nuevos:"
ls hello*.h hello*.c
comp
enter
echo
echo "Paso 3. Editar los programas principales servidor y cliente"
echo
echo "Voy a crear el cliente (hello-client.c)"
echo "Esto se hace habitualmente a mano, pero copiando de otro parecido"
echo
cat <<EOF >hello-client.c
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
    hello_puts(hello_client, "Hello, World!\n", &ev);
    if(ev._major != CORBA_NO_EXCEPTION) {
        printf("Recibi excepcion %d!\n", ev._major);
        return 1;
    }
    /* liberar recursos */
    CORBA_Object_release((CORBA_Object)hello_client, &ev);
    CORBA_Object_release((CORBA_Object)orb, &ev);
    return 0;
}
EOF
echo "Voy a crear el servidor (hello-server.c)"
echo "Esto se hace a partir de hello-skelimpl.c"
echo
cat hello-skelimpl.c |awk '{ 
	if ($0 == "}" && prev == "{") { 
		print "/* principio parte editada */"; 
		print "   puts(\"Hello, World!\");"; 
	}
	else
		print;
	prev=$0; }' > hello-server.c
cat <<EOF >>hello-server.c
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
EOF
echo
echo "Los añadidos se encuentran al final del fichero, entre comentarios."
comp
enter
echo
echo "Paso 4. Un Makefile"
echo
echo "Voy a crear uno sencillito..."
echo
cat <<EOF |tee Makefile
CFLAGS=`orbit-config --cflags client server`
LDLIBS=`orbit-config --libs client server`
all: hello-server hello-client
hello-server: hello-server.o hello-common.o hello-skels.o
hello-client: hello-client.o hello-common.o hello-stubs.o
EOF
echo
enter
echo
echo "Paso 5. Compilar"
make
echo
enter
echo
echo "Paso 6. Ejecutar"
echo
echo "./hello-server 2> hello-ior"
./hello-server 2> hello-ior &
sleep 2
echo "./hello-client `cat hello-ior`"
./hello-client `cat hello-ior`
sleep 1
killall hello-server
echo
echo "Terminado."
echo "Voy a borrar todo lo que he creado (hello*, Makefile)."
echo "Puede$S abortar pulsando Control-C."
enter
clean


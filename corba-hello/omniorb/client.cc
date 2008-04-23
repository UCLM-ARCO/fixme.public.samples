#include <iostream.h>
#include "hello.hh"

int
main(int argc, char* argv[])
{
  try {
    // iniciar orb
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);

    // Comprobar argumentos
    if (argc != 2) {
      cerr << "[CLIENT] Use: cliente IOR_string" << endl;
      throw 0;
    }

    // Extraer del string argv[1] un objeto
    CORBA::Object_var obj = orb->string_to_object(argv[1]);
    if (CORBA::is_nil(obj)) {
      cerr << "[CLIENT] Referencia a Hora Nil" << endl;
      throw 0;
    }

    hello_var objeto = hello::_narrow(obj);
    objeto->puts("Cliente Omniorb : Hello, world!!");
  }
  catch (const CORBA::Exception &) {
    cerr << "[CLIENT] Excepcion CORBA sin capturar" << endl;
    return 1;
  }
  catch (...) {
    return 1;
  }
    
  return 0;
}

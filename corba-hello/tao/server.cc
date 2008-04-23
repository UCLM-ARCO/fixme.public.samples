#include "helloS.h"
#include <iostream>

using namespace std;

class hello_impl : virtual public POA_HelloModule::hello {
public:
  void puts( const char* str ) throw(::CORBA::SystemException) {
    cout << "Servidor Hello MICO:" << endl;
    cout << str << endl;
  }
};

int
main (int argc, char *argv[])
{
  // Initialize the ORB
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

  // Obtain a reference to the RootPOA and its Manager
  CORBA::Object_var poaobj = orb->resolve_initial_references ("RootPOA");
  PortableServer::POA_var poa = PortableServer::POA::_narrow (poaobj);
  PortableServer::POAManager_var mgr = poa->the_POAManager();

  // Create a Hello World object
  hello_impl *hello1 = new hello_impl;

  //
  PortableServer::ObjectId_var oid = poa->activate_object (hello1);

  // Write reference to file
  CORBA::Object_var ref = poa->id_to_reference (oid.in());
  CORBA::String_var str = orb->object_to_string (ref.in());
  cerr << str.in() << endl;

  // Activate the POA and start serving requests
  mgr->activate ();
  orb->run();

  // Shutdown (never reached)
  poa->destroy (true, true);
  delete hello1;

  return 0;
}

//
// Example code for implementing IDL interfaces in file hello.idl
//

#include <iostream.h>
#include <hello.hh>

//
// Example class implementing IDL interface hello
//
class hello_i: public POA_hello,
                public PortableServer::RefCountServantBase {
private:
  // Make sure all instances are built on the heap by making the
  // destructor non-public
  //virtual ~hello_i();
public:
  // standard constructor
  hello_i();
  virtual ~hello_i();

  // methods corresponding to defined IDL attributes and operations
  void puts(const char* str);
  
};

//
// Example implementational code for IDL interface hello
//
hello_i::hello_i(){
  // add extra constructor code here
}
hello_i::~hello_i(){
  // add extra destructor code here
}
//   Methods corresponding to IDL attributes and operations
void hello_i::puts(const char* str){
  // insert code here and remove the warning
  // #warning "Code missing in function <void hello_i::puts(const char* str)>"
  cout << "[SERVER omniorb] " << str << endl;
}

// End of example implementational code

int main(int argc, char** argv)
{
  try {
    // Initialise the ORB.
    CORBA::ORB_var orb = CORBA::ORB_init(argc, argv, "omniORB3");

    // Obtain a reference to the root POA.
    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

    // We allocate the objects on the heap.  Since these are reference
    // counted objects, they will be deleted by the POA when they are no
    // longer needed.
    hello_i* myhello_i = new hello_i();
    
    // Activate the objects.  This tells the POA that the objects are
    // ready to accept requests.
    PortableServer::ObjectId_var myhello_iid = poa->activate_object(myhello_i);
    
    // Obtain a reference to each object and output the stringified
    // IOR to stdout
    {
      // IDL interface: hello
      CORBA::Object_var ref = myhello_i->_this();
      CORBA::String_var sior(orb->object_to_string(ref));
      cout << "IDL object hello IOR = '" << (char*)sior << "'" << endl;
    }
    
    // Obtain a POAManager, and tell the POA to start accepting
    // requests on its objects.
    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    orb->run();
    orb->destroy();
  }
  catch(CORBA::SystemException&) {
    cerr << "Caught CORBA::SystemException." << endl;
  }
  catch(CORBA::Exception&) {
    cerr << "Caught CORBA::Exception." << endl;
  }
  catch(omniORB::fatalException& fe) {
    cerr << "Caught omniORB::fatalException:" << endl;
    cerr << "  file: " << fe.file() << endl;
    cerr << "  line: " << fe.line() << endl;
    cerr << "  mesg: " << fe.errmsg() << endl;
  }
  catch(...) {
    cerr << "Caught unknown exception." << endl;
  }

  return 0;
}


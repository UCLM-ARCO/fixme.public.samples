#include "hello-cpp-stubs.h"
#include "stdio.h"


#include <unistd.h>


int
main (int argc, char *argv[])
{
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

  /*
   * Bind to Hello World server
   */
  CORBA::Object_var obj = orb->string_to_object (argv[1]);
  SENDA::hello_var hello1 = SENDA::hello::_narrow (obj);

  if (CORBA::is_nil (hello1)) {
    printf ("oops: could not locate HelloWorld server\n");
    exit (1);
  }

  hello1->puts ("Hello World Orbit2-cpp\n");
  return 0;
}

#include "hello.h"

#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef _WINDOWS
#include <direct.h>
#endif

int
main (int argc, char *argv[])
{
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

  /*
   * Bind to Hello World server
   */
  CORBA::Object_var obj = orb->string_to_object (argv[1]);
  HelloModule::hello_var hello1 = HelloModule::hello::_narrow (obj);

  if (CORBA::is_nil (hello1)) {
    printf ("oops: could not locate Hello server\n");
    exit (1);
  }

  hello1->puts ("Cliente MICO: Hello World.\n");
  return 0;
}

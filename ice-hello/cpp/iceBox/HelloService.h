#ifndef HELLO_SERVICE_I_H
#define HELLO_SERVICE_I_H

#include <IceBox/IceBox.h>

#ifndef HELLO_API
#   define HELLO_API ICE_DECLSPEC_EXPORT
#endif

class HELLO_API HelloService : public ::IceBox::Service
{
 public:
  
  HelloService();
  virtual ~HelloService();

  virtual void start(const ::std::string&,
		       const ::Ice::CommunicatorPtr&,
		       const ::Ice::StringSeq&);

  virtual void stop();

 private:
  ::Ice::ObjectAdapterPtr _adapter;
};

#endif

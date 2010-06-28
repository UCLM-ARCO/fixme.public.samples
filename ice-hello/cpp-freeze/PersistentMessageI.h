// -*- mode: C++; coding: utf-8 -*-

#ifndef __PersistentMessageI_h__
#define __PersistentMessageI_h__

#include <Freeze/Freeze.h>
#include <IceUtil/IceUtil.h>

#include <PersistentMessage.h>

namespace UCLM {

  class PersistentMessageI : virtual public PersistentMessage,
			     public IceUtil::AbstractMutexI<IceUtil::Mutex> {
  public:
    PersistentMessageI();
    PersistentMessageI(::std::string);
    virtual void write(const ::std::string&,		       
		       const Ice::Current&);
    virtual ::std::string read(const Ice::Current&);

  };


  class MessageFactory :  virtual public Ice::ObjectFactory {
  public:
    virtual Ice::ObjectPtr create(const ::std::string&);
    virtual void destroy();
  };

  
  class MessageInitializer : virtual public Freeze::ServantInitializer {
  public:
    virtual void initialize(const Ice::ObjectAdapterPtr&,
                            const Ice::Identity&,
                            const std::string&,
                            const Ice::ObjectPtr&);

  };
}

#endif // __PersistentMessageI_h__

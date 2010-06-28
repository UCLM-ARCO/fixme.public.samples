// -*- mode: C++; coding: utf-8 -*-

#include <PersistentMessageI.h>

using namespace std;

UCLM::PersistentMessageI::PersistentMessageI(){
}

UCLM::PersistentMessageI::PersistentMessageI(string msg){

  message = msg + "\n"
    "Awash with unfocused desire, Everett twisted the lobe of his one remaining\n"
    "ear and felt the presence of somebody else behind him, which caused terror\n"
    "to push through his nervous system like a flash flood roaring down the\n"
    "mid-fork of the Feather River before the completion of the Oroville Dam\n"
    "in 1959.\n"
    "		-- Grand Panjandrum's Special Award, 1984 Bulwer-Lytton\n"
    "		   bad fiction contest.\n"
    "\n";
}

void
UCLM::PersistentMessageI::write(const string& msg,
                      const Ice::Current& current) {
  
  cout << "Event: ++ write" << endl;
  message = msg;
}

::std::string
UCLM::PersistentMessageI::read(const Ice::Current& current) {

  cout << "Event: -- read" << endl;
  return message;
}


Ice::ObjectPtr 
UCLM::MessageFactory::create(const ::std::string& type){
  cout << "MessageFactory::create(" << type << ")" << endl;
  if (type == "::UCLM::PersistentMessage") {
    return new PersistentMessageI();
  }
  else {
    assert(false);
    return 0;
  }
}

void 
UCLM::MessageFactory::destroy(){
}
  

void 
UCLM::MessageInitializer::initialize(const Ice::ObjectAdapterPtr&,
				     const Ice::Identity&,
				     const std::string&,
				     const Ice::ObjectPtr&){
}

 

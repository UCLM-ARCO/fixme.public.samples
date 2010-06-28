// -*- mode: C++; coding: utf-8 -*-

#include <MessageI.h>

using namespace std;

UCLM::MessageI::MessageI(string msg){

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
UCLM::MessageI::write(const string& msg,
                      const Ice::Current& current) {
  
  cout << "Event: ++ write" << endl;
  message = msg;
}

::std::string
UCLM::MessageI::read(const Ice::Current& current) {

  cout << "Event: -- read" << endl;
  return message;
}

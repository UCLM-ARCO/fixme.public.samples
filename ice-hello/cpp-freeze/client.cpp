// -*- mode: C++; coding: utf-8 -*-

#include <cstring>

#include <Ice/Ice.h>
#include <Message.h>

using namespace std;

class MessageClient : virtual public Ice::Application {
public:  
  virtual int run(int argc, char* argv[]){

    // There need to be a proxy in argv
    if (argc < 3) {
      usage(argv[0]);
      return -1;
    }  

    // Create the casted proxy for remote object
    Ice::ObjectPrx base = communicator()->stringToProxy(argv[1]);
    if (!base) {
      cerr << "The proxy especified is invalid!" << endl;
      return -1;
    }
    
    UCLM::MessagePrx prx = UCLM::MessagePrx::checkedCast(base);
    
    // Parse command
    if (strcmp("read", argv[2]) == 0){
      cout << "COMMAND: read" << endl;
      cout << "VALUE: '" << prx->read() << "'" << endl;
    }

    else if (strcmp("write", argv[2]) == 0){
      if (argc != 4){
	usage(argv[0]);
	return -1;
      }

      else {
	cout << "COMMAND: write" << endl << "MESSAGE: '" << argv[3] << "'" << endl;
	prx->write(argv[3]);
      }
    }
    
    else {
      usage(argv[0]);
      return -1;      
    }

    return 0;
  }

private:
 
  void usage(char* pname){
    cout << "USAGE: " << pname << " <proxy> <read | write 'msg'>" << endl;
  }

};


int 
main(int argc, char* argv[]){

  MessageClient clt;
  return clt.main(argc, argv);
}


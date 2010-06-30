// -*- mode: C++; coding: utf-8 -*-

// Messase service.

#include <MessageI.h>
#include <Ice/Ice.h>

using namespace std;
using namespace UCLM;

#define DEF_MAX_SERVS 100000

class MessageServer : virtual public Ice::Application {
public:

  virtual int run(int argc, char* argv[]){

    // MAX_SERVS passed throught args or fixed
    int MAX_SERVS;
    if (argc > 1){
      MAX_SERVS = atoi(argv[1]);
    }
    else {
      MAX_SERVS = DEF_MAX_SERVS;
    }

    _ic = communicator();

    // Create the object adapter
    _adapter = _ic->createObjectAdapterWithEndpoints("MServer", "tcp -h 127.0.0.1 -p 11111");
    _adapter->activate();

    // Create MAX_SERVS servants
    UCLM::MessagePtr serv;
    Ice::ObjectPrx prx;

    cout << "Creating posts from 0 to " << MAX_SERVS << " ...";
    cout.flush();

    for (int i=0; i<MAX_SERVS; i++) {
      ostringstream sid;
      sid << "Post" << i;
      serv = new UCLM::MessageI("Message from " + sid.str());
      prx = _adapter->add(serv, _ic->stringToIdentity(sid.str()));
    }

    cout << " done." << endl;
    cout << "Proxies at 'PostX -t:tcp -h 127.0.0.1 -p 11111' where X is post number." << endl;
    cout << "Waiting events..." << endl;

    shutdownOnInterrupt();
    _ic->waitForShutdown();
    return 0;
  }


private:

  Ice::ObjectAdapterPtr _adapter;
  Ice::CommunicatorPtr _ic;

};


int
main(int argc, char* argv[]){

  MessageServer srv;
  return srv.main(argc, argv);
}

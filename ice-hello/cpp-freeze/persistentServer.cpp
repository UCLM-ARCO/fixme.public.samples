// -*- mode: C++; coding: utf-8 -*-

// Messase service with persistency

#include <PersistentMessageI.h>
#include <Freeze/Freeze.h>

using namespace std;
using namespace UCLM;

#define DEF_MAX_SERVS 100000

class PersistentMessageServer : virtual public Ice::Application {
public:
  PersistentMessageServer(const string& dbName) :
    _dbName(dbName) {
  }

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

    // The object factories
    Ice::ObjectFactoryPtr factory = new MessageFactory;
    _ic->addObjectFactory(factory, PersistentMessage::ice_staticId());

    // Create the object adapter
    _adapter =
			_ic->createObjectAdapterWithEndpoints("MServer",
																						"tcp -h 127.0.0.1 -p 11112");
    _adapter->activate();

    // Create the Freeze evictor
    Freeze::ServantInitializerPtr init = new MessageInitializer;
    _evictor = Freeze::createBackgroundSaveEvictor(_adapter, _dbName,
																									 "dbfile", init);
    _adapter->addServantLocator(_evictor, "");

    // Create MAX_SERVS servants
    UCLM::PersistentMessagePtr serv;
    Ice::ObjectPrx prx;

    cout << "Creating posts from 0 to " << MAX_SERVS << " ...";
    cout.flush();

    for (int i=0; i<MAX_SERVS; i++){
      ostringstream sid;
      sid << "Post" << i;
      Ice::Identity id = _ic->stringToIdentity(sid.str());

      if (!_evictor->hasObject(id)){
	serv = new UCLM::PersistentMessageI("Message from " + sid.str());
	prx = _evictor->add(serv, id);
      }
    }

    cout << " done." << endl;
    cout << "Proxies at 'PostX -t:tcp -h 127.0.0.1 -p 11112' where X is post number." << endl;
    cout << "Waiting events..." << endl;

    shutdownOnInterrupt();
    _ic->waitForShutdown();

    return 0;
  }

private:

  string _dbName;
  Ice::ObjectAdapterPtr _adapter;
  Freeze::EvictorPtr _evictor;
  Ice::CommunicatorPtr _ic;
};


int
main(int argc, char* argv[]){

  PersistentMessageServer srv("storage");
  return srv.main(argc, argv);
}

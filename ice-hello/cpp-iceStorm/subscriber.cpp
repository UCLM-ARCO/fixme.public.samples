#include <Ice/Application.h>
#include <IceStorm/IceStorm.h>
#include <IceUtil/UUID.h>

#include <helloI.h>

using namespace std;
using namespace UCLM;

class Subscriber : public Ice::Application
{
public:
  virtual int run(int, char*[]);
};

int
main(int argc, char* argv[])
{
  Subscriber app;
  return app.main(argc, argv, "config");
}

int
Subscriber::run(int argc, char* argv[])
{
  Ice::PropertiesPtr properties = communicator()->getProperties();
  
  const string prop_key = "IceStorm.TopicManager.Proxy";
  string endpoint = properties->getProperty(prop_key);
  if(endpoint.empty()){
    cerr << appName() << ": property `" << prop_key 
         << "' not set" << endl;
    return EXIT_FAILURE;
  }
  
  cout << "Using IceStorm in '" << endpoint << "' " << endl;

  Ice::ObjectPrx base = communicator()->stringToProxy(endpoint);
  IceStorm::TopicManagerPrx topic_mgr = IceStorm::TopicManagerPrx::checkedCast(base);
  if(!topic_mgr){
    cerr << appName() << ": invalid proxy" << endl;
    return EXIT_FAILURE;
  }


  // Create the servant to receive the events.
  Ice::ObjectAdapterPtr adapter = communicator()->createObjectAdapter("Hello.Subscriber");
  Ice::ObjectPtr helloObj = new HelloI;


  // Add a Servant for the Ice Object.
  Ice::ObjectPrx obj = adapter->addWithUUID(helloObj);
  IceStorm::TopicPrx topic;

  try{
    topic = topic_mgr->retrieve("HelloTopic");
    IceStorm::QoS qos;   
    topic->subscribe(qos, obj);
    
  }
  catch(const IceStorm::NoSuchTopic& e){
    cerr << appName() << ": " << e << " name: " << e.name << endl;
    return EXIT_FAILURE;
  }
    
  cout << "Waiting events..." << endl;
  
  adapter->activate();
  shutdownOnInterrupt();
  communicator()->waitForShutdown();

  topic->unsubscribe(obj); 
  
  return EXIT_SUCCESS; 
  
}

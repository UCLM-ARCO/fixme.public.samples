#include <Ice/Application.h>
#include <IceStorm/IceStorm.h>

#include <hello.h>

using namespace std;
using namespace UCLM;

class Publisher : public Ice::Application
{
public:
  virtual int run(int, char*[]);
};

int 
main(int argc, char* argv[])
{
  Publisher app;
  return app.main(argc, argv, "config");
}

int
Publisher::run(int argc, char*[])
{
  Ice::PropertiesPtr properties = communicator()->getProperties();

  const string prop_key = "IceStorm.TopicManager.Proxy";
  string endpoint = properties->getProperty(prop_key);
  if(endpoint.empty()){
    cerr << appName() << ": property `" << prop_key 
         << "' not set" << endl;
    return EXIT_FAILURE;
  }

  Ice::ObjectPrx base = communicator()->stringToProxy(endpoint);
  IceStorm::TopicManagerPrx topic_mgr = IceStorm::TopicManagerPrx::checkedCast(base);
  if(!topic_mgr){
    cerr << appName() << ": invalid proxy" << endl;
    return EXIT_FAILURE;
  }


  IceStorm::TopicPrx topic;
  try{
    topic = topic_mgr->retrieve("HelloTopic");
  } 
  catch (const IceStorm::NoSuchTopic& e){
    cerr << appName() << ": no sucho topic found, created" << endl;
    topic = topic_mgr->create("HelloTopic");
  }

  assert(topic);

  //
  // Get the topic's publisher object.
  Ice::ObjectPrx prx = topic->getPublisher();  

  HelloPrx hello = HelloPrx::uncheckedCast(prx);

  cout << "publishing 10 'Hello World!'  events" << endl;
  for(int i = 0; i < 10; ++i){
    hello->puts("Hello World!");
  }

  return EXIT_SUCCESS;
}

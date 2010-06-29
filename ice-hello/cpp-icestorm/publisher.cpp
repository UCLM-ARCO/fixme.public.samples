#include <Ice/Application.h>
#include <IceStorm/IceStorm.h>

#include <hello.h>

using namespace std;
using namespace Ice;
using namespace UCLM;

class Publisher : public Application {
public:
  virtual int run(int argc, char*[]) {
	  PropertiesPtr properties = communicator()->getProperties();

	  const string prop_key = "IceStorm.TopicManager.Proxy";
	  string endpoint = properties->getProperty(prop_key);

	  if (endpoint.empty()) {
		  cerr << appName() << ": property `" << prop_key
			   << "' not set" << endl;
		  return EXIT_FAILURE;
	  }

	  ObjectPrx base = communicator()->stringToProxy(endpoint);
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

	  // Get the topic's publisher object.
	  ObjectPrx prx = topic->getPublisher();

	  HelloPrx hello = HelloPrx::uncheckedCast(prx);

	  cout << "publishing 10 'Hello World!'  events" << endl;
	  for (int i = 0; i < 10; ++i) {
		  hello->puts("Hello World!");
	  }

	  return EXIT_SUCCESS;
  }
};

int main(int argc, char* argv[]) {
	Publisher app;
	return app.main(argc, argv);
}

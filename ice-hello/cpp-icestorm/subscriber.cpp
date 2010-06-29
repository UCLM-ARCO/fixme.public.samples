#include <Ice/Application.h>
#include <IceStorm/IceStorm.h>
#include <IceUtil/UUID.h>
#include <hello.h>

using namespace std;
using namespace Ice;
using namespace IceStorm;
using namespace UCLM;


class HelloI : public Hello {
	void puts(const string& s, const Current& current) {
		cout << "Event received: " << s << endl;
	}
};

class Subscriber : public Application {
public:
	virtual int run(int argc, char* argv[]) {

		PropertiesPtr properties = communicator()->getProperties();

		const string prop_key = "IceStorm.TopicManager.Proxy";
		string endpoint = properties->getProperty(prop_key);

		if (endpoint.empty()) {
			cerr << appName() << ": property `" << prop_key << "' not set" << endl;
			return EXIT_FAILURE;
		}

		cout << "Using IceStorm in '" << endpoint << "' " << endl;

		ObjectPrx base = communicator()->stringToProxy(endpoint);
		TopicManagerPrx topic_mgr = TopicManagerPrx::checkedCast(base);
		if (!topic_mgr) {
			cerr << appName() << ": invalid proxy" << endl;
			return EXIT_FAILURE;
		}

		// Create the servant to receive the events.
		ObjectAdapterPtr adapter = communicator()->createObjectAdapter("Hello.Subscriber");
		ObjectPtr helloObj = new HelloI;

		// Add a Servant for the Ice Object.
		ObjectPrx obj = adapter->addWithUUID(helloObj);
		TopicPrx topic;

		try{
			topic = topic_mgr->retrieve("HelloTopic");
			QoS qos;
			topic->subscribeAndGetPublisher(qos, obj);
		}
		catch(const NoSuchTopic& e){
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
};

int main(int argc, char* argv[]) {
	Subscriber app;
	return app.main(argc, argv);
}

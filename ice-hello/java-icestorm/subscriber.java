//
// subscriber.java
//
//
//


import UCLM.*;
import Ice.Application;

//
// class subscriber
//
public class subscriber extends Ice.Application {

		HelloI hello;

		//
		// run
		//
		public int run (String[] args) {
			// obtain a proxy for the Topic Manager
			Ice.Properties properties = communicator().getProperties();
			String strprx;

			try {
				strprx = properties.getProperty("IceStormAdmin.TopicManager.Default");
			}
			catch (Exception ep){
				System.err.println("No IceStormAdmin property set");
				return 1;
			}

			Ice.ObjectPrx base = communicator().stringToProxy(strprx);
			IceStorm.TopicManagerPrx topicManager =
				IceStorm.TopicManagerPrxHelper.checkedCast(base);
			Ice.ObjectAdapter adapter =
				communicator().createObjectAdapter("Hello.Subscriber");

			// instantiate the iListener servant
			hello = new HelloI();
			Ice.ObjectPrx proxy = adapter.addWithUUID(hello);
			IceStorm.TopicPrx topic = null;

			// subscribe to the asdf topic
			try {
				topic = topicManager.retrieve("HelloTopic");
				topic.subscribeAndGetPublisher(null, proxy);
			}
			catch (IceStorm.NoSuchTopic ex) {
				// Error! No topic found!
				System.err.println(ex);
				return 1;
			}
			catch (Exception e) {
				System.err.println(e);
				return 1;
			}

			// and activate it
			adapter.activate();
			// process report messages until shutdown
			communicator().waitForShutdown();
			// sunsubscribe from the asdf topic
			topic.unsubscribe(proxy);

			return 0;
		} // method run

		//
		// main
		//
		public static void main (String[] args) {
			subscriber app = new subscriber();
			app.main("subscriber", args);
		} // method main

} // class subscriber

//
// class HelloI
//
class HelloI extends UCLM._HelloDisp {

	public void puts(String cad, Ice.Current __current) {
		System.out.println(cad);

	} // method puts

} // class HelloI


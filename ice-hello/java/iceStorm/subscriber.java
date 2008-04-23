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
			String prop_key = "IceStorm.TopicManager.Proxy";
			String endpoint;
			
			try {
				endpoint = properties.getProperty(prop_key);
			}
			catch (Exception ep){
				System.err.println(ep+" property "+prop_key+" not set");
				return 1;
			}
			
			Ice.ObjectPrx obj = communicator().stringToProxy(endpoint);
			IceStorm.TopicManagerPrx topicManager =
				IceStorm.TopicManagerPrxHelper.checkedCast(obj);
			Ice.ObjectAdapter adapter =
				communicator().createObjectAdapter("HelloAdapter");

			// instantiate the iListener servant 
			hello = new HelloI();
			Ice.ObjectPrx proxy = adapter.addWithUUID(hello);
			IceStorm.TopicPrx topic = null;

			// subscribe to the asdf topic
			try {
   				topic = topicManager.retrieve("hello");
				// quality of service
				java.util.Map qos = null;
				topic.subscribe(qos, proxy);
			}
			catch (IceStorm.NoSuchTopic ex) {
				// Error! No topic found!
				System.err.println(ex);
				try{
					// create the asdf topic 
					topic = topicManager.create("hello");
					// quality of service
					java.util.Map qos = null;
					topic.subscribe(qos, proxy);
				}
				catch (Exception e) {
					System.err.println(e);
				}
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
			app.main("subscriber", args, "config");
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


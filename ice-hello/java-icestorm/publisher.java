//
// Publisher.java
//
//
//

import UCLM.*;
import Ice.Application;

//
// publisher
//
public class publisher extends Ice.Application {

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
			System.err.println("No IceStormAdmin property not set");
			return 1;
		}

		Ice.ObjectPrx base = communicator().stringToProxy(strprx);
		IceStorm.TopicManagerPrx topicManager =
			IceStorm.TopicManagerPrxHelper.checkedCast(base);


		IceStorm.TopicPrx topic = null;
		// obtain a proxy asdf topic
		try {
			topic = topicManager.retrieve("HelloTopic");
		}
		catch (IceStorm.NoSuchTopic ex) {
			System.out.println(ex);
			return 1;
		}

		// obtain a proxy for the publisher object
		Ice.ObjectPrx pub = topic.getPublisher();
		if (!pub.ice_isDatagram())
			pub = pub.ice_oneway();
		HelloPrx helloPrx = HelloPrxHelper.uncheckedCast(pub);

		// Create a null Property Server
		Ice.ObjectPrx obPrx = communicator().stringToProxy("");
		HelloPrx psPrx = HelloPrxHelper.checkedCast(obPrx);

		// publish
		helloPrx.puts("hola");

		return 0;
	} // method run

	//
	// main
	//
	static public void main (String[] args) {
		publisher app = new publisher();
		app.main("publisher", args);
	} // method main
} // class publisher

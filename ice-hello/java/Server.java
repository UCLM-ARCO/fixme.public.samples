public class Server extends Ice.Application {
  public int run(String[] args) {
	shutdownOnInterrupt();
	Ice.ObjectAdapter oa = communicator().createObjectAdapter("Server");
	Ice.ObjectPrx prx = oa.add(new HelloI(), Ice.Util.stringToIdentity("Hello"));
	oa.activate();
	System.out.println(communicator().proxyToString(prx));
	communicator().waitForShutdown();
  	return 0;
  }

  static public void main(String[] args) {
 	Server app = new Server();
  	app.main("Server", args);
  }
}


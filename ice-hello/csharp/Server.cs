using UCLM; using Ice;

public class HelloI: HelloDisp_ {
	public override void puts(string str, Current current) {
		System.Console.Out.WriteLine(str);
	}
}

public class Server: Application {
	public override int run(string[] args) {
		shutdownOnInterrupt();
		ObjectAdapter oa = communicator().createObjectAdapter("Servidor");
		ObjectPrx prx = oa.add(new HelloI(),Util.stringToIdentity("Hello"));
		oa.activate();
		System.Console.WriteLine(communicator().proxyToString(prx));
		communicator().waitForShutdown();
		return 0;
	}

	public static void Main(string[] args) {
		Application app = new Server();
		System.Environment.Exit(app.main(args));
	}
}


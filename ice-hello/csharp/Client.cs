using UCLM; using Ice;

public class Client: Application {
	public override int run(string[] args) {
		ObjectPrx prx = communicator().stringToProxy(args[0]);
		HelloPrx hello = HelloPrxHelper.checkedCast(prx);
		hello.puts("Hello, World!");
		return 0;
	}

	public static void Main(string[] args) {
		Application app = new Client();
		System.Environment.Exit(app.main(args));
	}
}


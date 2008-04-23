import HelloModule.*;
import HelloModule.*;

class helloClient
{
    public static void main(String args[]) {
        try {
            org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init(args, null);
	    org.omg.CORBA.Object obj = orb.string_to_object(args[0]);
	    hello clnt = helloHelper.narrow(obj);
	    clnt.puts("Java Client says Hello");
        } catch (Exception e) {
            System.err.println("ERROR: " + e);
            e.printStackTrace(System.out);
        }
    }

}

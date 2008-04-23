import HelloModule.*;

class helloServer extends helloPOA 
{
    public void puts (String str) {
	System.out.println(str);
    }
    public static void main(String args[]) {
        try {
            org.omg.CORBA.ORB orb = org.omg.CORBA.ORB.init(args, null);
	    helloServer hello = new helloServer();

	    org.omg.PortableServer.POA poa = (org.omg.PortableServer.POA)
		orb.resolve_initial_references("RootPOA");
	    poa.the_POAManager().activate();
	    poa.activate_object(hello);
	    System.out.println(orb.object_to_string(hello._this_object()));
	    orb.run();
 
        } catch (Exception e) {
            System.err.println("ERROR: " + e);
            e.printStackTrace(System.out);
        }
    }

}

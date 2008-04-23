//
// El servidor Hello World
//
//import HelloApp.*;					// Contiene los Stubs
import org.omg.CosNaming.*;				// El servicio de nombres
import org.omg.CosNaming.NamingContextPackage.*;	// Excepciones
import org.omg.CORBA.*;					// Pues eso...

// Para usar el POA
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;

import java.util.Properties;

class helloServer extends helloPOA {

	public void puts(String str) {
		System.out.println(str);
	}
	
	public static void main(String args[]) {
		try {
			// Creamos e inicializamos un ORB
			//
			ORB orb = ORB.init(args, null);
			// Obtenemos la referencia al rootpoa
			//
			POA rootpoa = POAHelper.narrow(orb.resolve_initial_references("RootPOA"));

			// Activamos el POA
			// 
			rootpoa.the_POAManager().activate();
			
			// Creamos el servant
			//
			helloServer hello = new helloServer();
			rootpoa.activate_object(hello);

			// Creamos un cabo y su sirviente delegado
			//
			//helloPOA poa_ = new helloPOA(helloImpl, rootpoa);
			//hello href = poa_._this(orb);

			// Obtenemos la raiz del servicio de nombres
			//
			org.omg.CORBA.Object objRef = orb.string_to_object(args[0]);
			NamingContext ncRef = NamingContextHelper.narrow(objRef);

			// Registramos el servant
			//
			NameComponent nc = new NameComponent("Hello", "");
			NameComponent path[] = {nc};
			ncRef.rebind(path, hello._this_object());

			// Esperamos peticiones de clientes
			//
			System.out.println("Servidor esperando...");
			
			orb.run();
		} catch (Exception e) {
			
			System.err.println("Error: "+e);
			e.printStackTrace(System.out);
		}

		System.out.println("Terminando servidor...");
	}

}


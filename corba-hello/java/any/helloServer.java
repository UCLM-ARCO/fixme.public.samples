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
import HelloModule.*;

class helloServer extends HelloModule.helloPOA {

	public void puts(Any str) {
		System.out.println("Java hello server: " + str.extract_string());
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

			// Esperamos peticiones de clientes
			//
			System.out.println(orb.object_to_string(hello._this_object()));
			
			orb.run();
		} catch (Exception e) {
			
			System.err.println("Error: "+e);
			e.printStackTrace(System.out);
		}

		System.out.println("Terminando servidor...");
	}

}


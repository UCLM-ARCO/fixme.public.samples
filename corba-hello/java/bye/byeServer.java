//
// El servidor Bye
//
import org.omg.CosNaming.*;				// El servicio de nombres
import org.omg.CosNaming.NamingContextPackage.*;	// Excepciones
import org.omg.CORBA.*;					// Pues eso...

// Para usar el POA
import org.omg.PortableServer.*;
import org.omg.PortableServer.POA;

import java.util.Properties;
import ByeModule.*;

class byeServer extends ByeModule.byePOA {

	static Any to_say;
	
	public Any gets() {
		
		System.out.println("Java server say bye!");
		return to_say;
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
			byeServer bye = new byeServer();
			rootpoa.activate_object(bye);

			// Creamos el Any que tenemos q devolver
			//
			to_say=orb.create_any();
			to_say.insert_string("bye!");
			
			// Esperamos peticiones de clientes
			//
			System.out.println(orb.object_to_string(bye._this_object()));
			
			orb.run();
		} catch (Exception e) {
			
			System.err.println("Error: "+e);
			e.printStackTrace(System.out);
		}

		System.out.println("Terminando servidor...");
	}

}


//
// Ejemplo de CORBA en java con CosNaming
//

import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import ByeModule.*;

// La clase del cliente
// 
public class byeClient {

	// Metodo principal del cliente
	//
	public static void main (String args[]){

		// Todas las operaciones CORBA las englobamos en un try-catch
		//
		try {
			// Creamos e inicializamos el ORB
			//
			ORB orb = ORB.init(args, null);

			bye byeImpl = byeHelper.narrow(orb.string_to_object(args[0]));

			// Llamamos al sirviente
			// 
			Any bye_any=orb.create_any();
			System.out.print("Java server says: ");
			
			bye_any=byeImpl.gets();
			System.out.println(bye_any.extract_string());

		} catch (Exception e) {
			
			// Si ocurrio algun error... lo decimos
			//
			System.out.println("Error: "+e);
			e.printStackTrace(System.out);
		}
	}
}

	

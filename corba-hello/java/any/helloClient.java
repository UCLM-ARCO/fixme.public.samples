//
// Ejemplo de CORBA en java con CosNaming
//

//import HelloApp.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;
import HelloModule.*;

// La clase del cliente
// 
public class helloClient {

	// Metodo principal del cliente
	//
	public static void main (String args[]){

		// Todas las operaciones CORBA las englobamos en un try-catch
		//
		try {
			// Creamos e inicializamos el ORB
			//
			ORB orb = ORB.init(args, null);

			hello helloImpl = helloHelper.narrow(orb.string_to_object(args[0]));

			// Llamamos al sirviente
			// 
			Any hello_any=orb.create_any();
			hello_any.insert_string("Java Client says Hello");
			
			helloImpl.puts(hello_any);
			//helloImpl.shutdown();

		} catch (Exception e) {
			
			// Si ocurrio algun error... lo decimos
			//
			System.out.println("Error: "+e);
			e.printStackTrace(System.out);
		}
	}
}

	

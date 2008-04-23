//
// Ejemplo de CORBA en java con CosNaming
//

//import HelloApp.*;
import org.omg.CosNaming.*;
import org.omg.CosNaming.NamingContextPackage.*;
import org.omg.CORBA.*;

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

			// Obtenemos el contexto del NamingContext raiz
			//
			//org.omg.CORBA.Object objRef = orb.resolve_initial_references("NameService");
			org.omg.CORBA.Object objRef = orb.string_to_object(args[0]);
			NamingContext ncRef = NamingContextHelper.narrow(objRef);

			// Resolvemos la referencia al objeto preguntando al NamingContext
			//
			NameComponent nc = new NameComponent("Hello", "");
			NameComponent path[] = {nc};
			hello helloImpl = helloHelper.narrow(ncRef.resolve(path));

			// Llamamos al sirviente
			// 
			helloImpl.puts("Hello World!");
			//helloImpl.shutdown();

		} catch (Exception e) {
			
			// Si ocurrio algun error... lo decimos
			//
			System.out.println("Error: "+e);
			e.printStackTrace(System.out);
		}
	}
}

	

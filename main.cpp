#include <iostream>
#include <string.h>

using namespace std;

struct Nodo{ //Estructura que representa cada posición de la lista, posee la información del estudiante y un nodo sucesor que apunta al siguiente nodo del lista
	char nombre[50];
	char sexo;
	int edad;
	Nodo *sucesor;	
};

void insertar(Nodo **cabecera); //función para insertar un nuevo nodo (estudiante) a la lista
void imprimirLista(Nodo **cabecera, char titulo[50]); //función para imprimir la lista y el titulo de la misma
void ordenarListaBurbuja(Nodo **cabecera); //funcion que implementa el metodo de ordenación burbuja, para ordenar la lista por el sexo de los estudiantes

int main(int argc, char** argv) {
	Nodo *cabecera = NULL;
	
	insertar(&cabecera);

	return 0;
}

void insertar(Nodo **cabecera){ //función para insertar un nuevo nodo (estudiante) a la lista
	Nodo *nuevo, *antes; //declaramos dos punteros tipo Nodo, nuevo guardará la información del nuevo estudiante y antes lo usaremos para modificar el nodo anterior de la lista
	
	char resp, titulo[50], sexo; 
	int cantidadPersonas = 1;
	
	do{
		nuevo = new Nodo; //pedimos memoria para el nuevo nodo
		if(nuevo){ //si tenemos memoria reservada procedemos a registrar al estudiante
			cout << endl << "Registro del Estudiante numero " << cantidadPersonas;    
			cout << endl << "Ingrese el nombre: "; //pide la información del estudiante y la almacena
			cin >> nuevo->nombre;
			do{ //valida que el sexo sea solo femenino (f o F) o masculino (m o M)
				cout << "Ingrese el sexo (F/M): ";
				cin >> sexo;
			}while(sexo != 'f' && sexo != 'F' && sexo != 'm' && sexo != 'M');
			nuevo->sexo = sexo;	
			cout << "Ingrese la edad: ";
			cin >> nuevo->edad;
			
			if(*cabecera == NULL){ //lista vacia, insertamos el primer valor
				nuevo->sucesor = NULL; //todo nodo nuevo que ingresemos no tiene sucesor aún, por lo que lo asignamos como NULL
				*cabecera = nuevo; // por ser el primer registro en la lista, lo asignamos a la cabecera de la misma
			}else{ //lista no vacia, insertamos un nuevo valor
				nuevo->sucesor = NULL; //todo nodo nuevo que ingresemos no tiene sucesor aún, por lo que lo asignamos como NULL
				antes->sucesor = nuevo; //al nodo anterior le asignamos sucesor, el nuevo nodo que acabamos de crear
			}
			antes = nuevo; //actualizamos el proximo nodo anterior como el nodo nuevo que acabamos de ingresar, es decir, el nodo nuevo actual será en el nodo anterior para la proxima iteracion
		}else{ //Si no se nos asigna memoria, imprimeremos un mensaje de fin de memoria
			cout << "No hay memoria";
		}
		cantidadPersonas++; //aumentamos la cantidad de estudiantes registrados
		cout << endl << "¿Desea registrar un nuevo Estudiante? Y/N ";
		cin >> resp;
	}while(resp == 'y' || resp == 'Y'); //el ciclo permite el registro de estudiantes hasta que el usuario lo desee
	
	strcpy(titulo, "Listado ingresado de Estudiantes");
	imprimirLista(cabecera, titulo); //imprime la lista que se acaba de ingresar
	
	ordenarListaBurbuja(cabecera); // llama al metodo que ordenará lista por sexo
	
	strcpy(titulo, "Listado de Estudiantes ordenada por Sexo");
	imprimirLista(cabecera, titulo); //imprime la lista ordenada
}

void imprimirLista(Nodo **cabecera, char titulo[50]){ //función para imprimir la lista y el titulo de la misma
	/*
	Como no podemos recorrer a lista enlazada como un vector normal por posiciones v[i], es necesario comenzar a recorrerla por el nodo cabecera hasta que el nodo actual no posea un sucesor
	*/
	Nodo *actual = *cabecera; //inicializamos el nodo actual con el nodo cabecera o primera posición de la lista
	char sexo[50]; //variable que nos permite imprimir de forma más clara el sexo del estudiante
	int cantidad = 0; //cantidad de estudiantes en la lista, inicializada en 0
	
	cout << endl << endl << endl << " ** "<< titulo <<" ** " << endl << endl; //imprime el titulo pasado por parametros
	while(actual->sucesor != NULL){ //recorrerá la lista hasta que el nodo actual no posea sucesor (ultima posicion)
		cantidad++; //aumentamos la cantidad de estudiantes para mostrar a partir de 1, bien podria haberse inicializado en 1 y aumentar al final del ciclo
		
		if(actual->sexo == 'f' || actual->sexo == 'F'){ //Asigna cadena con la palabra completa que define el sexo del estudiante a la variable sexo
			strcpy(sexo,"Femenino");	
		}else{
			strcpy(sexo,"Masculino");
		}
		
		cout << cantidad << ".- " << actual->nombre << " -> Edad:" << actual->edad << ", Sexo: " << sexo << endl; //imprime la información del estudiante actual
		actual = actual->sucesor; //Actualizamos el proximo nodo actual, con el sucesor del actual, es decir, avanzamos una posicion en la lista enlazada
		if(actual->sucesor == NULL){ //si llegamos al ultimo registro, como no tiene sucesor y no cumple la condicion del ciclo, imprimos su información 
			cantidad++; //aumenta la cantidad de estudiantes (esta sería la ultima posicion)
			if(actual->sexo == 'f' || actual->sexo == 'F'){ //Asigna cadena con la palabra completa que define el sexo del estudiante a la variable sexo
				strcpy(sexo,"Femenino");	
			}else{
				strcpy(sexo,"Masculino");
			}
			cout << cantidad << ".- " << actual->nombre << " -> Edad:" << actual->edad << ", Sexo: " << sexo << endl; //imprime información de la ultima posicion de la lista
		}
	}
}

void ordenarListaBurbuja(Nodo **cabecera){ //funcion que implementa el metodo de ordenación burbuja, para ordenar la lista por el sexo de los estudiantes
	Nodo *actual , *sucesor; //declaramos dos punteros tipo Nodo, actual guardará la información del nodo actual de la lista y sucesor la del siguiente, esto para hacer la comparacion
	char sexo, nombre[50]; //variables que sirven de auxiliares para hacer el intercambio de la lista
	int edad;  //variables que sirven de auxiliares para hacer el intercambio de la lista
	
	actual = *cabecera; //inicializamos el primer nodo actual como la cabecera de la lista
	
	while(actual->sucesor != NULL){ //recorrerá la lista hasta que el nodo actual no posea sucesor (ultima posicion)
	  sucesor = actual->sucesor; //guardamos en la variable sucesor, el sucesor del nodo actual para porder hacer la comparación de valores
	  while(sucesor != NULL){ //Comparará el valor actual con todos los sucesores posibles, hasta la ultima posición
	       if(actual->sexo > sucesor->sexo){ //si el valor del sexo actual es mayor al siguiente, realizamos el intercambio de valores (alfabeticamente M es mayor a F)
	            sexo = sucesor->sexo; //almacenamos en las variables auxiliares definidas en el metodo la informacion del estudiante del nodo sucesor
	            strcpy(nombre, sucesor->nombre);
	            edad = sucesor->edad;
	            
	            sucesor->sexo = actual->sexo; //almacenamos en el nodo sucesor la informacion del estudiante en la posicion actual
	            strcpy(sucesor->nombre, actual->nombre);
	            sucesor->edad = actual->edad;
	            
	            actual->sexo = sexo; //almacenamos en el nodo actual la informacion del estudiante del nodo sucesor inicial que guardamos en las variables auxiliares
				strcpy(actual->nombre,nombre); 
				actual->edad = edad;       
	       }
	       sucesor = sucesor->sucesor; //Actualizamos el nodo sucesor, con el proximo sucesor para comparar de nuevo con el nodo actual
	  }    
	  actual = actual->sucesor; //actualizamos el nuevo nodo actual, avanzamos una posicion en la lista
	  sucesor = actual->sucesor; //actualizamos el nuevo nodo sucesor, avanzamos una posicion en la lista	   
	}
}

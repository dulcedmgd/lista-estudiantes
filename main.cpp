#include <iostream>
#include <string.h>

using namespace std;

struct Nodo{
	char nombre[50];
	char sexo;
	int edad;
	Nodo *sucesor;	
};

void insertar(Nodo **cabecera);
void imprimirLista(Nodo **cabecera, char titulo[50]);
void ordenarListaBurbuja(Nodo **cabecera);

int main(int argc, char** argv) {
	Nodo *cabecera = NULL;
	
	insertar(&cabecera);

	return 0;
}

void insertar(Nodo **cabecera){
	Nodo *nuevo, *antes;
	
	char resp, titulo[50], sexo;
	int cantidadPersonas = 1;
	
	do{
		nuevo = new Nodo;
		if(nuevo){			
			cout << endl << "Registro del Estudiante numero " << cantidadPersonas;
			cout << endl << "Ingrese el nombre: ";
			cin >> nuevo->nombre;
			do{
				cout << "Ingrese el sexo (F/M): ";
				cin >> sexo;
			}while(sexo != 'f' && sexo != 'F' && sexo != 'm' && sexo != 'M');
			nuevo->sexo = sexo;	
			cout << "Ingrese la edad: ";
			cin >> nuevo->edad;
			
			if(*cabecera == NULL){ //lista vacia, insertamos el primer valor
				nuevo->sucesor = NULL;
				*cabecera = nuevo;
			}else{ //lista no vacia, insertamos un nuevo valor
				nuevo->sucesor = NULL;
				antes->sucesor = nuevo;
			}
			antes = nuevo;
		}else{
			cout << "No hay memoria";
		}
		cantidadPersonas++;
		cout << endl << "¿Desea registrar un nuevo Estudiante? Y/N ";
		cin >> resp;
	}while(resp == 'y' || resp == 'Y');
	
	strcpy(titulo, "Listado ingresado de Estudiantes");
	imprimirLista(cabecera, titulo);
	
	ordenarListaBurbuja(cabecera);
	
	strcpy(titulo, "Listado de Estudiantes ordenada por Sexo");
	imprimirLista(cabecera, titulo);
}

void imprimirLista(Nodo **cabecera, char titulo[50]){
	Nodo *actual = *cabecera;
	char sexo[50];
	int cantidad = 0;
	
	cout << endl << endl << endl << " ** "<< titulo <<" ** " << endl << endl;
	while(actual->sucesor != NULL){
		cantidad++;
		
		if(actual->sexo == 'f' || actual->sexo == 'F'){
			strcpy(sexo,"Femenino");	
		}else{
			strcpy(sexo,"Masculino");
		}
		
		cout << cantidad << ".- " << actual->nombre << " -> Edad:" << actual->edad << ", Sexo: " << sexo << endl;
		actual = actual->sucesor;
		if(actual->sucesor == NULL){
			cantidad++;
			if(actual->sexo == 'f' || actual->sexo == 'F'){
				strcpy(sexo,"Femenino");	
			}else{
				strcpy(sexo,"Masculino");
			}
			cout << cantidad << ".- " << actual->nombre << " -> Edad:" << actual->edad << ", Sexo: " << sexo << endl;
		}
	}
}

void ordenarListaBurbuja(Nodo **cabecera){
	Nodo *actual , *sucesor;
	char sexo, nombre[50];
	int edad;
	
	actual = *cabecera;
	
	while(actual->sucesor != NULL){
	  sucesor = actual->sucesor;          
	  while(sucesor != NULL){
	       if(actual->sexo > sucesor->sexo){
	            sexo = sucesor->sexo;
	            strcpy(nombre, sucesor->nombre);
	            edad = sucesor->edad;
	            
	            sucesor->sexo = actual->sexo;
	            strcpy(sucesor->nombre, actual->nombre);
	            sucesor->edad = actual->edad;
	            
	            actual->sexo = sexo;  
				strcpy(actual->nombre,nombre); 
				actual->edad = edad;       
	       }
	       sucesor = sucesor->sucesor;                    
	  }    
	  actual = actual->sucesor;
	  sucesor = actual->sucesor;	   
	}
}

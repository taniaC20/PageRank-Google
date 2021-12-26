#include "Archivos.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include<vector>
#include <iterator>
#include <algorithm>
#include <windows.h>
#include <dirent.h>
using namespace std;


Archivos:: Archivos(string pal, string dir): primero(0), ultimo(0), ultimo1(0), interacciones(5), d(0.85){
	this->palabra = pal;
	this->directorio = dir;

}

bool Archivos::esVacia() {

	return primero == 0;
}

void Archivos::agregarNodo(char * n) {

		nodo_Diagrama * nuevo2 = new nodo_Diagrama(n);

			if (esVacia()) {
				primero = nuevo2;
				ultimo = nuevo2;
			}
			else {
				ultimo->setSig(nuevo2);
				ultimo = nuevo2;
			}
		
}
void Archivos::agregarNodoHref(char * n) {

	if (!existeHref(n)) {
		nodo_Diagrama * nuevo2 = new nodo_Diagrama(n);
		if (esVacia()) {
			primero = nuevo2;
			ultimo = nuevo2;
		}
		else {
			ultimo->setSig(nuevo2);
			ultimo = nuevo2;
		}
	}

}

void Archivos::agregarNodoDirect(char * n, nodo_Diagrama * temp) {
		nodo_direct * nuevo2 = new nodo_direct(n);

		if (temp->direcciones == 0) {
			temp->setDirecciones(nuevo2);
			ultimo1 = nuevo2;

		}
		else {
			ultimo1->setSig(nuevo2);
			ultimo1 = nuevo2;
		}
}
void Archivos::leerComparacion(string archivo) {

	ifstream file(archivo, ios::in);
	string texto;
	string text1 = "keywords";
	bool encontro = false;
	bool encontro2 = false;

	if (!file) {
		cout << "No existe el archivo";
		exit(1);
	}
	while (!file.eof()) {
		int cont=0;
		while (getline(file, texto)) {

			if (texto.find(text1) != string::npos) {
				encontro = true;	
			}
			if (encontro) {
				//cout << texto << endl;
				
				if (texto.find(this->palabra) != string::npos) {
					encontro2 = true;
				}
				if (encontro2) {
					//cout << "Se encontro la palabra" << endl;
					char ar[100];
					strcpy_s(ar, archivo.c_str());
					char * arch = ar;
					agregarNodo(arch);
				}
				else {
					//cout << "No se encontro la palabra" << endl;
				}

				return;
			}

			cont++;
		}

	}
	
}

void Archivos::leerDirectorio() {


		DIR * directorio;
		struct dirent * elemento;
		string elem;
		if (directorio = opendir(this->directorio.c_str()))
		{
			while (elemento = readdir(directorio))
			{

				elem = elemento->d_name;

				if (elem != "." && elem != "..") {

					//cout << elem << endl;
					//cout << "-------------------------------------------------------------------------------------" << endl;
					leerComparacion(elem);
				}

			}
		}
		closedir(directorio);
	}

void Archivos::buscarHref(char* nom, nodo_Diagrama * temp) {

	DIR * directorio;
	struct dirent * elemento;
	string elem;
	if (directorio = opendir(this->directorio.c_str()))
	{
		while (elemento = readdir(directorio))
		{

			elem = elemento->d_name;

			if (elem != "." && elem != "..") {

				//cout << elem << endl;
				/*cout << "-------------------------------------------------------------------------------------" << endl;*/
				ifstream file(nom, ios::in);
				string texto;
				string text1 = "href";
				bool encontro = false;
				bool encontro2 = false;



				if (!file) {
					cout << "No existe el archivo";
					exit(1);
				} 

				while (!file.eof()) {
					int cont = 0;


					while (getline(file, texto)) {
						encontro = false;
						encontro2 = false;

						if (texto.find(text1) != string::npos) {
							encontro = true;
						}
						if (encontro) {
							//cout << texto << endl;

							if (texto.find(elem) != string::npos) {
								encontro2 = true;
							}
							if (encontro2) {
								//cout << "En el archivo "<<nom<<" se encontro archivo "<<elem << endl;
								cont++;
								char ar[100];
								strcpy_s(ar, elem.c_str());
								char * arch = ar;

								agregarNodoDirect(arch, temp);
								
							}
							
						}
					}

				}

			}

		}
	}
	closedir(directorio);
}
bool Archivos::existeHref(char * nombre) {
	nodo_Diagrama * temp = primero;
	while (temp != 0) {

		if (strcmp(temp->nombre,nombre) == 0) {
			return true;
			break;
		}
		temp = temp->getSig();
	}
	return false;
}

void Archivos::imprimirListaDirect() {
		nodo_Diagrama * temp = primero;
		while (temp != 0) {
			buscarHref(temp->nombre, temp);
			if (temp->direcciones != 0) {
				cout << "Los href (lista enlazada Horizontal) de " << temp->nombre << " son :" << endl;
			}
			while (temp->direcciones != 0) {
				printf("%s\n", temp->direcciones->nombre);
				agregarNodoHref(temp->direcciones->nombre);
				temp->direcciones = temp->direcciones->getSig();
				temp->enlaces++;
			}
			cout << "Enlaces de " << temp->nombre << " son: " << temp->enlaces << endl;
			temp = temp->getSig();
		}
		imprimirListaDiagrama();
		int inter = 0;
		calculoR(inter,primero,primero);
		cout << endl;
	}

void Archivos::imprimirListaDiagrama() {
	nodo_Diagrama * temp = primero;

	cout << "La lista enlazada Vertical es: " << endl;

	while (temp != 0) {

		printf("%s\n", temp->nombre);
		buscarHref(temp->nombre, temp);
		temp = temp->getSig();
	}
	cout << endl;
}

void Archivos::saveFile(int inter, char * nombre, float pr) {
	ofstream enlacesOut("enlaces.dat", ios::app);

	if (!enlacesOut) {
		cout << "Error al intentar abrir archivo alumnos.dat";
		return;
	}
	
	enlacesOut << inter << ' ' << nombre << ' ' << pr << "\n";
	
	enlacesOut.close();
}

//void Archivos::calculoPR(int inter) {
//	nodo_Diagrama * temp = primero;
//
//	if (inter == interacciones) {
//		ordenarLista();
//		while (temp != 0) {
//			saveFileOrden(temp->nombre, temp->pr);
//			temp = temp->getSig();
//		}
//		return;
//	}
//		cout << "-------------------------------------------------------------------------------------" << endl;
//		cout << "Interaccion : " <<inter+1<< endl;
//		while (temp != 0) {
//			float parentesis = 0;
//			while (temp->direcciones != 0) {
//
//					if (buscarEnlaces(temp->direcciones->nombre) != 0) {
//						parentesis = parentesis + (buscarPr(temp->direcciones->nombre) / buscarEnlaces(temp->direcciones->nombre));
//					}
//					else {
//						parentesis = parentesis + (buscarPr(temp->direcciones->nombre));
//					}
//				
//				temp->direcciones = temp->direcciones->getSig();
//			}
//			temp->setPr((1 - d)+ d *(parentesis));
//			cout << "PR: " << temp->nombre << " es: " << temp->getPr() << endl;
//			saveFile(inter+1, temp->nombre, temp->getPr()); 
//			temp = temp->getSig();
//		}
//		if (temp == 0) {
//			temp = primero;
//			while (temp != 0) {
//				buscarHref(temp->nombre, temp);
//				temp = temp->getSig();
//			}
//			
//		}
//		
//		calculoPR(inter+1);
//}

float Archivos::buscarPr(char * nombre) {
	nodo_Diagrama * temp = primero;
	while (temp != 0) {

		if (strcmp(temp->nombre, nombre) == 0) {
			return temp->pr;
		}
		temp = temp->getSig();
	}
	return 0;
}
int Archivos::buscarEnlaces(char * nombre) {
	nodo_Diagrama * temp = primero;
	while (temp != 0) {

		if (strcmp(temp->nombre, nombre) == 0) {
			return temp->enlaces;
			break;
		}
		temp = temp->getSig();
	}
	return 0;
}

void Archivos::ordenarLista() {
	nodo_Diagrama * actual = primero;

	while (actual != 0) {
		nodo_Diagrama * despues = actual->getSig();

		while (despues != NULL) {
			if (actual->pr < despues->pr) {
				//numero
				float pr = despues->pr;
				despues->pr = actual->pr;
				actual->pr = pr;
				//album
				char nombre[50];
				char * nom = nombre;

				nom = despues->nombre;
				despues->nombre = actual->nombre;
				actual->nombre = nom;

			}
			despues = despues->getSig();
		}
		actual = actual->getSig();
	}
}

void Archivos::saveFileOrden(char * nombre, float pr) {
	ofstream enlacesOut("enlacesOrdenados.html", ios::app);

	if (!enlacesOut) {
		cout << "Error al intentar abrir archivo alumnos.dat";
		return;
	}
	enlacesOut << "<h2>";
	enlacesOut << nombre << ' ' << pr << ' ' << "\n";
	enlacesOut << "</h2>";

	enlacesOut.close();
}
bool Archivos::buscarApuntadores(nodo_Diagrama * actual, nodo_Diagrama * apuntador) {

	while (actual != 0) {
		while (apuntador != 0) {
			while (apuntador->direcciones != 0) {
				if (strcmp(apuntador->direcciones->nombre, actual->nombre) == 0) {
					return true;
				}
				apuntador->direcciones = apuntador->direcciones->getSig();
			}
			apuntador = apuntador->getSig();
		}
		apuntador = primero;
		actual = actual->getSig();
	}

	return false;
}

void Archivos::calculoR(int inter, nodo_Diagrama * apuntador, nodo_Diagrama * actual) {
	if (inter == interacciones) {
		ordenarLista();
		while (actual != 0) {
			saveFileOrden(actual->nombre, actual->pr);
			actual = actual->getSig();
		}
		return;
	}
	cout << "-------------------------------------------------------------------------------------" << endl;
	cout << "Interaccion : " << inter + 1 << endl;
	/*	nodo_Diagrama *apuntador = primero;
		nodo_Diagrama *actual = primero;*/
		while (actual != 0) {
			float total = 0;
			while (apuntador != 0) {
				nodo_direct *tmp = apuntador->direcciones;
				while (tmp != 0) {
					if (strcmp(tmp->nombre, actual->nombre) == 0) {
						if (buscarEnlaces(tmp->nombre) == 0)
							total = total + apuntador->pr;
						if (buscarEnlaces(tmp->nombre) != 0)
							total = total + (apuntador->pr / buscarEnlaces(apuntador->nombre));
					}
					tmp = tmp->sig;
				}
				apuntador = apuntador->sig;
			}
			actual->pr = (1 - 0.85) + (0.85 * (total));
			cout << "PR: " << actual->nombre << " es: " << actual->getPr() << endl;
			saveFile(inter + 1, actual->nombre, actual->getPr());
			apuntador = primero;
			total = 0;
			actual = actual->sig;
		}
   calculoR(inter + 1,primero, primero);
}











































//
//
//void Archivos::imprimirListaDirect() {
//	nodo_Diagrama * temp = primero;
//
//	while (temp != 0) {
//		cout << "Los href (lista enlazada Horizontal) de " << temp->nombre << " son :" << endl;
//		while (temp->direcciones != 0) {
//
//			printf("%s\n", temp->direcciones->nombre);
//			agregarNodo(temp->direcciones->nombre);
//
//			temp->direcciones = temp->direcciones->getSig();
//
//		}
//
//		temp = temp->getSig();
//	}
//	cout << endl;
//}

//
//


//void Archivos::recorrerListaDiagrama() {
//	nodo_Diagrama * temp = primero;
//	while (temp != 0) {
//		buscarHref(temp->nombre, temp);
//		temp = temp->getSig();
//	}
//	cout << endl;
//}





//void Archivos::leerArchivo() {
//	ifstream amazonIn("amazon", ios::in);
//	if (!amazonIn) {
//		cout << "Error al intentar abrir el archivo amazon";
//		return;
//	}
//	bool encontro = false;
//	while(amazonIn.is_open()) {
//		/*if (str.find(str2) != "meta") {
//			encontro = true;
//		}*/
//	}
//	if (encontro == false)
//		cout << "No se encontro nada";
//	amazonIn.close();
//}
//void Archivos::leerLineaArchivo() {
//	ifstream amazonIn("amazon.html", ios::in);;
//	string linea;
//
//	int contador = 0;
//	int max;
//	if (!amazonIn) {
//		cout << "Error al intentar abrir el archivo amazon";
//		return;
//	}
//	bool encontro = false;
//	while (amazonIn.is_open()) {
//		cout << "Escribe una linea: ";
//		cin >> max;
//
//
//		while (getline(amazonIn, linea)) {
//
//			if (max == contador) {
//				cout << linea << endl;
//			}
//
//			contador++;
//		}
//
//		return;
//	}
//	return;
//
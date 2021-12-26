#ifndef ARCHIVOS_H
#define ARCHIVOS_H
#include <string>
#include <dirent.h>
using namespace std;


struct nodo_direct {
	char * nombre;
	float pr;
	nodo_direct * sig;
	/*nodo_Diagrama * anterior;*/
	void setSig(nodo_direct * siguiente) {
		sig = siguiente;
	}
	nodo_direct * getSig() {
		return sig;
	}

	nodo_direct( char * n) { 
		nombre = new char[strlen(n)];
		strcpy_s(nombre, strlen(n) + 1, n);
		sig = 0;
	}

};

struct nodo_Diagrama {

	char * nombre;
	nodo_Diagrama * sig;
	float pr;
	int enlaces;
	nodo_direct * direcciones;
	void setDirecciones(nodo_direct * dir) {
		direcciones = dir;
	}
	nodo_direct * getDirecciones() {
		return direcciones;
	}
	void setSig(nodo_Diagrama * siguiente) {
		sig = siguiente;
	}
	nodo_Diagrama * getSig() {
		return sig ;
	}

	void setPr(float pagerank) {
		pr = pagerank;
	}
	float getPr() {
		return pr;
	}

	nodo_Diagrama(const char * n) {
		nombre = new char[strlen(n)];
		strcpy_s(nombre, strlen(n) + 1, n);
		pr = 0;
		sig = 0;
		direcciones = 0;
		enlaces = 0;
	}

};
class Archivos {

public:

	nodo_Diagrama * primero, *ultimo;
	nodo_direct * ultimo1;

	string palabra;
	string directorio;
	string init();
	int interacciones;
	double d;


	// listas enlazadas
	void imprimirListaDiagrama();//VERTICAL
	void imprimirListaDirect();//HORIZONTAL
	void agregarNodo(char * n);// agrega a la lista Vertical los elementos nuevos
	void agregarNodoHref(char * n);//agrega a la lista Vertical los hRef de los  archivos que contienen la palabra
	void agregarNodoDirect(char * n, nodo_Diagrama * temp);//agrega a la lista Horizontal de cada archivo sus hRef
	bool esVacia();//si la lista enlazada esta vacia

	//hRef
	void buscarHref(char * nombre, nodo_Diagrama * temp);//busca los href dentro del archivo qe contiene la palabra
	bool existeHref(char * nombre);// condicion de si existe ya el archivo href en la lista Vertical

	
    //calclulos del PageRank

	void calculoPR(int inter);
	float buscarPr( char * nombre);
	int buscarEnlaces(char * nombre);
	void ordenarLista();
	bool buscarApuntadores(nodo_Diagrama *actual, nodo_Diagrama * apuntador);
	void calculoR(int inter, nodo_Diagrama * apuntador, nodo_Diagrama * actual);

	//otros (Directorios y archivos)
	void leerComparacion(string archivo);//Leer si existe la palabra
	void leerDirectorio();//Buscar en el directorio
	void saveFile(int inter, char * nombre, float pr);
	void saveFileOrden(char * nombre, float pr);

	Archivos(string pal, string dir);
};
#endif

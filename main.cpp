#include <iostream>
#include "Archivos.h"
#include <string>
using namespace std;




int main(/*int argc, char ** argv*/) {

	/*string text;
	string dir;*/
	/*for (int i = 0; i < argc; i++) {
		text = argv[i];
		dir = argv[i + 1];
	}
	Archivos ar(text, dir);*/
	string text;
	cout << " Ingrese la palabra: " << endl;
	cin >> text;
	cout << "Ruta del directorio a listar: ";
	string dir;
	cin >> dir;
	Archivos ar(text, dir);
	ar.leerDirectorio(/*dir*/);
	ar.imprimirListaDirect();
	system("pause");
	
}
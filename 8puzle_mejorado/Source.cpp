#include "Puzzle.h"
#include "Busqueda.h"
#include <ctime>
using namespace std; 
int main() {
	Busqueda p; //Se declara una instancia de la clase para buscar solucion 
	Nodo_agenda nodo_encontrado; //Se declara variable de tipo nodo agenda llamado nodo encontrado 
	nodo_encontrado.posicion = -1;  //se incializa en -1
	unsigned int t0, t1; //variables que ayudan a ver el tiempo que tarda en resolverse el puzzle 
	t0 = clock();
	p.busqueda_A(nodo_encontrado, 16); //poner el tamaño total de elementos del puzzle, puzzle 4x4 = 16, 5x5 = 25
	t1 = clock();
	double time = double(t1 - t0) / CLOCKS_PER_SEC; //resta para ver el tiempo de resolucion 
	p.devuelve_la_ruta_encontrada(nodo_encontrado.posicion); //imprime la ruta encontrada y la escribe en un txt 
	cout << endl << "Tiempo de ejecucion: " << time << "seg" << endl; //imprime el tiempo de ejecucion 
}

#include "Numeros_del_rey.h"
#include "Busqueda.h"
#include <iostream>
int main()
{
	Busqueda p; //Instancia de la clase Busqueda 
	vector<string> soluciones_encontradas;   //Vector que va a contener todas las soluciones que obtenga del algoritmo de busqueda 
	int num = 32;//numero que se busca que sea el resultado de los numeros evaluados 
	soluciones_encontradas = p.busqueda_A(num); //Se ejecuta el algoritmo de busqueda, y se guarda el vector resultando en el vector soluciones_encontradas 
	if (soluciones_encontradas.size() > 0) { //En caso de que haya encontrado por lo menos una solucion 
		cout << "Numero a buscar: " << num<<endl;  //se imprime que numero se estaba buscando encontrar 
		for (string a : soluciones_encontradas) //foreach que recorre cada string del vector de los resultados 
			cout << a << endl; //imprime cada solucion 
	}
	else {//en caso de que no haya encontrado una solucion 
		cout << "No fue posible llegar a una solucion para: " << num; //imprime este letrero si no encontro una solucion 
	}
	return 0; 
}
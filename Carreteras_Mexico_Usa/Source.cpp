#include "Busqueda.h"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;
void size_tabla(string& a, string& b, int agenda, int arbol)
{
	//Dimensiones a ajustar en caso del tamaño del numero 
	string milesima = "                |                   "; 
	string centesima = "                 |                   ";
	string decena = "                  |                   ";
	string unidad = "                   |                   ";

	string milesima_arbol = "              |";
	string centesima_arbol = "               |";
	string decena_arbol = "                |";

	if (agenda > 999) //Viendo que valor devuelve dependiendo de cada caso 
		a = milesima;
	else if (agenda > 99 && agenda < 1000)
		a = centesima;
	else if (agenda > 9 && agenda < 100)
		a = decena;
	else
		a = unidad;

	if (arbol > 999)
		b = milesima_arbol;
	else if (arbol > 99 && arbol < 1000)
		b = centesima_arbol;
	else if (arbol > 9 && arbol < 100)
		b = decena_arbol;

}

//Imprime la tabla que contiene el valor maximo de la agenda y el valor maximo el arbol. Esta tabla se adapta dependiendo si se utilizan unidades, decenas, centenas y miles
void imprimir_tabla(int agenda_max_b_ancho, int agenda_max_b_profundidad, int agenda_max_b_plimitada, int agenda_max_b_piterativa, int agenda_max_b_bidireccional,
	int agenda_max_b_acolina, int agenda_max_b_bf, int agenda_max_b_kbeans, int agenda_max_b_bb, int agenda_max_b_A,
	int arbol_max_b_ancho, int arbol_max_b_profundidad, int arbol_max_b_plimitada, int arbol_max_b_piterativa, int arbol_max_b_bidireccional,
	int arbol_max_b_acolina, int arbol_max_b_bf, int arbol_max_b_kbeans, int arbol_max_b_bb, int arbol_max_b_A)
{
	string a, b; 

	cout << endl << "============================================================================================================" << endl;
	cout << "Tabla" << endl << endl; 
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "          Algoritmo                       |          Max_size_agenda             |          Max_size_arbol             |" << endl; 
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_ancho, arbol_max_b_ancho);
	cout << " Busqueda a lo ancho                      |                  " << agenda_max_b_ancho << a << arbol_max_b_ancho << b << endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_profundidad, arbol_max_b_profundidad);
	cout << " Busqueda primero en profundidad          |                  " << agenda_max_b_profundidad << a<< arbol_max_b_profundidad <<b << endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_plimitada, arbol_max_b_plimitada);
	cout << " Busqueda primero profundidad limitada    |                  " << agenda_max_b_plimitada << a<< arbol_max_b_plimitada << b << endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_piterativa, arbol_max_b_piterativa);
	cout << " Busqueda primero profundidad iterativa   |                  " << agenda_max_b_piterativa << a<< arbol_max_b_piterativa << b << endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_bidireccional, arbol_max_b_bidireccional);
	cout << " Busqueda bidireccional                   |                  " << agenda_max_b_bidireccional << a<< arbol_max_b_bidireccional << b << endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_acolina, arbol_max_b_acolina);
	cout << " Busqueda ascenso a la colina             |                  " << agenda_max_b_acolina << a<< arbol_max_b_acolina << b << endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_bf, arbol_max_b_bf);
	cout << " Busqueda best first                      |                  " << agenda_max_b_bf << a<< arbol_max_b_bf <<b<< endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_kbeans, arbol_max_b_kbeans);
	cout << " Busqueda k beans                         |                  " << agenda_max_b_kbeans << a<< arbol_max_b_kbeans <<b << endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_bb, arbol_max_b_bb);
	cout << " Busqueda branch and bound                |                  " << agenda_max_b_bb << a << arbol_max_b_bb << b<< endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                          |                                      |                                     |" << endl;
	size_tabla(a, b, agenda_max_b_A, arbol_max_b_A);
	cout << " Busqueda A estrella                      |                  " << agenda_max_b_A << a << arbol_max_b_A << b << endl;
	cout << "                                          |                                      |                                     |" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	
}

int main(void)
{
	Busqueda p;
	string camino = "";
	int NodoEncontrado = -1;
	int NodoEncontradoInicio = -1;
	int NodoEncontradoFinal = -1;
	int agenda_max_b_ancho = 0, agenda_max_b_profundidad = 0, agenda_max_b_plimitada = 0, agenda_max_b_piterativa = 0, agenda_max_b_bidireccional = 0,
		agenda_max_b_acolina = 1, agenda_max_b_bf = 0, agenda_max_b_kbeans = 0, agenda_max_b_bb = 0, agenda_max_b_A = 0;  //Maximo numero de elementos en la agenda en cada algoritmo 

	int arbol_max_b_ancho = 0, arbol_max_b_profundidad = 0, arbol_max_b_plimitada = 0, arbol_max_b_piterativa = 0, arbol_max_b_bidireccional = 0,
		arbol_max_b_acolina = 0, arbol_max_b_bf = 0, arbol_max_b_kbeans = 0, arbol_max_b_bb = 0, arbol_max_b_A = 0;//Maximo numero de elementos en el arbol en cada algoritmo 

	if (p.lee_grafo("Mexico_USA_Corregido.csv"))//en caso de que si pueda leer el grafo 
	{
		//Rutas con grafo no dirgido 
		cout << "======================================================================================================" << endl; 
		cout << "Grafo no dirigido" << endl << endl; 
		if (p.busqueda_a_lo_ancho("Juarez","Dallas", NodoEncontrado, agenda_max_b_ancho, arbol_max_b_ancho, 0))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda a lo ancho: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda a lo ancho\n");

		if (p.busqueda_primero_en_profundidad("Juarez", "Dallas", NodoEncontrado, agenda_max_b_profundidad, arbol_max_b_profundidad, 0))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda primero en profundidad: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda primero en profundidad\n");

		if (p.busqueda_profundidad_limitada("Juarez", "Dallas", 3, NodoEncontrado, agenda_max_b_plimitada, arbol_max_b_plimitada, 0))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda con profundidad limitada: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda con profundidad limitada\n");

		if (p.busqueda_profundidad_iterativa("Juarez", "Dallas", 2, 2, NodoEncontrado, agenda_max_b_piterativa, arbol_max_b_piterativa, 0))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda con profundidad iterativa: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda con profundidad iterativa\n");

		if (p.busqueda_bidireccional("Juarez", "Dallas", NodoEncontradoInicio, NodoEncontradoFinal, agenda_max_b_bidireccional, arbol_max_b_bidireccional, 0))
		{
			camino = p.devuelve_la_ruta_encontrada_busqueda_bidireccional(NodoEncontradoInicio, NodoEncontradoFinal);
			printf("\nCamino encontrado por busqueda bidireccional: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda bidireccional\n");

		if (p.busqueda_ascenso_a_la_colina("Juarez", "Dallas", NodoEncontrado, arbol_max_b_acolina, 0))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por ascenso a la colina: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por ascenso a la colina\n");

		if (p.busqueda_primero_el_mejor("Juarez", "Dallas", NodoEncontrado, agenda_max_b_bf, arbol_max_b_bf, 0))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por primero el mejor: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por primero el mejor\n");

		if (p.busqueda_k_beans("Juarez", "Dallas", 200, NodoEncontrado, agenda_max_b_kbeans, arbol_max_b_kbeans, 0))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por k beans: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por k beans\n");

		if (p.busqueda_branch_and_bound("Juarez", "Dallas", NodoEncontrado, agenda_max_b_bb, arbol_max_b_bb, 0))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por branch and bound: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por branch and bound\n");

		if (p.busqueda_A_estrella("Juarez", "Dallas", NodoEncontrado, agenda_max_b_A, arbol_max_b_A, 0))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por A estrella: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por A estrella\n");


		imprimir_tabla(agenda_max_b_ancho, agenda_max_b_profundidad, agenda_max_b_plimitada, agenda_max_b_piterativa, agenda_max_b_bidireccional,
			agenda_max_b_acolina = 1, agenda_max_b_bf, agenda_max_b_kbeans, agenda_max_b_bb, agenda_max_b_A,
			arbol_max_b_ancho, arbol_max_b_profundidad, arbol_max_b_plimitada, arbol_max_b_piterativa, arbol_max_b_bidireccional,
			arbol_max_b_acolina, arbol_max_b_bf, arbol_max_b_kbeans, arbol_max_b_bb, arbol_max_b_A);
		cout << endl << endl; 

		//Rutas con grafo dirigido 
		cout << "======================================================================================================" << endl;
		cout << "Grafo dirigido" << endl << endl;
		if (p.busqueda_a_lo_ancho("Juarez", "Dallas", NodoEncontrado, agenda_max_b_ancho, arbol_max_b_ancho, 1))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda a lo ancho: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda a lo ancho\n");

		if (p.busqueda_primero_en_profundidad("Juarez", "Dallas", NodoEncontrado, agenda_max_b_profundidad, arbol_max_b_profundidad, 1))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda primero en profundidad: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda primero en profundidad\n");

		if (p.busqueda_profundidad_limitada("Juarez", "Dallas", 3, NodoEncontrado, agenda_max_b_plimitada, arbol_max_b_plimitada, 1))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda con profundidad limitada: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda con profundidad limitada\n");

		if (p.busqueda_profundidad_iterativa("Juarez", "Dallas", 2, 2, NodoEncontrado, agenda_max_b_piterativa, arbol_max_b_piterativa, 1))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por busqueda con profundidad iterativa: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda con profundidad iterativa\n");

		if (p.busqueda_bidireccional("Juarez", "Dallas", NodoEncontradoInicio, NodoEncontradoFinal, agenda_max_b_bidireccional, arbol_max_b_bidireccional, 1))
		{
			camino = p.devuelve_la_ruta_encontrada_busqueda_bidireccional(NodoEncontradoInicio, NodoEncontradoFinal);
			printf("\nCamino encontrado por busqueda bidireccional: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por busqueda bidireccional\n");

		if (p.busqueda_ascenso_a_la_colina("Juarez", "Dallas", NodoEncontrado, arbol_max_b_acolina, 1))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por ascenso a la colina: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por ascenso a la colina\n");

		if (p.busqueda_primero_el_mejor("Juarez", "Dallas", NodoEncontrado, agenda_max_b_bf, arbol_max_b_bf, 1))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por primero el mejor: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por primero el mejor\n");

		if (p.busqueda_k_beans("Juarez", "Dallas", 200, NodoEncontrado, agenda_max_b_kbeans, arbol_max_b_kbeans, 1))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por k beans: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por k beans\n");

		if (p.busqueda_branch_and_bound("Juarez", "Dallas", NodoEncontrado, agenda_max_b_bb, arbol_max_b_bb, 1))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por branch and bound: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por branch and bound\n");

		if (p.busqueda_A_estrella("Juarez", "Dallas", NodoEncontrado, agenda_max_b_A, arbol_max_b_A, 1))
		{
			camino = p.devuelve_la_ruta_encontrada(NodoEncontrado);
			printf("\nCamino encontrado por A estrella: \n%s\n", camino.c_str());
		}
		else
			printf("\nRuta no encontrada por A estrella\n");

		imprimir_tabla(agenda_max_b_ancho, agenda_max_b_profundidad, agenda_max_b_plimitada, agenda_max_b_piterativa, agenda_max_b_bidireccional,
			agenda_max_b_acolina = 1, agenda_max_b_bf, agenda_max_b_kbeans, agenda_max_b_bb, agenda_max_b_A,
			arbol_max_b_ancho, arbol_max_b_profundidad, arbol_max_b_plimitada, arbol_max_b_piterativa, arbol_max_b_bidireccional,
			arbol_max_b_acolina, arbol_max_b_bf, arbol_max_b_kbeans, arbol_max_b_bb, arbol_max_b_A);
	}
	return 0;
}
#pragma once

#include <string>
#include <vector>
#include <stddef.h>

using namespace std;

//Estructura tipo nodo información
struct tipo_nodo_informacion
{
	string nombre_del_nodo = "";  //Nombre del nodo
	float costo_acumulado = 0.0f; //Costo acumulado
	float costo_estimado = 0.0f; //Cuanto le falta para llegar al destino, distancia euclidiana 
};
//Nodo que se va a añadir al arbol 
struct tipo_nodo_del_arbol
{
	tipo_nodo_informacion contenido; //nombre, costo acumulado y estimado 
	int padre = -1; //Posicion del padre
	unsigned int profundidad = 0; //A que profundidad se encuentra el nodo 
	vector<unsigned int> hijos; //Vector que guarda la posicion de los hijos 
};
//Estructura que guarda la informacion del grafo 
struct tipo_enlace_de_grafo
{
	string nodo_1 = ""; //Nombre del primero nodo
	float costo_nodo_1 = 0.0f; //Su costo del nodo 
	string nodo_2 = ""; //Nombre del nodo 2
	float costo_nodo_2 = 0.0f; //Costo del segundo nodo 
	float costo_del_enlace = 0.0f; //Costo del enlace entre los dos nodos 
	float posicion_x_nodo_1 = 0.0f; //Posicion en x del primer nodo 
	float posicion_y_nodo_1 = 0.0f; //Posicion en y del primer nodo 
	float posicion_x_nodo_2 = 0.0f; //Posicion en x del segundo nodo 
	float posicion_y_nodo_2 = 0.0f; //Posicion en y del segundo nodo 
};

class Busqueda
{
public:
	//Constructor 
	Busqueda();
	//Destructor 
	~Busqueda();
	//Funcion para leer un csv, que es donde está el grafo 
	bool lee_grafo(string archivo);

	//Algoritmos de busqueda 
	bool busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido);
	bool busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido);
	bool busqueda_profundidad_limitada(string nodo_inicio, string nodo_final,
		unsigned int limite_de_profundidad, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido);
	bool busqueda_profundidad_iterativa(string nodo_inicio, string nodo_final,
		unsigned int limite_de_profundidad, unsigned int incremento_de_profundidad,
		int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido);
	bool busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado_desde_el_inicio,
		int& nodo_encontrado_desde_el_final, int& agenda_max, int& arbol_max, bool dirigido);
	bool busqueda_ascenso_a_la_colina(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& arbol_max, bool dirigido);
	bool busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido);
	bool busqueda_k_beans(string nodo_inicio, string nodo_final, unsigned int k, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido);
	bool busqueda_branch_and_bound(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido);
	bool busqueda_A_estrella(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido);
	//Devuelve la ruta encontrada en caso de que no sea bidireccional 
	string devuelve_la_ruta_encontrada(int nodo_encontrado) const;
	//Devuelve la ruta encontrada en caso de que sea bidireccional 
	string devuelve_la_ruta_encontrada_busqueda_bidireccional(int nodo_encontrado_desde_el_inicio,
		int nodo_encontrado_desde_el_final) const;


private:
	vector<tipo_enlace_de_grafo> grafo; //Grafo a analizar 
	vector<tipo_nodo_del_arbol> arbol_de_busqueda; //Arbol de busqueda, donde estarán los nodos 
	vector<unsigned int> Agenda; //Agenda donde se guardarán las posiciones del nodo en el arbol
	vector<tipo_nodo_del_arbol> arbol_de_busqueda_desde_el_inicio; //arbol de busqueda en caso de bidireccional 
	vector<unsigned int> Agenda_desde_el_inicio; //agenda en caso de bidireccional 
	vector<tipo_nodo_del_arbol> arbol_de_busqueda_desde_el_final; //arbol de busqueda en caso de bidireccional 
	vector<unsigned int> Agenda_desde_el_final; //agend en caso de bidireccional 

	//Distancia euclidiana 
	float calcula_heuristica_a_la_meta(string nodo_actual, string meta) const;
	//Devuelve lo vecinos del nodo actual de un grafo no dirigido 
	void devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const;
	//Devuelve la informacion de un nodo del grafo
	bool devuelve_informacion_de_un_vertice_del_grafo(string nodo, vector<tipo_nodo_del_arbol> arbol_creado,
		int nodo_padre, tipo_nodo_informacion& informacion) const;
	//crea la raiz del arbol de busqueda 
	void crea_arbol(tipo_nodo_informacion contenido, vector<tipo_nodo_del_arbol>& arbol_creado);
	//Agrega un hijo a un nodo en el arbol de busqueda 
	void agrega_hijo_a_un_nodo(vector<tipo_nodo_del_arbol>& arbol, int padre, tipo_nodo_informacion contenido);
	//Verifica si un nodo es repetido en la misma rama 
	bool esta_un_nodo_en_ancestros(vector<tipo_nodo_del_arbol> arbol, const int nodo_origen, string nombre_del_nodo) const;
	//Ve cuando dos agendas se interceptan 
	bool existe_un_nodo_comun_en_las_agendas(vector<unsigned int> agenda_1, vector<unsigned int> agenda_2,
		int& nodo_comun_inicio, int& nodo_comun_final) const;
	//Devuelve los vecinos de un grafo dirigido
	void devuelve_vecinos_grafo_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const; 
};


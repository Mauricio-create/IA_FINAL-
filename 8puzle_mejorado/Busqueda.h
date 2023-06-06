#pragma once
#include<string>
#include<vector>
#include <queue>
using namespace std;

//Contenido del nodo del arbol 
struct tipo_nodo_informacion 
{
	string nombre_del_nodo = ""; //estado del puzzle
	float costo_estimado = 0.0f; //costo estimado por le heuristica 
};
//Nodo del arbol 
struct tipo_nodo_del_arbol
{
	tipo_nodo_informacion contenido; //contenido que es estado y costo estimado 
	int padre = -1; //posicion del padre
	vector<unsigned int> hijos; //vector de posiciones de los hijos
};
//Nodo de la agenda
struct Nodo_agenda { 
	int posicion; //Posicion en el arbol de un nodo 
	double costo; //Costo, el cual servirá para ordenar la agenda de forma ascendente 
};
//Sobrecargar la funcion operator que viene por defecto en una cola de prioridad
struct ComparadorNodos { 
	bool operator()(const Nodo_agenda& n1, const Nodo_agenda& n2) const { //Compara dos nodos de una agenda para brindarles mas o menos prioridad en la cola 
		return n1.costo > n2.costo; // si n1 es mayor que n2, tiene menos prioridad, es decir, se coloca más adelante que n2, en caso contrario se coloca antes 
									//debido a que en una cola sale el primer elemento, que son los de mayor prioridad, y los ultimos de menos prioridad 
	}
};


class Busqueda
{
public:
	//Constructor 
	Busqueda();
	//Destructor 
	~Busqueda();
	//Resolucion del puzzle 
	bool busqueda_A(Nodo_agenda& nodo_encontrado, int n);
	//Imprime en consola la ruta encontrada, y escribe en un txt la misma
	void devuelve_la_ruta_encontrada(int nodo_encontrado) const;
private: 
	//Crea un arbol 
	void crea_arbol(tipo_nodo_informacion contenido);
	//Agrega un hijo al arbol 
	void agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido);
	//Verifica que no haya dos nodos en la misma rama 
	bool esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const;
	vector<tipo_nodo_del_arbol>arbol_de_busqueda; //arbol de busqueda 
	priority_queue<Nodo_agenda, vector<Nodo_agenda>, ComparadorNodos> agenda;
	//Tiene una cola ralizada con un vector de tipo nodo_agenda, que guarda el valor de la posicion el arbol y su costo acumulado
	//ComparadorNodos ayuda  ordenar la agenda dependiendo de la prioridad
	//Tiene tres parametros una priority_queue que son: 
	//1. Tipo de dato a almacenar, 2. Contenedor en donde se va a almacenar, 3. Criterio de comparacion para la definicion de prioridades en la cola 
	//El parametro 3 es una funcion llamada operator(), que se sobrecargó para ponerle criterios personaizados, que por defecto ordena de forma descendente 
	//y en este problema se ordenó de forma ascendente 
};






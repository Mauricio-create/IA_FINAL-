#pragma once
#include<string>
#include<vector>
#include <queue>
using namespace std;

//Estructura que contiene la cadena de caracteres a evaluar y el costo estimado, es decir, que tan alejado está del valor a buscar. 
struct tipo_nodo_informacion
{
	string nombre_del_nodo = ""; //Estado actual de los numeros
	int costo_estimado = 0; //Que tan alejado está de la meta 
};

//Estructura que define lo que contendrá un nodo del arbol
struct tipo_nodo_del_arbol
{
	tipo_nodo_informacion contenido; //Estado actual de los numeros y costo estimado 
	int padre = -1; //Posicion del padre del nodo 
	vector<unsigned int> hijos; //Vector con las posiciones de los hijos 
};

struct Nodo_agenda { 
	int posicion = 0; //Posicion del nodo en el arbol 
	int costo = 0; //Costo para evaluar que tan alejado 
};

//Sobrecarga de la funcion operator, que viene por defecto definida en la estructura de datos priority_queue 
struct ComparadorNodos {
	bool operator()(const Nodo_agenda& n1, const Nodo_agenda& n2) const { //sobrecarga la funcion operator 
		return n1.costo > n2.costo; // ordena por costo ascendente
		//En caso de que n1 sea mayor a n2, tiene menor prioridad, por lo cual se pone antes en la cola que n2
	}
};


class Busqueda
{
public:
	//Constructor 
	Busqueda();
	//Destructor 
	~Busqueda();
	//Busqueda, que se enfoca en encontrar una secuencia de operaciones entre 9 numeros para llegar a un numero definido por el usuario 
	vector<string> busqueda_A(int num_final);
private:
	//Crea la raiz del arbol 
	void crea_arbol(tipo_nodo_informacion contenido);
	//Agrega elementos al arbol 
	void agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido);
	//Busca si un nodo ya se encuentra sobre una misma rama 
	bool esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const;
	
	vector<tipo_nodo_del_arbol>arbol_de_busqueda;
	priority_queue<Nodo_agenda, vector<Nodo_agenda>, ComparadorNodos> agenda;
};






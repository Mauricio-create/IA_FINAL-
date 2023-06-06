#pragma once
#include<string>
#include<vector>
using namespace std;

class Numeros_del_rey
{
public:
	//Constructor 
	Numeros_del_rey();
	//Destructor 
	~Numeros_del_rey();
	//Imprime los numeros con sus operandos entre cada número 
	void mostrar_numeros()const;
	//Función que devuelve los posibles numeros con diversos operandos entre cada número 
	vector<string> posibles_movimientos(int pos)const;
	//Actualiza la cadena de caracteres 
	void actualizar_numeros(string actualizar);
	//Crea la cadena de caracteres inicial 
	void crear_numeros();
	//Convierte los numeros a enteros, y se hace ya sea suma, resta, multiplicación o división, dependiendo del caracter que esté entre los numeros 
	int evaluar_numeros(const string num);
	//Calcula que tan alejado está el valor encontrado del valor que se quiere encontrar 
	int heuristica(const string num, int final);
	//Devuelve cadena de caracteres del estado actual del string numeros 
	string devolver_nodo_actual();

private:
	//Numeros que se van a estar modificando los operandos entre cada numero 
	string numeros; 
};






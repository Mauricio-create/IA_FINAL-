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
	//Imprime los numeros con sus operandos entre cada n�mero 
	void mostrar_numeros()const;
	//Funci�n que devuelve los posibles numeros con diversos operandos entre cada n�mero 
	vector<string> posibles_movimientos(int pos)const;
	//Actualiza la cadena de caracteres 
	void actualizar_numeros(string actualizar);
	//Crea la cadena de caracteres inicial 
	void crear_numeros();
	//Convierte los numeros a enteros, y se hace ya sea suma, resta, multiplicaci�n o divisi�n, dependiendo del caracter que est� entre los numeros 
	int evaluar_numeros(const string num);
	//Calcula que tan alejado est� el valor encontrado del valor que se quiere encontrar 
	int heuristica(const string num, int final);
	//Devuelve cadena de caracteres del estado actual del string numeros 
	string devolver_nodo_actual();

private:
	//Numeros que se van a estar modificando los operandos entre cada numero 
	string numeros; 
};






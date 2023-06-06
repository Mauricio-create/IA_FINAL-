#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Puzzle {
public:
	//Constructor 
	Puzzle();
	//Destructor 
	~Puzzle();
	//Desordena el puzzle 
	void shuffle();
	//Imprime el estado actual 
	void mostrar_puzzle()const;
	//Crea un puzzle de tamaño n, bien ordenaod 
	void crear_puzzle(unsigned int n);
	//Devuelve los vecinos, es decir, los posibles movimientos del estado actual 
	vector<string> posibles_movimientos(int raiz)const;
	//Devuelve una cadena de caracteres del estaod actual 
	string primer_elemento()const;
	//Verifica si una o más filas ya están formadas
	bool revisar_linea(string cadena, int num_lineas, int raiz)const;
	//Cambia el puzzle a uno nuevo 
	void actualizar_puzzle(vector<string> actualizar);
	//Devuelve el numero de filas y columnas que tiene el puzzl e
	float raiz()const;
private:
	//vector de string, que contiene cada caracter del puzzle 
	vector<string>puzzle;
	//Numero de fichas en el puzzle 
	unsigned int size_puzzle;
};
#include "Numeros_del_rey.h"
#include "Busqueda.h"
#include <iostream>
#include <time.h>
using namespace std; 
#pragma warning(disable : 26451)
//Constructor 
Numeros_del_rey::Numeros_del_rey()
{

}
//Destructor 
Numeros_del_rey::~Numeros_del_rey()
{

}
//Mostrar numeros 
void Numeros_del_rey::mostrar_numeros()const
{
	//Foreach que toma como valor, cada caracter de numeros. Numeros es una cadena de caracteres que contiene tanto los numeros como sus 
	//operandos entre ellos, por ejemplo imprime en consola: "1+2+3+4+5+6+7+8+9"
	for (char c : numeros)
		cout << c; 
	cout << endl;
}
//Retorna los vecinos del estado actual 
vector<string> Numeros_del_rey::posibles_movimientos(int pos)const
{
	string temp; //Variable que se va a añadir a posibles movimientos, va a tomar el valor de cada posible estado partiendo de la variable numeros 
	vector<string>posibles_mov; //vector a devolver en la funcion, que contiene todos los posibles movimientos 
	if (pos == 0) //Condicional que verifica si el primer nodo del arbol tiene vecinos o no, en caso de no tener vecinos pos es igual a 0, ya que la agenda 
				  //solo contiene la posicion 0 
	{
		int j = 0;
		//suma
		//Crea la siguiente cadena de caracteres "1+2+3+4+5+6+7+8+9"
		for (unsigned int i = 0; i <= 16; i++)
			if (i % 2 == 0 || i == 0)
				temp += numeros[j++]; //En caso de que la posicion sea par se añade un numero 
			else
				temp += "+"; //En caso de que no sea par, se pone el caracter +
		posibles_mov.push_back(temp); //Se añade temp, que es la cadena "1+2+3+4+5+6+7+8+9" a posibles_mov
		temp = "";

		j = 0;
		//resta
		//Crea la siguiente cadena de caracteres: "1-2-3-4-5-6-7-8-9"
		for (unsigned int i = 0; i <= 16; i++)
			if (i % 2 == 0 || i == 0)
				temp += numeros[j++];//En caso de que la posicion sea par se añade un numero
			else
				temp += "-"; //En caso de que no sea par, se pone el caracter -
		posibles_mov.push_back(temp); //se añade temp al vector posibles mov
		temp = "";

		j = 0; 
		//multiplicacion
		//Se crea la siguiente cadena de caracteres "1*2*3*4*5*6*7*8*9"
		for (unsigned int i = 0; i <= 16; i++)
			if (i % 2 == 0 || i == 0)
				temp += numeros[j++];//En caso de que la posicion sea par se añade un numero
			else
				temp += "*";//En caso de que no sea par, se pone el caracter *
		posibles_mov.push_back(temp); //se añade temp al vector posibles mov
		temp = "";

		j = 0;
		//division
		//Se crea la siguiente cadena: "1/2/3/4/5/6/7/8/9"
		for (unsigned int i = 0; i <= 16; i++)
			if (i % 2 == 0 || i == 0)
				temp += numeros[j++];//En caso de que la posicion sea par se añade un numero
			else
				temp += "/";;//En caso de que no sea par, se pone el caracter /
		posibles_mov.push_back(temp);//se añade temp al vector posibles mov
		temp = "";
	}
	else {//En caso de que haya más nodos que la raiz 
		vector<char>operaciones = { '+', '-', '*', '/'}; //vector que contiene los posibles operandos 
		vector<int>posiciones = { 1,3,5,7,9,11,13,15 };//vector que contiene las posibles posiciones en donde hay un operador "+-*/"
		srand((unsigned int)time(NULL));//semilla que ayuda a cambiar los valores random 
		
		//De una cadena de caracteres, por ejemplo: "1+2+3+4+5+6+7+8+9" Genera n vecinos, dependiendo del valor que tenga el ciclo for, cambiando solo un 
		//operador al azar, por ejemplo, si se bisca tener 4 vecinos, se devolvería los siguiente: 
		//1) "1-2+3+4+5+6+7+8+9"
		//2) "1+2*3+4+5+6+7+8+9"
		//3) "1+2+3+4/5+6+7+8+9"
		//4) "1+2+3+4+5+6+7-8+9"

		for (unsigned int i = 0; i < 10; i++) { //for que declara cuantos vecinos se van a devolver, en este caso son 10 vecinos 
			bool isIn = false; //isIn es una variable que ayuda a verificar que dos vecinos no tengan el mismo valor antes de añadirse a posibles_mov
			temp = numeros; //temp es el estado actual de los numeros con sus respectivos operandos 
			temp[posiciones[rand() % posiciones.size()]] = operaciones[rand() % operaciones.size()]; //toma un operados al azar y le cambia el valor por
																									//otro al azar que está en el vector operaciones 
			//por ejemplo: "1+2+3+4+5+6+7+8+9" posiciones[random] = 1 y operaciones[random] = -
			//nueva cadena = "1-2+3+4+5+6+7+8+9"
			for (string c : posibles_mov)
				if (c == temp) //verfica si la cadena formada ya existe dentro de posibles mov
					isIn = true;
			if(!isIn)
				posibles_mov.push_back(temp); //si no existe la añade al vector 
		}
	}
	
	return posibles_mov; //devuelve los vecinos 
}
//Cambia la variable numeros por la variable actualizar 
void Numeros_del_rey::actualizar_numeros(string actualizar)//variable actualizar 
{
	numeros = actualizar; //numeros es la variable donde se guarda el estado actual de los numeros del rey, y actualizar es una nueva cadena que sustituirá a numeros 
}
//Crea una cadena de caracteres del 1 al 9
//"123456789"
void Numeros_del_rey::crear_numeros()
{
	for (unsigned int i = 1; i <= 9; i++)
		numeros += to_string(i); //añade cada caracter a la variable numero, utilizada a lo largo de la clase 
}

//Evalua la cadena de caracteres con sus respetivos operadores entre cada numero 
//Ej si la cadena fuese "1+2-3+4" evaluar_numeros haría lo siguiente: 
//1) 1+2 = 3
//2) 3-3 = 0
//3) 0+4 = 4
//La funcion devolveria el numero 4
int Numeros_del_rey::evaluar_numeros(const string num)
{
	//Los numeros en el codigo ascii empiezan desde el 48, por lo que para transformar un caracter a entero se le resta 48
	//Por ejemplo el numero 1 en el codigo ascii es el 49, la resta seria 49-48 = 1, y así con cada caracter que simbolice un numero 
	int suma = int(num[0]-48); //La variable suma se inicializa con el primer numero de la cadena, que en este caso siempre es 1
	char operacion = '0'; //Operacion se le incializa con un caracter que nunca se encuentra en la cadena 
	for (unsigned int i = 0; i < num.size(); i++) //for que realiza tantas iteraciones como caracteres en la cadena dada como parametro 
	{
		if (i % 2 == 0) //en caso de que i sea par, como ya se explico, significa que num[i] es numero, ya que los operandos siempre estan en una posicion impar
						//teniendo en cuenta que las posiciones empiezan desde 0 
		{
			switch(operacion) //Switch que verifica que valor tiene operacion 
			{
				case '+':
					suma += int(num[i] - 48); //si operacion es suma, se le suma al valor acumulado en suma
					break; 

				case '-':
					suma -= int(num[i] - 48); //si el valor es resta, se le resta al valor que se encuentra en suma 
					break;

				case '*':
					suma *= int(num[i] - 48); //si el valor es multiplicacion, se multiplica el numero al valor acumulado en suma 
					break;

				case '/':
					suma /= int(num[i] - 48);//si el valor es division, se divide suma entre el valor de num[i]
					break;
				default: //En caso de que no haya tomado un operando, simplemente no se hace nada 
					break;
			}
		}
		else {
			operacion = num[i]; //En caso de que no sea un numero par, operacion toma el valor de un operando, por ejemplo: 
								//1+2-4
								//la posicion del caracter '+' es la 1, debido a que se empieza desde 0, por lo que es una posicion impar
								//Se puede denotar que siempre los operadores se encuentran en posiciones impares y los numeros en pares
								//encontes cuando i sea un numero impar, significa que esa posicion es un operador, por lo que la variable operacion toma 
								//el valor de ese caracter 
		}
	}
	return suma; 
}

//Ve que tan alejado esta el valor evaluado al valor que se quiere obtener, introducido por el usuario
int Numeros_del_rey::heuristica(const string num, int final)
{
	int num_evaluar = evaluar_numeros(num); //num_evaluar es el resultado de la funcion evaluar_numeros, del estado actual de los numeros del rey 
	return abs(final - num_evaluar); //se retorna un valor positivo de la suma entre el valor que se quiere obtener y el numero evaluado 
}
//Devuelve un string, que contiene el estado actual de los numeros del rey 
string Numeros_del_rey::devolver_nodo_actual()
{
	return numeros; //retorna numeros, string utilizado a lo largo de la clase 
}

//Constructor 
Busqueda::Busqueda() {

}

//Destructor
Busqueda::~Busqueda() {

}

//Crea un arbol, donde la raiz es simplemente una cadena de nueve numeros "123456789"
void Busqueda::crea_arbol(tipo_nodo_informacion contenido)
{
	tipo_nodo_del_arbol temporal; //nodo que representa la raiz 
	temporal.padre = -1; //como no hay padre, el padre es -1
	temporal.contenido = contenido;
	temporal.hijos.clear(); //Como aun no hay hijos, está vacio el vector hijos 
	arbol_de_busqueda.push_back(temporal); //Se añade el nodo al arbol de busqueda 
}
//Se añade un hijo a un nodo en el arbol de busqueda 
void Busqueda::agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido)
{
	tipo_nodo_del_arbol temporal;//nodo a añadir como hijo 
	temporal.padre = padre; //Su padre es la posicion dada como parametro
	temporal.contenido = contenido; //Su contenido que es el nombre y el costo tambien es dado como parametro 
	temporal.hijos.clear(); //Como es un nodo nuevo aun no tiene hijos 
	arbol_de_busqueda.push_back(temporal); //Se añade el nodo al arbol de busqueda 
	arbol_de_busqueda[padre].hijos.push_back((unsigned int)(arbol_de_busqueda.size() - 1)); //Se añade la posicion del hijo al vector de hijos del padre 
}
//Permite ver si hay un nodo repetido en la misma rama 
bool Busqueda::esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const
{
	int temporal = arbol_de_busqueda[nodo_origen].padre; //Temporal toma como valor la posicion del padre del nodo origen 
	while (temporal != -1) //Va disminuyedo temporal, para recorrer la rama en donde se desea verificar si el nodo esta repetido 
	{
		if (arbol_de_busqueda[temporal].contenido.nombre_del_nodo == nombre_del_nodo) //En caso de que en la rama haya dos nodos con el mismo nombre, devuelve true 
			return true;
		temporal = arbol_de_busqueda[temporal].padre;
	}
	return false; //Si no se encontro el mismo nodo dentro de la rama se devuelve falso 
}

//Funcion que ayuda a ver si no hay un string repetido dentro del mismo vector
//Como este programa va a imprimir en consola todas las posibles combinaciones para llegar a una solucion, en este caso, que evaluar los numeros 
// y que den un numero dado por el usuario
//Ayuda a que no se repitan las mismas soluciones al imprimir en consola, ya que se puede llegar a la misma solucion mediante varias ramas 
bool busca_solucion_repetida(vector<string> a, string b) {
	for (string i : a) //for each del vector a 
	{
		if (b == i) {
			return true; //en caso de la cadena ya se encuentre en el vector, significa que la solucion es repetida y devuelve true 
		}
	}
	return false; //si nunca encontro la solucion dentro del vector devuelve falso 
}
//En esta funcion se va a buscar como ordenando de diferente forma cuatro operadores (+ - * /)
//entre el 1 y el 9, se puede llegar a un numero dado por el usuario
vector<string> Busqueda::busqueda_A(int num_final)
{
	vector<string> resultados; //Vector que guardan los resultados, es decir, cadenas de caracteres evaluadas que si dan como resultado el numero dado por 
							   //el usuario  
	Numeros_del_rey p; //Instancia de la clase Numeros del rey 
	p.crear_numeros(); //Se crea la cadena "123456789"
	tipo_nodo_informacion informacion_del_nodo_inicio;
	tipo_nodo_informacion informacion_del_hijo_a_adicionar;
	Nodo_agenda nodo_actual;
	vector<string> vecinos;//vector que va a guardar constantemente los vecinos del estaod actual de los numeros del rey 
	informacion_del_nodo_inicio.nombre_del_nodo = p.devolver_nodo_actual(); //El nombre del nodo raiz es asignado, que es "123456789"
	crea_arbol(informacion_del_nodo_inicio); //Se crea el arbol con el nodo raiz ya establecido 
	agenda.push({ 0,0 }); //Se añade la posicion 0 a la agenda 
	int contador = 0; //Contador que nos ayuda a actualizar los numeros del rey despues de la primer iteracion en el while 
	while (!agenda.empty()) //ciclo while que dura mientras la agenda no este vacia
	{
		nodo_actual = agenda.top(); //el nodo actual siempre es el ultimo nodo de la cola, ya que este es el que se devuelve 
		if (contador != 0) //En caso de que ya haya más de una iteración en el while, se debe actualizar el string numeros, que simboliza el estado actual de numeros del rey
						   //para poder obtener nuevos vecinos del string actualizado 
		{
			tipo_nodo_del_arbol nodo;
			nodo = arbol_de_busqueda[nodo_actual.posicion];
			string cadena = nodo.contenido.nombre_del_nodo;
			// Crear un vector de caracteres y guardar cada caracter en el vector
			p.actualizar_numeros(cadena);//actualiza la variable numeros de la clase numeros del rey 
		}
		agenda.pop(); //Se borra el elemento de la agenda 
		int cadena_evaluada = p.evaluar_numeros(arbol_de_busqueda[nodo_actual.posicion].contenido.nombre_del_nodo); //evalua la cadena de caracteres actual, y se guarda en la variable  
		if (cadena_evaluada == num_final) //Si es que despues de evaluar la cadena, el resultado es igual al numero final, significa que se ha encontrado una solucion 
		{
			if(!busca_solucion_repetida(resultados, arbol_de_busqueda[nodo_actual.posicion].contenido.nombre_del_nodo)) //Se busca que en el vector respuesta no se encuentre la solucion, para no repetir soluciones 
				resultados.push_back(arbol_de_busqueda[nodo_actual.posicion].contenido.nombre_del_nodo); //Si no esta la solucion, se guarda en el vector resultados 
		}
		vecinos = p.posibles_movimientos(nodo_actual.posicion); //Vecinos guarda los posibles estados a partir del nodo en el arbol actual 
		for (unsigned int i = 0; i < vecinos.size(); i++)
			if (esta_un_nodo_en_ancestros(nodo_actual.posicion, vecinos[i])) //Se verifica que en la misma rama no exista el mismo nodo
																			//En caso de que sí exista, se elimina el string del vector vecinos 
			{
				vecinos.erase(vecinos.begin() + i);
				i--;
			}
		//for ára añadir nuevos nodos al arbol de busqued, partiendo del vector vecinos 
		for (unsigned int i = 0; i < vecinos.size(); i++)
		{
			informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos[i]; //el nombre del nodo a añadir es igual al del vecinos[i]
			informacion_del_hijo_a_adicionar.costo_estimado = p.heuristica(vecinos[i], num_final);//El costo estimado es que tan alejado está del resultado deseado 
			agrega_hijo_a_un_nodo(nodo_actual.posicion, informacion_del_hijo_a_adicionar); //Se añade el nodo al arbol de busqueda 
			agenda.push({ int(arbol_de_busqueda.size() - 1) ,informacion_del_hijo_a_adicionar.costo_estimado }); //Se añade el costo estimado y la posicion el nodo añadido, para que la cola de prioridad
																												//ordene de forma adecuada 
		}
		contador++; //Contador aumenta en uno por cada iteracion del while 
		if (contador >= 100000)//Como es posible que se tarde demasiado tiempo en ver todos los nodos, se pone un condicional para que se detenga el ciclo despues de n operaciones 
			break;  
	}

	return resultados; 
}


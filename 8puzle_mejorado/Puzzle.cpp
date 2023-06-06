#include "Busqueda.h"
#include "Puzzle.h"
#include <unordered_map>
#include<iostream>
#include <fstream>
#pragma warning(disable : 6011)

//Heuristica a utilizar wen 8puzzle
float heuristica(const string& estado) { 
	int n = (int)sqrt(estado.size()); //Raiz del puzzle actual, si es 5x5 es 5, si es 4x4 es 4
	float dist = 0; //Se inicializa la distancia a 

	for (int i = 0; i < (int)estado.size(); i++) { //Un ciclo que recorra la cadena de caracteres 
		if (estado[i] != '0') { //Verifica el condicional que el elemento no sea un espacio en blanco 
			int filaActual = i / n; //La fila actual se obtiene dividiendo i/n, debido a que si por ejemplo 
									//Si i en un 3x3 es 0,1,2 y la raiz es 3, su division va a dar 0, por lo tanto se dirá que está en la fila 0
									//Si i en un 3x3 es 3,4,5, su division dará 1, por lo tanto está en la fila 1, y así sucesivamente, la division de la primer fila dará siempre 0, de la segunda 1 y así

			int columnaActual = i % n; //Para obtener la columna actual, se saca el modulo entre i y n. 
									   //Lo anterior debido a que en la primer columna, el modulo siempre va a dar 0, ya que i en esa posicion, 
									   //siempre será un multiplo de la raiz, en el caso de 3x3 la primera columna i toma los valores de 
									   // 0, 3, 6, que son multiplos de la raiz(3), y posteriormente es como si se utilizara la siguiente formula 
									  // (multiplo + k) % raiz = k. En donde k, es la columna a obtener, empezando desde 0
									  //  Entonces en la segunda columna, que tiene valor de 1, se obtiene así: 
									  // (0+1)%3 = 1, (3+1)%3 = 1, y (6+1)%3 = 1, y así sucesivamente 

			int filaObjetivo, columnaObjetivo; //Fila objetivo y columna objetivo del valor actual de la cadena 
			int peso = 1; // peso adicional, que se multiplicará por la distancia euclidiana 

			// obtiene la posición objetivo de la ficha y ajusta el peso si es necesario
			if (estado[i] >= '1' && estado[i] <= '9') { //Verifica si la ficha actual es un numero o no 
				filaObjetivo = (estado[i] - '1') / n; //En caso de que sea un numero, para obtener la posicion objetivo de ese numero se aplica 
													  //La formula (num -1)/n. Debido a que en este caso se empieza desde 0
													  //En un 3x3, la ficha con numero 3 está en la tercera posicion, en la primer fila, sin embargo si no le quitamos 1
													  // La operación sería 3/3, lo cual sería 1, y queremos que de 0, ya que es la primer fila
													 //Por lo tanto se resta 1, que daría (3-1)/3 = 2/3 = 0

				columnaObjetivo = (estado[i] - '1') % n; //Se aplica la misma logica que filaobjetivo, pero en lugar de dividir se aplica algebra modular
														//La ficha con numero 1 está en la primer columna( que es 0) pero si se hace la operacion 1%3 da 1, y queremos que de 0
														//por lo tanto (1-1)%3 = 0 % 3 = 0, que es la columna correcta 
				if (filaActual != filaObjetivo || columnaActual != columnaObjetivo) { //Condicional si no está en su fila o columna destino la ficha actual 
					peso = 2; //El paso se vuelve 2, que se multiplicará por la distancia euclidiana, lo cual aumentará su valor 
				}
			}
			else {
				//En el codigo ascii, las letras empiezas desde el numero 65, y van consecutivamente A = 65, b = 66  y así consecutivmente 
				//Por lo tanto si queremos obtener su numero equivalente se utiliza la operación Letra Actual - A
				//Por ejemplo la C, que equivale a 67, como sabemos que A es 65, se resta 67 - 65 = 2
				//Para saber su numero sería la resta anterior + 10, ya que en este caso efectivamente C es 12, A es 10, B es 11, y C es 12
				//Sin embargo, debido a que empieza en 0 las filas y columnas, en lugar de sumar 10, se suma 9, ya que esto simboliza la logica de restar -1, en el condicional 
				//anterior
				//Ejemplo C es 12, si hacemos 12%4, en un 4x4, saría 0, pero no esta en la columna 0, está en la columna 3, por lo tanto si aplicamos la logica anterior 
				//(12-1)%4 = 3. Para realizar lo anterior, simplemente se suma 9 en lugar de 10, ya que sería (2+9)%4 = 3
				filaObjetivo = (estado[i] - 'A' + 9) / n;
				columnaObjetivo = (estado[i] - 'A' + 9) % n;
				if (filaActual != filaObjetivo || columnaActual != columnaObjetivo) {
					peso = 2;
				}
			}

			int dx = columnaActual - columnaObjetivo;//diferencia en x es la resta entre la columna actual y columna objetivo 
			int dy = filaActual - filaObjetivo; //Diferencia en y es la resta entre la fila actual y fila objetivo 
			dist += float(peso * sqrt(dx * dx + dy * dy)); //Distancia Euclidiana multiplicada por 1 o dos dependiendo del peso
		}
	}

	return dist;
}



//Funciones del puzzle
//Constructor
Puzzle::Puzzle()
{
	puzzle.clear();
	size_puzzle = 0;
}

//Destructor
Puzzle::~Puzzle()
{
}

//Revuelve el puzzle 
void Puzzle::shuffle()
{
	string ayuda = ""; //variable que va a tomar un valor del puzzle
	srand((unsigned int)time(NULL));

	for (unsigned int i = 0; i < size_puzzle; i++)
	{
		unsigned int aleatorio = rand() % size_puzzle; //Posicion aleatoria que va a tomar la variable ayuda
		ayuda = puzzle.at(aleatorio);
		puzzle.erase(puzzle.begin() + aleatorio); //Se borra ese elemento en el puzzle 
		aleatorio = rand() % size_puzzle; //Se obtiene un nuevo sitio en donde insertar la variable ayuda
		puzzle.insert(puzzle.begin() + aleatorio, ayuda); //Se inserta en el puzzle, en una posicion aleatoria 
	}

}

//Print del puzzle actual 
void Puzzle::mostrar_puzzle()const
{
	int raiz = (int)pow(size_puzzle, 0.5);
	for (unsigned int i = 0; i < size_puzzle; i++)
	{
		if (i % raiz == 0) { //Hace salto de line cada vez que la variable i es multiplo de la raiz
			cout << "\n";
			cout << puzzle.at(i);
		}
		else
			cout << puzzle.at(i);
	}
	cout << "\n";

}

//Devuelve vector con strings de los posibles movimientos(vecinos)
vector<string> Puzzle::posibles_movimientos(int raiz)const
{
	vector<string>posibles_movimientos; //vector en donde se van a guardar cadenas de caracteres, las cuales simbolizan posibles estados del puzzle 
	vector<string>puzzle_temporal; //puzzle temporal va a tener los caracteres actuales en el puzzle  
	string temporal; //caracter a mover por un espacio
	string cadena_de_movimentos = ""; //cadena a añadir a posibles movimientos
	for (int i = 0; i < (int)puzzle.size(); i++) {
		puzzle_temporal = puzzle; //Puzzle temporal toma el valor del puzzle actual 
		//Mov derecha
		if (((i + 1) % raiz) != 0 && i + 1 != size_puzzle) //condicional que verifica que que no esté al final de la fila y que sea el ultimo elemento 
			if (puzzle_temporal.at(i) == "0" && puzzle_temporal.at(i + 1) != "0") { //condicional que verifica si se encontró un espacio(0)
				temporal = puzzle_temporal.at(i + 1); //temporal toma el valor de la derecha
				puzzle_temporal.erase(puzzle_temporal.begin() + i + 1); //Se borra el valor seleccionado 
				puzzle_temporal.insert(puzzle_temporal.begin() + (i), temporal); //Se inserta a un lado del 0, para hacer el intercambio o el movimiento 
				for (unsigned int j = 0; j < (unsigned int)puzzle_temporal.size(); j++)
					cadena_de_movimentos += puzzle_temporal.at(j);//cadena de movimientos, añade los valores puzzle temporal, que ahora es un estado diferente
				posibles_movimientos.push_back(cadena_de_movimentos); //se añade la cadena a posibles movimientos 
				cadena_de_movimentos = ""; //se borra la cadena para los siguientes condicionales 
				puzzle_temporal = puzzle; //puzzle temporal vuelve a tomar su valor original 
			}
		//Mov izquierda
		if (i != raiz && ((i) % raiz) != 0 && (i - 1) != -1) //Condicional verifica que el elemento no esté al inicio de una fila o que sea el primer elemento 
			if (puzzle_temporal.at(i) == "0" && puzzle_temporal.at(i - 1) != "0") { //Verifica si está sobre un espacio 
				temporal = puzzle_temporal.at(i - 1); //se toma el elemento de la izquierda 
				puzzle_temporal.erase(puzzle_temporal.begin() + (i - 1)); //se borra el elemento tomado 
				puzzle_temporal.insert(puzzle_temporal.begin() + (i), temporal); //se inserta en el espacio, para hacer el intercambio 
				for (unsigned int j = 0; j < (unsigned int)puzzle_temporal.size(); j++)
					cadena_de_movimentos += puzzle_temporal.at(j); //cadena de movimientos toma el valor del nuevo estado 
				posibles_movimientos.push_back(cadena_de_movimentos); //se añade a posibles movimientos 
				//se reinicializan las variables 
				cadena_de_movimentos = "";
				puzzle_temporal = puzzle;
			}
		//Mov abajo
		if (i + raiz < (int)size_puzzle) //se verifica que al sumar la raiz, para mover el elemento hacia abajo, no se salga del maximo tamaño posible 
			if (puzzle_temporal.at(i) == "0" && puzzle_temporal.at(i + raiz) != "0") { // se encuentra un espacio 
				temporal = puzzle_temporal.at(i + raiz); //se toma el valor del numero 
				puzzle_temporal.erase(puzzle_temporal.begin() + (i + raiz)); //se borra el numero 
				puzzle_temporal.insert(puzzle_temporal.begin() + (i), temporal); //se unserta donde va el espacio el numero 
				temporal = puzzle_temporal.at(i + 1); //se toma el valor del espacio (0)
				puzzle_temporal.erase(puzzle_temporal.begin() + (i + 1)); //se borra el caracter del espacio 
				puzzle_temporal.insert(puzzle_temporal.begin() + (i + raiz), temporal); //Se inserta donde estaba el numero 
				for (unsigned int j = 0; j < (unsigned int)puzzle_temporal.size(); j++)
					cadena_de_movimentos += puzzle_temporal.at(j);//cadena de movimientos toma el valor del nuevo estado 
				posibles_movimientos.push_back(cadena_de_movimentos);//se añade a posibles movimientos
				//se reinicializan las variables 
				cadena_de_movimentos = "";
				puzzle_temporal = puzzle;
			}
		//Mov arriba
		if (i - raiz >= 0 && i - 1 != -1) //se verifica que al restar la raiz, para mover el elemento hacia arriba, no se salga del minimo tamaño posible 
			if (puzzle_temporal.at(i) == "0" && puzzle_temporal.at(i - raiz) != "0") { //se verifica que haya un espacio 
				temporal = puzzle_temporal.at(i - raiz); //se toma el valor del caracter a mover 
				puzzle_temporal.erase(puzzle_temporal.begin() + (i - raiz)); //se elimina del caracter 
				puzzle_temporal.insert(puzzle_temporal.begin() + (i), temporal); //se mueve a la posicion del espacio 
				temporal = puzzle_temporal.at(i - 1); //se toma el valor del espacio
				puzzle_temporal.erase(puzzle_temporal.begin() + (i - 1)); 
				puzzle_temporal.insert(puzzle_temporal.begin() + (i - raiz), temporal);//Se mueve a donde estaba el caracter 
				for (unsigned int j = 0; j < (unsigned int)puzzle_temporal.size(); j++)
					cadena_de_movimentos += puzzle_temporal.at(j);;//cadena de movimientos toma el valor del nuevo estado
				posibles_movimientos.push_back(cadena_de_movimentos);//se añade a posibles movimientos
				//se reinicializan las variables
				cadena_de_movimentos = "";
				puzzle_temporal = puzzle;
			}

	}
	return posibles_movimientos;
}


//Crea un puzzle de tamaño n
void Puzzle::crear_puzzle(unsigned int n) {
	size_puzzle = n; //tamaño del puzzle a realizar 3x3 = 9, 4x4 = 16

	if (size_puzzle <= 9) { //en caso de que se un 3x3, solo se agrega un espacio 
		for (unsigned int i = 1; i <= size_puzzle; i++)
		{
			if (i < n)
				puzzle.push_back(to_string(i)); //se añaden los numeros
			else
				puzzle.push_back("0"); //se añade el espacio 
		}
	}
	else {//en caso de que sea un puzzle más grande que un 3x3
		string abecedario[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S"
		,"T", "U", "V", "W", "X", "Y", "Z" }; //Letras que simbolizan numeros A = 10, B = 11, C = 12...
		for (unsigned int i = 1; i < size_puzzle - 1; i++)
		{
			if (i <= 9)
				puzzle.push_back(to_string(i)); //En caso de que sea menor o igual a 9, se añade el numero 
			else
				puzzle.push_back(abecedario[i - 10]); //En caso de que sea mayor a 9, se añaden las letras en orden 
		}
		puzzle.push_back("0"); //se añade un espacio 
		puzzle.push_back("0"); //se añade otro espacio 

	}
}

//devuelve una cadena de caracteres de lo que hay en el puzzle
string Puzzle::primer_elemento()const
{
	string puzzle_actual = "";
	if (puzzle.size())
		for (string c: puzzle)
			puzzle_actual += c; //Se añade una cadena de caracteres en caso de que tenga un tamaño mayor a 0 
	return puzzle_actual;
}

//Actualiza el puzzle, esto se hara cada iteracion de busqueda
void Puzzle::actualizar_puzzle(vector<string> actualizar)
{
	puzzle = actualizar; //toma el puzzle, un valor diferente, esto ayuda para generar vecinos en posibles movimientos 
}


//Comrpueba si una linea del puzzle ya esta formada
bool Puzzle::revisar_linea(string cadena, int num_lineas, int raiz)const
{
	string abecedario[26] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S"
		,"T", "U", "V", "W", "X", "Y", "Z" }; //letras que simbolizan numeros 
	int size = num_lineas * raiz; //numero de caracteres a revisar que estén en orden, ejemplo: num lineas 1, raiz = 3, se verifica que 3 caracteres estén en su lugar 
								  //en caso de que num_lineas sea 2, sería 2 x 3 = 6, que sería verificar que 6 caracteres estén en su lugar 
	string cadena_ayuda = ""; //Cadena que ayudará a la comparación, la cual se llenará con los valores correctos y en orden  
	for (unsigned int i = 1; i <= (unsigned int)size; i++) { //ciclo que va desde 1 hasta el num de caracteres a añadir, que es size 
		if (i <= 9) 
			cadena_ayuda += to_string(i); //cadena_ayuda se llena con numeros
		else
			cadena_ayuda += abecedario[i - 10]; //cadena ayuda se llena con letras 
	}
	string verificar = cadena.substr(0, size); //verificar toma el numero de caracteres a buscar verificar, ejemplo: 
											   // size = 3, cadena = "189257640", verificar es un substring de tamaño size, que es verificar = "189"
											   //cadena ayuda si está en un orden correcto, por lo tanto cadena ayuda es "123"
	return verificar == cadena_ayuda; //se verifica si caden ayuda es igual a verificar 
}

//Devuelve el size de las filas y de las columnas que hay, es decir, devuelve 3 filas y 3 columnas, o 4 filas y 4 columnas, la raiz del numero total de fichas 
float Puzzle::raiz()const
{
	return (float)pow(size_puzzle, 0.5);
}

//Funciones de busqueda

//Constructor
Busqueda::Busqueda(){
	
}

//Destructor
Busqueda::~Busqueda(){

}

//Crea un arbol nuevo, donde la raiz es el puzzle desordenado 
void Busqueda::crea_arbol(tipo_nodo_informacion contenido)
{
	tipo_nodo_del_arbol temporal; //temporal es nodo a añadir 
	temporal.padre = -1; //no tiene padre, por eso el -1
	temporal.contenido = contenido; //se añade la cadena de caracteres y el costo estimado 
	temporal.hijos.clear(); //por el momento no tiene hijos, por eso está vacio 
	arbol_de_busqueda.push_back(temporal);//añade el elemento al arbol 
}
//Añade un nuevo elemento al arbol de busqueda 
void Busqueda::agrega_hijo_a_un_nodo(int padre, tipo_nodo_informacion contenido)
{
	tipo_nodo_del_arbol temporal; //temporal es el elemento a añadir 
	temporal.padre = padre; //se establece quien es su padre 
	temporal.contenido = contenido; //se añade el nombre del nodo y su costo estimado 
	temporal.hijos.clear(); //no tiene hijos, por lo tanto está vacio 
	arbol_de_busqueda.push_back(temporal); //se añade al arbol de busqueda 
	arbol_de_busqueda[padre].hijos.push_back((unsigned int)(arbol_de_busqueda.size() - 1)); //se añade la posicion del hijo al vector de hijos del padre 
}

//Verifica si un nodo ya se encuentra en la misma rama 
bool Busqueda::esta_un_nodo_en_ancestros(const int nodo_origen, string nombre_del_nodo) const
{
	int temporal = arbol_de_busqueda[nodo_origen].padre; //temporal a localidad en donde se va buscar en el arbol 
	while (temporal != -1) //incio ciclo while 
	{
		if (arbol_de_busqueda[temporal].contenido.nombre_del_nodo == nombre_del_nodo) //verifica que no exista en la misma rama un nodo que tenga el mismo valor al nodo ingresado a la funcion 
			return true;
		temporal = arbol_de_busqueda[temporal].padre; //temporal va tomando el valor de todos los padres, hasta que llega a la raiz 
	}
	return false;
}

//Soluciona el rompecabezas de un n fichas 
bool Busqueda::busqueda_A(Nodo_agenda& nodo_encontrado, int n)
{
	cout << "Rompecabezas desarmado: " << endl;  
	Puzzle p; //Se declara un puzzle nuevo
	p.crear_puzzle(n); //Se utiliza la funcion para generar una cadena de caracteres de tamaño nxn
	p.shuffle(); //Se desordena de forma aleatoria el puzzle, ya creado de una dimension nxn
	p.mostrar_puzzle(); //Se utiliza la funcion "mostrar puzzle" Para que se imprima el puzzle actual, en este caso, desordenado
	cout << endl << "Resolviendo rompecabezas "; 
	int raiz = (int)p.raiz(); //La raiz es un elemento que sirve bastante, debido a que indica aspectas tales como cuando realizar un salto de linea, o ayuda en los movimientos
	tipo_nodo_informacion informacion_del_nodo_inicio;
	tipo_nodo_informacion informacion_del_hijo_a_adicionar;
	Nodo_agenda nodo_actual;
	vector<string> vecinos; //Vector de string, donde se guardaran todos los posibles movimientos realizados en el rompecabezas
	informacion_del_nodo_inicio.nombre_del_nodo = p.primer_elemento(); //devuelve una cadena de caracteres de lo que hay en el puzzle actual
	float costo_uno = heuristica(informacion_del_nodo_inicio.nombre_del_nodo); //Calcula la heuristica inicial del primer estado del puzzle, el cual se va a resolver 
	cout << "con una complejidad de " << costo_uno << ": " << endl;
	crea_arbol(informacion_del_nodo_inicio); //Crea un nuevo arbol donde el nodo raiz es el puzzle desordenado 
	agenda.push({ 0,0 });  //agenda, que tiene una estructura de datos llamada cola de prioridad, lo cual servirá para que ordene la agenda dependiendo de la heuristica
	int contador = 0; //Contador, es el numero de elementos añadidos 
	int num_lineas = 1;  //Num de elineas que se busca resolver en un inicio 

	while (!agenda.empty()) //Inicio del ciclo while 
	{
		//condicion que ayuda a mantener un tamaño maximo de la agenda fijo, lo cual ayuda en la rapidez, pero es mas dificil encontrar la ruta optima 
		//En este caso la agenda si supera un numero dado, borra elementos hasta que quede una agenda más pequeña, y como están ordenados, solo quedan 
		//los nodos mas prometedores. 
		if (agenda.size() > 50)
		{
			priority_queue<Nodo_agenda, vector<Nodo_agenda>, ComparadorNodos> help;
			for (unsigned int i = 0; i <= 5; i++) //Cuando llega a un tamaño de 50, borramos los elementos de la agenda hasta que queden 5 elementos 
			{
				Nodo_agenda temp = agenda.top();
				agenda.pop();
				help.push(temp); //help se llena con n nodos, en este caso 5
			}
			while (!agenda.empty()) {
				agenda.pop(); //se vacia la agenda 
			}
			agenda = help; //agenda se iguala a help 
		}
		nodo_actual = agenda.top(); //nodo actual es el primer elemento de la agenda 

		//Este contador indica en que iteración se va, lo cual ayuda a que despues de la primer iteracion se actualice el puzzle por alguno de sus vecinos
		//Y con esto, se puedan obtener los nuevos vecinos del puzzle actualizado 
		if (contador != 0) {
			tipo_nodo_del_arbol nodo;
			nodo = arbol_de_busqueda[nodo_actual.posicion];
			string cadena = nodo.contenido.nombre_del_nodo;

			// Crear un vector de caracteres y guardar cada caracter en el vector
			vector<string> caracteres;
			for (char c : cadena) {
				caracteres.push_back(string(1, c));
			}
			p.actualizar_puzzle(caracteres);
		}


		tipo_nodo_del_arbol nodo_a_buscar;
		nodo_a_buscar = arbol_de_busqueda[nodo_actual.posicion];
		//Verifica que alguna, va en orden, linea esté hecha, en caso de que sí
		//Se toma al nodo encontrado como nodo actual, y el número de líneas que se buscan formar, aumenta en uno.  
		if (p.revisar_linea(nodo_a_buscar.contenido.nombre_del_nodo, num_lineas, raiz))
		{
			num_lineas += 1;
			nodo_encontrado = nodo_actual;
		}
		agenda.pop();
		tipo_nodo_del_arbol temporal;
		temporal = arbol_de_busqueda[nodo_actual.posicion];

		vecinos = p.posibles_movimientos(raiz); //Funcion que devuelve los posibles movimientos del estado actual

		for (unsigned int i = 0; i < (unsigned int)vecinos.size(); i++)
			if (esta_un_nodo_en_ancestros(nodo_actual.posicion, vecinos[i])) //Se borran los estados repetidos en la misma rama
			{
				vecinos.erase(vecinos.begin() + i);
				i--;
			}

		for (unsigned int i = 0; i < (unsigned int)vecinos.size(); i++)
		{
			//Se va a ejecutar este condicional en caso de que no haya ninguna fila formada, es decir que nodo encontrado sea -1
			if (nodo_encontrado.posicion == -1) {
				informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos.at(i); //El hijo a añadir es un estado tomado del vector vecinos
				informacion_del_hijo_a_adicionar.costo_estimado = heuristica(informacion_del_hijo_a_adicionar.nombre_del_nodo); //Se calcula el costo estimado con la heuristica
				agrega_hijo_a_un_nodo(nodo_actual.posicion,
					informacion_del_hijo_a_adicionar); //Agrega hijo al arbol
				agenda.push({ int(arbol_de_busqueda.size()-1), informacion_del_hijo_a_adicionar.costo_estimado }); //Se añade a la agenda la posicion, que es el ultimo elemento del arbo de busqueda, y 
																													//el costo del nodo, para que pueda ordenar de forma adecuada 
				contador += 1;
			}
			//Este condicional se ejecuta en caso de que ya se haya formado una linea, es decir, que nodo encontrado ya tenga un valor
			else {
				informacion_del_hijo_a_adicionar.nombre_del_nodo = vecinos.at(i); 
				informacion_del_hijo_a_adicionar.costo_estimado = heuristica(informacion_del_hijo_a_adicionar.nombre_del_nodo);
				int lineas_limites = num_lineas - 1; //Como num de lineas se aumenta cada que se forma una linea, se debe  comprobar que el numero de lineas ya resuelto siga resuelto, por eso el -1
				//Este condicional ayuda a que no se deshagan lineas formadas, ya que comprueba antes de añadir un hijo, que dicho hijo tenga la fila formada, en caso de que no, no se añade. 
				//Lo anterior debido a que una vez que es formada la primera o la primera y segunda fila, no es necesario deshacerla, lo cual limita el numero de estados posibles, lo que hace que 
				//se resuelva más rapido el algoritmo 
				if (lineas_limites > 2) //Para que sean solo dos lineas siempre 
					lineas_limites = 2; 
				if (p.revisar_linea(informacion_del_hijo_a_adicionar.nombre_del_nodo, lineas_limites, raiz)) { //Una vez comprobado que el estado si tiene una fila resuelta, o más, se añade como hijo
					agrega_hijo_a_un_nodo(nodo_actual.posicion,
						informacion_del_hijo_a_adicionar);
					agenda.push({ int(arbol_de_busqueda.size() - 1), informacion_del_hijo_a_adicionar.costo_estimado });
					contador += 1;
					if (informacion_del_hijo_a_adicionar.costo_estimado == 0) //En caso de que el hijo añadido tenga un costo de 0, significa que ya se llegó a la solución, por lo tanto, se puede retornar true
																			   // Y la posición del nodo encontrado es la ultima añadida. 
					{
						nodo_encontrado.posicion = arbol_de_busqueda.size() - 1;
						return true;
					}
				}
			}
		}
		p.mostrar_puzzle();
	}
	return false;
}

//Muestra todos los pasos que siguió para resolver el rompecabezas 
void Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{ 
	//Declaración de variables a utilizar 
	vector<unsigned int> vector_temporal;
	string camino = "";
	vector_temporal.clear();
	tipo_nodo_del_arbol temporal;
	ofstream archivo("Solucion_puzzle", ofstream::out | ofstream::trunc); // Abre el archivo en modo escritura, eliminando su contenido si existe
																		  //out simboliza modo escritura 
																		 //trunc, si tiene contenido lo borra 
	cout << endl << "---------------------------Los movimientos utilizados son: ----------------------------------------" << endl;
	//Inicio ciclo while 
	while (nodo_encontrado != -1)
	{
		vector_temporal.insert(vector_temporal.begin(), nodo_encontrado); //vector_temporal guarda cada posicion de la rama que encontró la solucion 
		temporal = arbol_de_busqueda[nodo_encontrado];
		nodo_encontrado = temporal.padre; // va retrocediendo hasta llegar e la raiz 
	}
	int contador = 0;
	int raiz = (int)pow(temporal.contenido.nombre_del_nodo.size(), 0.5);
	for (unsigned int i : vector_temporal) { //foreach de cada valor en el vector_temporal 
		temporal = arbol_de_busqueda[i]; //temporal toma el valor de cada elemento de arbol
		for (char c : temporal.contenido.nombre_del_nodo) //foreach de cada elemento de la cadena de caracteres, que simboliza cada estado  
		{
			contador += 1;
			if (contador % raiz == 0) //en caso de que se llegue a un valor multiplo de la raiz, se hace salto de linea 
			{
				cout << c << " "; //Imprime el caracter 
				cout << endl;
				if (archivo.is_open()) { //verifica que se pueda abrir 
					archivo << c << " " << endl; // Escribe el contenido en el archivo
				}
			}
			else {
				if (archivo.is_open()) { //verifica que se pueda abrir 
					archivo << c << " "; // Escribe el contenido en el archivo
				}
				cout << c << " "; // imprime el caracter
			}
		}
		cout << endl;
		cout << endl;
		contador = 0;
		if (archivo.is_open()) { //verifica que se pueda abrir 
			archivo << endl<<endl; // Escribe el contenido en el archivo
		}
	}
	archivo.close(); // Cierra el archivo
	cout << endl << "Movimientos utilizados: " << vector_temporal.size() << endl;  //el tamaño del vector temporal es el numero de estados se utilizaron para resolver el puzzle
	cout << "Si se quiere ver la lista completa de movimientos, revistar el archivo txt anexo a la carpeta de 8puzzle_mejorado"; 
}







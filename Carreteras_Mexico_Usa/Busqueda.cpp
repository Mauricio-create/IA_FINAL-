#include "Busqueda.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>  
#include <stddef.h>
#include <cmath>

using namespace std;

#pragma warning(disable : 6011)

Busqueda::Busqueda()
{
    grafo.clear();//Vacia el grafo y el arbol 
    arbol_de_busqueda.clear();
}

Busqueda::~Busqueda()
{

}
//Lee un csv y crea un grafo con la información de dicho csv 
bool Busqueda::lee_grafo(string archivo)
{
    string leida;
    tipo_enlace_de_grafo enlace;
    fstream newfile; //crea una variable archivo, que servirá para leer el grafo 
    vector<string> vector_de_cadenas;
    grafo.clear();
    newfile.open(archivo, ios::in); //Abre el archivo en donde se contiene el grafo
    if (newfile.is_open())
    {
        getline(newfile, leida); //lee lo que hay en una linea del csv 
        while (getline(newfile, leida))
        {
            vector_de_cadenas.clear();
            stringstream cadena(leida);
            string temporal;
            while (getline(cadena, temporal, ','))
                vector_de_cadenas.push_back(temporal); //Se añade a vector de cadenas los elementos de la linea 
            //Se asignan las variables del tipo grafo, ya previamente guardadas en vector de cadenas 
            enlace.nodo_1 = vector_de_cadenas[0];
            enlace.costo_nodo_1 = (float)atof(vector_de_cadenas[1].c_str());
            enlace.posicion_x_nodo_1 = (float)atof(vector_de_cadenas[2].c_str());
            enlace.posicion_y_nodo_1 = (float)atof(vector_de_cadenas[3].c_str());
            enlace.nodo_2 = vector_de_cadenas[4];
            enlace.costo_nodo_2 = (float)atof(vector_de_cadenas[5].c_str());
            enlace.posicion_x_nodo_2 = (float)atof(vector_de_cadenas[6].c_str());
            enlace.posicion_y_nodo_2 = (float)atof(vector_de_cadenas[7].c_str());
            enlace.costo_del_enlace = (float)atof(vector_de_cadenas[8].c_str());
            grafo.push_back(enlace); //se añade un elemento del grafo a un vector 
        }
        //se cierra el archivo 
        newfile.close();
        return true;
    }
    else
        return false; //en caso de que no se haya podido leer 
}
//Devuelve vecinos de un nodo en cuestion, almacena los vecincos dentro de un vector 
void Busqueda::devuelve_vecinos_grafo_no_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const
{
    vecinos.clear();
    tipo_enlace_de_grafo temporal;
    for (size_t i = 0; i < grafo.size(); i++)
        //En caso de que el nodo a buscar sea el nodo1, se añade al vector vecinos 
        if (grafo[i].nodo_1 == nodo)
            vecinos.push_back(grafo[i]);
        //En caso de que el nodo a buscar sea el nodo2, simplemente se cambia de lugar el nodo1 y el nodo1, para poder añadir como nodo a buscar el nodo1 
        else if (grafo[i].nodo_2 == nodo)
        {
            temporal.nodo_1 = grafo[i].nodo_2;//Cambio de lugar entre nodo1 y nodo 2
            temporal.costo_nodo_1 = grafo[i].costo_nodo_2;
            temporal.posicion_x_nodo_1 = grafo[i].posicion_x_nodo_2;
            temporal.posicion_y_nodo_1 = grafo[i].posicion_y_nodo_2;
            temporal.nodo_2 = grafo[i].nodo_1;
            temporal.costo_nodo_2 = grafo[i].costo_nodo_1;
            temporal.posicion_x_nodo_2 = grafo[i].posicion_x_nodo_1;
            temporal.posicion_y_nodo_2 = grafo[i].posicion_y_nodo_1;
            temporal.costo_del_enlace = grafo[i].costo_del_enlace;
            vecinos.push_back(temporal);
        }

}
//El grafo dirigido solo va de nodo1 a nodo2, por lo que siempre se busca el que el nodo a buscar sea el nodo1 
void Busqueda::devuelve_vecinos_grafo_dirigido(string nodo, vector<tipo_enlace_de_grafo>& vecinos) const
{
    vecinos.clear();
    tipo_enlace_de_grafo temporal;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == nodo)
            vecinos.push_back(grafo[i]);//solo se añade en caso de que el nodo a buscar sea el nodo1 
}
//Devuelve la informacion de un elemento del grafo 
bool Busqueda::devuelve_informacion_de_un_vertice_del_grafo(string nodo, vector<tipo_nodo_del_arbol> arbol,
    int nodo_padre, tipo_nodo_informacion& informacion) const
{
    //inicializan las variables 
    float costo_acumulado_del_padre = 0.0f;
    string nombre_del_nodo_padre = "";
    if (nodo_padre != -1) //en caso de que no sea la raiz 
    {
        costo_acumulado_del_padre = arbol[nodo_padre].contenido.costo_acumulado; //Costo acumulado de padre se obtiene del arbol 
        nombre_del_nodo_padre = arbol[nodo_padre].contenido.nombre_del_nodo; //nombre del padre
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo &&
                grafo[i].nodo_2 == nombre_del_nodo_padre) //En caso de que el nodo padre esté a la derecha, se obtiene la informacion del nodo1 
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo && //en caso de que el nodo padre esté a la izquierda, se obtiene la informacion del nodo2 
                grafo[i].nodo_1 == nombre_del_nodo_padre)
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2 +
                    costo_acumulado_del_padre +
                    grafo[i].costo_del_enlace;
                return true;
            }
        return false;
    }
    else
    {
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_1 == nodo) //en caso de que nodo este en el nodo1, se devuelve la informacion del nodo1
            {
                informacion.nombre_del_nodo = grafo[i].nodo_1;
                informacion.costo_acumulado = grafo[i].costo_nodo_1;
                return true;
            }
        for (size_t i = 0; i < grafo.size(); i++)
            if (grafo[i].nodo_2 == nodo) //en caso de que nodo este en el nodo2, se devuelve la informacion del nodo2
            {
                informacion.nombre_del_nodo = grafo[i].nodo_2;
                informacion.costo_acumulado = grafo[i].costo_nodo_2;
                return true;
            }
        return false;
    }
}
//Se crea la raiz del arbol 
void Busqueda::crea_arbol(tipo_nodo_informacion contenido, vector<tipo_nodo_del_arbol>& arbol_creado)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = -1; //no tiene posicion del padre
    temporal.profundidad = 0;//no tiene profundidad
    temporal.contenido = contenido;
    temporal.hijos.clear();//no tiene hijos 
    arbol_creado.clear();
    arbol_creado.push_back(temporal);//se añade nodo al arbol de busqueda 
}
//Este metodo agrega un hijo a un nodo 
void Busqueda::agrega_hijo_a_un_nodo(vector<tipo_nodo_del_arbol>& arbol, int padre, tipo_nodo_informacion contenido)
{
    tipo_nodo_del_arbol temporal;
    temporal.padre = padre; //se pone la posicion del padre 
    temporal.profundidad = arbol[padre].profundidad + 1; //se agranda la profundidad 
    temporal.contenido = contenido;
    temporal.hijos.clear(); //no tiene hijos 
    arbol.push_back(temporal); //se añade al arbol 
    arbol[padre].hijos.push_back((unsigned int)(arbol.size() - 1));//Se añade la posicion dle hijo al vector de hijos del padre 
}
//Busca si un nodo está repetido en la misma rama 
bool Busqueda::esta_un_nodo_en_ancestros(vector<tipo_nodo_del_arbol> arbol, const int nodo_origen, string nombre_del_nodo) const
{
    int temporal = arbol[nodo_origen].padre;
    while (temporal != -1)
    {
        if (arbol[temporal].contenido.nombre_del_nodo == nombre_del_nodo)//si se encontro en la misma rama un nodo con el mismo nombre se devuelve true 
            return true;
        temporal = arbol[temporal].padre;//temporal va tomando posicion de los paadres, lo cual hace que vaya de reversa 
    }
    return false;
}

//Algoritmo de busqueda completo, que utiliza de estructura como agenda una pila, por lo cual el arbol se expande en profundidad 
bool Busqueda::busqueda_primero_en_profundidad(string nodo_inicio, string nodo_final, int& nodo_encontrado, int &agenda_max, int& arbol_max, bool dirigido)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_inicio, arbol_de_busqueda, -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda); //se crea un arbol con la raiz en la posicion incial 
    Agenda.clear();
    Agenda.push_back(0);//se agrega la posicion de la raiz a la agenda 
    agenda_max = 0; //numero maximo de elementos que va a contener la agenda  
    arbol_max = 0; //numero maximo de elementos que va a contener el arbol 
    while (!Agenda.empty())
    {   
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)//busca si ya se llegó al destino 
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        if(dirigido == false)//Ve si el grafo va a ser dirigido o no, con la variable booleana del grafo dirigido, y se añaden los nodos al vector de vecinos 
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2)) //ve si hay nodos repetidos en los ancestros 
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_del_grafo(vecinos[i].nodo_2,
                arbol_de_busqueda, nodo_actual,
                informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual,
                informacion_del_hijo_a_adicionar);//añade un hijo al arbol de busqueda 
            Agenda.insert(Agenda.begin(), (unsigned int)(arbol_de_busqueda.size() - 1));//agenda con funcion de pila 
        }
        if (Agenda.size() > agenda_max)
            agenda_max = Agenda.size(); 
        if (arbol_de_busqueda.size() > arbol_max)
            arbol_max = arbol_de_busqueda.size();
    }
    return false;
}
//Busqueda en donde su agenda tiene la estructura de una cola, lo que hace que el arbol se expanda a lo ancho, y busque la ruta más corta 
bool Busqueda::busqueda_a_lo_ancho(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    agenda_max = 0;
    arbol_max = 0;
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)//Si ya encontró la solucion devuelve true 
        {
            nodo_encontrado = nodo_actual;
            return true;
        }

        if (dirigido == false)
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_del_grafo(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));//agenda que hace funcion de una cola 
        }
        if (Agenda.size() > agenda_max)
            agenda_max = Agenda.size();
        if (arbol_de_busqueda.size() > arbol_max)
            arbol_max = arbol_de_busqueda.size();
    }
    return false;
}
//Busqueda con profundidad, pero establece un limite de profundidad para el arbol, la agenda igual es una pila. 
bool Busqueda::busqueda_profundidad_limitada(string nodo_inicio, string nodo_final,
    unsigned int limite_de_profundidad, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    agenda_max = 0;
    arbol_max = 0;
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
        if (arbol_de_busqueda[nodo_actual].profundidad < limite_de_profundidad)//solo añade elementos en caso de que no se haya llegado a la profundidad maxima 
        {
            if (dirigido == false)
                devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
            else
                devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

            for (unsigned int i = 0; i < vecinos.size(); i++)
                if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
                {
                    vecinos.erase(vecinos.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos.size(); i++)
            {
                devuelve_informacion_de_un_vertice_del_grafo(vecinos[i].nodo_2, arbol_de_busqueda,
                    nodo_actual, informacion_del_hijo_a_adicionar);
                agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
                Agenda.insert(Agenda.begin(), (unsigned int)(arbol_de_busqueda.size() - 1));
            }
        }
        if (Agenda.size() > agenda_max)
            agenda_max = Agenda.size();
        if (arbol_de_busqueda.size() > arbol_max)
            arbol_max = arbol_de_busqueda.size();
    }
    return false;
}

//Algoritmo en donde se va sumando un numero a la profundidad máxima, y se ejecuta cada vez desde cero el algoritmo de profundidad limitada 
bool Busqueda::busqueda_profundidad_iterativa(string nodo_inicio, string nodo_final,
    unsigned int limite_de_profundidad, unsigned int incremento_de_profundidad,
    int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido)
{
    unsigned int profundidad_actual = limite_de_profundidad;
    do
    {
        if (busqueda_profundidad_limitada(nodo_inicio, nodo_final,
            profundidad_actual, nodo_encontrado, agenda_max,arbol_max, dirigido))
            return true;
        profundidad_actual += incremento_de_profundidad;
    } while (true);
    return false;
}

//Verifica si tienen un nodo en comun dos agenda, lo que ayuda a terminar el algoritmo de busqueda bidireccional 
bool Busqueda::existe_un_nodo_comun_en_las_agendas(vector<unsigned int> agenda_1, vector<unsigned int> agenda_2,
    int& nodo_comun_inicio, int& nodo_comun_final) const
{
    for (auto elemento_agenda_1 = agenda_1.begin(); elemento_agenda_1 != agenda_1.end(); elemento_agenda_1++)
        for (auto elemento_agenda_2 = agenda_2.begin(); elemento_agenda_2 != agenda_2.end(); elemento_agenda_2++)
            if (arbol_de_busqueda_desde_el_inicio[*elemento_agenda_1].contenido.nombre_del_nodo ==
                arbol_de_busqueda_desde_el_final[*elemento_agenda_2].contenido.nombre_del_nodo) //Ve que una posicion de las agendas tenga el mismo nodo en su respectivo arbol de busqueda 
            {
                nodo_comun_inicio = *elemento_agenda_1;//Si es así, ya se asigna como nodo en comun entre las dos agendas 
                nodo_comun_final = *elemento_agenda_2;
                return true;
            }
    return false;
}

//Algoritmo de busqueda, que busca desde un principio mediante busqueda a lo ancho, y busca desde el final con busqueda en profundidad, y cuando ambos se encuentren, significa que ya se llegó a lasolución
//Este algoritmo ayuda mucho a la velocidad 
bool Busqueda::busqueda_bidireccional(string nodo_inicio, string nodo_final, int& nodo_encontrado_desde_el_inicio,
    int& nodo_encontrado_desde_el_final, int& agenda_max, int& arbol_max, bool dirigido)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_nodo_final;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    int nodo_actual_desde_el_inicio = 0;
    int nodo_actual_desde_el_final = 0;
    vector<tipo_enlace_de_grafo> vecinos_desde_el_inicio;
    vector<tipo_enlace_de_grafo> vecinos_desde_el_final;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_inicio, arbol_de_busqueda_desde_el_inicio,
        -1, informacion_del_nodo_inicio))
        return false;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_final, arbol_de_busqueda_desde_el_final,
        -1, informacion_del_nodo_final))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda_desde_el_inicio);
    crea_arbol(informacion_del_nodo_final, arbol_de_busqueda_desde_el_final);
    Agenda_desde_el_inicio.clear();
    Agenda_desde_el_final.clear();
    Agenda_desde_el_inicio.push_back(0);
    Agenda_desde_el_final.push_back(0);
    agenda_max = 0;
    arbol_max = 0;
    while (true)
    {
        if (Agenda_desde_el_inicio.empty() && Agenda_desde_el_final.empty())
            return false;
        //Algoritmo de busqueda a lo ancho, que empieza desde el principio 
        if (!Agenda_desde_el_inicio.empty())
        {
            nodo_actual_desde_el_inicio = Agenda_desde_el_inicio.front();
            Agenda_desde_el_inicio.erase(Agenda_desde_el_inicio.begin());
            if (arbol_de_busqueda_desde_el_inicio[nodo_actual_desde_el_inicio].contenido.nombre_del_nodo == nodo_final)
            {
                nodo_encontrado_desde_el_inicio = nodo_actual_desde_el_inicio;
                nodo_encontrado_desde_el_final = -1;
                return true;
            }
            if (dirigido == false)
                devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda_desde_el_inicio[nodo_actual_desde_el_inicio].contenido.nombre_del_nodo,
                    vecinos_desde_el_inicio);
            else
                devuelve_vecinos_grafo_dirigido(arbol_de_busqueda_desde_el_inicio[nodo_actual_desde_el_inicio].contenido.nombre_del_nodo,
                    vecinos_desde_el_inicio);

            for (unsigned int i = 0; i < vecinos_desde_el_inicio.size(); i++)
                if (esta_un_nodo_en_ancestros(arbol_de_busqueda_desde_el_inicio,
                    nodo_actual_desde_el_inicio,
                    vecinos_desde_el_inicio[i].nodo_2))
                {
                    vecinos_desde_el_inicio.erase(vecinos_desde_el_inicio.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos_desde_el_inicio.size(); i++)
            {
                devuelve_informacion_de_un_vertice_del_grafo(vecinos_desde_el_inicio[i].nodo_2,
                    arbol_de_busqueda_desde_el_inicio,
                    nodo_actual_desde_el_inicio,
                    informacion_del_hijo_a_adicionar);
                agrega_hijo_a_un_nodo(arbol_de_busqueda_desde_el_inicio,
                    nodo_actual_desde_el_inicio,
                    informacion_del_hijo_a_adicionar);
                Agenda_desde_el_inicio.push_back((unsigned int)(arbol_de_busqueda_desde_el_inicio.size() - 1));
            }
        }
        //Algoritmo de busqueda por profundidad, que empieza desde el final 
        if (!Agenda_desde_el_final.empty())
        {
            nodo_actual_desde_el_final = Agenda_desde_el_final.front();
            Agenda_desde_el_final.erase(Agenda_desde_el_final.begin());
            if (arbol_de_busqueda_desde_el_final[nodo_actual_desde_el_final].contenido.nombre_del_nodo == nodo_inicio)
            {
                nodo_encontrado_desde_el_inicio = -1;
                nodo_encontrado_desde_el_final = nodo_actual_desde_el_final;
                return true;
            }
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda_desde_el_final[nodo_actual_desde_el_final].contenido.nombre_del_nodo,
                vecinos_desde_el_final);

            if (dirigido == false)
                devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda_desde_el_final[nodo_actual_desde_el_final].contenido.nombre_del_nodo,
                vecinos_desde_el_final);
            else
                devuelve_vecinos_grafo_dirigido(arbol_de_busqueda_desde_el_final[nodo_actual_desde_el_final].contenido.nombre_del_nodo,
                    vecinos_desde_el_final);

            for (unsigned int i = 0; i < vecinos_desde_el_final.size(); i++)
                if (esta_un_nodo_en_ancestros(arbol_de_busqueda_desde_el_final,
                    nodo_actual_desde_el_final,
                    vecinos_desde_el_final[i].nodo_2))
                {
                    vecinos_desde_el_final.erase(vecinos_desde_el_final.begin() + i);
                    i--;
                }
            for (unsigned int i = 0; i < vecinos_desde_el_final.size(); i++)
            {
                devuelve_informacion_de_un_vertice_del_grafo(vecinos_desde_el_final[i].nodo_2,
                    arbol_de_busqueda_desde_el_final,
                    nodo_actual_desde_el_final,
                    informacion_del_hijo_a_adicionar);
                agrega_hijo_a_un_nodo(arbol_de_busqueda_desde_el_final,
                    nodo_actual_desde_el_final,
                    informacion_del_hijo_a_adicionar);
                Agenda_desde_el_final.push_back((unsigned int)(arbol_de_busqueda_desde_el_final.size() - 1));
            }
        }
        if (existe_un_nodo_comun_en_las_agendas(Agenda_desde_el_inicio, Agenda_desde_el_final,
            nodo_encontrado_desde_el_inicio, nodo_encontrado_desde_el_final)) //Verifica que haya un nodo en comun, lo que significa que ya encontró una ruta 
            return true;
        if (Agenda_desde_el_final.size()+Agenda_desde_el_inicio.size() > agenda_max)
            agenda_max = Agenda_desde_el_final.size() + Agenda_desde_el_inicio.size(); //Maxima cantidad de elementos que tienen ambas agendas 
        if (arbol_de_busqueda_desde_el_final.size()+arbol_de_busqueda_desde_el_inicio.size() > arbol_max)
            arbol_max = arbol_de_busqueda_desde_el_final.size() + arbol_de_busqueda_desde_el_inicio.size();//Maxima cantidad de elementos que tienen ambos arboles  
    }
    return false;
}
//Imprime la ruta encontrada 
string Busqueda::devuelve_la_ruta_encontrada(int nodo_encontrado) const
{
    vector<unsigned int> temporal;
    string camino = "";
    temporal.clear();
    while (nodo_encontrado != -1)
    {
        temporal.push_back(nodo_encontrado);
        nodo_encontrado = arbol_de_busqueda[nodo_encontrado].padre;
    }
    for (int i = (int)(temporal.size() - 1); i >= 0; i--)
        camino = camino + " - " + arbol_de_busqueda[temporal[i]].contenido.nombre_del_nodo;
    camino.erase(camino.begin(), camino.begin() + 3);
    return camino;
}
//Imprime la ruta encontrada en la busqueda bidireccional 
string Busqueda::devuelve_la_ruta_encontrada_busqueda_bidireccional(int nodo_encontrado_desde_el_inicio,
    int nodo_encontrado_desde_el_final) const
{
    vector<unsigned int> temporal;
    string camino_desde_el_inicio = "";
    string camino_desde_el_final = "";
    if (nodo_encontrado_desde_el_inicio != -1)
    {
        temporal.clear();
        while (nodo_encontrado_desde_el_inicio != -1)
        {
            temporal.push_back(nodo_encontrado_desde_el_inicio);
            nodo_encontrado_desde_el_inicio = arbol_de_busqueda_desde_el_inicio[nodo_encontrado_desde_el_inicio].padre;
        }
        for (int i = (int)(temporal.size() - 1); i >= 0; i--)
            camino_desde_el_inicio = camino_desde_el_inicio + " - " +
            arbol_de_busqueda_desde_el_inicio[temporal[i]].contenido.nombre_del_nodo;
    }
    camino_desde_el_inicio.erase(camino_desde_el_inicio.begin(), camino_desde_el_inicio.begin() + 3);
    if (nodo_encontrado_desde_el_final != -1)
    {
        temporal.clear();
        nodo_encontrado_desde_el_final = arbol_de_busqueda_desde_el_final[nodo_encontrado_desde_el_final].padre;
        while (nodo_encontrado_desde_el_final != -1)
        {
            temporal.push_back(nodo_encontrado_desde_el_final);
            nodo_encontrado_desde_el_final = arbol_de_busqueda_desde_el_final[nodo_encontrado_desde_el_final].padre;
        }
        for (int i = (int)(temporal.size() - 1); i >= 0; i--)
            camino_desde_el_final = arbol_de_busqueda_desde_el_final[temporal[i]].contenido.nombre_del_nodo + " - " + camino_desde_el_final;
        camino_desde_el_final.erase(camino_desde_el_final.end() - 3, camino_desde_el_final.end());
    }
    return camino_desde_el_inicio + " - " + camino_desde_el_final;
}
//Busqueda glotona, donde la agenda solo tiene un elemento siempre, y ese elemento siempre es el de menor costo acumulado, es un algoritmo que no es completo 
bool Busqueda::busqueda_ascenso_a_la_colina(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& arbol_max, bool dirigido)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    unsigned int mejor_nodo = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    arbol_max = 0;
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }

        if (dirigido == false)
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_del_grafo(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
        if (Agenda.size() == 0)
            return false;
        mejor_nodo = Agenda[0];
        for (unsigned int i = 1; i < Agenda.size(); i++)
            if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado <
                arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado)
                mejor_nodo = Agenda[i];//nodo con menor costo acumulado 
        Agenda.clear();
        Agenda.push_back(mejor_nodo);//se añade el nodo con el menor costo acumulado 

        if (arbol_de_busqueda.size() > arbol_max)
            arbol_max = arbol_de_busqueda.size();
    }
    return false;
}
//Algoritmo que no limita el tamaño de la agenda, sin embargo si ordena la agenda conforme el nodo con menor costo acumulado 
bool Busqueda::busqueda_primero_el_mejor(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    unsigned int temporal = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    agenda_max = 0;
    arbol_max = 0;
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }
       
        if (dirigido == false)
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_del_grafo(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
        if (!Agenda.empty())
            for (unsigned int i = 0; i < Agenda.size() - 1; i++)//ordenacion de la agenda, usando burbuja 
                for (unsigned int j = i + 1; j < Agenda.size(); j++)
                    if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado >
                        arbol_de_busqueda[Agenda[j]].contenido.costo_acumulado)
                    {
                        temporal = Agenda[i];
                        Agenda[i] = Agenda[j];
                        Agenda[j] = temporal;
                    }
        if (Agenda.size() > agenda_max)
            agenda_max = Agenda.size();
        if (arbol_de_busqueda.size() > arbol_max)
            arbol_max = arbol_de_busqueda.size();
    }
    return false;
}
//Algoritmo que igual ordena la agenda, sin embargo limita el tamaño de la agenda, que en este caso es tamaño k 
bool Busqueda::busqueda_k_beans(string nodo_inicio, string nodo_final, unsigned int k, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int nodo_actual = 0;
    unsigned int temporal = 0;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    agenda_max = k;
    arbol_max = 0;
    while (!Agenda.empty())
    {
        nodo_actual = Agenda.front();
        Agenda.erase(Agenda.begin());
        if (arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo == nodo_final)
        {
            nodo_encontrado = nodo_actual;
            return true;
        }

        if (dirigido == false)
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);
        else
            devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[nodo_actual].contenido.nombre_del_nodo, vecinos);

        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, nodo_actual, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_del_grafo(vecinos[i].nodo_2, arbol_de_busqueda,
                nodo_actual, informacion_del_hijo_a_adicionar);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, nodo_actual, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
        if (!Agenda.empty())
            for (unsigned int i = 0; i < Agenda.size() - 1; i++)//ordenacion burbuja 
                for (unsigned int j = i + 1; j < Agenda.size(); j++)
                    if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado > arbol_de_busqueda[Agenda[j]].contenido.costo_acumulado)
                    {
                        temporal = Agenda[i];
                        Agenda[i] = Agenda[j];
                        Agenda[j] = temporal;
                    }
        if (arbol_de_busqueda.size() > arbol_max)
            arbol_max = arbol_de_busqueda.size();
        if (Agenda.size() > k)//limita el tamaño de la agenda 
            Agenda.erase(Agenda.begin() + k, Agenda.end());
    }
    return false;
}
//Algoritmo de busqueda que busca diversas soluciones, hasta que encuentra la de menor costo acumulado. Al encontrar una solucion, elimina los datos de la agenda que no son prometedores, o que tienen mayor costo 
 //que la solucion encontrada 
bool Busqueda::busqueda_branch_and_bound(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    float costo_del_mejor_nodo = 0.0f;
    int meta_temporal = -1;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    Agenda.clear();
    Agenda.push_back(0);
    agenda_max = 0;
    arbol_max = 0;
    while (!Agenda.empty())
    {
        mejor_nodo = Agenda[0];
        posicion_del_mejor_nodo = 0;
        costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado;
        for (unsigned int i = 1; i < Agenda.size(); i++)
            if (costo_del_mejor_nodo >
                (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado))
            {
                mejor_nodo = Agenda[i];
                posicion_del_mejor_nodo = i;
                costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado;
            }
        Agenda.erase(Agenda.begin() + posicion_del_mejor_nodo);
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == nodo_final)
        {
            if (meta_temporal == -1)
                meta_temporal = mejor_nodo;
            else
                if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado >
                    arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado)
                    meta_temporal = mejor_nodo; //solucion o meta temporal encontrada 
            for (unsigned int i = 0; i < Agenda.size(); i++)//poda la agenda si el costo es mayor 
                if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado >=
                    arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                {
                    Agenda.erase(Agenda.begin() + i);
                    i--;
                }
            if (Agenda.empty())
            {
                nodo_encontrado = meta_temporal;
                return true;
            }
        }
        if (dirigido == false)
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        else
            devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);

        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, mejor_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_del_grafo(vecinos[i].nodo_2, arbol_de_busqueda,
                mejor_nodo, informacion_del_hijo_a_adicionar);
            if (meta_temporal != -1)
                if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado <
                    informacion_del_hijo_a_adicionar.costo_acumulado)
                    continue;
            agrega_hijo_a_un_nodo(arbol_de_busqueda, mejor_nodo, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
        if (Agenda.size() > agenda_max)
            agenda_max = Agenda.size();
        if (arbol_de_busqueda.size() > arbol_max)
            arbol_max = arbol_de_busqueda.size();
    }
    nodo_encontrado = meta_temporal;
    return meta_temporal != -1;
}
//Obtiene la distancia euclidiana, para encaminar al algoritmo, y obtener un costo estimado hacia el destino, utilizado en el algoritmo A* 
float Busqueda::calcula_heuristica_a_la_meta(string nodo_actual, string meta) const
{
    float calculo = 0.0f;
    float x1 = 0.0f;
    float y1 = 0.0f;
    float x2 = 0.0f;
    float y2 = 0.0f;
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == nodo_actual)
        {
            x1 = grafo[i].posicion_x_nodo_1;
            y1 = grafo[i].posicion_y_nodo_1;
            break;
        }
        else if (grafo[i].nodo_2 == nodo_actual)
        {
            x1 = grafo[i].posicion_x_nodo_2;
            y1 = grafo[i].posicion_y_nodo_2;
            break;
        }
    for (size_t i = 0; i < grafo.size(); i++)
        if (grafo[i].nodo_1 == meta)
        {
            x2 = grafo[i].posicion_x_nodo_1;
            y2 = grafo[i].posicion_y_nodo_1;
            break;
        }
        else if (grafo[i].nodo_2 == meta)
        {
            x2 = grafo[i].posicion_x_nodo_2;
            y2 = grafo[i].posicion_y_nodo_2;
            break;
        }
    calculo = (float)pow(pow(x2 - x1, 2) + pow(y2 - y1, 2), 0.5);//Distancia euclidiana 
    return calculo;
}
//Algoritmo que encuentra varias soluciones, pero despues de encontrar la primera, solo acepta soluciones con menor costo, y así cada vez, para encontrar la solucion optima 
//Para encaminar la busqueda se usa la variable costo estimado, que es la distancia euclidiana de donde se encuentra y el destino a donde se quiere llegar 
bool Busqueda::busqueda_A_estrella(string nodo_inicio, string nodo_final, int& nodo_encontrado, int& agenda_max, int& arbol_max, bool dirigido)
{
    tipo_nodo_informacion informacion_del_nodo_inicio;
    tipo_nodo_informacion informacion_del_hijo_a_adicionar;
    unsigned int mejor_nodo = 0;
    unsigned int posicion_del_mejor_nodo = 0;
    float costo_del_mejor_nodo = 0.0f;
    int meta_temporal = -1;
    vector<tipo_enlace_de_grafo> vecinos;
    if (!devuelve_informacion_de_un_vertice_del_grafo(nodo_inicio, arbol_de_busqueda,
        -1, informacion_del_nodo_inicio))
        return false;
    crea_arbol(informacion_del_nodo_inicio, arbol_de_busqueda);
    arbol_de_busqueda[0].contenido.costo_estimado = calcula_heuristica_a_la_meta(nodo_inicio, nodo_final);
    Agenda.clear();
    Agenda.push_back(0);
    agenda_max = 0;
    arbol_max = 0;
    while (!Agenda.empty())
    {
        mejor_nodo = Agenda[0];
        posicion_del_mejor_nodo = 0;
        costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado +
            arbol_de_busqueda[mejor_nodo].contenido.costo_estimado;
        for (unsigned int i = 1; i < Agenda.size(); i++)
            if (costo_del_mejor_nodo >
                (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado +
                    arbol_de_busqueda[Agenda[i]].contenido.costo_estimado))
            {
                mejor_nodo = Agenda[i];
                posicion_del_mejor_nodo = i;
                costo_del_mejor_nodo = arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado +
                    arbol_de_busqueda[mejor_nodo].contenido.costo_estimado;
            }
        Agenda.erase(Agenda.begin() + posicion_del_mejor_nodo);
        if (arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo == nodo_final)
        {
            if (meta_temporal == -1)
                meta_temporal = mejor_nodo;//solucion o meta temporal encontrada 
            else if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado >
                arbol_de_busqueda[mejor_nodo].contenido.costo_acumulado)
                meta_temporal = mejor_nodo;
            for (unsigned int i = 0; i < Agenda.size(); i++)//Eliminan datos que no daran una solucion optima 
                if (arbol_de_busqueda[Agenda[i]].contenido.costo_acumulado >=
                    arbol_de_busqueda[meta_temporal].contenido.costo_acumulado)
                {
                    Agenda.erase(Agenda.begin() + i);
                    i--;
                }
            if (Agenda.empty())
            {
                nodo_encontrado = meta_temporal;
                return true;
            }
        }
       
        if (dirigido == false)
            devuelve_vecinos_grafo_no_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);
        else
            devuelve_vecinos_grafo_dirigido(arbol_de_busqueda[mejor_nodo].contenido.nombre_del_nodo, vecinos);

        for (unsigned int i = 0; i < vecinos.size(); i++)
            if (esta_un_nodo_en_ancestros(arbol_de_busqueda, mejor_nodo, vecinos[i].nodo_2))
            {
                vecinos.erase(vecinos.begin() + i);
                i--;
            }
        for (unsigned int i = 0; i < vecinos.size(); i++)
        {
            devuelve_informacion_de_un_vertice_del_grafo(vecinos[i].nodo_2, arbol_de_busqueda,
                mejor_nodo, informacion_del_hijo_a_adicionar);
            if (meta_temporal != -1)
                if (arbol_de_busqueda[meta_temporal].contenido.costo_acumulado <
                    informacion_del_hijo_a_adicionar.costo_acumulado)
                    continue;
            informacion_del_hijo_a_adicionar.costo_estimado = calcula_heuristica_a_la_meta(vecinos[i].nodo_2,
                nodo_final);
            agrega_hijo_a_un_nodo(arbol_de_busqueda, mejor_nodo, informacion_del_hijo_a_adicionar);
            Agenda.push_back((unsigned int)(arbol_de_busqueda.size() - 1));
        }
        if (Agenda.size() > agenda_max)
            agenda_max = Agenda.size();
        if (arbol_de_busqueda.size() > arbol_max)
            arbol_max = arbol_de_busqueda.size();
    }
    nodo_encontrado = meta_temporal;
    return meta_temporal != -1;
}




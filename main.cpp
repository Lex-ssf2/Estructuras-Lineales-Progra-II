#include <iostream>
#include "ArbolBin.hpp"
#include "ABB.hpp"
#include "ArbolN.hpp"
#include <list>
#include <string>
#include <sstream>

using namespace std;

//LOS METODOS USADOS

template <class Elemento>
void ArbolBin<Elemento>::enlaces(NodoAB<Elemento> *actual, int altura, list<Elemento> &result, int maxAltura){
	int HI,HD;
	HI = altura + 1;
	HD = altura + 1;
	//Contador de altura para saber si la altura es mayor a k, entonces se devuelve
    if(actual == nullptr || altura > maxAltura){
        return;
    }
    if(altura == maxAltura && actual->getHijoIzq() == nullptr && actual->getHijoDer() == nullptr){
		//Si la altura = k entonces, lo añade a una lista de salida, ya que hay que mostrar el recorrido del nodo por salida
		result.push_back(actual->getInfo());
		return;
	}
	//Recorrido preOrden
    enlaces(actual->getHijoIzq(),HI,result,maxAltura);
    enlaces(actual->getHijoDer(),HD,result,maxAltura);
}

template<class Elemento>
list<Elemento> ArbolBin<Elemento>::enlacesConKLongitud(int k){

	//Funcion publicar donde se llama a enlaces que es la protegida
	list<Elemento> salida;
	int alturaTMP = 0;
	this->enlaces(this->NodoRaiz,alturaTMP,salida,k);
	return salida;
}

void imprimirRes(list<string> res);
void insertarLista(list<string> &orden,list<string> &inorden,list<string> &postOrden, string tmp);
void lecturaArbol();

int main() 
{
    int numCasos;
    int i = 0;
    cin >> numCasos;
    while(i < numCasos){
		lecturaArbol();
		++i;
		if(i != numCasos){
			//Esto para evitar un salto de linea de sobra
			cout << "\n";
		}
	}
    return 0;
}

void insertarLista(list<string> &orden,list<string> &inorden,list<string> &postOrden, string tmp){
	
	char aux = '\0';
	string line,test;
	while(aux != '\n' && aux != -1){
		//Obtiene caracter por caracter hasta encontrar el [
		aux = cin.get();
		if(aux != ' ' && aux != ']' && aux != ',' && aux != '='){
			if(aux == '['){
				//devuelve un string hasta ]
				getline(cin,line,']');
				stringstream s(line);

				while (getline(s,test,','))
				{
					//Saca cada parametro que encuentre hasta la , y si tiene un espacio o un caracter negativo lo elimina
					while(test.front() == 32 || test.front() < 0){
						test.erase(test.begin());
					}
					//Lo inserta basado en el tipo de lista que sale en la entrada
					if(tmp == "PREORDEN"){
						orden.push_back(test);
					}else if(tmp == "INORDEN"){
						inorden.push_back(test);
					}else{
						postOrden.push_back(test);
					};
				}
			}
		}
	}
}

void imprimirRes(list<string> res){
	//Imprime la base de salida
	cout << "[";
	for(auto e: res){
		cout << e;
		if(e != res.back())
			cout << ", ";
	}
	cout << "]\n";
}

void lecturaArbol(){
	ArbolBin<string> arbol;
	list<string> orden,inorden,postOrden,res,resAux;
	string tmp;
	int j = 0;
	bool preorden;
	int numRamas;
	cin >> numRamas;
	while(j < 2){
		//Lee las 2 listas XOrden e Inorden
		cin >> tmp;
		//Si detecta un pre orden es para activar la bandera y leer el preOrden e Inorden, en lugar de usar el postOrden
		preorden = (tmp == "PREORDEN" || preorden);
		insertarLista(orden,inorden,postOrden,tmp);
		++j;
	}
	//Saber si usar el preORden e Inorden o postOrden e Inorden
	if(preorden){
		arbol.leerPI(orden,inorden);
		preorden = false;
	}
	else{
		arbol.leerPoI(postOrden,inorden);
	}
	//Llamada de la funcion que devuelve los nodos con K longitud
	res = arbol.enlacesConKLongitud(numRamas);
	//Si la lista es Vacia es pq es ninguno
	if(res.empty()){
			cout << "None\n";
	}
	//Si no es vacia imprime el recorrido de la Raiz al nodo Hoja
	while(!res.empty()){
		resAux = arbol.camino(arbol.getInfo(),res.front());
		res.pop_front();
		imprimirRes(resAux);
	}
	//Limpia las listas
	orden.clear();
	inorden.clear();
	postOrden.clear();
}

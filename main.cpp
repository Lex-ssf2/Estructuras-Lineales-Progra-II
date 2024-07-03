#include <iostream>
#include "ArbolBin.hpp"
#include "ABB.hpp"
#include "ArbolN.hpp"
#include <list>
#include <string>
#include <sstream>

using namespace std;


template <class Elemento>
void ArbolBin<Elemento>::enlaces(NodoAB<Elemento> *actual, int altura, list<Elemento> &result, int maxAltura){
	int HI,HD;
	HI = altura + 1;
	HD = altura + 1;
    if(actual == nullptr || altura > maxAltura){
        return;
    }
    if(altura == maxAltura && actual->getHijoIzq() == nullptr && actual->getHijoDer() == nullptr){
		result.push_back(actual->getInfo());
		return;
	}
    enlaces(actual->getHijoIzq(),HI,result,maxAltura);
    enlaces(actual->getHijoDer(),HD,result,maxAltura);
}

template<class Elemento>
list<Elemento> ArbolBin<Elemento>::enlacesConKLongitud(int k){
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
			cout << "\n";
		}
	}
    return 0;
}

void insertarLista(list<string> &orden,list<string> &inorden,list<string> &postOrden, string tmp){
	
	char aux = '\0';
	string line,test;
	while(aux != '\n' && aux != -1){
		aux = cin.get();
		if(aux != ' ' && aux != ']' && aux != ',' && aux != '='){
			if(aux == '['){
				getline(cin,line,']');
				stringstream s(line);
				while (getline(s,test,','))
				{
					while(test.front() == 32 || test.front() < 0){
						test.erase(test.begin());
					}
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
		cin >> tmp;
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
	/*for(auto e: arbol.postOrden()){
		cout << e;
		if(e != res.back())
			cout << ", ";
	}
	cout << endl;*/
	res = arbol.enlacesConKLongitud(numRamas);
	if(res.empty()){
			cout << "None\n";
	}
	while(!res.empty()){
		resAux = arbol.camino(arbol.getInfo(),res.front());
		res.pop_front();
		imprimirRes(resAux);
	}
	orden.clear();
	inorden.clear();
	postOrden.clear();
}

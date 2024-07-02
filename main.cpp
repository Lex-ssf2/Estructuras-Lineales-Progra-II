#include <iostream>
#include "ArbolBin.hpp"
#include <list>

using namespace std;

void preOrden(ArbolBin<int> Arb){
    if(!Arb.esNulo()){
        cout << Arb.getInfo() << " ";
        preOrden(Arb.getHijoIzq());
        preOrden(Arb.getHijoDer());
    }
}

int main() 
{
    ArbolBin<int> padre, aux;
    padre.setInfo(2); 
    padre.setHijoDer(7);
    padre.setHijoIzq(3);
    padre.insertarNodo(7,9);
    padre.insertarNodo(7,10);
    padre.insertarNodo(9,5);
    padre.insertarNodo(9,23);
    padre.insertarNodo(23,44); 
    padre.camino(10,44); 
    padre.niveles();
    //cout <<   
    //padre.getHijoDer().getHijoDer();
    return 0;
}
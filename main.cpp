#include <iostream>
#include "ArbolBin.hpp"
#include "ABB.hpp"
#include <list>

using namespace std;

int main() 
{
    ArbolBin<int> padre;
    list<int> postorden,inorden;
    postorden.push_back(4);
    postorden.push_back(5);
    postorden.push_back(2);
    postorden.push_back(6);
    postorden.push_back(7);
    postorden.push_back(3);
    postorden.push_back(1);

    inorden.push_back(4);
    inorden.push_back(2);
    inorden.push_back(5);
    inorden.push_back(1);
    inorden.push_back(6);
    inorden.push_back(3);
    inorden.push_back(7);

    padre.leerPoI(postorden,inorden); 
    padre.postOrden();
    padre.eliminarSubArbol(3);
    cout << endl;
    padre.inOrden();

    /*ABB<int> arbol;
    arbol.insertar(15);
    arbol.insertar(16);
    arbol.insertar(20); 
    arbol.insertar(5);
    arbol.insertar(12);
    arbol.insertar(18);
    arbol.insertar(3);
    arbol.insertar(23);
    arbol.insertar(10); 
    arbol.insertar(13); 
    arbol.eliminar(20);
    arbol.niveles();*/
    return 0; 
}
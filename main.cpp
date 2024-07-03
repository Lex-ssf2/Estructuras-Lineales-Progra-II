#include <iostream>
#include "ArbolBin.hpp"
#include "ABB.hpp"
#include "ArbolN.hpp"
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
    cout << padre.getDiametro();


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

    /*ArbolN<int> test, papa;
    test.setInfo(2);
    test.insertarNodo(2,1);
    test.insertarNodo(1,3);
    test.insertarNodo(2,111);
    test.insertarNodo(111,333);
    test.insertarNodo(111,555);
    test.insertarNodo(555,1111);
    test.insertarNodo(555,2222);
    test.insertarNodo(111,666);
    test.insertarNodo(111,777);
    test.insertarNodo(2,5);
    test.insertarNodo(5,7);
    test.insertarNodo(5,14);
    test.insertarNodo(14,32);
    cout << test.LCA(666,1111);*/
    return 0; 
}
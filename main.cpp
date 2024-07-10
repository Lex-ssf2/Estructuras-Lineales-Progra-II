#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include "GrafoD.hpp"
#include "Grafo.hpp"

using namespace std;

int main() 
{
    Grafo<string> test;
    list<string> bloqueo;
    test.agregarVertice("A");
    test.agregarVertice("B");
    test.agregarVertice("C");
    test.agregarVertice("D");
    test.agregarVertice("E");
    test.agregarArco("A","B",2);
    test.agregarArco("A","C",7);
    test.agregarArco("A","D",2);
    test.agregarArco("A","E",6);
    test.agregarArco("B","C",8);
    test.agregarArco("C","D",9);
    //test.agregarArco("B","E",1);
    test.agregarArco("D","E",2);
    
    test.eliminarArco("A","B");
    test.eliminarArco("A","C");
    test.eliminarArco("A","D");
    test.eliminarArco("A","E");
    test.agregarArco("A","B",2);
    test.getPuentes();

    /*for(auto xd : test.getPuentes()){
        for(auto que : xd){
            cout << que << " ";
        }
        cout << endl;
    }*/
    return 0;
}
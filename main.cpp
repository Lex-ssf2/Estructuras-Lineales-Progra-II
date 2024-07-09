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
    test.agregarVertice("A");
    test.agregarVertice("B");
    test.agregarVertice("C");
    test.agregarVertice("D");
    test.agregarVertice("E");
    test.agregarArco("A","E",100);
    test.agregarArco("A","B",1);
    test.agregarArco("A","C",1);
    test.agregarArco("B","C",1);
    test.agregarArco("E","C",1);
    test.agregarArco("D","A",20);
    test.agregarArco("E","D",15);
    test.cicloSimple("A");
    return 0;
}
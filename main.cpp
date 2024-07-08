#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <vector>
#include "GrafoD.hpp"

using namespace std;

int main() 
{
    GrafoD<string> test;
    test.agregarVertice("Paso 1");
    test.agregarVertice("Paso 2");
    test.agregarVertice("Paso 3");
    test.agregarVertice("Paso 4");
    test.agregarVertice("Paso 5");
    test.agregarArco("Paso 1","Paso 3");
    test.agregarArco("Paso 1","Paso 2");
    test.agregarArco("Paso 2","Paso 3");
    test.agregarArco("Paso 3","Paso 5");
    test.agregarArco("Paso 3","Paso 4");
    test.agregarArco("Paso 4","Paso 1");
    test.DFS("Paso 1");
    return 0;
}
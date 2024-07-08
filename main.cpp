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
    vector<string> holaa;
    test.agregarVertice("hola");
    test.agregarVertice("SonGoku");
    test.agregarVertice("hola");
    test.agregarVertice("SonGoku");
    test.agregarVertice("queque a");
    test.agregarArco("SonGoku","hola",7);
    test.setPesoArco("SonGoku","hola",12);
    cout << test.existeVertice("hola") << " " << test.existeVertice("SonGoku") << " " << test.existeVertice("xd") << " " << test.getNVertices() << " " << test.existeArco("hola","SonGoku")
    << " " << test.getTotalArcos() << " " << test.getNArcos("hola") << " " << test.getNArcos("hell yeah") << " " << test.getPesoArco("hola","SonGoku") << " " << test.getPesoArco("hola","xd") 
    << " " << test.getPesoArco("damn","xd");
    test.getVecinos("hola");
    cout << endl;
    test.agregarVertice("oh yeah");
    test.agregarArco("oh yeah","hola");
    test.agregarArco("queque a","hola");
    test.agregarArco("queque a","SonGoku");
    test.agregarArco("queque a","oh yeah"); 
    cout << test.getNArcos("hola") << " " << test.getTotalArcos() << " " << test.getNArcos("SonGoku") << " " << test.getNArcos("oh yeah") << " " << test.getNVertices() << " " << test.getNArcos("queque a") <<  endl;
    for(auto xd: test.getSucesores("queque a")){
        cout << xd << " "; 
    }
    cout << endl << endl;
    test.eliminarVertice("queque a");
    cout << test.getNArcos("hola") << " " << test.getTotalArcos() << " " << test.getNArcos("SonGoku") << " " << test.getNArcos("oh yeah") << " " << test.getNVertices() << " " << test.getNArcos("queque a") << endl;
    return 0;
}
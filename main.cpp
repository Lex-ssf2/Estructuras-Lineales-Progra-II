#include <iostream>
#include "ArbolBin.hpp"
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
    cout << endl;
    padre.inOrden();
    //cout <<    
    //padre.getHijoDer().getHijoDer();
    return 0;
}
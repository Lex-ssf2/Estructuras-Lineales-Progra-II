#include "Cola.h"
#include <iostream>

using namespace std;

template<class e>
Cola<e>::Cola(){
    this->frente = NULL;
    this->final = NULL;
    this->longitud = 0;
}

template<class e>
Cola<e>::~Cola(){
    this->vaciar();
}

template<class e>
void Cola<e>::encolar(e Elemento){
    Nodo<e> *nuevo;
    nuevo = new Nodo<e>(Elemento);
    this->longitud++;
    if(this->longitud <= 1)
    { 
        this->frente = nuevo;
        this->final = nuevo;
        return;
    }
    this->final->setSig(nuevo);
    this->final = this->final->getSig();
    return;
}

template<class e>
void Cola<e>::desencolar(){
    
    if(this->longitud <= 0){
        return;
    }
    Nodo<e> *aux;
    aux = this->frente;
    this->frente = this->frente->getSig();
    this->longitud--;
    delete aux;
}

template<class e>
void Cola<e>::vaciar(){
    while(!this->esVacia())
    {
        this->desencolar();
    }
    this->frente = NULL;
    this->final = NULL;
}

template<class e>
void Cola<e>::invertir(){
    if(this->esVacia())
        return;
    Nodo<e> *actual, *sig, *anterior = NULL;
    this->final = this->frente;
    actual = this->frente;
    for(;actual != NULL; actual = sig){
        sig = actual->getSig();
        actual->setSig(anterior);
        anterior = actual;
    }
    this->frente = anterior;
}

template <class e>
void Cola<e>::imprimir(){
    Nodo<e> *aux;
    if(this->esVacia()){
        cout << endl;
        return;
    }
    for(aux = this->frente;aux != NULL;aux = aux->getSig())
    {
        cout << aux->getInfo() << " , ";
    }
    cout << endl;
}

template<class e>
void Cola<e>::copiar(const Cola &c){
    this->vaciar();
    this->longitud = c.longitud;
    if(c.longitud <= 0)
        return;
    Nodo<e> *actual, *actualCopia = c.frente;
    actual = new Nodo<e>();
    actual->setInfo(actualCopia->getInfo());
    this->frente = actual;
    actualCopia = actualCopia->getSig();
    for(; actualCopia != NULL ; actualCopia = actualCopia->getSig())
    {
        actual->setSig(new Nodo<e>());
        actual = actual->getSig();
        actual->setInfo(actualCopia->getInfo());
    }
    actual->setSig(NULL);
}

template<class e>
e Cola<e>::getFrente(){
    return this->frente->getInfo();
}

template<class e>
e Cola<e>::getFinal(){
    return this->final->getInfo();
}

template<class e>
bool Cola<e>::esVacia(){
    return this->longitud <= 0 ? true : false;
}

template<class e>
Cola<e>& Cola<e>::operator=(const Cola<e> &c){
    this->copiar(&c);
}

template<class e>
Cola<e>& Cola<e>::operator<<(e elem){
    this->encolar(elem);
    return *this;
}

template<class e>
Cola<e>& Cola<e>::operator--(int){
    this->desencolar();
    return *this;
}

template<class e>
Cola<e>& Cola<e>::operator!(){
    this->invertir();
    return *this;
}


#include "Pila.h"
#include <iostream>

using namespace std;

template<class e>
Pila<e>::Pila(){
    this->tope = NULL;
    this->longitud = 0;
}

template<class e>
Pila<e>::Pila(const Pila &p){
    this->tope = NULL;
    this->longitud = 0;
    this->copiar(p);
}

template<class e>
Pila<e>::~Pila(){
    this->vaciar();
}

template<class e>
void Pila<e>::apilar(e Elemento)
{
    Nodo<e> *nuevo;
    nuevo = new Nodo<e>(Elemento);
    this->longitud++;
    if(this->longitud <= 1)
    {
        this->tope = nuevo;
        this->tope->setSig(NULL);
        return;
    }
    nuevo->setSig(this->tope);
    this->tope = nuevo;
}

template<class e>
void Pila<e>::desapilar(){
    if(this->longitud <= 0)
        return;
    this->longitud--;
    Nodo<e> *aux = this->tope;
    if(longitud != 0)
        this->tope = this->tope->getSig();
    else
        this->tope = NULL;
    delete aux;
}

template<class e>
void Pila<e>::vaciar(){
    while(!this->esVacia())
    {
        this->desapilar();
    }
    this->tope = NULL;
}

template<class e>
void Pila<e>::copiar(const Pila &p){
    this->vaciar();
    this->longitud = p.longitud; 
    if(p.longitud <= 0)
        return;
    Nodo<e> *actual, *actualCopia = p.tope;
    actual = new Nodo<e>();
    actual->setInfo(actualCopia->getInfo());
    this->tope = actual;
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
void Pila<e>::invertir(){
    if(this->esVacia())
        return;
    Nodo<e> *actual, *sig, *anterior = NULL;
    actual = this->tope;
    for(;actual != NULL; actual = sig){
        sig = actual->getSig();
        actual->setSig(anterior);
        anterior = actual;
    }
    this->tope = anterior;
}

template <class e>
void Pila<e>::imprimir(){
    Nodo<e> *aux;
    if(this->esVacia()){
        cout << endl;
        return;
    }
    for(aux = this->tope;aux != NULL;aux = aux->getSig())
    {
        cout << aux->getInfo() << " , ";
    }
    cout << endl;
}

template<class e>
e Pila<e>::getTope(){
    return this->tope->getInfo();
}

template<class e>
bool Pila<e>::esVacia(){
    return this->longitud <= 0 ? true : false;
}

template<class e>
int Pila<e>::getLongitud(){
    return this->longitud;
}

template<class e>
Pila<e>& Pila<e>::operator=(const Pila<e> &p){
    this->copiar(&p);
};

template<class e>
Pila<e>& Pila<e>::operator<<(e elem){
    this->apilar(elem);
    return *this;
}

template<class e>
Pila<e>& Pila<e>::operator--(int){
    this->desapilar();
    return *this;
};

template<class e>
Pila<e>& Pila<e>::operator!(){
    this->invertir();
    return *this;
};

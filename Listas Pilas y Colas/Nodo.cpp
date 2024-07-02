#include "Nodo.h"
#include <iostream>

using namespace std;


template <class Elemento>
Nodo<Elemento>::Nodo()
{
    this->sig =  NULL;
}

template <class Elemento>
Nodo<Elemento>::Nodo(Elemento valor)
{
    this->info = valor;
    this->sig =  NULL;
}

template <class Elemento>
Nodo<Elemento>::Nodo(Elemento valor, Nodo<Elemento>* next)
{
    this->info = valor;
    this->sig = next;
}

template <class Elemento>
Elemento Nodo<Elemento>::getInfo(){
    return this->info;
}

template <class Elemento>
Nodo<Elemento>* Nodo<Elemento>::getSig()
{
    return this->sig;
}

template <class Elemento>
void Nodo<Elemento>::setInfo(Elemento e)
{
    this->info = e;
}

template <class Elemento>
void Nodo<Elemento>::setSig(Nodo<Elemento>* next)
{
    this->sig = next;
}

template <class Elemento>
Nodo<Elemento>::~Nodo(){
    this->sig = NULL;
}
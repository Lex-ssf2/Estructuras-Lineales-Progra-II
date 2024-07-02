#ifndef ARBOL_BINBUSQ_HEADER
#define ARBOL_BINBUSQ_HEADER

#include "ArbolBin.hpp"
#include <iostream>

template<class Elemento>
class ABB : public ArbolBin<Elemento>
{
private:
    void insertarNodo(Elemento nuevo, NodoAB<Elemento> *actual);
    void eliminarNodo(Elemento nuevo, NodoAB<Elemento> *actual);
public:
    void insertar(Elemento nuevo);
    void eliminar(Elemento nuevo);
    bool buscar(Elemento e);
    ABB(/* args */);
    ~ABB();
};

template<class Elemento>
ABB<Elemento>::ABB(/* args */)
{
}

template<class Elemento>
ABB<Elemento>::~ABB()
{
}

template<class Elemento>
void ABB<Elemento>::insertarNodo(Elemento nuevo, NodoAB<Elemento> *actual){
    NodoAB<Elemento> *aux;
    if(nuevo < actual->getInfo()){
        if(actual->getHijoIzq() == nullptr){
            aux = new NodoAB<Elemento>;
            aux->setInfo(nuevo);
            actual->setPointerHI(aux);
            return;
        }
        this->insertarNodo(nuevo,actual->getHijoIzq());
        return;
    }
    if(actual->getHijoDer() == nullptr){
        aux = new NodoAB<Elemento>;
        aux->setInfo(nuevo);
        actual->setPointerHD(aux);
        return;
    }
    this->insertarNodo(nuevo,actual->getHijoDer());
}

template<class Elemento>
void ABB<Elemento>::insertar(Elemento nuevo){
    if(this->NodoRaiz == nullptr){
        this->setInfo(nuevo);
        return;
    }
    this->insertarNodo(nuevo, this->NodoRaiz);
}

template<class Elemento>
bool ABB<Elemento>::buscar(Elemento e)
{
    bool encontrado = false;
    if(this->NodoRaiz == nullptr){
        return encontrado;
    }
    NodoAB<Elemento> *aux = this->NodoRaiz;
    while (aux != nullptr && aux->getInfo() != e)
    {
        if(e < aux->getInfo()){
            aux = aux->getHijoIzq();
        }
        else{
            aux = aux->getHijoDer();
        }
    }
    if(aux != nullptr && aux->getInfo() == e){
        encontrado = true;
    }
    return encontrado;
}

#endif
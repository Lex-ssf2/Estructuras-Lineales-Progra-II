#ifndef VERTICE_GRAFO_HEADER
#define VERTICE_GRAFO_HEADER

#include <list>
#include "NodoAdy.hpp"
using namespace std;

template<typename Elemento>
class NodoVertice
{
  protected:
    Elemento info;
    NodoVertice<Elemento> *prox;
    NodoAdy<Elemento> *ady;

  public:
    NodoVertice();
    NodoVertice(Elemento e, NodoVertice<Elemento> *next = nullptr, NodoAdy<Elemento> *Arcos = nullptr);
    ~NodoVertice();

    Elemento getInfo();
    void setInfo(Elemento e);

    NodoVertice<Elemento> getProx();
    void setProx(NodoVertice<Elemento> *next);

    NodoAdy<Elemento> getAdy();
    void setAdy(NodoAdy<Elemento> *arco);

};

template<typename Elemento>
NodoVertice<Elemento>::NodoVertice(){
  this->prox = nullptr;
  this->ady = nullptr;
}

template<typename Elemento>
NodoVertice<Elemento>::NodoVertice(Elemento e, NodoVertice<Elemento> *next, NodoAdy<Elemento> *Arcos){
  this->info = e;
  this->prox = next;
  this->ady = Arcos;
}

template<typename Elemento>
NodoVertice<Elemento>::~NodoVertice(){

}

template<typename Elemento>
Elemento NodoVertice<Elemento>::getInfo(){
  return this->info;
}

template<typename Elemento>
void NodoVertice<Elemento>::setInfo(Elemento e){
  this->info = e;
}

template<typename Elemento>
NodoVertice<Elemento> NodoVertice<Elemento>::getProx(){
  return this->prox;
}

template<typename Elemento>
void NodoVertice<Elemento>::setProx(NodoVertice<Elemento> *next){
  this->prox = next;
}

template<typename Elemento>
NodoAdy<Elemento> NodoVertice<Elemento>::getAdy(){
  return this->ady;
}

template<typename Elemento>
void NodoVertice<Elemento>::setAdy(NodoAdy<Elemento> *arco){
  this->ady = arco;
}

#endif
#ifndef NODO_ADY_GRAFO_HEADER
#define NODO_ADY_GRAFO_HEADER

#include <list>
#include "NodoVertice.hpp"

using namespace std;

template<typename  Elemento>
class NodoVertice;
template<typename  Elemento>
class NodoAdy
{
  protected:
    NodoVertice<Elemento> *info;
    NodoAdy<Elemento> *prox;
    float costo;

  public:
    NodoAdy();
    NodoAdy(NodoVertice<Elemento> *v, float c = 0,NodoAdy<Elemento> *p = nullptr);
    virtual ~NodoAdy();

    NodoVertice<Elemento>* getInfo();
    void setInfo(NodoVertice<Elemento> *v);

    float getCosto();
    void setCosto(float c);

    NodoAdy<Elemento>* getProx();
    void setProx(NodoAdy<Elemento> *p);
};

template<typename Elemento>
NodoAdy<Elemento>::NodoAdy(){
  this->info = nullptr;
  this->prox = nullptr;
  this->costo = 0;
}

template<typename Elemento>
NodoAdy<Elemento>::NodoAdy(NodoVertice<Elemento> *v, float c,NodoAdy<Elemento> *p){
  this->info = v;
  this->prox = p;
  this->costo = c;
}


template<typename Elemento>
NodoAdy<Elemento>::~NodoAdy(){
  this->info = nullptr;
  this->prox = nullptr;
  this->costo = 0;
}

template<typename Elemento>
NodoVertice<Elemento>* NodoAdy<Elemento>::getInfo(){
  return this->info;
}

template<typename Elemento>
void NodoAdy<Elemento>::setInfo(NodoVertice<Elemento> *v){
  this->info = v;
}

template<typename Elemento>
float NodoAdy<Elemento>::getCosto(){
  return this->costo;
}

template<typename Elemento>
void NodoAdy<Elemento>::setCosto(float c){
  this->costo = c;
}

template<typename Elemento>
NodoAdy<Elemento>* NodoAdy<Elemento>::getProx(){
  return this->prox;
}

template<typename Elemento>
void NodoAdy<Elemento>::setProx(NodoAdy<Elemento> *p){
  this->prox = p;
}


#endif
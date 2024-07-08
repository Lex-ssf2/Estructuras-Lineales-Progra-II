#ifndef GRAFO_DIRIGIDO_HEADER
#define GRAFO_DIRIGIDO_HEADER

#include "Grafo.hpp"
#include <list>
#include <vector>

using namespace std;

template<typename Elemento>
class GrafoD: public Grafo<Elemento>
{
protected:
  GrafoD<int> setMapeo(vector<Elemento> *mapeo);
public:
  void agregarArco(Elemento v, Elemento w,float c = 0.f);
  void eliminarArco(Elemento v, Elemento w);
  void setPesoArco(Elemento v, Elemento w, float c = 0);

  void eliminarVertice(Elemento v);
  list<Elemento> getPredecesores(Elemento v);
  list<Elemento> getSucesores(Elemento v);
};

template<typename Elemento>
void GrafoD<Elemento>::agregarArco(Elemento v, Elemento w,float c){
  NodoVertice<Elemento> *actual, *destino = nullptr, *origen = nullptr;
  NodoAdy<Elemento> *conexion, *conexionAux;
  actual = this->g;
  while (actual != nullptr && actual->getInfo() != v)
  {
    if(actual->getInfo() == w){
      destino = actual;
    }
    actual = actual->getProx();
  }
  origen = actual;
  while(actual != nullptr && destino == nullptr){
    if(actual->getInfo() == w){
      destino = actual;
    }
    actual = actual->getProx();
  }
  if(origen == nullptr || destino == nullptr){
    cout << "Uno de los dos nodos no existe\n";
    return;
  }
  conexion = origen->getAdy();
  conexionAux = new NodoAdy<Elemento>;
  conexionAux->setInfo(destino);
  conexionAux->setProx(conexion);
  conexionAux->setCosto(c);
  origen->setArcos(origen->getNArcos() + 1);
  origen->setAdy(conexionAux);
  ++(this->nArcos);
}

template<typename Elemento>
void GrafoD<Elemento>::eliminarArco(Elemento v, Elemento w){
  NodoVertice<Elemento> *actual;
  NodoAdy<Elemento> *arco, *AuxA;
  actual = this->getVertice(v);
  if(actual == nullptr){
    return;
  }
  arco = actual->getAdy();
  if(arco->getInfo()->getInfo() == w){
    actual->setArcos(actual->getNArcos() - 1);
    AuxA = arco->getProx();
    delete arco;
    actual->setAdy(AuxA);
    --(this->nArcos);
    return;
  }
  arco = actual->getAdy();
  while (arco->getProx() != nullptr)
  {
    if(arco->getProx()->getInfo()->getInfo() == w){
      actual->setArcos(actual->getNArcos() - 1);
      AuxA = arco->getProx();
      arco->setProx(AuxA->getProx());
      delete AuxA;
      --(this->nArcos);
      return;
    }
    arco = arco->getProx();
  }
}

template<typename Elemento>
list<Elemento> GrafoD<Elemento>::getPredecesores(Elemento v){
  NodoVertice<Elemento> *actual;
  NodoAdy<Elemento> *arco;
  list<Elemento> salida;
  actual = this->g;
  while (actual != nullptr)
  {
    if(actual->getInfo() != v){
      arco = actual->getAdy();
      while (arco != nullptr)
      {
        if(arco->getInfo()->getInfo() == v){
          salida.push_back(actual->getInfo());
        }
        arco = arco->getProx();
      }
    }
    actual = actual->getProx();
  }
  return salida;
}

template<typename Elemento>
list<Elemento> GrafoD<Elemento>::getSucesores(Elemento v){
  return this->getVecinos(v);
}

template<typename Elemento>
void GrafoD<Elemento>::setPesoArco(Elemento v, Elemento w, float c){
  NodoVertice<Elemento> *actual;
  NodoAdy<Elemento> *arco;
  actual = this->getVertice(v);
  if(actual == nullptr){
    return;
  }
  arco = actual->getAdy();
  while (arco != nullptr)
  {
    if(arco->getInfo()->getInfo() == w){
      arco->setCosto(c);
      return;
    }
    arco = arco->getProx();
  }
  return;
}

template<typename Elemento>
void GrafoD<Elemento>::eliminarVertice(Elemento v){
  NodoVertice<Elemento> *actual, *destino, *anterior, *auxV, *antV;
  NodoAdy<Elemento> *arco, *AuxA, *AuxA2;
  bool eliminado = false,encontrado = false;
  actual = this->g;
  while (actual != nullptr)
  {
    if(actual->getInfo() == v){
      arco = actual->getAdy();
      while (arco != nullptr)
      {
        AuxA2 = arco->getProx();
        arco->setProx(nullptr);
        delete arco;
        --(this->nArcos);
        actual->setAdy(AuxA2);
        arco = actual->getAdy();
      }
      antV = anterior;
      auxV = actual;

    }else{
      eliminado = false;
      arco = actual->getAdy();
      if(arco != nullptr && arco->getInfo()->getInfo() == v){
      
        actual->setArcos(actual->getNArcos() - 1);
        AuxA = arco->getProx();
        actual->setAdy(AuxA);
        eliminado = true;
        --(this->nArcos);
        delete arco;
      }
      arco = actual->getAdy();
      while (arco != nullptr && arco->getProx() != nullptr && !eliminado)
      {
        if(arco->getProx()->getInfo()->getInfo() == v){
          actual->setArcos(actual->getNArcos() - 1);
          AuxA = arco->getProx();
          arco->setProx(AuxA->getProx());
          eliminado = true;
          --(this->nArcos);
          delete AuxA;
        }
        arco = arco->getProx();
      }
    }
    anterior = actual;
    actual = actual->getProx();
  }
  if(auxV == nullptr){
    return;
  }

  if(auxV == this->g){
    this->g = auxV->getProx();
  }else{
    antV->setProx(auxV->getProx());
  }
  delete auxV;
  --(this->nVertices);
}

template<typename Elemento>
GrafoD<int> GrafoD<Elemento>::setMapeo(vector<Elemento> *mapeo){
  GrafoD<int> salida;
  NodoVertice<Elemento> *actual;
  NodoAdy<Elemento> *arco;
  int i = 0;
  actual = this->g;
  while (actual != nullptr)
  {
    mapeo->emplace_back(actual->getInfo());
    salida.agregarVertice(i);
    ++i;
    actual = actual->getProx();
  };

  i = 0;
  actual = this->g;
  while (actual != nullptr)
  {
    arco = actual->getAdy();
    while (arco != nullptr)
    {
      int conexionMap = this->desMap(*mapeo,arco->getInfo()->getInfo());
      salida.agregarArco(i,conexionMap,arco->getCosto());
      arco = arco->getProx();
    }
    actual = actual->getProx();
    ++i;
  }

  cout << salida.getTotalArcos() << endl;
  return salida;
  
}
#endif
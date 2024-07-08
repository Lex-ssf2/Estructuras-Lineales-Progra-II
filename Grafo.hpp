#ifndef GRAFO_HEADER
#define GRAFO_HEADER

#include "NodoVertice.hpp"
#include "NodoAdy.hpp"
#include <list>

using namespace std;

template<typename Elemento>
class Grafo
{
private:

  NodoVertice<Elemento> *g;
  int nVertices;
  int nArcos;

  NodoVertice<Elemento> *getVertice(Elemento v);
  void getVertices(list<Elemento> lista, list<NodoVertice<Elemento>*> salida);

public:
  Grafo();
  ~Grafo();

  bool esVacio();
  
  void agregarVertice(Elemento v);
  void agregarArco(Elemento v, Elemento w,float c = 0.f);

  void eliminarVertice(Elemento v);
  void eliminarArco(Elemento v, Elemento w);

  bool existeVertice(Elemento v);
  void setVertice(Elemento v, Elemento w);
  bool existeArco(Elemento v, Elemento w);

  float getPesoArco(Elemento v,Elemento w);
  void setPesoArco(Elemento v, Elemento w, float c = 0);
  
  int getNVertices();
  int getNArcos(Elemento v);
  int getTotalArcos();

  /*list<Elemento> getPredecesores(Elemento v);
  list<Elemento> getSucesores(Elemento v);*/
  list<Elemento> getVecinos(Elemento v);
};

template<typename Elemento>
Grafo<Elemento>::Grafo(){
  this->g = nullptr;
  this->nVertices = 0;
  this->nArcos = 0;
}

template<typename Elemento>
Grafo<Elemento>::~Grafo(){

}

template<typename Elemento>
bool Grafo<Elemento>::esVacio(){
  return this->g = nullptr;
}

template<typename Elemento>
void Grafo<Elemento>::agregarVertice(Elemento v){
  NodoVertice<Elemento> *aux, *actual;
  actual = this->getVertice(v);
  if(actual != nullptr){
    cout << "Ya existe\n";
    return;
  }
  ++(this->nVertices);
  actual = this->g;
  aux = new NodoVertice<Elemento>;
  aux->setInfo(v);
  aux->setProx(actual);
  this->g = aux;
}

template<typename Elemento>
NodoVertice<Elemento>* Grafo<Elemento>::getVertice(Elemento v){
  NodoVertice<Elemento> *actual;
  actual = this->g;
  while (actual != nullptr)
  {
    if(actual->getInfo() == v){
      return actual;
    }
    actual = actual->getProx();
  }
  return nullptr;
}

template<typename Elemento>
bool Grafo<Elemento>::existeVertice(Elemento v){
  NodoVertice<Elemento> *actual;
  actual = this->getVertice(v);
  return actual != nullptr;
}

template<typename Elemento>
int Grafo<Elemento>::getNVertices(){
  return this->nVertices;
}

template<typename Elemento>
int Grafo<Elemento>::getNArcos(Elemento v){
  NodoVertice<Elemento> *actual;
  actual = this->getVertice(v);
  if(actual == nullptr){
    return -1;
  }
  return actual->getNArcos();
}

template<typename Elemento>
int Grafo<Elemento>::getTotalArcos(){
  return this->nArcos;
}

template<typename Elemento>
void Grafo<Elemento>::getVertices(list<Elemento> lista, list<NodoVertice<Elemento>*> salida){
  if(lista.empty()){
    return;
  };
  NodoVertice<Elemento> *actual;
  actual = this->g;
  typename list<Elemento>::iterator it;
  while (actual != nullptr && !lista.empty())
  {
    for (it = lista.begin(); it != lista.end(); ++it)
    {
      if(actual->getInfo() == *it){
        cout << *it <<" Encontrado\n";
        lista.erase(it);
        cout << lista.size();
        salida.push_back(actual);
      }
    }
    actual = actual->getProx();
  }
}

template<typename Elemento>
bool Grafo<Elemento>::existeArco(Elemento v, Elemento w){
  NodoVertice<Elemento> *actual;
  NodoAdy<Elemento> *conexion;
  actual = this->getVertice(v);
  if(actual == nullptr){
    return false;
  };
  conexion = actual->getAdy();
  while (conexion != nullptr)
  {
    if(conexion->getInfo()->getInfo() == w){
      return true;
    }
    conexion = conexion->getProx();
  }
  return false;
}

template<typename Elemento>
void Grafo<Elemento>::agregarArco(Elemento v, Elemento w,float c){
  NodoVertice<Elemento> *actual, *destino = nullptr, *origen = nullptr;
  NodoAdy<Elemento> *conexion, *conexionAux;
  bool encontrado = false;
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
  while (conexion != nullptr && !encontrado)
  {
    if(conexion->getInfo()->getInfo() == w){
      encontrado = true;
    }
    conexion = conexion->getProx();
  }
  if(!encontrado){
    conexion = origen->getAdy();
    conexionAux = new NodoAdy<Elemento>;
    conexionAux->setInfo(destino);
    conexionAux->setProx(conexion);
    conexionAux->setCosto(c);
    origen->setArcos(origen->getNArcos() + 1);
    origen->setAdy(conexionAux);
    ++(this->nArcos);
  }

//Aprovechar y hacerla doble via xd
  conexion = destino->getAdy();
  while (conexion != nullptr)
  {
    if(conexion->getInfo()->getInfo() == v){
      return;
    }
    conexion = conexion->getProx();
  }
  conexion = destino->getAdy();
  conexionAux = new NodoAdy<Elemento>;
  conexionAux->setInfo(origen);
  conexionAux->setProx(conexion);
  conexionAux->setCosto(c);
  destino->setArcos(destino->getNArcos() + 1);
  destino->setAdy(conexionAux);
  ++(this->nArcos);
}

template<typename Elemento>
void Grafo<Elemento>::setVertice(Elemento v, Elemento w){
  NodoVertice<Elemento> *actual;
  actual = getVertice(v);
  if(actual == nullptr){
    return;
  }
  actual->setInfo(v);
}

template<typename Elemento>
float Grafo<Elemento>::getPesoArco(Elemento v,Elemento w){
  NodoVertice<Elemento> *actual;
  NodoAdy<Elemento> *arco;
  actual = getVertice(v);
  if(actual == nullptr){
    return -1.f;
  }
  arco = actual->getAdy();
  while (arco != nullptr)
  {
    if(arco->getInfo()->getInfo() == w){
      return arco->getCosto();
    }
    arco = arco->getProx();
  }
  return -1.f;
}

template<typename Elemento>
void Grafo<Elemento>::setPesoArco(Elemento v, Elemento w, float c){
  NodoVertice<Elemento> *actual, *destino;
  NodoAdy<Elemento> *arco;
  bool encontrado = false;
  actual = getVertice(v);
  if(actual == nullptr){
    return;
  }
  arco = actual->getAdy();
  while (arco != nullptr && !encontrado)
  {
    if(arco->getInfo()->getInfo() == w){
      destino = arco->getInfo();
      arco->setCosto(c);
      encontrado = true;
    }
    arco = arco->getProx();
  }
  arco = destino->getAdy();
  while (arco != nullptr)
  {
    if(arco->getInfo()->getInfo() == v){
      arco->setCosto(c);
      return;
    }
    arco = arco->getProx();
  }
  return;
}

template<typename Elemento>
list<Elemento> Grafo<Elemento>::getVecinos(Elemento v){
  NodoVertice<Elemento> *actual;
  NodoAdy<Elemento> *arco;
  list<Elemento> salida;
  actual = this->getVertice(v);
  if(actual == nullptr){
    return salida;
  }
  arco = actual->getAdy();
  while (arco != nullptr)
  {
    salida.push_back(arco->getInfo()->getInfo());
    arco = arco->getProx();
  }
  return salida;
}

template<typename Elemento>
void Grafo<Elemento>::eliminarVertice(Elemento v){
  NodoVertice<Elemento> *actual, *destino, *anterior;
  NodoAdy<Elemento> *arco, *AuxA, *AuxA2;
  bool eliminado = false,encontrado = false;
  actual = this->g;
  while (actual != nullptr && !encontrado)
  {
    if(actual->getInfo() == v){
      encontrado = true;
    }else{
      anterior = actual;
      actual = actual->getProx();
    }
  }
  if(actual == nullptr){
    return;
  }
  while (actual->getAdy() != nullptr)
  {
    eliminado = false;
    arco = actual->getAdy();
    destino = arco->getInfo();
    AuxA2 = arco->getProx();
    delete arco;
    --(this->nArcos);
    actual->setAdy(AuxA2);
    arco = destino->getAdy();
    if(arco != nullptr && arco->getInfo()->getInfo() == v){
      destino->setArcos(destino->getNArcos() - 1);
      AuxA = arco->getProx();
      destino->setAdy(AuxA);
      eliminado = true;
      --(this->nArcos);
      delete arco;
    }
    arco = destino->getAdy();
    while (arco != nullptr && arco->getProx() != nullptr && !eliminado)
    {
      if(arco->getProx()->getInfo()->getInfo() == v){
        destino->setArcos(destino->getNArcos() - 1);
        AuxA = arco->getProx();
        arco->setProx(AuxA->getProx());
        eliminado = true;
        --(this->nArcos);
        delete AuxA;
      }
      arco = arco->getProx();
    }
  }
  if(actual == this->g){
    this->g = actual->getProx();
  }else{
    anterior->setProx(actual->getProx());
  }
  delete actual;
  --(this->nVertices);
}

template<typename Elemento>
void Grafo<Elemento>::eliminarArco(Elemento v, Elemento w){
  NodoVertice<Elemento> *actual, *destino;
  NodoAdy<Elemento> *arco, *AuxA;
  bool encontrado = false;
  actual = this->getVertice(v);
  if(actual == nullptr){
    return;
  }
  arco = actual->getAdy();
  if(arco->getInfo()->getInfo() == w){
    actual->setArcos(actual->getNArcos() - 1);
    destino = arco->getInfo();
    AuxA = arco->getProx();
    encontrado = true;
    delete arco;
    actual->setAdy(AuxA);
    --(this->nArcos);
  }
  arco = destino->getAdy();
  while (arco->getProx() != nullptr && !encontrado)
  {
    if(arco->getProx()->getInfo()->getInfo() == w){
      actual->setArcos(actual->getNArcos() - 1);
      AuxA = arco->getProx();
      destino = AuxA->getInfo();
      arco->setProx(AuxA->getProx());
      delete AuxA;
      encontrado = true;
      --(this->nArcos);
    }
    arco = arco->getProx();
  }


  arco = destino->getAdy();
  if(arco->getInfo()->getInfo() == v){
    destino->setArcos(destino->getNArcos() - 1);
    AuxA = arco->getProx();
    delete arco;
    actual->setAdy(AuxA);
    --(this->nArcos);
    return;
  }
  arco = destino->getAdy();
  while (arco->getProx() != nullptr)
  {
    if(arco->getProx()->getInfo()->getInfo() == v){
      destino->setArcos(destino->getNArcos() - 1);
      AuxA = arco->getProx();
      arco->setProx(AuxA->getProx());
      delete AuxA;
      --(this->nArcos);
      return;
    }
    arco = arco->getProx();
  }
}
#endif
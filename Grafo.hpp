#ifndef GRAFO_HEADER
#define GRAFO_HEADER

#include "NodoVertice.hpp"
#include "NodoAdy.hpp"
#include <list>
#include <vector>
#include <queue>

using namespace std;

template<typename Elemento>
class Grafo
{
protected:

  NodoVertice<Elemento> *g;
  int nVertices;
  int nArcos;

  NodoVertice<Elemento> *getVertice(Elemento v);
  void getVertices(list<Elemento> lista, list<NodoVertice<Elemento>*> salida);
  Grafo<int> setMapeo(vector<Elemento> *mapeo);
  int desMap(vector<Elemento> mapeo, Elemento e);
  void DFS(Grafo<int> g, int fuente, list<int> &recorrido, vector<bool> &visitados);
  void caminoMasCortoPeso(int start, Grafo<int> g, vector<int> &anterior);
  void caminoMinPesoBloq(int start, Grafo<int> g, vector<int> &anterior, vector<int> bloqueos);
  void BFS(Grafo<int> g, int fuente, list<int> &recorrido);
  void cicloSimple(int start, Grafo<int> g, vector<int> &anterior);
  void esBipartito(int inicio,Grafo<int> grafo, bool &resultado);
  void esMulticoloreable(int inicio, int nColoresGrafo, Grafo<int> grafo, bool &resultado);
  void arcoMinimo(list<int> activos, int &v, int &w, float &peso, vector<bool> visitados, bool &band);

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

  list<Elemento> getVecinos(Elemento v);
  list<Elemento> DFS(Elemento v);
  list<Elemento> BFS(Elemento v);

  list<Elemento> cicloSimple(Elemento v);
  list<Elemento> caminoMasCortoPeso(Elemento v, Elemento w);
  list<Elemento> caminoConBloqueoPeso(Elemento v, Elemento w, list<Elemento> bloqueo);

  int arbolExpandidoMinimo();
  void arbolExpandidoMinimo(Grafo<int> &g, float &peso);

  bool esBipartito();
  bool esMulticoloreable(int nColores = 4);
  bool esConexo();
  list<list<Elemento>> getPuentes();
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
  actual = this->getVertice(v);
  if(actual == nullptr){
    return;
  }
  actual->setInfo(v);
}

template<typename Elemento>
float Grafo<Elemento>::getPesoArco(Elemento v,Elemento w){
  NodoVertice<Elemento> *actual;
  NodoAdy<Elemento> *arco;
  actual = this->getVertice(v);
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
  actual = this->getVertice(v);
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
    NodoVertice<Elemento> *actual, *objetivo = NULL;
    NodoAdy<Elemento> *auxAct, *borrar;
    if(v != w)
    {
        actual = this->g;
        while((actual->getInfo() != v)&&(actual->getProx() != NULL))
        {
            if(actual->getInfo() == w)
            {
                objetivo = actual;
            }
            actual = actual->getProx();
        }
        if(actual->getInfo() != v)
        {
            return;
        }

        if(objetivo == NULL)
        {
            objetivo = actual->getProx();
            if(objetivo == NULL)
            {
                return;
            }
            while((objetivo->getInfo() != w)&&(objetivo->getProx() != NULL))
            {
                objetivo = objetivo->getProx();
            }
            if(objetivo->getInfo() != w)
            {
                return;
            }
        }
        
        if(actual->getAdy() == NULL)
        {
            return;
        }
        else
        {
            if(actual->getAdy()->getInfo() == objetivo)
            {
                borrar = actual->getAdy();
                actual->setAdy(borrar->getProx());
                delete borrar;
            }
            else
            {
                auxAct = actual->getAdy();
                borrar = auxAct->getProx();
                while(borrar->getInfo() != objetivo && borrar != NULL)
                {
                    auxAct = borrar;
                    borrar = borrar->getProx();
                }
                if(borrar != NULL)
                {
                    auxAct->setProx(borrar->getProx());
                    delete borrar;
                }
            }
        }
        if(objetivo->getAdy() == NULL)
        {
            return;
        }
        else
        {
            if(objetivo->getAdy()->getInfo() == actual)
            {
                borrar = objetivo->getAdy();
                objetivo->setAdy(borrar->getProx());
                delete borrar;
            }
            else
            {
                auxAct = objetivo->getAdy();
                borrar = auxAct->getProx();
                while(borrar->getInfo() != actual && borrar != NULL)
                {
                    auxAct = borrar;
                    borrar = borrar->getProx();
                }
                if(borrar != NULL)
                {
                    auxAct->setProx(borrar->getProx());
                    delete borrar;
                }
            }
        }
    }
    /*NodoVertice<Elemento> *inicio = this->g;
    NodoAdy<Elemento> *ady, *objetivo;

    if(this->existeArco(v,w)){
        //ENCONTRAR VERTICE V
        while((inicio!=nullptr) && (inicio->getInfo() != v)){
            inicio = inicio->getProx();
        }
        
        //RECORRER ARCOS DE V HASTA ENCONTRAR ARCO CON W
        ady = inicio->getAdy();
        if(ady != nullptr){
            if(ady->getInfo()->getInfo() == w){
                inicio->setAdy(ady->getProx());
                inicio->setArcos(inicio->getNArcos() - 1);
                delete ady;
                this->nArcos = this->nArcos - 1;
            }else{
                if (ady->getProx() != nullptr){
                    while (ady->getProx()->getInfo()->getInfo() != w){
                        ady=ady->getProx();
                    }
                    objetivo = ady->getProx();
                    ady->setProx(objetivo->getProx());
                    objetivo->setProx(nullptr);
                    inicio->setArcos(inicio->getNArcos() - 1);
                    delete objetivo;
                    this->nArcos = this->nArcos - 1;

                }
            }
        }
    }  */
  /*NodoVertice<Elemento> *actual, *destino;
  NodoAdy<Elemento> *arco, *AuxA;
  bool encontrado = false;
  actual = this->getVertice(v);
  if(actual == nullptr){
    return;
  }
  arco = actual->getAdy();
  if(arco->getInfo()->getInfo() == w){
    actual->setArcos(actual->getNArcos() - 1);
    actual->setAdy(arco->getProx());
    destino = arco->getInfo();
    encontrado = true;
    //delete arco;
    --(this->nArcos);
  }

  arco = actual->getAdy();
  while (arco->getProx() != nullptr && !encontrado)
  {
    if(arco->getProx()->getInfo()->getInfo() == w){
      actual->setArcos(actual->getNArcos() - 1);
      AuxA = arco->getProx();
      destino = AuxA->getInfo();
      arco->setProx(AuxA->getProx());
      //delete AuxA;
      encontrado = true;
      --(this->nArcos);
    }else{
      arco = arco->getProx();
    }
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
    }else{
      arco = arco->getProx();
    }
  }*/
}

template<typename Elemento>
Grafo<int> Grafo<Elemento>::setMapeo(vector<Elemento> *mapeo){
  Grafo<int> salida;
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

  return salida;
  
  
}

template<typename Elemento>
int Grafo<Elemento>::desMap(vector<Elemento> mapeo, Elemento e){
  int i = 0, max = mapeo.size();
  for (i = 0; i < max; ++i)
  {
    if(mapeo.at(i) == e){
      return i;
    }
  }
  return -1;
}

template<typename Elemento>
void Grafo<Elemento>::DFS(Grafo<int> g, int fuente, list<int> &recorrido, vector<bool> &visitados){
  list<int> sucesores;
  int w;
  sucesores = g.getVecinos(fuente);
  while(!sucesores.empty()){
    w = sucesores.front();
    if(!visitados.at(w)){
      visitados[w] = true;
      recorrido.push_back(w);
      this->DFS(g,w,recorrido,visitados);
    }
    sucesores.pop_front();
  }
}

template<typename Elemento>
list<Elemento> Grafo<Elemento>::DFS(Elemento v){
  vector<Elemento> map;
  vector<bool> visitados;
  list<int> recorrido;
  list<Elemento> recorridoMap;
  Grafo<int> mapeo = this->setMapeo(&map);
  int fuente = this->desMap(map,v);

  visitados.resize(map.size(),false);

  recorrido.push_back(fuente);
  visitados[fuente] = true;
  this->DFS(mapeo,fuente,recorrido,visitados);
  while (!recorrido.empty())
  {
    recorridoMap.push_back(map[recorrido.front()]);
    recorrido.pop_front();
  }

  /*for(auto xd: recorridoMap){
    cout << xd << " ";
  }*/
  cout << endl;
  return recorridoMap;
  
}

template<typename Elemento>
void Grafo<Elemento>::BFS(Grafo<int> g, int fuente, list<int> &recorrido){
  vector<bool> visitados;
  visitados.resize(g.getNVertices(),false);
  queue<int> c;
  list<int> sucesores;
  int v,w;

  visitados[fuente] = true;
  c.push(fuente);
  while(!c.empty()){
    v = c.front();
    c.pop();
    recorrido.emplace_back(v);
    sucesores = g.getVecinos(v);
    while (!sucesores.empty())
    {
      w = sucesores.front();
      if(!visitados[w]){
        visitados[w] = true;
        c.push(w);
      }
      sucesores.pop_front();
    }
  }
  return;
}

template<typename Elemento>
list<Elemento> Grafo<Elemento>::BFS(Elemento v){
  vector<Elemento> map;
  list<int> recorrido;
  list<Elemento> recorridoMap;
  Grafo<int> mapeo = this->setMapeo(&map);
  int fuente = this->desMap(map,v);
  this->BFS(mapeo,fuente,recorrido);

  while (!recorrido.empty())
  {
    recorridoMap.push_back(map[recorrido.front()]);
    recorrido.pop_front();
  }
  /*for(auto xd: recorridoMap){
    cout << xd << " ";
  }*/
  cout << endl;
  return recorridoMap;
}

template<typename Elemento>
list<Elemento> Grafo<Elemento>::cicloSimple(Elemento v){
  vector<Elemento> map;
  vector<int> recorrido;
  list<Elemento> recorridoMap;
  Grafo<int> mapeo = this->setMapeo(&map);
  int fuente = this->desMap(map,v);
  this->cicloSimple(fuente,mapeo,recorrido);
  int aux = recorrido[fuente];
  recorridoMap.push_front(v);
  while (aux != fuente)
  {
    recorridoMap.push_front(map[aux]);
    aux = recorrido[aux];
  }
  recorridoMap.push_front(v);

  for(auto xd: recorridoMap){
    cout << xd << " ";
  }

  cout << endl;
  return recorridoMap;
}

template<typename Elemento>
void Grafo<Elemento>::cicloSimple(int start, Grafo<int> g, vector<int> &anterior){
  vector<float> acumulado;
  acumulado.resize(g.getNVertices(),0);
  anterior.resize(g.getNVertices(),-1);
  queue<int> c;
  list<int> sucesores;
  float costo;
  int v,w;

  c.push(start);
  while(!c.empty()){
    v = c.front();
    c.pop();
    sucesores = g.getVecinos(v);
    while (!sucesores.empty())
    {
      w = sucesores.front();
      costo = g.getPesoArco(v,w) + acumulado[v];
      if((acumulado[w] == 0 || acumulado[w] > costo || (anterior[w] == anterior[v] && acumulado[w] >= acumulado[v])) && w != anterior[v]){
        acumulado[w] = costo;
        anterior[w] = v;
        c.push(w);
      }
      sucesores.pop_front();
    }
  }
}


template<typename Elemento>
void Grafo<Elemento>::caminoMasCortoPeso(int start, Grafo<int> g, vector<int> &anterior){
  vector<float> acumulado;
  acumulado.resize(g.getNVertices(),-1);
  anterior.resize(g.getNVertices(),-1);
  queue<int> c;
  list<int> sucesores;
  float costo;
  int v,w;

  acumulado[start] = 0;
  c.push(start);
  while(!c.empty()){
    v = c.front();
    c.pop();
    sucesores = g.getVecinos(v);
    while (!sucesores.empty())
    {
      w = sucesores.front();
      costo = g.getPesoArco(v,w) + acumulado[v];
      if(acumulado[w] == -1 || acumulado[w] > costo){
        acumulado[w] = costo;
        anterior[w] = v;
        c.push(w);
      }
      sucesores.pop_front();
    }
  }
}

template<typename Elemento>
list<Elemento> Grafo<Elemento>::caminoMasCortoPeso(Elemento v, Elemento w){
  vector<Elemento> map;
  vector<int> recorrido;
  list<Elemento> recorridoMap;
  Grafo<int> mapeo = this->setMapeo(&map);
  int fuente = this->desMap(map,v);
  this->caminoMasCortoPeso(fuente,mapeo,recorrido);
  int aux = recorrido[this->desMap(map,w)];
  recorridoMap.push_front(w);
  while (aux != -1)
  {
    recorridoMap.push_front(map[aux]);
    aux = recorrido[aux];
  }

  for(auto xd: recorridoMap){
    cout << xd << " ";
  }

  cout << endl;
  return recorridoMap;
}

template<typename Elemento>
void Grafo<Elemento>::caminoMinPesoBloq(int start, Grafo<int> g, vector<int> &anterior, vector<int> bloqueos){
  vector<float> acumulado;
  acumulado.resize(g.getNVertices(),-1);
  anterior.resize(g.getNVertices(),-1);
  queue<int> c;
  list<int> sucesores;
  float costo;
  int v,w;

  acumulado[start] = 0;
  c.push(start);
  while(!c.empty()){
    v = c.front();
    c.pop();
    sucesores = g.getVecinos(v);
    while (!sucesores.empty())
    {
       w = sucesores.front();
      if(bloqueos.at(w) != 1){
        costo = g.getPesoArco(v,w) + acumulado[v];
        if(acumulado[w] == -1 || acumulado[w] > costo){
          acumulado[w] = costo;
          anterior[w] = v;
          c.push(w);
        }
      }
      sucesores.pop_front();
    }
  }
};

template<typename Elemento>
list<Elemento> Grafo<Elemento>::caminoConBloqueoPeso(Elemento v, Elemento w, list<Elemento> bloqueo){
  vector<Elemento> map;
  vector<int> recorrido, bloqueoMap;
  list<Elemento> recorridoMap;
  Grafo<int> mapeo = this->setMapeo(&map);
  int fuente = this->desMap(map,v);
  bloqueoMap.resize(this->getNVertices(),0);
  while (!bloqueo.empty())
  {
    bloqueoMap[this->desMap(map,bloqueo.front())] = 1;
    bloqueo.pop_front();
  }
  
  this->caminoMinPesoBloq(fuente,mapeo,recorrido,bloqueoMap);
  int aux = recorrido[this->desMap(map,w)];
  recorridoMap.push_front(w);
  while (aux != -1)
  {
    recorridoMap.push_front(map[aux]);
    aux = recorrido[aux];
  }

  for(auto xd: recorridoMap){
    cout << xd << " ";
  }
  return recorridoMap;
};

template<typename Elemento>
bool Grafo<Elemento>::esBipartito(){
  vector<Elemento> map;
  bool bicoloreable = true;
  Grafo<int> mapeo = this->setMapeo(&map);
  int fuente = this->desMap(map,this->g->getInfo());
  this->esBipartito(fuente,mapeo,bicoloreable);
  return bicoloreable;
}

template<typename Elemento>
void Grafo<Elemento>::esBipartito(int inicio,Grafo<int> grafo, bool &resultado){
  vector<int> colores;
  colores.resize(grafo.getNVertices(),-1);
  queue<int> c;
  list<int> sucesores;
  int v,w;
  resultado = true;
  colores[inicio] = 0;
  c.push(inicio);
  while(!c.empty() && resultado){
    v = c.front();
    c.pop();

    sucesores = grafo.getVecinos(v);
    while (!sucesores.empty() && resultado)
    {
      w = sucesores.front();
      if(colores[w] == -1){
        colores[w] = (colores[v] + 1) % 2;
        c.push(w);
      }
      if(colores[w] == colores[v]){
        resultado = false;
        return;
      }
      sucesores.pop_front();
    }
  }
  return;
}

template<typename Elemento>
bool Grafo<Elemento>::esMulticoloreable(int nColores){
  vector<Elemento> map;
  bool multicoloreable = true;
  Grafo<int> mapeo = this->setMapeo(&map);
  int fuente = this->desMap(map,this->g->getInfo());
  this->esMulticoloreable(fuente,nColores,mapeo,multicoloreable);
  return multicoloreable;
}

template<typename Elemento>
void Grafo<Elemento>::esMulticoloreable(int inicio, int nColoresGrafo, Grafo<int> grafo, bool &resultado){
  vector<int> colores;
  vector<bool> coloresDisponibles, visitados;
  int i;
  for(i=0;i<this->getNVertices();i++){
      colores.emplace_back(-1);
      coloresDisponibles.emplace_back(true);
      visitados.emplace_back(false);
  }
  queue<int> c;
  list<int> sucesores;
  int v,w;
  bool encontrado = false;
  resultado = true;
  colores[inicio] = 0;
  c.push(inicio);
  while(!c.empty() && resultado){
    v = c.front();
    c.pop();

    sucesores = grafo.getVecinos(v);
    while (!sucesores.empty() && resultado)
    {
      w = sucesores.front();
      visitados[w] = true;
      if(colores[w] != -1){
        coloresDisponibles[colores[w]] = false;
      }
      if(!visitados[v]){
        c.push(w);
      }   
      sucesores.pop_front();
    }
    i = 0;
    encontrado = false;
    while (i < nColoresGrafo && !encontrado){
      if(coloresDisponibles[i]){
        colores[w] = i;
        encontrado = true;
      }
      ++i;
    }
    visitados[v] = true;
    if(!encontrado){
      resultado = false;
      return;
    }
  }
  return;
}

template<typename Elemento>
void Grafo<Elemento>::arbolExpandidoMinimo(Grafo<int> &g, float &peso){
  vector<bool> visitados;
  int i,v,w;
  bool fin, band=false;
  list<int> vertices, activos;
  float p;

  for(i=0;i<this->getNVertices();i++){
      g.agregarVertice(i);
      visitados.emplace_back(false);
  }

  activos.push_back(0);
  visitados.at(0) = true;
  fin = false;
  p=0;
  peso=0;
  while(!fin){
    this->arcoMinimo(activos,v,w,p,visitados, band);
    g.agregarArco(v,w, p);
    peso = peso + p;
    activos.push_back(w);
    visitados.at(w) = true;

    fin = true;
    if(!band){
        for ( i = 0; i< this->getNVertices(); i++){
            fin = fin && visitados.at(i);
        }
    }else{
        peso = 0;
    }

  }
}

template<typename Elemento>
void Grafo<Elemento>::arcoMinimo(list<int> activos, int &v, int &w, float &peso, vector<bool> visitados, bool &band){
  int actual, act;
  list<int> vecinos;
  float pesoArco;
  bool prim=false;

  while(!activos.empty()){
    actual = activos.front();
    vecinos = this->getVecinos(actual);
    while(!vecinos.empty()){
      act = vecinos.front();
      if (!visitados.at(act)){
        pesoArco = this->getPesoArco(actual, act);
        if((pesoArco<peso) || (!prim)){
            peso = pesoArco;
            v = actual;
            w = act;
            prim=true;
        }
      }
      vecinos.pop_front();
    }
    activos.pop_front();
  }
  //Si no se pudo procesar ni un solo arco, se activa la bandera band para finalizar el proceso
  if(!prim){
      band = true;
  }
}

template<typename Elemento>
int Grafo<Elemento>::arbolExpandidoMinimo(){
  vector<Elemento> map;
  bool multicoloreable = true;
  Grafo<int> mapeo = this->setMapeo(&map), arbolMinimo;
  float peso;
  mapeo.arbolExpandidoMinimo(arbolMinimo,peso);
  return peso;
}

template <typename Elemento>
bool Grafo<Elemento>::esConexo(){
  Elemento fuente = this->g->getInfo();
  list<Elemento> salida;
  salida = this->BFS(fuente);
    return salida.size() == this->getNVertices();
}

template <typename Elemento>
list<list<Elemento>> Grafo<Elemento>::getPuentes(){
  list<list<Elemento>> arcosPuente;
  list<Elemento> arco;
  list<int> vecinos;
  float peso;
  int i,w;
  vector<Elemento> m;
  Grafo<int> aux = this->setMapeo(&m);//MAPEAR GRAFO O(N+M)

  for (i=0; i<this->getNVertices(); i++){ //RECORRER VERTICES 
      vecinos = aux.getVecinos(i);
      //RECORRER ARCOS
      /*if(vecinos.size() > 2){
        vecinos.pop_front();
        continue;
      }*/
      while(!vecinos.empty()){
          w = vecinos.front();
          peso = aux.getPesoArco(i,w);
          //ELIMINAR ARCO
          cout << aux.existeArco(i,w) << " ";
          aux.eliminarArco(i,w);
          //VERIFICAR QUE EL GRAFO SIGA CONEXO (Si no es conexo, el arco es un arco puente)
          /*if((!aux.esConexo()) && (i<w)){
              //Agregar arco a la lista de arcos puente
              cout << i << " ";
              arco.clear();
              arco.push_back(m.at(i));
              arco.push_back(m.at(w));
              arcosPuente.push_back(arco);
              cout << i << " ";
              
          }*/
          //VOLVER A AGREGAR EL ARCO ELIMINADO
          aux.agregarArco(i,w,peso);
          vecinos.pop_front();
      }
  }
  return arcosPuente;
}
#endif
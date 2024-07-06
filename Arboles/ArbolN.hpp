#ifndef ARBOL_N_HEADER
#define ARBOL_N_HEADER

#include "NodoAN.hpp"
#include <list>
#include <queue>

using namespace std;

template<class Elemento>
class ArbolN
{
protected:
    NodoAN<Elemento> *NodoRaiz;
    int peso;
    static NodoAN<Elemento> *copiarNodos(NodoAN<Elemento> *ptrNodo, int &contador);
    void destruirNodos(NodoAN<Elemento> **ptrNodo);
    void find(NodoAN<Elemento> *actual ,Elemento padre,NodoAN<Elemento> *papa2,NodoAN<Elemento> *abuelo, NodoAN<Elemento> **salida, NodoAN<Elemento> **dad, NodoAN<Elemento> **granddad);
    void anadir(NodoAN<Elemento> *actual, Elemento nuevo);
    void preOrden(NodoAN<Elemento> *actual, list<Elemento> &result);
    void inOrden(NodoAN<Elemento> *actual, list<Elemento> &result);
    void postOrden(NodoAN<Elemento> *actual, list<Elemento> &result);
    void niveles(queue<NodoAN<Elemento>*> actual,list<Elemento> &result);
    void LCA(NodoAN<Elemento> *actual, Elemento origen, Elemento destino, int &contadorEncontrado, int *contTemp, bool &LCAEncontrado, Elemento &ancestro);
    void camino(NodoAN<Elemento> *actual, Elemento origen, Elemento destino, int &contadorEncontrado, int *contTemp, bool &LCAEncontrado, list<Elemento> &salida, list<Elemento> &aux);

    ArbolN<Elemento> nodoToArbol(NodoAN<Elemento> *nodo);

public:
    ArbolN();
    ArbolN(Elemento e, list<ArbolN<Elemento>> Hijos);
    ArbolN(ArbolN<Elemento> &a);
    ~ArbolN();

    Elemento getInfo();
    void setInfo(Elemento e);

    list<ArbolN<Elemento>> getHijos();
    ArbolN<Elemento> getHijoIzq();
    ArbolN<Elemento> getHermanoDerecho();

    void copiar(const ArbolN<Elemento> &a);

    void insertarNodo(Elemento padre, Elemento nuevo);
    void eliminarSubArbol(Elemento e);

    list<Elemento> preOrden();
    list<Elemento> inOrden();
    list<Elemento> postOrden();
    list<Elemento> niveles();
    Elemento LCA(Elemento origen, Elemento destino);
    list<Elemento> camino(Elemento origen, Elemento destino);

    ArbolN<Elemento>& operator=(const ArbolN<Elemento> &a);
};

template<class Elemento>
ArbolN<Elemento>::ArbolN()
{
    this->peso = 0;
}

template<class Elemento>
ArbolN<Elemento>::ArbolN(Elemento e, list<ArbolN<Elemento>> Hijos){

}

template<class Elemento>
ArbolN<Elemento>::ArbolN(ArbolN<Elemento> &a){
    this->copiar(a);
}

template<class Elemento>
ArbolN<Elemento>::~ArbolN()
{

}

template<class Elemento>
NodoAN<Elemento> *ArbolN<Elemento>::copiarNodos(NodoAN<Elemento> *ptrNodo, int &contador)
{
    NodoAN<Elemento> *Aux;
    if(ptrNodo == nullptr){
        return nullptr;
    }
    ++contador; 
    Aux = new NodoAN<Elemento>(ptrNodo->getInfo(), copiarNodos(ptrNodo->getHijoIzq(),contador), copiarNodos(ptrNodo->getHermanoDer(),contador) );
    return Aux;
}

template<class Elemento>
void ArbolN<Elemento>::destruirNodos(NodoAN<Elemento> **ptrNodo){
    delete *ptrNodo;
}

template<class Elemento>
void ArbolN<Elemento>::copiar(const ArbolN<Elemento> &a){
    int aux = 1;
    NodoRaiz = copiarNodos(a.NodoRaiz,aux);
    this->peso = a.peso;
}

template<class Elemento>
void ArbolN<Elemento>::eliminarSubArbol(Elemento e){
    NodoAN<Elemento> *aux, *padre, *abuelo, *aux2, *elim;
    this->find(NodoRaiz,e,nullptr,nullptr, &aux, &padre, &abuelo);
    aux2 = padre->getHijoIzq();
    if(aux2 == aux){
        padre->setPointerHI(aux2->getHermanoDer());
        destruirNodos(&aux);
        return;
    }
    while (aux2->getHermanoDer() != nullptr)
    {
        if(aux2->getHermanoDer() == aux){
            aux2->setPointerHD(aux2->getHermanoDer()->getHermanoDer());
            destruirNodos(&aux);
            return;
        }
        aux2 = aux2->getHermanoDer();
    }
}

template<class Elemento>
void ArbolN<Elemento>::find(NodoAN<Elemento> *actual ,Elemento padre,NodoAN<Elemento> *papa2,NodoAN<Elemento> *abuelo, NodoAN<Elemento> **salida, NodoAN<Elemento> **dad, NodoAN<Elemento> **granddad){
    if(actual == nullptr){
        return;
    }
    NodoAN<Elemento> *aux = actual;
    if(aux->getInfo() == padre){
        *granddad = abuelo;
        *dad = papa2;
        *salida = actual;
        return;
    }
    aux = aux->getHijoIzq();
    this->find(aux,padre,actual,papa2,salida,dad,granddad);
    while (aux != nullptr)
    {
        aux = aux->getHermanoDer();
        this->find(aux,padre,actual,papa2,salida,dad,granddad);
    }
}

template<class Elemento>
void ArbolN<Elemento>::anadir(NodoAN<Elemento> *actual, Elemento nuevo){

    NodoAN<Elemento> *aux = new NodoAN<Elemento>;
    aux->setInfo(nuevo);
    ++(this->peso);
    aux->setPointerHD(actual->getHijoIzq());
    actual->setPointerHI(aux);
}

template<class Elemento>
void ArbolN<Elemento>::insertarNodo(Elemento padre, Elemento nuevo){
    NodoAN<Elemento> *aux, *papa, *abuelo;
    papa = abuelo = nullptr;
    find(NodoRaiz,padre,nullptr,nullptr, &aux, &papa, &abuelo);
    anadir(aux,nuevo);
    /*if(papa != nullptr && abuelo != nullptr){
        cout << abuelo->getInfo() << endl;
        cout << papa->getInfo() << endl;
        cout << padre << "\n\n";
    }*/
}

template<class Elemento>
Elemento ArbolN<Elemento>::getInfo(){
    return this->NodoRaiz->getInfo();
}

template<class Elemento>
void ArbolN<Elemento>::setInfo(Elemento e){
    if(NodoRaiz == nullptr){
        ++(this->peso);
        NodoRaiz = new NodoAN<Elemento>;
    }
    NodoRaiz->setInfo(e);
}

template<class Elemento>
list<Elemento> ArbolN<Elemento>::preOrden(){
    list<Elemento> result;
    this->preOrden(NodoRaiz, result);
    typename list<Elemento>::iterator it;
    for(it = result.begin(); it != result.end();++it){
        cout << *it << " "; 
    }
    return result;
}

template<class Elemento>
list<Elemento> ArbolN<Elemento>::inOrden(){
    list<Elemento> result;
    this->inOrden(NodoRaiz, result);

    typename list<Elemento>::iterator it;
    for(it = result.begin(); it != result.end();++it){
        cout << *it << " "; 
    }
    return result;
}

template<class Elemento>
list<Elemento> ArbolN<Elemento>::postOrden(){
    list<Elemento> result;
    this->postOrden(NodoRaiz, result);

    typename list<Elemento>::iterator it;
    for(it = result.begin(); it != result.end();++it){
        cout << *it << " "; 
    }
    return result;
}

template<class Elemento>
list<Elemento> ArbolN<Elemento>::niveles(){
    list<Elemento> result;
    queue<NodoAN<Elemento>*> aux;
    aux.push(NodoRaiz);
    this->niveles(aux,result);
    typename list<Elemento>::iterator it;
    for(it = result.begin(); it != result.end();++it){
        cout << *it << " "; 
    }
    return result;
}

template<class Elemento>
void ArbolN<Elemento>::preOrden(NodoAN<Elemento> *actual, list<Elemento> &result){
    NodoAN<Elemento> *aux;
    if(actual == nullptr){
        return;
    }
    result.push_back(actual->getInfo());
    aux = actual->getHijoIzq();
    while (aux != nullptr)
    {
        preOrden(aux,result);
        aux = aux->getHermanoDer();
    }
}

template<class Elemento>
void ArbolN<Elemento>::inOrden(NodoAN<Elemento> *actual, list<Elemento> &result){
    NodoAN<Elemento> *aux;
    if(actual == nullptr){
        return;
    }
    aux = actual->getHijoIzq();
    inOrden(aux,result);
    result.push_back(actual->getInfo());
    while (aux != nullptr)
    {
        aux = aux->getHermanoDer();
        inOrden(aux,result);
    }
}

template<class Elemento>
void ArbolN<Elemento>::postOrden(NodoAN<Elemento> *actual, list<Elemento> &result){
    if(actual == nullptr){
        return;
    }
    NodoAN<Elemento> *aux;
    aux = actual->getHijoIzq();
    while (aux != nullptr)
    {
        postOrden(aux,result);
        aux = aux->getHermanoDer();
    }
    result.push_back(actual->getInfo());
}

template <typename Elemento>
void ArbolN<Elemento>::niveles(queue<NodoAN<Elemento>*> actual,list<Elemento> &result){

    queue<NodoAN<Elemento>*> sigNivel;
    NodoAN<Elemento> *aux;

    while (!actual.empty()) {
        aux = actual.front()->getHijoIzq();
        while (aux != nullptr)
        {
            sigNivel.push(aux);
            aux = aux->getHermanoDer();
        }
        result.push_back(actual.front()->getInfo());
        actual.pop();
    }
    if(!sigNivel.empty()){
        this->niveles(sigNivel,result);
    }
}

template <class Elemento>
list<ArbolN<Elemento>> ArbolN<Elemento>::getHijos(){
    NodoAN<Elemento> *aux;
    list<ArbolN<Elemento>> res;
    ArbolN<Elemento> Hijos;
    int contador;
    aux = this->NodoRaiz;
    aux = aux->getHijoIzq();
    while (aux != nullptr)
    {
        /*Hijos.NodoRaiz = copiarNodos(aux,contador);
        Hijos.peso = contador;
        res.push_back(Hijos);*/
        cout << "Tiene errores con hacer listas de arboles no se pq\n";
        aux = aux->getHermanoDer();
    }
    /*while (!res.empty())
    {
        cout << res.back()->getInfo();
        res.pop_front();
    }*/
    
    return res;
}

template<class Elemento>
ArbolN<Elemento> ArbolN<Elemento>::nodoToArbol(NodoAN<Elemento> *nodo){
    ArbolN<Elemento> Hijo;
    int aux = 0;
    if(nodo != nullptr){
        Hijo.NodoRaiz = copiarNodos(nodo, aux);
        Hijo.peso = aux;
    }else{
        Hijo.NodoRaiz = nullptr;
    }
    return Hijo;
}

template<class Elemento>
ArbolN<Elemento> ArbolN<Elemento>::getHijoIzq(){
    return nodoToArbol(copiarNodos(NodoRaiz->getHijoIzq()));
}

template<class Elemento>
ArbolN<Elemento> ArbolN<Elemento>::getHermanoDerecho(){
    return nodoToArbol(copiarNodos(NodoRaiz->getHermanoDer()));
}

template<class Elemento>
void ArbolN<Elemento>::LCA(NodoAN<Elemento> *actual, Elemento origen, Elemento destino, int &contadorEncontrado, int *contTemp, bool &LCAEncontrado, Elemento &ancestro){
    int encontrados = 0;
    int totalTmp = 0;
    NodoAN<Elemento> *auxN;
    if(actual == nullptr){
        return;
    }
    auxN = actual->getHijoIzq();
    while (auxN != nullptr)
    {
        encontrados = 0;
        this->LCA(auxN,origen,destino, contadorEncontrado,&encontrados,LCAEncontrado,ancestro);
        totalTmp = totalTmp + encontrados;
        *contTemp = encontrados;
        auxN = auxN->getHermanoDer();
    }
    if(totalTmp == 2 && !LCAEncontrado){
        ancestro = actual->getInfo();
        LCAEncontrado = true;
    }
    *contTemp = totalTmp;
    if(actual->getInfo() == origen || actual->getInfo() == destino){
        ++contadorEncontrado;
        ++(*contTemp);
    }
}

template<class Elemento>
Elemento ArbolN<Elemento>::LCA(Elemento origen, Elemento destino){
    bool LCAEncontrado;
    int total = 0, cont = 0;
    Elemento ancestro;

    LCAEncontrado = false;
    this->LCA(NodoRaiz,origen,destino,total,&cont,LCAEncontrado,ancestro);
    return ancestro;
}

template<class Elemento>
void ArbolN<Elemento>::camino(NodoAN<Elemento> *actual, Elemento origen, Elemento destino, int &contadorEncontrado, int *contTemp, bool &LCAEncontrado, list<Elemento> &salida, list<Elemento> &aux){
    int encontrados = 0;
    int totalTmp = 0;
    NodoAN<Elemento> *auxN;
    if(actual == nullptr){
        return;
    }

    auxN = actual->getHijoIzq();
    while (auxN != nullptr)
    {
        encontrados = 0;
        this->camino(auxN,origen,destino, contadorEncontrado,&encontrados,LCAEncontrado,salida,aux);
        totalTmp = totalTmp + encontrados;
        *contTemp = encontrados;
        auxN = auxN->getHermanoDer();
    }
    if(totalTmp == 1){
        if(contadorEncontrado == 2){
            aux.push_front(actual->getInfo());
        }else{
            salida.push_back(actual->getInfo());
        }
    }else if(totalTmp == 2 && !LCAEncontrado){
        salida.push_back(actual->getInfo());
        salida.splice(salida.end(),aux);
        for (auto v: salida)
        {
            cout << v << endl;
        }
        LCAEncontrado = true;
    }
    *contTemp = totalTmp;
    if(actual->getInfo() == origen || actual->getInfo() == destino){
        ++contadorEncontrado;
        ++(*contTemp);
        if(contadorEncontrado == 2){
            aux.push_front(actual->getInfo());
        }else{
            salida.push_back(actual->getInfo());
        }
    }
}

template<class Elemento>
list<Elemento> ArbolN<Elemento>::camino(Elemento origen, Elemento destino){
    bool LCAEncontrado;
    int total = 0, cont = 0;
    list<Elemento> camino,aux;
    LCAEncontrado = false;
    this->camino(NodoRaiz,origen,destino,total,&cont,LCAEncontrado,camino,aux);
    return camino;
}

template <class Elemento>
ArbolN<Elemento>& ArbolN<Elemento>::operator=(const ArbolN<Elemento> &a){
    this->copiar(a);
    return *this;
}

#endif
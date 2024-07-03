#ifndef NODO_ARBOL_N_HEADER
#define NODO_ARBOL_N_HEADER

using namespace std;

template <class Elemento>
class NodoAN
{
    private:
        Elemento e;
        NodoAN<Elemento> *hijoIzq, *hermanoDer;

    public:
        NodoAN();
        NodoAN(Elemento e, NodoAN<Elemento> *izq = nullptr,NodoAN<Elemento> *der = nullptr);
        ~NodoAN();

        Elemento getInfo();
        void setInfo(Elemento e);

        NodoAN *getHijoIzq();
        NodoAN *getHermanoDer();

        void setPointerHI(NodoAN<Elemento> * e);
        void setPointerHD(NodoAN<Elemento> * e);

        void setHijoIzq(Elemento e);
        void setHermanoDer(Elemento e);
};

template <class Elemento>
NodoAN<Elemento>::NodoAN(){
    this->hijoIzq = nullptr;
    this->hermanoDer = nullptr;
}

template <class Elemento>
NodoAN<Elemento>::NodoAN(Elemento valor, NodoAN<Elemento> *izq,NodoAN<Elemento> *der){
    this->e = valor;
    this->hijoIzq = izq;
    this->hermanoDer = der;
}

template <class Elemento>
NodoAN<Elemento>::~NodoAN(){
    this->hijoIzq = nullptr;
    this->hermanoDer = nullptr;
}

template <class Elemento>
Elemento NodoAN<Elemento>::getInfo(){
    return this->e;
}

template <class Elemento>
void NodoAN<Elemento>::setInfo(Elemento valor){
    this->e = valor;
}

template <class Elemento>
NodoAN<Elemento>* NodoAN<Elemento>::getHijoIzq(){
    return this->hijoIzq;
}

template <class Elemento>
NodoAN<Elemento> *NodoAN<Elemento>::getHermanoDer(){
    return this->hermanoDer;
}

template <class Elemento>
void NodoAN<Elemento>::setHijoIzq(Elemento e){
    if(this->hijoIzq == nullptr){
        NodoAN<Elemento> *aux = new NodoAN<Elemento>;
        this->hijoIzq = aux;
    }
    this->hijoIzq->setInfo(e);
}

template <class Elemento>
void NodoAN<Elemento>::setHermanoDer(Elemento e){
    if(this->hermanoDer == nullptr){
        NodoAN<Elemento> *aux = new NodoAN<Elemento>;
        this->hermanoDer = aux;
    }
    this->hermanoDer->setInfo(e);
}

template<class Elemento>
void NodoAN<Elemento>::setPointerHI(NodoAN<Elemento> * e){
    this->hijoIzq = e;
};

template<class Elemento>
void NodoAN<Elemento>::setPointerHD(NodoAN<Elemento> * e){
    this->hermanoDer = e;
};

#endif
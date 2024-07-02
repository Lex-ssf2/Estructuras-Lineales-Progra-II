#include "Lista.h"
#include <iostream>

using namespace std;

template <class Elemento>
Lista<Elemento>::Lista(){
    this->primero = NULL;
    this->ultimo = NULL;
    this->n = 0;
}

template <class Elemento>
Lista<Elemento>::Lista(const Lista<Elemento> &L){
    this->primero = NULL;
    this->ultimo = NULL;
    this->n = 0;
    this->copiar(L);
}

template <class Elemento>
Lista<Elemento>::~Lista()
{
    this->vaciar();
}

template <class Elemento>
Elemento Lista<Elemento>::getPrimero(){
    return this->primero->getInfo();
}

template <class Elemento>
Elemento Lista<Elemento>::getUltimo(){
    return this->ultimo->getInfo();
}

template <class Elemento>
int Lista<Elemento>::getLongitud(){
    return this->n;
}

template <class Elemento>
void Lista<Elemento>::insertar(Elemento e, int pos)
{
    Nodo<Elemento> *nuevo, *aux;
    nuevo = new Nodo<Elemento>(e);
    this->n++;
    if(this->n == 1 || pos == 0)
    {
        aux = this->primero;
        this->primero = nuevo;
        this->primero->setSig(aux);
        if(this->n == 1)
          this->ultimo = this->primero;
        return;
    }
    if(pos >= this->n)
    {
        aux = this->ultimo;
        this->ultimo->setSig(nuevo);
        this->ultimo = this->ultimo->getSig();
        return;
    }
    int contador = 1;
    aux = this->primero;
    for(contador = 1; contador <= pos;contador++)
    {
        if(contador == pos)
        {
            nuevo->setSig(aux->getSig());
            aux->setSig(nuevo);
            return;
        }
        aux = aux->getSig();
    }

}

template <class Elemento>
void Lista<Elemento>::eliminar (int pos){
    Nodo<Elemento> *aux, *old;
    if(this->esVacia())
        return;
    aux = this->primero;
    this->n--;
    if(pos == 0)
    {
        this->primero = this->primero->getSig();
        delete aux;
        return;
    }
    int contador;
    for(contador = 1; contador <= this->n;contador++)
    {
        if(contador == pos)
        {
            old = aux->getSig();
            aux->setSig(old->getSig());
            delete old;
            return;
        }
        aux = aux->getSig();
    }
}

template <class Elemento>
void Lista<Elemento>::imprimir(){
    Nodo<Elemento> *aux;
    if(this->n <= 0){
        cout << endl;
        return;
    }
    for(aux = this->primero;aux != NULL;aux = aux->getSig())
    {
        cout << aux->getInfo() << " , ";
    }
    cout << endl;
}

template <class Elemento>
bool Lista<Elemento>::esVacia(){
    return this->n == 0 ? true : false;
}

template <class Elemento>
void Lista<Elemento>::vaciar(){
    while(!this->esVacia())
    {
        this->eliminar(0);
    }
    this->primero = NULL;
    this->ultimo = NULL;
}

template <class Elemento>
bool Lista<Elemento>::esta(Elemento e){
    Nodo<Elemento> *aux;
    aux = this->primero;
    for(aux = this->primero;aux != NULL;aux = aux->getSig())
    {
        if(e == aux->getInfo())
            return true;
    }
    return false;
}

template <class Elemento>
Elemento Lista<Elemento>::consultar(int pos){
    Nodo<Elemento> *aux;
    int actual;
    for(aux = this->primero,actual = 0;aux != NULL || actual > pos;aux = aux->getSig(), actual++)
    {
        if(pos == actual)
            return aux->getInfo();
    }
    return Elemento(NULL);
}

template <class Elemento>
int Lista<Elemento>::obtPos(Elemento e){
    Nodo<Elemento> *aux;
    int pos;
    for(aux = this->primero, pos = 0 ;aux != NULL;aux = aux->getSig(), pos++)
    {
        if(e == aux->getInfo())
            return pos;
    }
    return -1;
}

template <class Elemento>
void Lista<Elemento>::eliminarE(Elemento e){
    Nodo<Elemento> *cur , *next;
    if(this->esVacia())
        return;
    cur = this->primero;
    next = cur->getSig();
    if(e == cur->getInfo())
    {
        this->eliminar(0);
        return;
    }
    for(;cur->getSig() != NULL;cur = next)
    {
        next = cur->getSig();
        if(e == next->getInfo())
        {
            cur->setSig(next->getSig());
            delete next;
            this->n--;
            return;
        }
    }
    return;
}

template <class Elemento>
void Lista<Elemento>::modificar (Elemento e, int pos){
    Nodo<Elemento> *aux;
    int actual;
    for(aux = this->primero,actual = 0;aux != NULL || actual > pos;aux = aux->getSig(), actual++)
    {
        if(pos == actual){
            aux->setInfo(e);
            return;
        }
    }
    return;
}

template <class Elemento>
void Lista<Elemento>::invertir()
{
    if(this->esVacia())
        return;
    Nodo<Elemento> *ant = NULL, *actual = this->primero, *sig;
    this->ultimo = this->primero;
    for(;actual != NULL; actual = sig)
    {
        sig = actual->getSig();
        actual->setSig(ant);
        ant = actual;
    }
    this->primero = ant;
    return;
}

template <class Elemento>
void Lista<Elemento>::concat(Lista<Elemento> l){
    this->ultimo->setSig(l.primero);
    this->ultimo = l.ultimo; 
}

template <class Elemento>
void Lista<Elemento>::ordenBurbuja(){
    if(this->esVacia())
        return;
    int i, j;
    Nodo<Elemento> *aux, *aux2;
    for(i = 0; i <= this->n; i++){
        aux = this->primero;
        for(j = 0; j < this->n - i - 1; j++)
        {
            aux2 = aux->getSig();
            if(aux->getInfo() > aux2->getInfo())
            {
                Elemento temp = aux2->getInfo();
                aux2->setInfo(aux->getInfo());
                aux->setInfo(temp);
            }
            aux = aux->getSig();
        }
    }
}

template <class Elemento>
void Lista<Elemento>::copiar(const Lista<Elemento> &L){
    Nodo<Elemento> *actualCopia = L.primero ,*actual;
    this->vaciar();
    this->n = L.n;
    if(L.n <= 0)
        return;
    actual = new Nodo<Elemento>();
    actual->setInfo(actualCopia->getInfo());
    this->primero = actual;
    actualCopia = actualCopia->getSig();
    for(; actualCopia != NULL ; actualCopia = actualCopia->getSig())
    {
        actual->setSig(new Nodo<Elemento>());
        actual = actual->getSig();
        actual->setInfo(actualCopia->getInfo());
    }
    actual->setSig(NULL);
    this->ultimo = actual;
}

template <class Elemento>
Lista<Elemento>& Lista<Elemento>::operator=(const Lista<Elemento> &L){
    this->copiar(&L);
}

template <class Elemento>
Elemento Lista<Elemento>::operator [] (int pos){
    this->consultar(pos);
}

template <class Elemento>
Lista<Elemento>& Lista<Elemento>::operator<<(Elemento elem){
    this->insertar(elem ,this->getLongitud() + 1);
    return *this; 
}

template <class Elemento>
Lista<Elemento>& Lista<Elemento>::operator--(int){
    this->eliminar(0);
    return *this;
}

template <class Elemento>
Lista<Elemento>& Lista<Elemento>::operator!(){
    this->invertir();
    return *this;
}

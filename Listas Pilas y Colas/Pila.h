#ifndef PILA_H
#define PILA_H
#include "Nodo.h"

template<class e> 
class Pila{
    //atributos
    private:
        Nodo<e> *tope;
        int longitud;
    //Metodos
    public:
        Pila();
        Pila(const Pila &p);
        ~Pila();
        void copiar(const Pila &p);
        void vaciar();
        void apilar(e Elemento);
        void desapilar();
        void invertir();
        void imprimir();
        void concat(Pila &p); //wip

        e getTope();
        bool esVacia();
        int getLongitud();
    
    //Operadores Miembros
        Pila<e>& operator=(const Pila<e> &p);
		Pila<e>& operator<<(e elem);
		Pila<e>& operator--(int);
		Pila<e>& operator!();
};
#endif
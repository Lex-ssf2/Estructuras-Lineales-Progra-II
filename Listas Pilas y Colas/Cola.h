#ifndef COLA_H
#define COLA_H
#include "Nodo.h"

template<class e>
class Cola{
    //atributos
    private:
        Nodo<e> *frente,*final;
        int longitud;
    
    //Metodos
    public:
        Cola();
        Cola(const Cola<e> &c);
        ~Cola();
        void copiar(const Cola<e> &c);
        void encolar(e Elemento);
        void concat(Cola<e> &c); // para el final Xd
        void desencolar();
        void vaciar();
        e getFrente();
        e getFinal();
        bool esVacia();
        void invertir();
        void imprimir(); 

    //Operadores Miembros
        Cola<e>& operator=(const Cola<e> &c);
		Cola<e>& operator<<(e elem);
		Cola<e>& operator--(int);
		Cola<e>& operator!();
};
#endif
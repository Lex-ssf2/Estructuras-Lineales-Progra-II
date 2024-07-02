#ifndef NODO_H
#define NODO_H

template <class Elemento>
class Nodo
{
protected:
    Elemento info;
    Nodo<Elemento>* sig;
public:
    Nodo();
    Nodo(Elemento valor); 
    Nodo(Elemento valor, Nodo<Elemento>* next);

    Elemento getInfo();
    Nodo<Elemento>* getSig();

    void setInfo(Elemento e);
    void setSig(Nodo<Elemento>* next);

    ~Nodo();
};

#endif
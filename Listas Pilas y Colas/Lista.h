#ifndef LISTA_H
#define LISTA_H
#include "Nodo.h"
template <class Elemento>
class Lista
{
	//atributos
	private:
		Nodo<Elemento> *primero, *ultimo;
		int n;
	//metodos
	public: 
		Lista();
		Lista(const Lista<Elemento> &L);
		~Lista();
		void copiar (const Lista<Elemento> &L);
		void vaciar();
		bool esVacia();
		void imprimir();

		Elemento getPrimero();
		Elemento getUltimo();
		int getLongitud();

		bool esta(Elemento e);
		Elemento consultar(int pos);
		int obtPos(Elemento e);

		void insertar(Elemento e, int pos);
		void eliminar (int pos);
		void eliminarE (Elemento e);
		void modificar (Elemento e, int pos);

		void invertir();
		void concat(Lista<Elemento> l);
		void ordenBurbuja ();

	//Operadores Miembros
		Lista<Elemento>& operator=(const Lista<Elemento> &L);
		Elemento operator [] (int pos);
		Lista<Elemento>& operator<<(Elemento elem);
		Lista<Elemento>& operator--(int);
		Lista<Elemento>& operator!();

};

#endif
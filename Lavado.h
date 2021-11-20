#pragma once
#include "Prenda.h"

class Lavado {

	public:
		Lavado();
		Lavado(int posicion);
		~Lavado();
		void asignarPosicion(int pos_nueva);
		void aniadirPrenda(Prenda* prenda);
		int devolverTiempo();
		int devolverCantidadDePrendasEnElLavado();
		bool esIgualA(Lavado* lavado);
		bool esCompatibleCon(Prenda* prenda);
		bool tieneLaPrendaDeNombre(int nombre);
		vector<Prenda> devolverPrendas();

	private:
		int posicion_lavado;
		vector<Prenda> prendas;
		int tiempo_lavado;

};
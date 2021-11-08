#pragma once
#include "Prenda.h"

class Lavado {

	public:
		Lavado(int posicion);
		~Lavado();
		void aniadirPrenda(Prenda* prenda);
		int devolverTiempo();
		int devolverCantidadDePrendasEnElLavado();
		vector<Prenda> devolverPrendas();

	private:
		int posicion_lavado;
		vector<Prenda> prendas;
		int tiempo_lavado;

};
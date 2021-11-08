#pragma once
#include "Lavado.h"

class Solucion {

	public:

		Solucion(int max_prendas);
		~Solucion();
		void agregarLavado(Lavado* lavado);
		int devolverTiempoTotal();
		void mostrarPrendasFaltantes();	//nos dice que prendas falta agregar para completar el set
		void mostrarLavados();	//va a mostrar que lavados se encuentran en esta solucion (que prendas poseen, posicion del lavado, etc)

	private:

		vector<Lavado> lavados;
		int tiempo_neto;
		int cant_total_prendas;
		int max_cant_prendas;

};
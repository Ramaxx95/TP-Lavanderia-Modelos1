#pragma once
#include <stdio.h>
#include<stdlib.h>
#include<vector>

using namespace std;

class Prenda{

	public:
		Prenda(int nombre, int tiempo);
		~Prenda();
		void aniadirPrendaCompatible(Prenda* prenda);
		int devolverTiempoDeLavado();
		int devolverNombre();
		int devolverCantidadDeCompatibilidades();
		Prenda* obtenerCompatible(int indice);
		bool esCompatibleCon(Prenda* prenda);

	private:
		int nombre;
		vector<Prenda> lista_compatibles;
		int tiempo_lavado;
		
};

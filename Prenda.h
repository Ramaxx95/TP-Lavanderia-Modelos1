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
		void cambiarNombre(int nombre_nuevo);
		void cambiarTiempo(int tiempo_nuevo);
		int devolverTiempoDeLavado();
		int devolverNombre();
		int devolverCantidadDeCompatibilidades();
		Prenda* obtenerCompatible(int indice);
		vector<Prenda*> obtenerListaDeCompatibles();
		bool esCompatibleCon(Prenda* prenda);

	private:
		int nombre;
		vector<Prenda*> lista_compatibles;
		int tiempo_lavado;
		
};

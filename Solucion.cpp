#include "Solucion.h"

Solucion::Solucion(int max_prendas) {

	this->tiempo_neto = 0;
	this->cant_total_prendas = 0;
	this->max_cant_prendas = max_prendas;

}

void Solucion::agregarLavado(Lavado* lavado) {

	this->lavados.push_back(*lavado);
	this->cant_total_prendas += lavado->devolverCantidadDePrendasEnElLavado();
	this->tiempo_neto += lavado->devolverTiempo();

}

int Solucion::devolverTiempoTotal() {

	return this->tiempo_neto;

}

void Solucion::mostrarLavados() {

	for (int i = 0; i < this->lavados.size(); i++) {

		printf("Lavado %d:\n", i + 1);
		vector<Prenda> prendas_lavado = this->lavados[i].devolverPrendas();

		for (int j = 0; j < this->lavados[i].devolverCantidadDePrendasEnElLavado(); j++) {

			int num_prenda = prendas_lavado[j].devolverNombre();
			printf(" %d ", num_prenda);

		}

		printf("\n\n");

	}

}

void Solucion::mostrarPrendasFaltantes() {

	int contador_pren_falt = 0;

	for (int i = 0; i < this->max_cant_prendas; i++) {

		bool la_prenda_esta = false;
		int k = 0;

		while (( k < this->lavados.size())&&(!la_prenda_esta)) {

			vector<Prenda> prendas_lavado = this->lavados[k].devolverPrendas();

			for (int j = 0; j < this->lavados[k].devolverCantidadDePrendasEnElLavado(); j++) {

				int num_prenda = prendas_lavado[j].devolverNombre();
				if (num_prenda == (i+1)) {

					la_prenda_esta = true;

				}

			}

			k++;
		}
		
		if (!la_prenda_esta) {

			printf(" %d ", i+1);
			contador_pren_falt++;

		}

	}
	printf("\n");
	printf("Faltan un total de %d prendas\n\n", contador_pren_falt);
	

}

Solucion::~Solucion() {

	this->lavados.clear();

}
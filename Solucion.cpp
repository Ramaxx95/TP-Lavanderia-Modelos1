#include "Solucion.h"

Solucion::Solucion(int max_prendas) {

	this->tiempo_neto = 0;
	this->cant_total_prendas = 0;
	this->max_cant_prendas = max_prendas;

}

void Solucion::agregarLavado(Lavado* lavado) {

	if (!yaPoseeAlgunaPrendaDeEste(lavado)) {

		this->lavados.push_back(*lavado);
		this->cant_total_prendas += lavado->devolverCantidadDePrendasEnElLavado();
		this->tiempo_neto += lavado->devolverTiempo();

	}
	
}

void Solucion::agregarLavados(vector<Lavado> lavados) {

	for (int i = 0; i < lavados.size(); i++) {

		this->agregarLavado(&lavados[i]);

	}

}

int Solucion::devolverTiempoTotal() {

	return this->tiempo_neto;

}

int Solucion::devolverMaxPrendas() {

	return this->max_cant_prendas;

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

int Solucion::mostrarPrendasFaltantes() {

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
	
	return contador_pren_falt;

}

bool Solucion::seEncuentraLaPrendaDeNombre(int nombre) {

	bool se_encuentra = false;
	int ind = 0;

	while ((ind < this->lavados.size()) && !se_encuentra) {

		se_encuentra = this->lavados[ind].tieneLaPrendaDeNombre(nombre);
		ind++;

	}

	return se_encuentra;

}

Solucion::~Solucion() {

	this->lavados.clear();

}

/****Funciones Privadas****/

bool Solucion::yaPoseeAlgunaPrendaDeEste(Lavado* lavado) {

	int cant_repeticiones = 0;
	bool alguna_prenda_repetida = false;

	for (int ind_prenda_lavado = 0; ind_prenda_lavado < lavado->devolverCantidadDePrendasEnElLavado(); ind_prenda_lavado++) {

		for (int lav_sol = 0; lav_sol < this->lavados.size(); lav_sol++) {

			if (this->lavados[lav_sol].tieneLaPrendaDeNombre(lavado->devolverPrendas()[ind_prenda_lavado].devolverNombre())){

				cant_repeticiones++;

			}

		}

	}

	if (cant_repeticiones > 0) {

		alguna_prenda_repetida = true;

	}

	return alguna_prenda_repetida;

}
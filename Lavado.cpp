#include "Lavado.h"

Lavado::Lavado(int posicion) {

	this->posicion_lavado = posicion;
	this->tiempo_lavado = 0;

}

void Lavado::aniadirPrenda(Prenda* prenda) {

	if (this->prendas.size() == 0) {

		this->prendas.push_back(*prenda);
		if (prenda->devolverTiempoDeLavado() > this->tiempo_lavado) {

			this->tiempo_lavado = prenda->devolverTiempoDeLavado();

		}

	}
	else {

		bool es_compatible = false;

		for (int i = 0; i < this->prendas.size(); i++) {

			if (this->prendas[i].esCompatibleCon(prenda)) {
				
				es_compatible = true;

			}
			else {

				es_compatible = false;
				i = this->prendas.size(); //termino el ciclo

			}

		}

		if (es_compatible) {

			this->prendas.push_back(*prenda);
			if (prenda->devolverTiempoDeLavado() > this->tiempo_lavado) {

				this->tiempo_lavado = prenda->devolverTiempoDeLavado();

			}

		}

	}

}

int Lavado::devolverTiempo() {

	return this->tiempo_lavado;

}

int Lavado::devolverCantidadDePrendasEnElLavado() {

	return this->prendas.size();

}

vector<Prenda> Lavado::devolverPrendas() {

	return this->prendas;

}

Lavado::~Lavado() {

	this->prendas.clear();

}
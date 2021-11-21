#include "Lavado.h"

Lavado::Lavado() {

	this->posicion_lavado = 0;
	this->tiempo_lavado = 0;

}

Lavado::Lavado(int posicion) {

	this->posicion_lavado = posicion;
	this->tiempo_lavado = 0;

}

void Lavado::asignarPosicion(int pos_nueva) {

	this->posicion_lavado = pos_nueva;

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

//elimina la ULTIMA prenda que se encuentra en la lista de prendas
void Lavado::quitarPrenda() {

	this->prendas.pop_back();

	int nuevo_tiempo_lavado = 0;

	for (int i = 0; i < this->prendas.size(); i++) {

		if (this->prendas[i].devolverTiempoDeLavado() > nuevo_tiempo_lavado) {

			nuevo_tiempo_lavado = this->prendas[i].devolverTiempoDeLavado();

		}

	}

	this->tiempo_lavado = nuevo_tiempo_lavado;

}

int Lavado::devolverTiempo() {

	return this->tiempo_lavado;

}

int Lavado::devolverCantidadDePrendasEnElLavado() {

	return this->prendas.size();

}

bool Lavado::esIgualA(Lavado* lavado) {

	bool son_iguales = false;
	int cant_prendas_iguales = 0;

	if (this->prendas.size() == lavado->devolverCantidadDePrendasEnElLavado()) {

		for (int indice = 0; indice < this->prendas.size(); indice++) {

			if (lavado->tieneLaPrendaDeNombre(this->prendas[indice].devolverNombre())) {

				cant_prendas_iguales++;

			}

		}

		if (cant_prendas_iguales == this->devolverCantidadDePrendasEnElLavado()) {

			son_iguales = true;

		}

	}

	return son_iguales;

}

bool Lavado::esCompatibleCon(Prenda* prenda) {

	bool es_compatible = true;
	int indice = 0;

	while ((indice < this->prendas.size()) && (es_compatible)) {

		es_compatible = (prenda->esCompatibleCon(&this->prendas[indice])
						&& (this->prendas[indice].esCompatibleCon(prenda)));
		indice++;

	}

	return es_compatible;

}

bool Lavado::tieneLaPrendaDeNombre(int nombre) {

	int indice = 0;
	bool contiene_la_prenda = false;

	while ((indice < this->prendas.size()) && (!contiene_la_prenda)) {

		contiene_la_prenda = (this->prendas[indice].devolverNombre() == nombre);
		indice++;

	}

	return contiene_la_prenda;

}

vector<Prenda> Lavado::devolverPrendas() {

	return this->prendas;

}

Lavado::~Lavado() {

	this->prendas.clear();

}
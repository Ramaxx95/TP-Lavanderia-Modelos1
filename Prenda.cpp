#include "Prenda.h"

Prenda::Prenda(int nombre, int tiempo) {

	this->nombre = nombre;
	this->tiempo_lavado = tiempo;

}

void Prenda::aniadirPrendaCompatible(Prenda* prenda) {

	this->lista_compatibles.push_back(prenda);

}

void Prenda::cambiarNombre(int nombre_nuevo) {

	this->nombre = nombre_nuevo;

}

void Prenda::cambiarTiempo(int tiempo_nuevo) {

	this->tiempo_lavado = tiempo_nuevo;

}

int Prenda::devolverTiempoDeLavado() {

	return this->tiempo_lavado;

}

int Prenda::devolverNombre() {

	return this->nombre;

}

int Prenda::devolverCantidadDeCompatibilidades() {

	return this->lista_compatibles.size();

}

Prenda* Prenda::obtenerCompatible(int indice) {

	return this->lista_compatibles[indice];

}

vector<Prenda*> Prenda::obtenerListaDeCompatibles() {

	return this->lista_compatibles;

}

bool Prenda::esCompatibleCon(Prenda* prenda) {

	bool resultado = false;
	int nombre_prenda, nombre_pren_lista;

	nombre_prenda = prenda->devolverNombre();

	int i = 0;

	while ((i < this->lista_compatibles.size()) && resultado == false) {

		nombre_pren_lista = this->lista_compatibles[i]->devolverNombre();

		if (nombre_prenda == nombre_pren_lista) {

			resultado = true;

		}

		i++;

	}

	return resultado;

}

Prenda::~Prenda() {

	this->lista_compatibles.clear();

}
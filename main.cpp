#include <stdio.h>
#include <stdlib.h>
#include "leer_archivo.h"
#include "Solucion.h"

Prenda* buscarPrendaMinima(vector<Prenda*> prendas) {

	Prenda* prenda_minima = prendas[0];

	for (int i = 1; i < prendas.size(); i++) {

		if (prendas[i]->devolverTiempoDeLavado() < prenda_minima->devolverTiempoDeLavado()) {

			prenda_minima = prendas[i];

		}

	}

	return prenda_minima;

}

//elimina todo lavado repetido dentro de la lista
void limpiarListaDeLavados(vector<Lavado>* lavados) {

	if (lavados->size() > 0) {

		for (int i = 0; i < lavados->size(); i++) {

			for (int j = 0; j < lavados->size(); j++) {

				if ((lavados->at(j).esIgualA(&lavados->at(i))) && (i != j)) {

					lavados->erase(lavados->begin() + j);

				}

			}

		}

	}

}

//analiza que Prendas faltan en la solucion y agrega la cantidad de lavados necesarios
//para completar el set de Prendas faltantes
void completarRestoDeLasPrendas(Solucion* sol) {


	for (int i = 0; i < sol->devolverMaxPrendas(); i++) {

		if (!sol->seEncuentraLaPrendaDeNombre(i + 1)) {

			Lavado lavado_aux;
			lavado_aux.aniadirPrenda(&devolverListaDePrendas()[i]);

			for (int j = 0; j < sol->devolverMaxPrendas(); j++) {

				if ((!sol->seEncuentraLaPrendaDeNombre(j + 1)) && (j != i)) {

					if (lavado_aux.esCompatibleCon(&devolverListaDePrendas()[j])) {

						lavado_aux.aniadirPrenda(&devolverListaDePrendas()[j]);

					}

				}
			}

			sol->agregarLavado(&lavado_aux);

		}
		
	}

}

//De una lista de lavados, devuelve la cantidad indicada de lavados cuyo tiempo son los mas chicos 
//de la lista especificada
vector<Lavado>* buscarLavadosConMenorTiempoDe(vector<Lavado>* lavados, int cant_lavados) {

	vector<Lavado>* lavados_minimos = new vector<Lavado>;

	for (int i = 0; i < lavados->size(); i++) {

		if (i == 0) {

			lavados_minimos->push_back(lavados->at(i));

		}
		else {

			for (int j = 0; j < lavados_minimos->size(); j++) {

				if (lavados->at(i).devolverTiempo() <= lavados_minimos->at(j).devolverTiempo()) {

					lavados_minimos->insert(lavados_minimos->begin() + j, lavados->at(i));
					j = lavados_minimos->size();

					if (lavados_minimos->size() > cant_lavados) {

						lavados_minimos->pop_back();

					}

				}

			}

		}

	}

	return lavados_minimos;

}

//funcion RECURSiVA
//recorre cada compatible de "prenda" y si es compatible con el "lavado" completo->la agrega
void buscarSiguienteCompatiblePara(Prenda* prenda, Lavado* lavado, int a_partir_de, vector<Lavado>* lavados) {

	Lavado aux(lavados->size());
	vector<Prenda*> compatibles = prenda->obtenerListaDeCompatibles();

	for (int i = a_partir_de; i < compatibles.size(); i++) {

		if (lavado->esCompatibleCon(compatibles[i])) {

			aux.aniadirPrenda(compatibles[i]);
			lavados->push_back(aux);
			buscarSiguienteCompatiblePara(prenda, &aux, a_partir_de + 1, lavados);

		}

		limpiarListaDeLavados(lavados);

	}

	for (int j = 0; j < lavado->devolverCantidadDePrendasEnElLavado() - 1; j++) {

		aux.aniadirPrenda(&lavado->devolverPrendas()[j]);
		lavados->push_back(aux);

	}


}

//busca toda combinacion de lavado para una prenda en especial y las guarda de menor a mayor en una lista
//de lavados
//TODO: funciona pero solo devuelve la cantidad que tiene de compatibles la prenda en si (para la
//prenda 1, solo devuelve 8 lavados cuando tendria que devolver 24)

void buscarPosiblesLavadosPara(Prenda* prenda) {

	vector<Prenda*> compatibles = prenda->obtenerListaDeCompatibles();
	vector<Lavado> lavados;

	int num_lavado = 0;

	for (int i = 0; i < compatibles.size(); i++) {

			Lavado lavado_aux(num_lavado);
			lavado_aux.aniadirPrenda(prenda);

			if (lavado_aux.esCompatibleCon(compatibles[i])){

				lavado_aux.aniadirPrenda(compatibles[i]);
				buscarSiguienteCompatiblePara(prenda, &lavado_aux, i, &lavados);
			
			}
			/*
			if (lavados.size() > 0) {
				for (int k = 0; k < lavados.size(); k++) { 
					
					if (lavados.at(k).esIgualA(&lavado_aux)) {

						lavados.erase(lavados.begin()+k);

					}
				}
					
			}
			*/
			lavados.push_back(lavado_aux);
			num_lavado++;
		
	}

	/*DEBUG*/
	
	Solucion sol(385);//hardcodeo
	sol.agregarLavados(lavados);
	printf("Cantidad de lavados posibles para la Prenda %d\n\n", prenda->devolverNombre());
	sol.mostrarLavados();
	
	Solucion sol_min(385);//hardcodeo
	vector<Lavado>* lav_min = buscarLavadosConMenorTiempoDe(&lavados, 7);
	sol_min.agregarLavados(*lav_min);
	printf("7 lavados con menor tiempo de lavado para la Prenda 1\n\n");
	sol_min.mostrarLavados();
	/*END DEBUG*/
}

//POSIBLE FUNCION QUE ENCOMPASE LA BUSQUEDA DE LA SOLUCION OPTIMA
void buscarLavadosMinimos(vector<Prenda> prendas, Solucion* sol) {

	vector<Lavado> lavados_minimos;

	for (int i = 0; i < prendas.size() / 2; i++) {

		vector<Prenda*> compatibles = prendas[i].obtenerListaDeCompatibles();
		Lavado lavado_a_agregar(i);
		lavado_a_agregar.aniadirPrenda(&prendas[i]);


		lavados_minimos.push_back(lavado_a_agregar);

	}

	sol->agregarLavados(lavados_minimos);

	sol->mostrarLavados();
	printf("tiempo: %d\n", sol->devolverTiempoTotal());

}

/*PARA HACER PRUEBAS*/
void prueba() {


}

int main(int argc, char* argv[]) {

	leer_archivo((char *)"primer_problema.txt");

	int res = get_params();
	if (res > 0) {

		armar_matriz();
		crear_prendas();

	}

	vector<Prenda> lista = devolverListaDePrendas();
	Solucion solucion(lista.size()); 

	//buscarLavadosMinimos(devolverListaDePrendas(), &solucion);
	//buscarPosiblesLavadosPara(&lista[0]);
	prueba();
	liberar_memoria();
}


/*******BACKUP*******/
//busca toda combinacion de lavado para una prenda en especial y las guarda de menor a mayor en una lista
//de lavados
//TODO: funciona en el contexto del primer tp. Expandir para entrar en el esquema del segundo tp

/*void buscarPosiblesLavadosPara(Prenda* prenda) {

	vector<Prenda*> compatibles = prenda->obtenerListaDeCompatibles();
	vector<Lavado> lavados;

	int num_lavado = 0;

	for (int i = 0; i < compatibles.size(); i++) {

		if (prenda->esCompatibleCon(compatibles[i])) {

			for (int j = 0; j < compatibles[i]->devolverCantidadDeCompatibilidades(); j++) {

				Lavado lavado_aux(num_lavado);
				lavado_aux.aniadirPrenda(prenda);
				lavado_aux.aniadirPrenda(compatibles[i]);

				bool es_comp = true;
				int indice = 0;
				while ((lavado_aux.devolverCantidadDePrendasEnElLavado() - indice > 0) && es_comp) {

					//antes era copatibles[i]
					es_comp = lavado_aux.devolverPrendas()[indice].esCompatibleCon(compatibles[i]->obtenerListaDeCompatibles()[j]);
					indice++;

				}

				if (es_comp)
				{
					lavado_aux.aniadirPrenda(compatibles[i]->obtenerListaDeCompatibles()[j]);
				}

				if (lavados.size() > 0) {

					for (int k = 0; k < lavados.size(); k++) {

						if (lavados.at(k).esIgualA(&lavado_aux)) {

							lavados.erase(lavados.begin() + k);

						}
					}

				}
				lavados.push_back(lavado_aux);
				num_lavado++;
			}

		}

	}

}*/

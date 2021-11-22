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

vector<Lavado>* buscarLavadosConMayorCantidadDePrendas(vector<Lavado>* lavados) {

	vector<Lavado>* lavados_grandes = new vector<Lavado>;
	int lav_mayor_cant_pren = 0;

	for (int i = 0; i < lavados->size(); i++) {

		if (lavados->at(i).devolverCantidadDePrendasEnElLavado() > lav_mayor_cant_pren) {

			lav_mayor_cant_pren = lavados->at(i).devolverCantidadDePrendasEnElLavado();

		}

	}

	for (int j = 0; j < lavados->size(); j++) {

		if (lavados->at(j).devolverCantidadDePrendasEnElLavado() > lav_mayor_cant_pren/2) {//lav_mayor / 2

			lavados_grandes->push_back(lavados->at(j));

		}

	}

	return lavados_grandes;

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


//busca toda combinacion de lavado para una prenda en especial y las guarda de menor a mayor en una lista
//de lavados
//TODO: funciona pero solo en el contexto del primer tp

void buscarPosiblesLavadosPara(Prenda* prenda, vector<Lavado>* lavados) {

	vector<Prenda*> compatibles = prenda->obtenerListaDeCompatibles();

	int num_lavado = 0;

	for (int i = 0; i < compatibles.size(); i++) {

			Lavado lavado_aux(num_lavado);
			lavado_aux.aniadirPrenda(prenda);

			if (lavado_aux.esCompatibleCon(compatibles[i])){

				lavado_aux.aniadirPrenda(compatibles[i]);
				lavados->push_back(lavado_aux);

				for (int j = 0; j < compatibles.size(); j++) {

					if ((lavado_aux.esCompatibleCon(compatibles[j])) && (j != i)) {

						lavado_aux.aniadirPrenda(compatibles[j]);
						lavados->push_back(lavado_aux);

						lavado_aux.quitarPrenda();

					}

				}
			
			}
			
			num_lavado++;
		   
	}

	limpiarListaDeLavados(lavados);

}

//FUNCION QUE SE ENCARGA DE LA BUSQUEDA DE LA SOLUCION OPTIMA
void buscarLavadosMinimos(vector<Prenda> prendas, Solucion* sol) {

	vector<Lavado>* lavados_minimos = new vector<Lavado>;

	for (int i = 0; i < 1; i++) { //prendas.size()/2

		vector<Lavado>* lav_min_i = new vector<Lavado>;

		//Primero: buscamos todo posible lavado que se pueda hacer con la prenda "i"
		buscarPosiblesLavadosPara(&prendas[i], lav_min_i);

		//Despues: de los lavados encontrados, nos quedamos con los que lavan la mayor cantidad de prendas posibles
		lav_min_i = buscarLavadosConMayorCantidadDePrendas(lav_min_i);

		//Por ultimo: nos quedamos con aquellos lavados que tardan menos en realizarse
		lav_min_i = buscarLavadosConMenorTiempoDe(lav_min_i, 1);

		if (lavados_minimos->empty()) {

			lavados_minimos->swap(*lav_min_i);

		}
		else {

			lavados_minimos->insert(lavados_minimos->end(), lav_min_i->begin(), lav_min_i->end());

		}
		
	}

	sol->agregarLavados(*lavados_minimos);

	completarRestoDeLasPrendas(sol);

	sol->mostrarLavados();
	printf("tiempo: %d\n", sol->devolverTiempoTotal());
	sol->mostrarPrendasFaltantes();

}

/*PARA HACER PRUEBAS*/
void prueba() {


}

int main(int argc, char* argv[]) {

	leer_archivo((char *)"segundo_problema.txt");

	int res = get_params();
	if (res > 0) {

		armar_matriz();
		crear_prendas();

	}

	vector<Prenda> lista = devolverListaDePrendas();
	Solucion solucion(lista.size()); 

	buscarLavadosMinimos(lista, &solucion);
	//prueba();
	liberar_memoria();
}


/*******BACKUP*******/

/*
void buscarPosiblesLavadosPara(Prenda* prenda) {

	vector<Prenda*> compatibles = prenda->obtenerListaDeCompatibles();
	vector<Lavado> lavados;

	int num_lavado = 0;

	for (int i = 0; i < compatibles.size(); i++) {

			Lavado lavado_aux(num_lavado);
			lavado_aux.aniadirPrenda(prenda);

			if (lavado_aux.esCompatibleCon(compatibles[i])){

				lavado_aux.aniadirPrenda(compatibles[i]);
				lavados.push_back(lavado_aux);

				for (int j = 0; j < compatibles.size(); j++) {

					if ((lavado_aux.esCompatibleCon(compatibles[j])) && (j != i)) {

						lavado_aux.aniadirPrenda(compatibles[j]);
						lavados.push_back(lavado_aux);

						lavado_aux.quitarPrenda();

					}

				}

			}

			num_lavado++;

	}

	limpiarListaDeLavados(&lavados);

	//DEBUG
/*
printf("Cantidad de lavados posibles para la Prenda %d\n\n", prenda->devolverNombre());
for (int n = 0; n < lavados.size(); n++) {

	printf("Lavado %d:\n", n + 1);

	for (int prenda_n = 0; prenda_n < lavados[n].devolverCantidadDePrendasEnElLavado(); prenda_n++) {

		printf(" %d ", lavados[n].devolverPrendas()[prenda_n]);

	}

	printf("\n\n");

}

vector<Lavado>* lav_min = buscarLavadosConMenorTiempoDe(&lavados, 7);
printf("7 lavados con menor tiempo de lavado para la Prenda 1\n\n");

for (int m = 0; m < lav_min->size(); m++) {

	printf("Lavado %d:\n", m + 1);

	for (int prenda_m = 0; prenda_m < lav_min->at(m).devolverCantidadDePrendasEnElLavado(); prenda_m++) {

		printf(" %d ", lav_min->at(m).devolverPrendas()[prenda_m]);

	}

	printf("\n\n");

}

vector<Lavado>* lav_gran = buscarLavadosConMayorCantidadDePrendas(&lavados);
printf("Los lavados con mayor cantidad de prendas para la Prenda 1\n\n");

for (int k = 0; k < lav_gran->size(); k++) {

	printf("Lavado %d:\n", k + 1);

	for (int prenda_k = 0; prenda_k < lav_gran->at(k).devolverCantidadDePrendasEnElLavado(); prenda_k++) {

		printf(" %d ", lav_gran->at(k).devolverPrendas()[prenda_k]);

	}

	printf("\n\n");

}
//END DEBUG
}*/

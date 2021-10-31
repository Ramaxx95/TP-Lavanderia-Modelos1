#include <stdio.h>
#include <stdlib.h>
#include "leer_archivo.h"

int main(int argc, char* argv[]) {

	leer_archivo((char *)"primer_problema.txt");

	int res = get_params();
	if (res > 0) {

		armar_matriz();
		crear_prendas();

	}

	/*
	//DEBUG
	if (devolverListaDePrendas()[0].devolverNombre() == 1) {

		printf("Esta es la prenda numero 1\n");

	}
	if (devolverListaDePrendas()[1].devolverNombre() == 2) {

		printf("Esta es la prenda numero 2\n");

	}
	//END DEBUG
	*/

	liberar_memoria();
}
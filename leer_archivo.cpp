#include <stdlib.h>
#include <stdio.h>
#include "leer_archivo.h"

#pragma warning(disable : 4996)

#define MAX_BUFFER 1000000
static char Texto[MAX_BUFFER];

int Nr_vert, Nr_edges;

bool** matriz;
int* pesos;
vector<Prenda> prendas;


void leer_archivo(char* file) {

	int c, oc;
	char* pp = Texto;
	FILE* fp;

	if ((fp = fopen(file, "r")) == NULL) {
		printf("ERROR: Cannot open infile\n");
		exit(10);
	}

	for (oc = '\0'; (c = fgetc(fp)) != EOF; oc = *pp++ = c)
		;

	ungetc(c, fp);
	*pp = '\0';

	fclose(fp);

}

int get_params() {
	
	char c, * tmp;
	char* pp = Texto;
	int stop = 0;
	tmp = (char*)calloc(100, sizeof(char));

	Nr_vert = Nr_edges = 0;

	while (!stop && (c = *pp++) != '\0') {
		switch (c) {
		case 'c':
			while ((c = *pp++) != '\n' && c != '\0')
				;
			break;

		case 'p':
			sscanf(pp, "%s %d %d\n", tmp, &Nr_vert, &Nr_edges);
			stop = 1;
			break;

		default:
			break;
		}
	}

	free(tmp);

	if (Nr_vert == 0 || Nr_edges == 0)
		return 0; /* error */

	return 1;
}

void armar_matriz() {

	char c;
	char* pp = Texto;
	int stop = 0;

	matriz = (bool**)malloc(Nr_vert * sizeof(bool*));
	pesos = (int*)malloc(Nr_vert * sizeof(int));

	//armamos la matriz inicial
	for (int i = 0; i < Nr_vert; i++) {

		matriz[i] = (bool*)malloc(Nr_vert * sizeof(bool));

		for (int j = 0; j < Nr_vert; j++) {

			matriz[i][j] = true;
			if (i == j) {
				matriz[i][j] = false;
			}

		}

	}

	int prenda, incompatibleCon, tiempoLavado;

	//armamos la lista de incompatibilidad y vector de pesos(tiempo de lavado)
	while (!stop) {
		c = *pp++;
		switch (c) {
		case 'c':
			while ((c = *pp++) != '\n' && c != '\0')
				;
			break;

		case 'p':
			while ((c = *pp++) != '\n' && c != '\0')
				;
			break;

		case 'e':
			sscanf(pp, "%d %d\n", &prenda, &incompatibleCon);
			matriz[prenda - 1][incompatibleCon - 1] = false;//matriz[prenda - 1][incompatibleCon - 1] 
			while ((c = *pp++) != '\n' && c != '\0')
				;
			break;

		case 'n':
			sscanf(pp, "%d %d\n", &prenda, &tiempoLavado);
			pesos[prenda - 1] = tiempoLavado;
			while ((c = *pp++) != '\n' && c != '\0')
				;
			break;

		case '\0':
			break;

		default:
			stop = 1;
			break;
		}
	}

	//PARA DEBUGGING
	/*
	for (int k = 84; k < 84 + 5; k++) {
		
		printf("%d", (int) matriz[1][k]);
		
	}
	printf("\n");
	
	for (int p = 0; p < Nr_vert; p++) {
		printf("prenda: %d tarda en lavarse: %d\n", p + 1, pesos[p]);
	}
	*/
	//END DEBUGGING

}

int devolver_vertices() {

	return Nr_vert;

}

int devolver_aristas() {

	return Nr_edges;

}

vector<Prenda> devolverListaDePrendas() {

	return prendas;

}

void crear_prendas() {

	for (int i = 0; i < Nr_vert; i++) {

		Prenda prenda_a_agregar(i + 1, pesos[i]);

		prendas.push_back(prenda_a_agregar);

		/*
		//DEBUG
		for (int k = 0; k < prenda_a_agregar.devolverCantidadDeCompatibilidades(); k++) {

			printf("La prenda %d es compatible con la prenda %d\n", prenda_a_agregar.devolverNombre(), prenda_a_agregar.obtenerCompatible(k)->devolverNombre());

		}
		//END DEBUG
		*/

	}
	for (int i = 0; i < Nr_vert; i++) {

		for (int j = 0; j < Nr_vert; j++) {

			if (matriz[i][j] == 1) {

				prendas[i].aniadirPrendaCompatible(&prendas[j]);

			}

		}

	}

}

void liberar_memoria() {

	free(matriz);
	free(pesos);

}
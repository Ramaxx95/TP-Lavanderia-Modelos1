#pragma once
#include "Prenda.h"

//int Nr_vert, Nr_edges;

//bool** matriz;
//int* pesos;

int get_params();

int devolver_vertices();
int devolver_aristas();
vector<Prenda> devolverListaDePrendas();

void leer_archivo(char* file);
void armar_matriz();
void crear_prendas();
void liberar_memoria();
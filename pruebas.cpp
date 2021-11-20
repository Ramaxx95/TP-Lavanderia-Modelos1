#include "leer_archivo.h"
#include "Solucion.h"

void prueba_lavado() {

	Lavado lavado_prueba(1);
	vector<Prenda> prendas = devolverListaDePrendas();
	Prenda* prenda1 = &prendas[0];	//prenda 1, lavado 8
	Prenda* prenda2 = &prendas[13];	//prenda 14, lavado 1
	Prenda* prenda3 = &prendas[14];	//prenda 15, lavado 5
	Prenda* prenda4 = &prendas[19];	//prenda 20, lavado 5


	printf("******\n\nPrimera Prueba: se aniade la prenda 3 al lavado\n\n******\n");

	lavado_prueba.aniadirPrenda(prenda3);
	if (lavado_prueba.devolverTiempo() == 5) {

		printf("La prueba se realizo exitosamente\n");

	}
	else {

		printf("La prueba ha fallado\n");

	}

	printf("******\n\nSegunda Prueba: se aniade la prenda 1 al lavado\n\n******\n");

	lavado_prueba.aniadirPrenda(prenda1);
	if (lavado_prueba.devolverTiempo() == 8) {

		printf("La prueba se realizo exitosamente\n");
		if (lavado_prueba.devolverCantidadDePrendasEnElLavado() == 2) {
			printf("Ahora el lavado esta compuesto por las prendas 1 y 3\n");
		}

	}
	else {

		printf("La prueba ha fallado\n");

	}

	printf("******\n\nTercera Prueba: se aniade la prenda 2 al lavado pero esta no es compatible\n\n******\n");

	lavado_prueba.aniadirPrenda(prenda2);
	if (lavado_prueba.devolverCantidadDePrendasEnElLavado() == 2) {

		printf("La prueba se realizo exitosamente\n");
		if (lavado_prueba.devolverTiempo() == 8) {
			printf("el tiempo de lavado no cambio\n");
		}

	}
	else {

		printf("La prueba ha fallado\n");

	}

	printf("******\n\nCuarta Prueba: se aniade la prenda 4 al lavado \n\n******\n");

	lavado_prueba.aniadirPrenda(prenda4);
	if (lavado_prueba.devolverCantidadDePrendasEnElLavado() == 3) {

		printf("La prueba se realizo exitosamente\n");

	}
	else {

		printf("La prueba ha fallado\n");

	}

}

void prueba_solucion() {

	Lavado lavado_prueba(1);
	Lavado otro_lavado(2);
	vector<Prenda> prendas = devolverListaDePrendas();
	Solucion sol(prendas.size());

	lavado_prueba.aniadirPrenda(&prendas[7]);
	lavado_prueba.aniadirPrenda(&prendas[13]);
	lavado_prueba.aniadirPrenda(&prendas[18]);

	otro_lavado.aniadirPrenda(&prendas[4]);
	otro_lavado.aniadirPrenda(&prendas[14]);
	otro_lavado.aniadirPrenda(&prendas[17]);

	sol.agregarLavado(&lavado_prueba);

	/*PRUEBA 1*/
	printf("Prueba 1:\n la solucion solo consiste del lavado 1 (prendas 8, 14 y 19)\n");
	sol.mostrarLavados();
	printf("la duracion de este lavado debe ser 4\n");
	printf("la duracion es de: %d\n\n", sol.devolverTiempoTotal());

	/*PRUEBA 2*/
	printf("Prueba 2:\n agregamos un segundo lavado que consiste de las prendas 5, 15 y 18\n");
	sol.agregarLavado(&otro_lavado);
	sol.mostrarLavados();
	printf("la duracion ahora deberia ser de 9\n");
	printf("la duracion es de: %d\n\n", sol.devolverTiempoTotal());

	/*PRUEBA 3*/
	printf("Prueba 3:\n vamos a ver que nos indiquen que prendas nos faltan para completar el set\n");
	printf("Nos deberian decir que faltan: \n");
	printf("1, 2, 3, 4, 6, 7, 9, 10, 11, 12, 13, 16, 17, 20\n");
	sol.mostrarPrendasFaltantes();

	/*PRUEBA 4*/
	printf("Prueba 4:\n simulamos una solucion que debe dar un tiempo total de 63\n");
	Lavado lavado3(3);
	Lavado lavado4(4);
	Lavado lavado5(5);
	Lavado lavado6(6);
	Lavado lavado7(7);
	Lavado lavado8(8);

	lavado3.aniadirPrenda(&prendas[1]);
	lavado3.aniadirPrenda(&prendas[11]);
	lavado3.aniadirPrenda(&prendas[16]);

	lavado4.aniadirPrenda(&prendas[2]);
	lavado4.aniadirPrenda(&prendas[15]);
	lavado4.aniadirPrenda(&prendas[19]);

	lavado5.aniadirPrenda(&prendas[5]);
	lavado5.aniadirPrenda(&prendas[8]);

	lavado6.aniadirPrenda(&prendas[6]);
	lavado6.aniadirPrenda(&prendas[10]);

	lavado7.aniadirPrenda(&prendas[0]);
	lavado7.aniadirPrenda(&prendas[12]);

	lavado8.aniadirPrenda(&prendas[3]);
	lavado8.aniadirPrenda(&prendas[9]);


	sol.agregarLavado(&lavado3);
	sol.agregarLavado(&lavado4);
	sol.agregarLavado(&lavado5);
	sol.agregarLavado(&lavado6);
	sol.agregarLavado(&lavado7);
	sol.agregarLavado(&lavado8);

	sol.mostrarLavados();
	printf("El tiempo deberia ser 63\n");
	printf("El tiempo total es de: %d\n", sol.devolverTiempoTotal());
	sol.mostrarPrendasFaltantes();

}

void prueba_seEncuentraUnaPrendaEspecificaEnLaSolucion() {

	Solucion solucion(devolverListaDePrendas().size());

	Lavado lavado1(0);
	Lavado lavado2(1);

	lavado1.aniadirPrenda(&devolverListaDePrendas()[0]);
	lavado1.aniadirPrenda(&devolverListaDePrendas()[10]);

	lavado2.aniadirPrenda(&devolverListaDePrendas()[1]);
	lavado2.aniadirPrenda(&devolverListaDePrendas()[11]);
	lavado2.aniadirPrenda(&devolverListaDePrendas()[16]);

	solucion.agregarLavado(&lavado1);
	solucion.agregarLavado(&lavado2);

	printf("Vamos a verificar que la prenda 3 NO se encuentra en la solucion:\n");
	printf("Buscando...\n");

	if (!solucion.seEncuentraLaPrendaDeNombre(3))
	{
		printf("La prueba se realizo correctamente!\n");
	}

	printf("Vamos a verificar que la prenda 17 SI se encuentra en la solucion:\n");
	printf("Buscando...\n");

	if (solucion.seEncuentraLaPrendaDeNombre(17))
	{
		printf("La prueba se realizo correctamente!\n");
	}

}

void prueba_completarLavadosConLasPrendasFaltantes() {
	Solucion sol(20);

	Lavado lavado1(0);
	Lavado lavado2(1);
	Lavado lavado3(2);
	Lavado lavado4(3);

	lavado1.aniadirPrenda(&devolverListaDePrendas()[4]);
	lavado1.aniadirPrenda(&devolverListaDePrendas()[14]);
	lavado1.aniadirPrenda(&devolverListaDePrendas()[17]);

	lavado2.aniadirPrenda(&devolverListaDePrendas()[7]);
	lavado2.aniadirPrenda(&devolverListaDePrendas()[13]);
	lavado2.aniadirPrenda(&devolverListaDePrendas()[18]);

	lavado3.aniadirPrenda(&devolverListaDePrendas()[1]);
	lavado3.aniadirPrenda(&devolverListaDePrendas()[11]);
	lavado3.aniadirPrenda(&devolverListaDePrendas()[16]);

	lavado4.aniadirPrenda(&devolverListaDePrendas()[3]);
	lavado4.aniadirPrenda(&devolverListaDePrendas()[9]);

	sol.agregarLavado(&lavado1);
	sol.agregarLavado(&lavado2);
	sol.agregarLavado(&lavado3);
	sol.agregarLavado(&lavado4);

	printf("Asi es el lavado inicial:\n");
	sol.mostrarLavados();
	sol.mostrarPrendasFaltantes();

	printf("Ahora aplicamos agregar la Prendas faltantes:\n");
	//completarRestoDeLasPrendas(&sol);
	sol.mostrarLavados();

	if (sol.mostrarPrendasFaltantes() == 0) {
		printf("Funciono correctamente\n");
	}
}

void prueba_tratarDeAgregarUnLavadoQuePoseaAlgunaPrendaQueSeRepiteEnLaSolucionDirectamenteNoLoAniade() {

	Solucion sol(20);

	Lavado lavado1(0);
	Lavado lavado2(1);

	lavado1.aniadirPrenda(&devolverListaDePrendas()[0]);
	lavado1.aniadirPrenda(&devolverListaDePrendas()[10]);

	lavado2.aniadirPrenda(&devolverListaDePrendas()[0]);
	lavado2.aniadirPrenda(&devolverListaDePrendas()[11]);

	printf("Agregamos el primer lavado:\n");
	sol.agregarLavado(&lavado1);
	sol.mostrarLavados();

	printf("Agregamos el segundo lavado:\n");
	sol.agregarLavado(&lavado2);
	sol.mostrarLavados();
	if (sol.mostrarPrendasFaltantes() == 18) {
		printf("La prueba se realizo con exito!\n");
	}
}
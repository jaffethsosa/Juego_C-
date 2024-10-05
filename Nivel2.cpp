#include "Nivel2.h"
#include "minigraph.h"
#include "controlesGUI.h"
#include <iostream>
#include <cmath>
#include <ctime>

using namespace minigraph;
using namespace std;

void nivel2() {
    vredimensiona(800, 500);
    color(CL_PLATA);
    espera(100);
    rectangulo_lleno(10, 10, 790, 490);
    espera(100);

    int FILAS_INICIALES = 2;
    const int COLUMNAS = 5;
    const int ANCHO_CASILLA = 75;
    const int ALTO_CASILLA = 50;
    const int ESPACIO_ENTRE_CASILLAS = 40;

    Casilla casillero[FILAS_INICIALES][COLUMNAS];
    float coordenadasCasillas[FILAS_INICIALES][COLUMNAS];

    srand(time(nullptr));
    for (int f = 0; f < FILAS_INICIALES; f++) {
        for (int i = 0; i < 1; i++) {
            int c;
            do {
                c = rand() % COLUMNAS;
            } while (casillero[f][c].verificarBomba());
            casillero[f][c].colocarBomba();
            casillero[f][c].setTieneBomba(true);
        }
    }
    espera(100);

    for (int f = 0; f < FILAS_INICIALES; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            casillero[f][c].redim(ANCHO_CASILLA, ALTO_CASILLA);
            casillero[f][c].mover(150 + c * (ANCHO_CASILLA + ESPACIO_ENTRE_CASILLAS), 25 + f * (ALTO_CASILLA + ESPACIO_ENTRE_CASILLAS));

            coordenadasCasillas[f][c] = 150 + c * (ANCHO_CASILLA + ESPACIO_ENTRE_CASILLAS); // Guardar coordenadas

            if (casillero[f][c].verificarBomba()) {
                casillero[f][c].retinte(CL_ROJO); // Si la casilla tiene una bomba, cambiar el color a rojo
            } else {
                casillero[f][c].retinte(CL_VERDE); // Si la casilla no tiene una bomba, cambiar el color a verde
            }
            casillero[f][c].mostrar();
        }
    }

    espera(100);

    canion c1(400, 485, 60, 60, 90);
    int ang = 90;
    c1.mostrar();
    bool actualizar = false;
    int x = 0;

    while (true) {
        switch (tecla()) {
            case IZQUIERDA:
                if (ang >= 150) {
                    ang = 150;
                } else {
                    ang += 5;
                    actualizar = true;
                }
                break;

            case DERECHA:
                if (ang <= 30) {
                    ang = 30;
                } else {
                    ang -= 5;
                    actualizar = true;
                }
                break;

            case ARRIBA:
                float coordenadaBalaX = 400 + (x * 20 + 150) * cos(ang * 3.1416 / 180);
                float coordenadaBalaY = 485 - (x * 20 + 150) * sin(ang * 3.1416 / 180);

                for (int x = 0; x < 40; x++) {
                    color(CL_PLATA);
                    circulo_lleno(400 + ((x - 1) * 20 + 150) * cos(ang * 3.1416 / 180), 485 - ((x - 1) * 20 + 150) * sin(ang * 3.1416 / 180), 5);
                    color(CL_NEGRO);
                    circulo_lleno(coordenadaBalaX, coordenadaBalaY, 5);

                    for (int f = 0; f < FILAS_INICIALES; f++) {
                        for (int c = 0; c < COLUMNAS; c++) {
                            if (coordenadaBalaX >= coordenadasCasillas[f][c] &&
                                coordenadaBalaX <= coordenadasCasillas[f][c] + ANCHO_CASILLA &&
                                coordenadaBalaY >= 25 + f * (ALTO_CASILLA + ESPACIO_ENTRE_CASILLAS) &&
                                coordenadaBalaY <= 25 + f * (ALTO_CASILLA + ESPACIO_ENTRE_CASILLAS) + ALTO_CASILLA) {
                                cout << "La bala ha impactado en la casilla [" << f << "][" << c << "]" << endl;
                            }
                        }
                    }


                }



                    espera(100);
                break;
        }

        if (actualizar) {
            c1.apuntar(ang);
            actualizar = false;
        }

    }
}

#include "Nivel1.h"
#include "Nivel2.h"
#include "minigraph.h"
#include "controlesGUI.h"
#include <iostream>
#include <ctime>

using namespace minigraph;
using namespace std;

void nivel1(const string& nombre) {

    const int FILAS = 7;
    const int COLUMNAS = 5;
    const int ANCHO_CASILLA = 50;
    const int ALTO_CASILLA = 50;
    const int ESPACIO_ENTRE_CASILLAS = 4;
    const int MAX_VIDAS = 5;
    const int PUNTOS_BOMBA = -5;
    const int PUNTOS_VACIA = 10;
    int puntaje = 0;
    int vidas = MAX_VIDAS;
    int aciertos = 7;



    vredimensiona(700, 600);
    color(CL_NEGRO);
    rectangulo_lleno(10, 10, 790, 490);
    espera(100);

    color(CL_PLATA);
    formatotexto("Arial", 50, 0, FT_NEGRITA | FT_SUBRAYADO);
    justificartexto(JF_CENTRO);
    texto(164, 50, 200, 100, "Nivel 1");
    formatotexto("Arial", 25, 0, FT_NORMAL);
    texto(425, 50, 200, 100, "Nombre:");
    texto(550, 50, 200, 100, nombre);
    justificartexto(JF_CENTRO);
    texto(440, 100, 200, 100, "Puntuacion: ");
    texto(550, 100, 200, 100, to_string(puntaje));
    texto(414, 150, 200, 100, "Vidas: ");
    texto(550, 150, 200, 100, to_string(vidas));
    texto(500, 300, 200, 100, "!Logra llegar al final!");
    texto(500, 350, 200, 100, "Sin perder vidas.");

    espera(100);

    Casilla casillero[FILAS][COLUMNAS];
    bool tiene_bomba[FILAS][COLUMNAS] = {false};

    // Colocar tres bombas al azar en cada fila
    srand(time(nullptr));
    for (int f = 0; f < FILAS; f++) {
        for (int i = 0; i < 3; i++) {
            int c;
            do {
                c = rand() % COLUMNAS;
            } while (tiene_bomba[f][c]);
            casillero[f][c].colocarBomba();
            tiene_bomba[f][c] = true;

        }
    }

    //casillas en una cuadrícula
    int offsetX = 100;
    int offsetY = 100;

    espera(100);

    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            casillero[f][c].redim(ANCHO_CASILLA, ALTO_CASILLA);
            casillero[f][c].mover(offsetX + c * (ANCHO_CASILLA + ESPACIO_ENTRE_CASILLAS),
                                   offsetY + f * (ALTO_CASILLA + ESPACIO_ENTRE_CASILLAS));

            casillero[f][c].mostrar();
        }
    }



    bool game_over = false;
    bool ganaste = false;

    // interacción


    while (!game_over) {
    for (int f = 0; f < FILAS; f++) {
        for (int c = 0; c < COLUMNAS; c++) {
            if (casillero[f][c].verificaraccion()) {
                if (tiene_bomba[f][c]) {
                    vidas--;
                    puntaje += PUNTOS_BOMBA;
                    mensaje("¡Has hecho clic en una bomba! Vidas restantes: " + to_string(vidas));
                } else {
                    puntaje += PUNTOS_VACIA;
                    aciertos--;
                    mensaje("¡Has hecho clic en una casilla sin bomba!");
                    cout << aciertos;
                }

                    // Redibujar el texto de la puntuación
                    color(CL_PLATA);
                    formatotexto("Arial", 50, 0, FT_NEGRITA | FT_SUBRAYADO);
                    justificartexto(JF_CENTRO);
                    texto(164, 50, 200, 100, "Nivel 1");
                    formatotexto("Arial", 25, 0, FT_NORMAL);
                    texto(425, 50, 200, 100, "Nombre:");
                    texto(550, 50, 200, 100, nombre);
                    justificartexto(JF_CENTRO);
                    texto(440, 100, 200, 100, "Puntuacion: ");
                    color(CL_NEGRO);
                    rectangulo_lleno(530,110,570,85);
                    color(CL_PLATA);
                    texto(550, 100, 200, 100, to_string(puntaje));
                    texto(414, 150, 200, 100, "Vidas: ");
                    color(CL_NEGRO);
                    rectangulo_lleno(530,170,600,125);
                    color(CL_PLATA);
                    texto(550, 150, 200, 100, to_string(vidas));

                }
                if (vidas == 0) {
                    game_over = true;
                    break;
                }
                if (aciertos == 0) {
                    ganaste = true;
                    break;
                }

                }
            }
            if (game_over || ganaste) break;
        }


    //mensaje de fin de juego
    if(game_over == true){

    mensaje("¡Juego terminado! Vidas restantes: " + to_string(vidas) + ". Puntaje: " + to_string(puntaje) + ". Pulsa OK para salir.");
    vcierra();

    }
    if (ganaste == true) {
    // Llama a la función mensajeEx con nivel2 como callback
    mensajeEx("¡Juego terminado! Vidas restantes: " + to_string(vidas) + ". Puntaje: " + to_string(puntaje) + ". Pulsa OK para salir.", nivel2);

    }
}

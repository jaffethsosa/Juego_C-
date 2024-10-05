#include "controlesGUI.h"
#include "minigraph.h"
#include <iostream>
#include <ctime>

using namespace std;

// Modificar las constantes NUM_ROWS y NUM_COLS

// Función para jugar al buscaminas
void jugarBuscaminas() {
    vredimensiona(800, 700);
    espera(100);
     int puntaje = 0;
    int clics = 0;


    color(CL_PLATA);
    formatotexto("Arial", 50, 0, FT_NEGRITA | FT_SUBRAYADO);
    justificartexto(JF_CENTRO);
    texto(664, 50, 200, 100, "Nivel 3");
    justificartexto(JF_CENTRO);
    formatotexto("Arial", 25, 0, FT_NORMAL);
    texto(640, 100, 200, 100, "Puntuacion: ");
    texto(750, 100, 200, 100, to_string(puntaje));
    texto(664, 150, 200, 100, "Vidas: ");
    texto(750, 150, 200, 100, to_string(clics));
    texto(650, 300, 200, 100, "!Logra llegar al final!");
    texto(650, 350, 200, 100, "Sin perder vidas.");

    Casilla tablero[NUM_ROWS][NUM_COLS];


    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            tablero[i][j] = Casilla(j * ESPACIO_ENTRE_CASILLAS, i * ESPACIO_ENTRE_CASILLAS, ESPACIO_ENTRE_CASILLAS, ESPACIO_ENTRE_CASILLAS);
        }
    }

    srand(time(NULL));
    int bombs_placed = 0;
    while (bombs_placed < NUM_BOMBS) {
        int row = rand() % NUM_ROWS;
        int col = rand() % NUM_COLS;
        if (!tablero[row][col].verificarBomba()) {
            tablero[row][col].colocarBomba();
            ++bombs_placed;
        }
    }

    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            tablero[i][j].mostrar();
        }
    }



    while (true) {

        espera(50);

        if (raton_boton_izq()) {
            int mouseX = raton_x();
            int mouseY = raton_y();

            int row = mouseY / ESPACIO_ENTRE_CASILLAS;
            int col = mouseX / ESPACIO_ENTRE_CASILLAS;

            if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
                if (!tablero[row][col].esLibre()) {
                    mensaje("¡Has perdido!");
                    break;
                } else {
                    tablero[row][col].colocarLibre();
                    tablero[row][col].descubrirAdyacentes(row, col);
                    ++puntaje;
                    ++clics;
                }
            }
        }

        if (raton_boton_der()) {
            int mouseX = raton_x();
            int mouseY = raton_y();

            int row = mouseY / ESPACIO_ENTRE_CASILLAS;
            int col = mouseX / ESPACIO_ENTRE_CASILLAS;

            if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
                tablero[row][col].colocarBomba();
                ++clics;
            }
        }

        int minasMarcadas = 0;
        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                if (tablero[i][j].verificarBomba() && tablero[i][j].esLibre()) {
                    ++minasMarcadas;
                }
            }
        }
        puntaje += (minasMarcadas * 10);

        for (int i = 0; i < NUM_ROWS; ++i) {
            for (int j = 0; j < NUM_COLS; ++j) {
                tablero[i][j].mostrar();
            }
        }

        if (puntaje == NUM_BOMBS * 10 || clics == (NUM_ROWS * NUM_COLS) - NUM_BOMBS) {
            mensaje("¡Has ganado!");
            break;
        }
    }
}

int nivel3() {
    jugarBuscaminas();
    return 0;
}

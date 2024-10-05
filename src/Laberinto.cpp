#include "Laberinto.h"

Laberinto::Laberinto()
{
    //ctor
}

Laberinto::~Laberinto()
{
    //dtor
}

void Laberinto::generarLaberinto(int fila, int columna) {
    laberinto[fila][columna] = 0; // Marcar la celda actual como pasillo

    // Direcciones: arriba, abajo, izquierda, derecha
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};
    // Orden aleatorio de direcciones
    vector<int> dirs = {0, 1, 2, 3};
    random_shuffle(dirs.begin(), dirs.end());

    for (int dir : dirs) {
        int nx = fila + dx[dir];
        int ny = columna + dy[dir];

        if (nx >= 0 && nx < FILAS && ny >= 0 && ny < COLUMNAS && laberinto[nx][ny] == 1) {
            // Si la celda vecina es válida y es una pared
            laberinto[fila + dx[dir] / 2][columna + dy[dir] / 2] = 0; // Romper la pared entre las dos celdas
            generarLaberinto(nx, ny); // Continuar generando el laberinto desde la celda vecina
        }
    }
}

void Laberinto::imprimirLaberinto() {
    // Aquí va la lógica para imprimir el laberinto
}

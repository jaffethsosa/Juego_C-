#include "laberinto.h"

Laberinto::Laberinto() {
    // Constructor
    srand(time(0));
    generarLaberinto(0, 0);
}

Laberinto::~Laberinto() {
    // Destructor
}

void Laberinto::imprimirLaberinto() {
    // Implementaci�n de la funci�n imprimirLaberinto
    // Aqu� se muestra el laberinto en la consola
    // ...
}

void Laberinto::mostrarLaberinto() {
    // Implementaci�n de la funci�n mostrarLaberinto
    // Llama a imprimirLaberinto para mostrar el laberinto
    imprimirLaberinto();
}

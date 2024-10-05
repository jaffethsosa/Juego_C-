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
    // Implementación de la función imprimirLaberinto
    // Aquí se muestra el laberinto en la consola
    // ...
}

void Laberinto::mostrarLaberinto() {
    // Implementación de la función mostrarLaberinto
    // Llama a imprimirLaberinto para mostrar el laberinto
    imprimirLaberinto();
}

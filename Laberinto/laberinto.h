#ifndef LABERINTO_H_INCLUDED
#define LABERINTO_H_INCLUDED

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int FILAS = 10;
const int COLUMNAS = 10;

class Laberinto {
public:
    Laberinto();
    virtual ~Laberinto();

    void imprimirLaberinto();
     void mostrarLaberinto(); // Declaración de la función mostrarLaberinto

private:
    vector<vector<int>> laberinto;

    void generarLaberinto(int fila, int columna);
};


#endif // LABERINTO_H_INCLUDED

#ifndef LABERINTO_H
#define LABERINTO_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

const int FILAS = 10;
const int COLUMNAS = 10;

class Laberinto
{
public:
    Laberinto();
    virtual ~Laberinto();

    void imprimirLaberinto();

private:
    vector<vector<int>> laberinto;

    void generarLaberinto(int fila, int columna);
};



#endif // LABERINTO_H

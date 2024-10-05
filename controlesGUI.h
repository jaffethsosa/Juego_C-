#ifndef CONTROLES_GUI_H
#define CONTROLES_GUI_H

#include "minigraph.h"
#include <iostream>
using namespace minigraph;
using namespace std;

extern const int ESPACIO_ENTRE_CASILLAS;

const int NUM_ROWS = 11;
const int NUM_COLS = 13;
const int NUM_BOMBS = 20;


class ControlGUI {
private:
    static int contador;
    static int focus;
    static int pfocus;
    static bool cambiofocus;
protected:
    int id;
    int x, y;
    int ancho, alto;
    int tinte;
    int tintefocus;
    bool visible;
    bool tocado;
    string etiqueta;

public:
    ControlGUI(int _x = 100, int _y = 100, int _ancho = 50, int _alto = 30, string _etiqueta = "");
    void ocultar();
    void mover(int, int);
    void redim(int, int);
    void retinte(int);
    void reetiquetar(string);
    bool estadentro();
    bool clic();
    int mi_id();
    bool tienefocus();
    bool pierdefocus();
    void limpiapfocus();
    void sedefocus();
    bool recibefocus();

    virtual bool verificaraccion();
    virtual void mostrar() {};
    virtual bool capturarteclas() { return false; };
    virtual void actualizar() {};
};

class Boton : public ControlGUI {
public:
    Boton(int _x = 100, int _y = 100, int _ancho = 50, int _alto = 30, string _etiqueta = "OK");
    void mostrar();
    bool capturarteclas();
    void actualizar();
};

class Ctexto : public ControlGUI {
    string txt;
public:
    Ctexto(int _x = 100, int _y = 100, int _ancho = 50, int _alto = 30, string _etiqueta = "texto:");
    void mostrar();
    bool capturarteclas();
    void limpiarcontenido();
    void actualizar();
    void asignarcontenido(string);
    string obtenercontenido();
};

class Casilla : public ControlGUI {
private:
    bool tiene_bomba;
    bool es_libre;

public:
    Casilla() : ControlGUI() {
        tiene_bomba = false;
        es_libre = false;

    }

    Casilla(int _x, int _y, int _ancho, int _alto);
    void colocarBomba();
    void colocarLibre();
    bool verificarBomba() const;
    void mostrar();
    bool capturarteclas();
    void actualizar();
    bool esBomba();
    bool esLibre();
    void setTieneBomba(bool valor);
    bool estaDentroDeCasilla(int x, int y, const Casilla& casilla);

    void descubrirAdyacentes(int row, int col) {}

};




#define ID_BOTON_SALIR 1001
#endif



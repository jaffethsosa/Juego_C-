#include "ControlesGUI.h"
#include "minigraph.h"
#include "Nivel1.h"
#include "Nivel2.h"
#include "Nivel3.h"
#include <ctime>

using namespace minigraph;
using namespace std;


void ejecutarJuego() {
   vredimensiona(800, 500);

    int vidas = 5;
    int puntuacion = 0;

    string vidaStr = to_string(vidas);
    string puntuacionStr = to_string(puntuacion);

    color(CL_PLATA);
    rectangulo_lleno(10, 10, 790, 490);
    espera(100);

    color(CL_NEGRO);
    formatotexto("Arial", 50, 0, FT_NEGRITA | FT_SUBRAYADO);
    justificartexto(JF_CENTRO);
    texto(400, 100, 600, 100, "El Juego De Sosa");

    Ctexto txt2(200, 225, 300, 40, "Nombre:");
    Boton boton1(530, 225, 100, 40, "Borrar");
    Boton boton2(150, 350, 100, 40, "Nivel 1");
    Boton boton3(350, 350, 100, 40, "Nivel 2");
    Boton boton4(550, 350, 100, 40, "Nivel 3");

    ControlGUI *controles[] = { &boton1, &boton2, &boton3, &boton4, &txt2 };

    for (auto ctrl : controles)
        ctrl->mostrar();

    int idcontrol = -1;
    string nombre; // Declara la variable fuera del switch

    while (true) {
        idcontrol = -1;
        for (auto ctrl : controles) {
            if (ctrl->verificaraccion())
                idcontrol = ctrl->mi_id();
        }
        switch (idcontrol) {
            case 1:
                txt2.limpiarcontenido();
                break;
            case 2:
                nombre = txt2.obtenercontenido(); // Asigna valor a la variable aquí
                nivel1(nombre);
                break;
            case 3:
                nivel2();
                break;
            case 4:
                nivel3();
                break;
        }

    }
}

int main() {
    ejecutarJuego();
    return 0;
}

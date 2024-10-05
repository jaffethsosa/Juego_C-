
/*
 *  Minigraph: Un mini-conjunto de funciones para abrir una ventana, pintar en
 *    ella y detectar la presión de algunas teclas.
 */

// VERSION: 1.2.0


#ifndef _MINIGRAPH_H_
#define _MINIGRAPH_H_

#include <iostream>

#ifndef MINIGRAPH_SOURCE
#define main _main_
#endif

int _main_();

std::ostream& log();

// Funciones del API

namespace minigraph {

//void vdefine(int ample=800, int alt=500,std::string vtitulo="Mi App");
void vredimensiona(int ample, int alt);
int  vancho();
int  valto();
void vborra();
void vrefresca();
void vcierra();


void mensaje(std::string msj);
void mensajeEx(const std::string& msj, void (*callback)());
bool pregunta(std::string msj);
void espera(int miliseg);

void color(int c);
void color_rgb(int r, int g, int b);

void estilolinea(int ELinea, int GLinea=1);
void estilorelleno(int ERelleno);

void punto(float x, float y);

void linea(float x_ini, float y_ini, float x_fin, float y_fin);
void linea_polar(float x, float y, float lon,float ang);

void rectangulo(float izq, float arr, float der, float aba);
void rectangulo_lleno(float izq, float arr, float der, float aba);

void rectanguloredondeado(float izq, float arr, float der, float aba, float Resquina);
void rectanguloredondeado_lleno(float izq, float arr, float der, float aba, float Resquina);

void arco(float x_cen, float y_cen, float radio, float ang_i, float ang_f);
void arco_lleno(float x_cen, float y_cen, float radio, float ang_i, float ang_f);

void circulo(float x_cen, float y_cen, float radio);
void circulo_lleno(float x_cen, float y_cen, float radio);

void elipse(float izq, float arr, float der, float aba);
void elipse_lleno(float izq, float arr, float der, float aba);

void justificartexto(int _estilo);
void formatotexto(std::string nombrefuente, int tamanofuente, int inclinacion, int NSCT);
void texto(float x, float y, float ancho, float alto, const std::string& texto);
int alturafuente();

int tecla();
void limpiamemoriatecla();

bool  raton(float& x, float& y);
bool  raton_dentro();
float raton_x();
float raton_y();
void  raton_botones(bool& izq, bool& der);
bool  raton_boton_izq();
bool  raton_boton_der();

enum {
  ESCAPE,
  IZQUIERDA, DERECHA, ARRIBA, ABAJO,
  F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
  ESPACIO,
  ENTER,
  RETROCESO,
  TABULADOR,
  NINGUNA
};


enum {          //---------- PALETA DE COLORES ----------
  CL_NEGRO, CL_ROJO, CL_VERDE, CL_AZUL, CL_AMARILLO, CL_MAGENTA, CL_CYAN, CL_BLANCO,
  CL_GRIS, CL_CAFE, CL_NARANJA, CL_SALMON, CL_ROSADO, CL_ROSADOFUERTE, CL_ORO,
  CL_LAVANDA, CL_VIOLETA, CL_MORADO, CL_LIMON, CL_OLIVO, CL_TURQUESA, CL_PLATA
};

enum {          //---------- ESTILOS DE LINEAS ----------
    EL_CONTINUA, EL_RAYAS, EL_PUNTOS, EL_RAYAPUNTO, EL_RAYAPUNTOPUNTO
};

enum{           //---------- ESTILOS DE RELLENO ----------
    ER_HORIZONTAL, ER_VERTICAL, ER_DIAGONALDERECHA, ER_DIAGONALIZQUIERDA,
    ER_CUADRICULADO, ER_DIAGONALCRUZADO, ER_SOLIDO
};

enum{           //---------- ESTILOS DE JUSTIFICADO DE TEXTO ----------
    JF_IZQUIERDA, JF_CENTRO, JF_DERECHA
};

enum{           //---------- ESTILOS FORMATOS DE TEXTO ----------
    FT_NORMAL, FT_NEGRITA, FT_SUBRAYADO, FT_CURSIVA=4, FT_TACHADO=8

};

} // namespace minigraph

#endif



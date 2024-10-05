#include "controlesGUI.h"
#include "Nivel2.h"
#include "minigraph.h"
#include <iostream>
#include <cmath>
#include <ctime>
using namespace std;
using namespace minigraph;

int ControlGUI::contador = 0;
int ControlGUI::focus = 0;
int ControlGUI::pfocus = -1;
bool ControlGUI::cambiofocus = true;
const int ESPACIO_ENTRE_CASILLAS = 40;

ControlGUI::ControlGUI(int _x,int _y, int _ancho, int _alto, string _etiqueta){
    x = _x;
    y = _y;
    ancho = _ancho;
    alto = _alto;
    tinte = CL_PLATA;
    visible = false;
    tocado = false;
    etiqueta = _etiqueta;
    id=contador++;

}

void ControlGUI::ocultar(){
    if(visible){
        color(CL_PLATA);
        rectangulo_lleno(x-1,y-1,x+ancho+2,y+alto+2);
        visible = false;
    }
}

void ControlGUI::mover(int _x,int _y){
    bool esvisible = visible;
    if(esvisible)
        ocultar();

    x = _x;
    y = _y;

    if(esvisible)
        mostrar();
}

void ControlGUI::redim(int _ancho,int _alto){
    bool esvisible = visible;
    if(esvisible)
        ocultar();

    ancho = _ancho;
    alto = _alto;

    if(esvisible)
        mostrar();
}

void ControlGUI::retinte(int _tinte){
    tinte = _tinte;
    if(visible){
        visible = false;
        mostrar();
    }
}

void ControlGUI::reetiquetar(string _etiqueta){
    bool esvisible = visible;
    if(esvisible)
        ocultar();

    etiqueta = _etiqueta;

    if(esvisible)
        mostrar();
}

bool ControlGUI::estadentro(){
    if(visible){
        float rx,ry;
        raton(rx,ry);
        return ((rx>x)&&(rx<x+ancho)&&(ry>y)&&(ry<y+alto));
    }
    return false;
}

bool ControlGUI::clic(){
    if(estadentro()){
        if(raton_boton_izq()&&!tocado){
            tocado = true;
            visible=false;
            mostrar();
            pfocus = focus;
            focus = id;
            limpiamemoriatecla();

        }
    }
    if(!raton_boton_izq()&&tocado){
        tocado = false;
        espera(100);
        visible=false;
        mostrar();

        return true;

    }
    return false;
}


bool ControlGUI::tienefocus(){
    return (focus==id);

}

bool ControlGUI::pierdefocus(){
    return (pfocus==id);
}

void ControlGUI::limpiapfocus(){
    pfocus = -1;
}

int ControlGUI::mi_id(){
    return id;
}

bool ControlGUI::verificaraccion(){
    bool acc = false;
    acc |= clic();
    acc |= capturarteclas();
    if((acc)||(pierdefocus())||(recibefocus()))
        actualizar();
    return acc;
}

void ControlGUI::sedefocus(){
    pfocus = focus;
    focus = (id<contador-1)?id+1:0;
    cambiofocus = true;
}

bool ControlGUI::recibefocus(){
    if ((cambiofocus)&&(focus==id)){
        cambiofocus = false;
        return true;
    }
    return false;

}
//------------------------- Boton ------------------------------

Boton::Boton(int _x,int _y,int _ancho,int _alto,string _etiqueta):ControlGUI(_x,_y,_ancho,_alto,_etiqueta){
}

void Boton::mostrar(){
    if(!visible){
        estilolinea(EL_CONTINUA,2);
        estilorelleno(ER_SOLIDO);
        color(tinte);
        if(!tocado)
            rectangulo_lleno(x,y,x+ancho,y+alto);
        color((tocado)?CL_NEGRO:CL_BLANCO);
        linea(x,y,x,y+alto);
        linea(x,y,x+ancho,y);
        color((tocado)?CL_BLANCO:CL_NEGRO);
        linea(x+ancho,y,x+ancho,y+alto);
        linea(x,y+alto,x+ancho,y+alto);
        color((tienefocus())?CL_AMARILLO:CL_NEGRO);
        formatotexto("Times New Roman",20,0,FT_NORMAL);
        justificartexto(JF_CENTRO);
        texto(x+ancho/2,y+alto/2,ancho,alto,etiqueta);
        visible = true;

    }
}

bool Boton::capturarteclas(){
    int tec=NINGUNA;

    if(tienefocus()){
        tec=tecla();
        if(tec==ENTER){
            tocado = true;
            visible=false;
            mostrar();
            espera(100);
            tocado = false;
            visible=false;
            mostrar();
            return true;
        }
        if(tec==TABULADOR){
            sedefocus();
            return false;
        }
    }
    return false;
}

void Boton::actualizar(){
    if(visible){
        visible = false;
        mostrar();
        if(pierdefocus())
            limpiapfocus();
    }
}


//------------------------- Ctexto ------------------------------

Ctexto::Ctexto(int _x,int _y,int _ancho,int _alto,string _etiqueta):ControlGUI(_x,_y,_ancho,_alto,_etiqueta){
    txt = "";
    tinte = CL_LAVANDA;
    tintefocus = CL_AMARILLO;
}

void Ctexto::mostrar(){
    if(!visible){
        color((tienefocus())?tintefocus:tinte);
        rectangulo_lleno(x,y,x+ancho,y+alto);
        color(CL_NEGRO);
        linea(x,y,x+ancho,y);
        linea(x,y,x,y+alto);
        color(CL_BLANCO);
        linea(x+ancho,y,x+ancho,y+alto);
        linea(x,y+alto,x+ancho,y+alto);
        color(CL_NEGRO);
        formatotexto("Times New Roman",20,0,FT_NORMAL);
        justificartexto(JF_DERECHA);
        texto(x-4,y+alto/2,100,alto,etiqueta);
        justificartexto(JF_IZQUIERDA);
        texto(x+4,y+alto/2,ancho-5,alto-2,txt);
        visible = true;
    }
}

bool Ctexto::capturarteclas(){
    int tec=NINGUNA;

    if(tienefocus()){
        tec=tecla();
        if(((tec>=48)&&(tec<=57))||((tec>=65)&&(tec<=90))||(tec==ESPACIO)||(tec=='Ñ')){
            txt+=(tec!=ESPACIO)?tec:' ';
            return true;
        }
        if((tec==RETROCESO)&&(txt.length()>0)){
            txt.pop_back();
            return true;
        }
        if((tec==TABULADOR)||(tec==ENTER)){
            sedefocus();
            return false;
        }
    }
    return false;
}

void Ctexto::actualizar(){
    if(visible){
        color((tienefocus())?tintefocus:tinte);
        rectangulo_lleno(x+1,y+1,x+ancho,y+alto);
        color(CL_NEGRO);
        formatotexto("Times New Roman",20,0,FT_NORMAL);
        justificartexto(JF_IZQUIERDA);
        texto(x+4,y+alto/2,ancho-5,alto,txt);
        if(pierdefocus())
            limpiapfocus();
    }
}

void Ctexto::limpiarcontenido(){
    txt = "";
    actualizar();
}


void Ctexto::asignarcontenido(string _txt){
    txt = _txt;
    actualizar();
}

string Ctexto::obtenercontenido(){
    return txt;
}



//-------------------- Casilla-----------------

Casilla::Casilla(int _x, int _y, int _ancho, int _alto) : ControlGUI(_x, _y, _ancho, _alto) {
    tintefocus = CL_GRIS;
    tiene_bomba = false;
    es_libre = false;
}

void Casilla::colocarBomba() {
    tiene_bomba = true;
}

bool Casilla::verificarBomba() const {
    return tiene_bomba;
}

bool Casilla::esBomba() {
    return tiene_bomba;
}

void Casilla::setTieneBomba(bool valor) {
    tiene_bomba = valor;
}

bool Casilla::esLibre() {
    return es_libre;
}

void Casilla::colocarLibre() {
    es_libre = true;
}



void Casilla::mostrar(){
    if(!visible){

        color((tienefocus())?CL_PLATA:CL_GRIS);
        rectanguloredondeado_lleno(x,y,x+ancho,y+alto,5);
        color(CL_NEGRO);
        rectanguloredondeado(x,y,x+ancho,y+alto,5);
        if(tocado)
            etiqueta=(etiqueta=="X")?"":"X";
        formatotexto("Times New Roman",20,0,FT_NORMAL);
        justificartexto(JF_CENTRO);
        texto(x+ancho/2,y+alto/2,ancho,alto,etiqueta);
        visible = true;

    }
}

void Casilla::actualizar(){
    visible = false;
    mostrar();
    if(pierdefocus())
        limpiapfocus();
}


bool Casilla::capturarteclas(){
    int tec=NINGUNA;

    if(tienefocus()){
        tec=tecla();
        if(tec==ENTER){
            tocado = true;
            visible=false;
            mostrar();
            espera(100);
            tocado = false;
            visible=false;
            mostrar();
            return true;
        }
        if(tec==TABULADOR){
            sedefocus();
            return false;
        }
    }
    return false;
}

//-----------------------Bomba Canion----------------------------------
bool Casilla::estaDentroDeCasilla(int x, int y, const Casilla& casilla) {
    int x_casilla_centro = casilla.x + casilla.ancho / 2;
    int y_casilla_centro = casilla.y + casilla.alto / 2;
    double distancia = sqrt(pow(x - x_casilla_centro, 2) + pow(y - y_casilla_centro, 2));
    return distancia < casilla.ancho / 2; // Comparamos con el radio del círculo
}

//------------------------Busca Minas---------------------------------

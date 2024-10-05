#ifndef NIVEL2_H
#define NIVEL2_H

#include "minigraph.h"
#include "controlesGUI.h"

class canion{
private:
    int x,y;
    int anchoBase;
    int largoCanion;
    int anchoCanion;
    int tinteBase,tinteCanion;
    int angCanion;
    int dirBase;
    bool visible;
public:
    canion(int=100,int=100,int=50,int=50,int=90);
    void mostrar();
    void ocultar();
    void mover(int,int);
    void retinte(int,int=-1);
    void redimensionar(int,int,int=10);
    void rotar(int);
    void apuntar(int);

};

void nivel2();



#endif

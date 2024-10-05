#include "Nivel2.h"
#include "minigraph.h"

using namespace minigraph;

canion::canion(int _x,int _y,int _anchoBase,int _largoCanion, int _dirBase){
    x = _x;
    y = _y;
    anchoBase = _anchoBase;
    largoCanion = _largoCanion;
    dirBase = _dirBase;
    angCanion = dirBase;
    anchoCanion = 10;
    tinteBase = CL_NEGRO;
    tinteCanion = CL_GRIS;
    visible = false;
}

void canion::mostrar(){
    if(!visible){
        color(tinteBase);
        arco_lleno(x,y,anchoBase/2,dirBase-90,dirBase+90);
        estilolinea(EL_CONTINUA,anchoCanion);
        color(tinteCanion);
        linea_polar(x,y,largoCanion,angCanion);
        visible=true;
    }
}

void canion::ocultar(){
    if(visible){
        int tbtmp = tinteBase;
        int tctmp = tinteCanion;
        tinteBase = tinteCanion = CL_PLATA;
        visible = false;
        mostrar();
        tinteBase = tbtmp;
        tinteCanion = tctmp;
        visible = false;
    }
}

void canion::mover(int _x,int _y){
    bool estavisible = visible;
    if(estavisible)
        ocultar();
    x = _x;
    y = _y;

    if(estavisible)
        mostrar();
}

void canion::retinte(int _tinteBase,int _tinteCanion){
    tinteBase = _tinteBase;
    tinteCanion = (_tinteCanion==-1)?tinteBase:_tinteCanion;

    if(visible){
        visible = false;
        mostrar();
    }
}

void canion::redimensionar(int _anchoBase,int _largoCanion, int _anchoCanion){
    bool estavisible = visible;
    if(estavisible)
        ocultar();
    anchoBase = _anchoBase;
    largoCanion = _largoCanion;
    anchoCanion = _anchoCanion;

    if(estavisible)
        mostrar();
}

void canion::rotar(int _dirBase){
    int desfase = angCanion-dirBase;
    bool estavisible = visible;
    if(estavisible)
        ocultar();

    dirBase = _dirBase;
    angCanion = dirBase+desfase;

    if(estavisible)
        mostrar();

}

void canion::apuntar(int _angCanion){
    bool estavisible = visible;
    if(estavisible)
        ocultar();

    angCanion = _angCanion;

    if(angCanion>(dirBase+80))
        angCanion=dirBase+80;

    if(angCanion<(dirBase-80))
        angCanion=dirBase-80;

    if(estavisible)
        mostrar();
}



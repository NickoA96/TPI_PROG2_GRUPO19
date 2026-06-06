#include "ProyectilMediano.h"

ProyectilMediano::ProyectilMediano(){
    cargarTextura("proyectilBueno.png");
    setScale(0.1f,0.1f);
    setEsBueno(true);
    setVelocidad(3.f);
    setSegundosEfecto(3.f);

};



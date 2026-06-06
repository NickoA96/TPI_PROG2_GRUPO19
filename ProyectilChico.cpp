#include "ProyectilChico.h"

ProyectilChico::ProyectilChico(){
    cargarTextura("proyectil1.png");
    setScale(0.1f, 0.1f);
    setEsBueno(false);
    setVelocidad(4.f);
    setSegundosEfecto(6.f);
};

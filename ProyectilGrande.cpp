#include "ProyectilGrande.h"
#include <cmath>


ProyectilGrande::ProyectilGrande(){
    _posXInicio = 0;
    _tiempo = 0;
    cargarTextura("proyectilGrande.png");
    setScale(0.2f, 0.2f);
    setEsBueno(false);
    setVelocidad(4.f);
    setSegundosEfecto(8.f);
}



void ProyectilGrande::movimiento(){
    float y = this->getPos().y;
    _tiempo += 0.05f; //se le asigna un valor para que la funcion seno siga dando resultados y no quede estatica en el tiempo
    float amplitud=40.f; //controla que tanto puede expandirse en la pantalla el zig-zag
    float frecuencia=1.f; //regula la velocidad del zig-zag
    y+=_velocidad;
    float ondulado=_posXInicio+(amplitud*sin(_tiempo*frecuencia));
    this->setPosition(ondulado,y);
};


void ProyectilGrande::posicionRandom(){
float y = 180.f;
    float x = rand() % 1550;
    this->setPosition(x, y);
    _posXInicio=x;
}

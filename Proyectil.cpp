#include "Proyectil.h"
#include <cmath>
#include <iostream>
Proyectil::Proyectil():_velocidad(0.f), _esBueno(false), _segundosEfecto(0.f), _posXInicio(0), _tiempo(0){}

void Proyectil::setVelocidad(float velocidad){
    _velocidad=velocidad;
}

void Proyectil::setEsBueno(bool concepto){
    _esBueno=concepto;
}

void Proyectil::setSegundosEfecto(float tiempo){
    _segundosEfecto=tiempo;
}

float Proyectil::getVelocidad()const{
    return _velocidad;
}

bool Proyectil::getEsBueno()const{
    return _esBueno;
}

float Proyectil::getSegundosEfecto()const{
    return _segundosEfecto;
}

bool Proyectil::fueraPantalla()const {
    return getPos().y > 900;
}

void Proyectil::actualizarProyectil(){
    movimiento();
}

/*void Proyectil::movimiento(){
    float x = this->getPos().x;
    float y = this->getPos().y;

    y +=_velocidad;
    this->setPosition(x,y);
}*/

void Proyectil::movimiento(){
    float y = this->getPos().y;
    _tiempo += 0.05f; //se le asigna un valor para que la funcion seno siga dando resultados y no quede estatica en el tiempo
    float amplitud=40.f; //controla que tanto puede expandirse en la pantalla el zig-zag
    float frecuencia=1.f; //regula la velocidad del zig-zag
    y+=_velocidad;
    float ondulado=_posXInicio+(amplitud*sin(_tiempo*frecuencia));
    this->setPosition(ondulado,y);
}

void Proyectil::posicionRandom(){
    float y = 180.f;
    float x = rand() % 1550;
    this->setPosition(x, y);
    _posXInicio=x;
}

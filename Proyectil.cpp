#include "Proyectil.h"

#include <iostream>
Proyectil::Proyectil():_velocidad(0.f), _esBueno(false), _segundosEfecto(0.f){}

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

void Proyectil::movimiento(){
    float x = this->getPos().x;
    float y = this->getPos().y;

    y +=_velocidad;
    this->setPosition(x,y);
}



void Proyectil::posicionRandom(){
    float y = 180.f;
    float x = rand() % 1550;
    this->setPosition(x, y);
}

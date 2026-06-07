#include "Jugador.h"

Jugador::Jugador(){

    cargarTextura("alumno_sprite_trasera.png");
    setPosition(750.f, 700.f);
    setScale(0.4f, 0.4f);

    _velocidad = 8.f;
    _tiempoCursada = 30.f;
    _conceptosBuenos = 0;
    _conceptosMalos = 0;
    _colorCambiado = false;

};

void Jugador::moverConTeclado(){
    float x = this->getPos().x;
    float y = this->getPos().y;

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) x -=_velocidad;
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) x +=_velocidad;

    this->setPosition(x, y);

}

void Jugador::limitarZona(){
    float x = this->getPos().x;
    float y = this->getPos().y;
        if(x >= 1550){x = x-_velocidad;} /*Aca hay que hacer un pivot o calcular bien para poner la resolucion exacta, revisar*/
        if(x <= 0){x = x+_velocidad;}

        this->setPosition(x,y);

}
void Jugador::actualizar(){
    if(_colorCambiado){
        if(_relojColor.getElapsedTime().asSeconds() >= 0.5f){
            setColor(sf::Color::White);
            _colorCambiado = false;
            setScale(0.4f, 0.4f);
        }
    }
    this->moverConTeclado();
    this->limitarZona();
}

void Jugador::sumarTiempo(float segundos) {
    _tiempoCursada += segundos;
    _conceptosBuenos++;
}

void Jugador::restarTiempo(float segundos) {
    _tiempoCursada -= segundos;
    _conceptosMalos++;
}

float Jugador::getTiempoIncial()const {
    return _tiempoCursada;
}

void Jugador::setTiempoIncial(float tiempo) {
    _tiempoCursada = tiempo;
}

int Jugador::getPuntaje() const {
    return _conceptosBuenos - _conceptosMalos;
}



void Jugador::cambiarColorTemporal(sf::Color _color){
    this->setColor(_color);
    if(_color == sf::Color::Green){
        this->setScale(0.45f, 0.45f);
    }else if (_color == sf::Color::Red){
        this->setScale(0.38f, 0.38f);
    }
    _colorCambiado = true;
    _relojColor.restart();
}

void Jugador::reiniciar(){

    cargarTextura("alumno_sprite_trasera.png");
    setPosition(750.f, 700.f);
    setScale(0.4f, 0.4f);
    setColor(sf::Color::White);
    _relojColor.restart();
    _velocidad = 8.f;
    _tiempoCursada = 30.f;
    _conceptosBuenos = 0;
    _conceptosMalos = 0;
    _colorCambiado = false;


}

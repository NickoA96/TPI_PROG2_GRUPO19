#include "Juego.h"
#include <iostream>
using namespace std;

Juego::Juego(){
    ///FONDO
    _fondo.cargarTextura("fondo2.png");
    ///profesor
    _profesor.cargarTextura("profesor_sprite.png");
    _profesor.setPosition(700.f, 25.f);
    _profesor.setScale(0.4f, 0.4f);
    ///letra tiempo
    _font.loadFromFile("arial.ttf");
    _textTiempo.setFont(_font);
    _textTiempo.setCharacterSize(25);

    ///letra pausa
    _textPausa.setFont(_font);
    _textPausa.setCharacterSize(25);
    _textPausa.setPosition(10.f, 865.f);
    _textPausa.setOutlineThickness(5.f);
    _textPausa.setString("Presione P para pausar la partida");

    ///estilo letra
    _textTiempo.setFillColor(sf::Color::Red);
    _textTiempo.setPosition(720.f, 0.f);
    _textTiempo.setOutlineThickness(2.f);
    _textTiempo.setOutlineColor(sf::Color::Black);


    ///sonidos
    _sonido_Colision_Erroneo_Buffer.loadFromFile("erroneo.wav");
    _sonido_Colision_Erroneo.setBuffer(_sonido_Colision_Erroneo_Buffer);
    _sonido_Colision_Erroneo.setVolume(20.f);
    _sonido_Colision_Correcto_Buffer.loadFromFile("correcto.wav");
    _sonido_Colision_Correcto.setBuffer(_sonido_Colision_Correcto_Buffer);
    _sonido_Colision_Correcto.setVolume(20.f);


    inicializarArray();

    _vProyectiles[0] = new ProyectilChico;
    _vProyectiles[0]->posicionRandom();

    _vProyectiles[1] = new ProyectilMediano;
    _vProyectiles[1]->posicionRandom();

}


void Juego::draw(sf::RenderTarget& target, sf::RenderStates states) const{

            target.draw(_fondo);
            target.draw(_profesor);

            for(int i = 0; i<100; i++){
                if(_vProyectiles[i]!=nullptr){
                    target.draw(*_vProyectiles[i]);
                }
            }
            target.draw(_jugador);
            target.draw(_textTiempo);
            target.draw(_textPausa);
}

void Juego::actualizarJuego(){

    _jugador.actualizar();
    for(int i = 0; i < 100; i++) {
        if(_vProyectiles[i] != nullptr) {
            _vProyectiles[i]->actualizarProyectil();
            if(_vProyectiles[i]->fueraPantalla()){
                delete _vProyectiles[i];
                _vProyectiles[i] = nullptr;
            }
        }
    }
    chequearColisiones();
    spawnearProyectiles();
    subirDificultad();
    actualizarTextoTiempo();

}

void Juego::chequearColisiones(){
            for(int i = 0; i<100; i++){
                if(_vProyectiles[i]!= nullptr){
                    if(_jugador.getBounds().intersects(_vProyectiles[i]->getBounds())){
                            aplicarEfectoProyectil(i);
                    }
                }
            }

}


void Juego::aplicarEfectoProyectil(int pos){

    if(_vProyectiles[pos]->getEsBueno()){
        _jugador.cambiarColorTemporal(sf::Color::Green);
        _jugador.sumarTiempo(_vProyectiles[pos]->getSegundosEfecto());
        _sonido_Colision_Correcto.setPitch(1.f + (rand()%3/10.f));
        _sonido_Colision_Correcto.play();
    }else if(!_vProyectiles[pos]->getEsBueno()){
        _jugador.cambiarColorTemporal(sf::Color::Red);
        _jugador.restarTiempo(_vProyectiles[pos]->getSegundosEfecto());
        _sonido_Colision_Erroneo.setPitch(0.7f + (rand()%3/10.f));
        _sonido_Colision_Erroneo.play();
    }

    delete _vProyectiles [pos];
    _vProyectiles [pos] = nullptr;

}


void Juego::subirDificultad(){
    float segundosTranscurridos = _relojDificultad.getElapsedTime().asSeconds();

    if(segundosTranscurridos >= 5.f){
        _velocidadAcumulada +=0.5f;
        if(_tiempoEntreProyectiles >0.5f){
            _tiempoEntreProyectiles -= 0.3f;
        }
        if(_cantidadProyectiles < 50){
            _cantidadProyectiles++;
        }
        for(int i = 0; i<100;i++){
            if(_vProyectiles[i] != nullptr){
                _vProyectiles[i]->setVelocidad(_vProyectiles[i]->getVelocidad()+0.5f);

            }
        }
        _relojDificultad.restart();
    }

}


/// funcion que spawnea misiles en cierto tiempo, a cierta velocidad y el proyectil que sale depende del rand()
void Juego::spawnearProyectiles(){

    int tipoProyectil;
    int contadorProyectiles = 0;


    ///cuento proyectiles activos
    for(int i =0 ; i<100; i++){
        if(_vProyectiles[i] != nullptr){
            contadorProyectiles++;
        }
    }
    ///verifico tiempo con el reloj que se reinicia cada cierto tiempo
    if(_relojSpawn.getElapsedTime().asSeconds() >= _tiempoEntreProyectiles ){
        for(int i = 0; i<100; i++){
            if(contadorProyectiles < _cantidadProyectiles) {
                if(_vProyectiles[i]== nullptr){
                    tipoProyectil = rand() % 3;
                    if(tipoProyectil == 0){
                        _vProyectiles[i] = new ProyectilChico;
                    }else if(tipoProyectil ==1){
                        _vProyectiles[i] = new ProyectilMediano;
                    }else if(tipoProyectil ==2){
                        _vProyectiles[i] = new ProyectilGrande;
                       //_vProyectiles[i] = new ProyectilChico;
                    }
                    float x = evitarSuperposicionProyectiles();
                    _vProyectiles[i]->posicionRandom(x);
                    _vProyectiles[i]->setVelocidad(_vProyectiles[i]->getVelocidad() + _velocidadAcumulada);
                    break;
                }
            }
        }
        _relojSpawn.restart();
    }

}


float Juego::getTiempoXPartida()const {

 float tiempoRestante = _jugador.getTiempoIncial();
 tiempoRestante -= _tiempoJugador.getElapsedTime().asSeconds();
 return tiempoRestante;

}


bool Juego::juegoTerminado() const {
    if(_estaPausado) return false;

    if (this->getTiempoXPartida()<= 0){
        return true;
    }else{
        return false;
    }
}

void Juego::inicializarArray(){
    for(int i = 0; i<100; i++){
        _vProyectiles[i] = nullptr;
    }
}


void Juego::actualizarTextoTiempo(){
    float tiempoActual = getTiempoXPartida();
    int minutos = (int)tiempoActual / 60;
    int segundos = (int)tiempoActual % 60;

    string textoSegundos;
    string textoMinutos;

    if(segundos < 10){
        textoSegundos = "0" + std::to_string(segundos);
    }else{
        textoSegundos = std::to_string(segundos);
    }
    textoMinutos = std::to_string(minutos);
    _textTiempo.setString("Tiempo: " + textoMinutos + ":" + textoSegundos);

}


void Juego::reiniciar(){

    _tiempoJugador.restart();
    _relojSpawn.restart();
    _relojDificultad.restart();
    _cantidadProyectiles = 2;
    _velocidadAcumulada = 0.f;
    _tiempoEntreProyectiles = 3.f;
    _estaPausado = false;
    _jugador.reiniciar();

    for(int i = 0; i < 100; i++){
            if(_vProyectiles[i]!=nullptr){
                delete _vProyectiles[i];
                _vProyectiles[i] = nullptr;
            }
    }

    _vProyectiles[0] = new ProyectilChico;
    _vProyectiles[0]->posicionRandom();
    _vProyectiles[1] = new ProyectilMediano;
    _vProyectiles[1]->posicionRandom();
}

void Juego::pausar(){
    _tiempoGuardado = getTiempoXPartida();
    _estaPausado = true;

}
void Juego::reanudar(){
    _jugador.setTiempoIncial(_tiempoGuardado);
    _tiempoJugador.restart();
    _estaPausado =false;
}

float Juego::evitarSuperposicionProyectiles(){

    ProyectilChico nuevoProyectil;
    nuevoProyectil.posicionRandom();
    float x = nuevoProyectil.getPos().x;
    bool posicionInvalida = true;

    while(posicionInvalida){
        posicionInvalida = false;
        for(int i=0; i<100;i++){
            if(_vProyectiles[i]!= nullptr){
                //if(_vProyectiles[i]->getPos().x == x){ /// riesgo xq como son float puede dar error, mejor usar abs que compara el valor absoluto
                if(abs(_vProyectiles[i]->getPos().x - x) < 50.f){
                    posicionInvalida = true;
                }
            }
        }
        if(posicionInvalida){
            nuevoProyectil.posicionRandom();
            x = nuevoProyectil.getPos().x;
        }
    }
    return x;
}


Juego::~Juego() {
    for(int i = 0; i < 100; i++) {
        if(_vProyectiles[i] != nullptr) {
            delete _vProyectiles[i];
            _vProyectiles[i] = nullptr;
        }
    }
}

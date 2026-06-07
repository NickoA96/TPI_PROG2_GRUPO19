#include <SFML/Graphics.hpp>
#include <ctime>
#include "Juego.h"
#include <iostream>
using namespace std;

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Prueba Juego");
    window.setFramerateLimit(60);
    Juego* juego = nullptr;

    ///menu
    //ESTADO
    int estado=0; //0-Menu Principal, 1-Jugando, 2-Pausa
    sf::Text textoMenu;
    sf::Font fuenteMenu;
    if(!fuenteMenu.loadFromFile("arial.ttf")){
        cout << "Error al cargar fuente.";
    };
    textoMenu.setFont(fuenteMenu);
    textoMenu.setString("Presione X para empezar a jugar.\nPresione Z para salir.");

    sf::Text textGameOver;
    textGameOver.setFont(fuenteMenu);
    textGameOver.setString("Game Over");
    sf::Text textGameOver2;
    textGameOver2.setFont(fuenteMenu);
    textGameOver2.setPosition(10,50);
    textGameOver2.setString("Para volver a jugar presione C");

    ///musica
    sf::Music musica;
    if (!musica.openFromFile("musica.mp3")) {
        std::cout << "Error al abrir el archivo de musica." << std::endl;
    }
    sf::SoundBuffer _sonido_Inicio_Buffer;
    _sonido_Inicio_Buffer.loadFromFile("bienvenido.wav");
    sf::Sound _sonido_Inicio;
    _sonido_Inicio.setBuffer(_sonido_Inicio_Buffer);
    sf::SoundBuffer _sonido_Pausa_Buffer;
    sf::Sound _sonido_Pausa;
    sf::SoundBuffer _sonido_Continuar_Buffer;
    sf::Sound _sonido_Continuar;
    _sonido_Pausa_Buffer.loadFromFile("pausa.wav");
    _sonido_Pausa.setBuffer(_sonido_Pausa_Buffer);
    _sonido_Continuar_Buffer.loadFromFile("continuar.wav");
    _sonido_Continuar.setBuffer(_sonido_Continuar_Buffer);

    bool sonidoPausa=false;
    bool sonidoInicio=true;

/// bucle
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed){window.close();}
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z && estado!=1){
                window.close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X && estado!=1){
                musica.setVolume(15);
                musica.play();
                if(estado==0){
                    juego = new Juego();
                    estado=1;
                }
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
                if(estado==1 && !juego->juegoTerminado()){
                    estado=2;
                    sonidoPausa=true;
                    juego->pausar();
                }
                else if(estado==2){
                    _sonido_Continuar.setVolume(60);
                    _sonido_Continuar.play();
                    musica.play();
                    estado=1;
                    juego->reanudar();
                }
            }

            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::C){
                if(juego != nullptr && juego->juegoTerminado()){
                    juego->reiniciar();
                    musica.play();
                    estado=1;
                }
            }
        }

        window.clear();

        if(estado==0){
            if(sonidoInicio){
                _sonido_Inicio.play();
                sonidoInicio=false;
            }
            window.draw(textoMenu);
        }
        if(juego != nullptr && !juego->juegoTerminado() && estado==1) {
            juego->actualizarJuego();
            window.draw(*juego);
        }else if(juego != nullptr && !juego->juegoTerminado() && estado==2){
            if(sonidoPausa){
                musica.pause();
                _sonido_Pausa.setVolume(60);
                _sonido_Pausa.play();
                sonidoPausa=false;
            }
            window.draw(*juego);
        }
        if(juego != nullptr && juego->juegoTerminado()){
            //Hacer sonido de salida de juego si llega le tiempo.
            window.draw(textGameOver);
            window.draw(textGameOver2);
            musica.pause();
        }

        window.display();
    }
    delete juego;
    return 0;
}

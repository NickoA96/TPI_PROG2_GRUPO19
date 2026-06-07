#include <SFML/Graphics.hpp>
#include <ctime>
#include "Juego.h"
#include <iostream>
using namespace std;

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Prueba Juego");
    window.setFramerateLimit(60);
    //ESTADO
    int estado=0; //0-Menu, 1-Jugando, 2-Pausa, 3-Menu Finalizada Partida?
    Juego juego;
    sf::Music musica;
    if (!musica.openFromFile("musica.mp3")) {
        std::cout << "Error al abrir el archivo de musica." << std::endl;
    }
    sf::SoundBuffer _sonido_Pausa_Buffer;
    sf::Sound _sonido_Pausa;
    sf::SoundBuffer _sonido_Continuar_Buffer;
    sf::Sound _sonido_Continuar;
    _sonido_Pausa_Buffer.loadFromFile("pausa.wav");
    _sonido_Pausa.setBuffer(_sonido_Pausa_Buffer);
    _sonido_Continuar_Buffer.loadFromFile("continuar.wav");
    _sonido_Continuar.setBuffer(_sonido_Continuar_Buffer);
    sf::Text textoMenu;
    sf::Font fuenteMenu;
    if(!fuenteMenu.loadFromFile("arial.ttf")){
        cout << "Error al cargar fuente.";
    };
    textoMenu.setFont(fuenteMenu);
    textoMenu.setString("Presiona X para empezar a jugar.\nPresione Z para salir.");
    bool sonidoPausa=false;
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)window.close();
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z && estado!=1){
                window.close();
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::X && estado!=1){
                musica.setVolume(20);
                musica.play();
                if(estado==0){
                    estado=1;
                }
            }
            if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
                if(estado==1){
                    estado=2;
                    sonidoPausa=true;
                }
                else if(estado==2){
                    _sonido_Continuar.setVolume(60);
                    _sonido_Continuar.play();
                    musica.play();
                    estado=1;
                }
            }
        }

        window.clear();

        if(estado==0){
            window.draw(textoMenu);
        }
        if(!juego.juegoTerminado() && estado==1) {
            juego.actualizarJuego();
            juego.dibujar(window);
        }else if(!juego.juegoTerminado() && estado==2){
            if(sonidoPausa){
                musica.pause();
                _sonido_Pausa.setVolume(60);
                _sonido_Pausa.play();
                sonidoPausa=false;
            }
            juego.dibujar(window);
        }

        window.display();
    }
    return 0;
}

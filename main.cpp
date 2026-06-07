#include <SFML/Graphics.hpp>
#include <ctime>
#include "Juego.h"
using namespace std;

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Prueba Juego");
    window.setFramerateLimit(60);
    //ESTADO
    int estado=1; //0-Menu, 1-Jugando, 2-Pausa
    Juego juego;
    sf::SoundBuffer _sonido_Pausa_Buffer;
    sf::Sound _sonido_Pausa;
    sf::SoundBuffer _sonido_Continuar_Buffer;
    sf::Sound _sonido_Continuar;
    _sonido_Pausa_Buffer.loadFromFile("pausa.wav");
    _sonido_Pausa.setBuffer(_sonido_Pausa_Buffer);
    _sonido_Continuar_Buffer.loadFromFile("continuar.wav");
    _sonido_Continuar.setBuffer(_sonido_Continuar_Buffer);
    bool sonidoPausa=false;
    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P){
                if(estado==1){
                    estado=2;
                    sonidoPausa=true;
                }
                else if(estado==2){
                    _sonido_Continuar.play();
                    estado=1;
                }
            }
        }

        window.clear();

        if(!juego.juegoTerminado() && estado==1) {
            juego.actualizarJuego();
            juego.dibujar(window);
        }else if(!juego.juegoTerminado() && estado==2){
            if(sonidoPausa){
                _sonido_Pausa.play();
                sonidoPausa=false;
            }
            juego.dibujar(window);
        }

        window.display();
    }
    return 0;
}

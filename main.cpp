#include <SFML/Graphics.hpp>
#include <ctime>
#include "Juego.h"
using namespace std;

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Prueba Juego");
    //probar con resolucion HD+, creo que da un buen margen y deberia verse bien con cualquier monitor moderno.
    window.setFramerateLimit(60);

    Juego juego;

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if(!juego.juegoTerminado()) {
            juego.actualizarJuego();
            juego.dibujar(window);
        }

        window.display();
    }
    return 0;
}

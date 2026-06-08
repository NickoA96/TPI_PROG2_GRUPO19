#include "Menu.h"
#include <iostream>
Menu::Menu(){
    if(!_fuente.loadFromFile("arial.ttf")){
        std::cout << "Error al cargar fuente.";
    }
    _texto.setFont(_fuente);
    _textoMenuPrincipal="Presiona X para iniciar el juego.\n"
                        "Presiona Z para salir.\n"
                        "Presiona A para ver el ranking.\n"
                        "Presiona S para ver el ultimo jugador.";
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states)const {
        target.draw(_texto, states);
}

void Menu::mostrarMenuPrincipal(){
        _texto.setString(_textoMenuPrincipal);

}

void Menu::mostrarGameOver(int puntaje){
        std::string texto ="Fin del juego.\n"
                    "Puntaje Total: "+ std::to_string(puntaje) + "\n"
                    "Presione C para volver a jugar.\n"
                    "Presione D para volver al menu principal.";
        _texto.setString(texto);
}

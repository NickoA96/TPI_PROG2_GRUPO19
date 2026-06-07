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
    _textoGameOver="Fin del juego.\n"
                    "Puntaje Total: \n" //no funciona todavia.
                    "Presione C para volver a jugar.\n"
                    "Presione D para volver al menu principal."; //no funciona todavia.
    _texto.setString(_textoMenuPrincipal);
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states)const {
        target.draw(_texto, states);
}

void Menu::setMensaje(const int estado){
    if(estado==0){
        _texto.setString(_textoMenuPrincipal);
    }
    if(estado==3){
        _texto.setString(_textoGameOver);
    }
}

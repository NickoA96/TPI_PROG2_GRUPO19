#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable{
    public:
        Menu();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void mostrarMenuPrincipal();
        void mostrarGameOver(int puntaje);
    protected:

    private:
        std::string _textoMenuPrincipal;
        std::string _textoGameOver;
        sf::Text _texto;
        sf::Font _fuente;
};



#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable{
    public:
        Menu();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setMensaje(const int estado);
    protected:

    private:
        std::string _textoMenuPrincipal;
        std::string _textoGameOver;
        sf::Text _texto;
        sf::Font _fuente;
};

#endif // MENU_H

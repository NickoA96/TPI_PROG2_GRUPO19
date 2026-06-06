#include "Objeto.h"

Objeto::Objeto(){};


void Objeto::cargarTextura(std::string archivo) {
	_textura.loadFromFile(archivo);
	_sprite.setTexture(_textura);
}


void Objeto::setScale(float x, float y) {
	_sprite.setScale(x, y);
}


void Objeto::setPosition(float x, float y){
	_sprite.setPosition(x,y);
}



void Objeto::setColor(sf::Color color){
    _sprite.setColor(color);
}

sf::Color Objeto::getColor() const {
    return _sprite.getColor();
}


sf::FloatRect Objeto::getBounds() const {
    return _sprite.getGlobalBounds();
}


sf::Vector2f Objeto::getPos() const {
	return _sprite.getPosition();
}

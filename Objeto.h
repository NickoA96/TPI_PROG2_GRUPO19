#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

class Objeto : public sf::Drawable {
private:
	sf::Sprite _sprite;
	sf::Texture _textura;

protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(_sprite, states);
	}
public:
	Objeto();

	void cargarTextura(std::string archivo);


	void setScale(float x, float y);

	void setPosition(float x, float y);

	void setColor(sf::Color color);

	sf::Color getColor() const;

	sf::FloatRect getBounds() const;

	sf::Vector2f getPos() const;

};




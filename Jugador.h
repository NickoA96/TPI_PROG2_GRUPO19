#pragma once
#include "Objeto.h"

class Jugador : public Objeto {
private:
	float _tiempoCursada;
	int _conceptosBuenos;
	int _conceptosMalos;
	float _velocidad;
    sf::Clock _relojColor;
    bool _colorCambiado;

public:

	Jugador();

	void moverConTeclado();
	void limitarZona();
	void actualizar();
	void sumarTiempo(float segundos);
	void restarTiempo(float segundos);
    void cambiarColorTemporal(sf::Color);
	void setTiempoIncial(float tiempo);
    void reiniciar();
	float getTiempoIncial()const;
	int getPuntaje() const;

};

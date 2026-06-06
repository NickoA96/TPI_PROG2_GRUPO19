#pragma once
#include "Objeto.h"


class Proyectil : public Objeto {
protected:
	float _velocidad;
	bool _esBueno;
	float _segundosEfecto;

public:
    Proyectil();
	///set
	void setVelocidad(float velocidad);
	void setEsBueno(bool concepto);
	void setSegundosEfecto(float tiempo);

	///get
	float getVelocidad()const;
	bool getEsBueno() const;
	float getSegundosEfecto()const;
    bool fueraPantalla() const;
    void posicionRandom();

	void actualizarProyectil();

	virtual void movimiento();

};

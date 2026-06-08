#pragma once
#include "Proyectil.h"

class ProyectilGrande : public Proyectil {
private:
    	float _tiempo;
        float _posXInicio;
public:
	ProyectilGrande();

	void movimiento() override;
	void posicionRandom() override;
};




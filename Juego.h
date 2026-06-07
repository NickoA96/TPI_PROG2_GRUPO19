#pragma once
#include <ctime>
#include "Objeto.h"
#include "Jugador.h"
#include "Proyectil.h"
#include "ProyectilMediano.h"
#include "ProyectilGrande.h"
#include "ProyectilChico.h"

class Juego : public sf::Drawable{
private:
	Jugador _jugador;
	Objeto _profesor;
	Objeto _fondo;
	Proyectil* _vProyectiles[100];
	sf::Clock _tiempoJugador;
	sf::Clock _relojSpawn;
	sf::Clock _relojDificultad; /// reloj que cada cierto tiempo le sube la velocidad a los misiles
	float _tiempoEntreProyectiles = 3.f; /// tiempo que tardan los proyectiles para reaparecer, a medida que pasa cierto tiempo va bajando ej = 15.f  y baja 14.f cada 15 sg
	int _cantidadProyectiles = 2;
	float _velocidadActual = 0.f;
    sf::Text _textTiempo;
    sf::Font _font;
	sf::Sound _sonido_Colision_Erroneo;
    sf::SoundBuffer _sonido_Colision_Erroneo_Buffer;
    sf::Sound _sonido_Colision_Correcto;
    sf::SoundBuffer _sonido_Colision_Correcto_Buffer;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	Juego();
	~Juego();
	void actualizarTextoTiempo();
	void inicializarArray();
    float getTiempoXPartida();
	void actualizarJuego(); //ok
	void chequearColisiones(); //ok
	void aplicarEfectoProyectil(int pos); //ok
	void subirDificultad();                 // ok              // controla cuando agregar mas misiles -> modifica _tiempoEntreProyectiles y _velocidad del proyectil
	void spawnearProyectiles();             //ok/// funcion que spawnea misiles en cierto tiempo, a cierta velocidad y el proyectil que sale depende del rand()
	bool juegoTerminado()const ; //ok   /// verifica cuando el tiempo
	void reiniciar();           //ok /// inicia con reloj en 0, puntake 0, y 2 proyectiles, podria llamar al constructor directmanete ?
};

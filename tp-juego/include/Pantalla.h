#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"

class Juego;

class Pantalla {
    protected:
        Juego* juego;

        Input input;

    public:
        Pantalla(Juego* juego) : juego(juego) {}

        virtual ~Pantalla() = default;

        virtual void manejarEventos(const sf::Event& evento) = 0;
        virtual void actualizar(float deltaTime) = 0;
        virtual void dibujar(sf::RenderWindow& ventana) = 0;
};
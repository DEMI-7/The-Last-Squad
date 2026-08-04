#pragma once
#include <SFML/Graphics.hpp>

class Juego;

class Pantalla {
    protected:
        Juego* juego;

    public:
        Pantalla(Juego* juego) : juego(juego) {}

        virtual ~Pantalla() = default;

        virtual void manejarEventos(const sf::Event& evento) = 0;
        virtual void actualizar(float deltaTime) = 0;
        virtual void dibujar(sf::RenderWindow& ventana) = 0;
};
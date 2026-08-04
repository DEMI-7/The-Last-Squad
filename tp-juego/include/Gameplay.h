#pragma once
#include "Pantalla.h"

class Gameplay : public Pantalla {
    public:
        Gameplay(Juego* juego);

        void manejarEventos(const sf::Event&) override;

        void actualizar(float deltaTime) override;

        void dibujar(sf::RenderWindow&) override;

    private:

    sf::Texture texturaEjemplo;
    sf::Sprite spriteEjemplo;
};
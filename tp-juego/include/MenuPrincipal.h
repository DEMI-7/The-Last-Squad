#pragma once
#include "Pantalla.h"

class MenuPrincipal : public Pantalla {
    public:
        MenuPrincipal(Juego* juego);

        void manejarEventos(const sf::Event& evento) override;

        void actualizar(float deltaTime) override;

        void dibujar(sf::RenderWindow& ventana) override;
};
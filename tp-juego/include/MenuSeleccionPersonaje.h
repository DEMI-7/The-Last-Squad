#pragma once
#include "Pantalla.h"
#include "Boton.h"

class MenuSeleccionPersonaje : public Pantalla {
    public:
        MenuSeleccionPersonaje(Juego* juego);

        void manejarEventos(const sf::Event&) override;

        void actualizar(float deltaTime) override;

        void dibujar(sf::RenderWindow&) override;

    private:

    Boton botonEjemplo;

    std::vector<Boton> vectorBotones;
};
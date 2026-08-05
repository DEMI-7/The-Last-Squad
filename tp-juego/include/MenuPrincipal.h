#pragma once
#include "Pantalla.h"
#include "boton.h"

class MenuPrincipal : public Pantalla {
    public:
        MenuPrincipal(Juego* juego);

        void manejarEventos(const sf::Event& evento) override;

        void actualizar(float deltaTime) override;

        void dibujar(sf::RenderWindow& ventana) override;

    private:

        sf::Texture texturaFondoMenu;
        sf::Sprite spriteFondoMenu;
        Boton botonJugar;
};
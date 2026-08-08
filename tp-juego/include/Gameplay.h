#pragma once
#include "Pantalla.h"
#include "Personaje.h"

class Gameplay : public Pantalla {
    public:
        Gameplay(Juego* juego);

        void manejarEventos(const sf::Event&) override;

        void actualizar(float deltaTime) override;

        void dibujar(sf::RenderWindow&) override;

    private:

    Personaje jugador;

    //---- Vectores de elementos del juego ----
    std::vector<sf::FloatRect> obstaculosHitbox;
    std::vector<sf::FloatRect> hitboxZombies;

};
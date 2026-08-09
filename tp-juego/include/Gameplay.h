#pragma once
#include "Pantalla.h"
#include "Personaje.h"
#include "ObjetoMapa.h"

class Gameplay : public Pantalla {
    public:
        Gameplay(Juego* juego);

        void manejarEventos(const sf::Event&) override;

        void actualizar(float deltaTime) override;

        void dibujar(sf::RenderWindow&) override;

        void inicializarObstaculos(std::vector<ObjetoMapa> &vectorObjetosMapa);

    private:

    Personaje jugador;

    //---- Vectores de elementos del juego ----
    std::vector<ObjetoMapa> vectorObjetosMapa;
    std::vector<sf::FloatRect> vectorObjetosMapaHitbox;
    std::vector<sf::FloatRect> hitboxZombies;

};
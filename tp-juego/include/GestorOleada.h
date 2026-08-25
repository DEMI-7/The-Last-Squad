#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Zombie;

class GestorOleada {
    public:
        GestorOleada(std::vector<Zombie>& vectorZombies);

        void actualizar(sf::Vector2f posJugador, float deltaTime);

        void spawnZombie();

    private:
        std::vector<Zombie>& vectorZombies;
        sf::Vector2f posJugador;

        sf::Texture texturaZombie;

        float tiempoSpawn;

};
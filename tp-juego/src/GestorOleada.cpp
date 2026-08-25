#include "../include/GestorOleada.h"
#include "../include/Zombie.h"
#include <iostream>

GestorOleada::GestorOleada (std::vector<Zombie>& vector) : vectorZombies(vector) {
    if (!texturaZombie.loadFromFile("assets/zombie.png")) {
        std::cout << "Error al cargar la textura desde: " << "assets/zombie.png" << std::endl;
        return;
    }

    tiempoSpawn = 0;

    vectorZombies.emplace_back(texturaZombie, sf::Vector2f(390,310));
    vectorZombies.emplace_back(texturaZombie, sf::Vector2f(390,1020));
    vectorZombies.emplace_back(texturaZombie, sf::Vector2f(1920,1020));
}

void GestorOleada::actualizar (sf::Vector2f posJugador, float deltaTime) {
    this->posJugador = posJugador;
    tiempoSpawn += deltaTime;

    if (tiempoSpawn >= 1) {
        vectorZombies.emplace_back(texturaZombie, sf::Vector2f(390,310));
        tiempoSpawn = 0;
    }
}

void GestorOleada::spawnZombie () {
    vectorZombies.emplace_back(texturaZombie, sf::Vector2f(390,310));
}
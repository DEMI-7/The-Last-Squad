#pragma once
#include <SFML/Graphics.hpp>
#include "Proyectil.h"

class ProyectilPool {
    private:
        sf::Texture texturaProyectil;
        std::vector<Proyectil> proyectilesVector;

    public:
        ProyectilPool();
};
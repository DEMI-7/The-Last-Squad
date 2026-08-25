#pragma once
#include <SFML/Graphics.hpp>
#include "Proyectil.h"

class ProyectilPool {
    private:
        sf::Texture texturaProyectil;
        std::vector<Proyectil> proyectilesVector;

    public:
        ProyectilPool();

        void disparar(sf::Vector2f posInicial, sf::Vector2f direccion, float alcance, float velocidad, float danio, int tipo);
        
        void actualizar(float deltaTime);

        void dibujar(sf::RenderWindow& ventana);

        std::vector<Proyectil>& getVectorProyectiles();
};
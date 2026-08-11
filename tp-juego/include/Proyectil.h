#pragma once
#include "ObjetoGrafico.h"

class Proyectil : public ObjetoGrafico{
    private:
        float velocidad;
        float alcanceMax;
        float danio;

        float distanciaRecorrida;

        bool disponible;
        int idArma;

        sf::Vector2f direccion;
        
    public:
        Proyectil(const sf::Texture& textura);

        void usarProyectil(sf::Vector2f posInicial, sf::Vector2f direccion, float alcanceMax, float velocidad, float danio, int idArma);

        void actualizar(float deltaTime);

        bool estaDisponible() {return disponible;}
};
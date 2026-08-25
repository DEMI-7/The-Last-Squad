#pragma once
#include "ObjetoGrafico.h"

class Proyectil : public ObjetoGrafico{
    private:
        float velocidad;
        float alcanceMax;
        float danio;

        float distanciaRecorrida;

        bool activo;
        int idArma;

        sf::Vector2f direccion;

        
        public:
        Proyectil(const sf::Texture& textura);
        
        void usarProyectil(sf::Vector2f posInicial, sf::Vector2f direccion, float alcanceMax, float velocidad, float danio, int idArma);
        
        void actualizar(float deltaTime);
        
        virtual void dibujar(sf::RenderWindow& ventana) override;
        
        bool estaActivo() {return activo;}

        void activar() {this->activo = true;}

        void desactivar() {this->activo = false;}

        float getDanio() {return this->danio;}
};
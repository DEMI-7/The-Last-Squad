#include "../include/Proyectil.h"
#include <cmath>

Proyectil::Proyectil(const sf::Texture& textura) : ObjetoGrafico(textura){
    velocidad = 0;
    alcanceMax = 0;
    danio = 0;
    idArma = -1.f;
    direccion.x = 0;
    direccion.y = 0;

    this->disponible = true;
}

void Proyectil::usarProyectil(sf::Vector2f posInicial, sf::Vector2f direccion, float alcanceMax, float velocidad, float danio, int idArma) {
    this->velocidad = velocidad;
    this->alcanceMax = alcanceMax;
    this->danio = danio;
    this->idArma = idArma;
    this->distanciaRecorrida = 0;
    this->direccion.x = direccion.x - posInicial.x;
    this->direccion.y = direccion.y - posInicial.y;

    float longitud = std::sqrt(direccion.x * direccion.x + direccion.y * direccion.y);
    this->direccion.x /= longitud;
    this->direccion.y /= longitud;

    this->disponible = false;

    setPosicion(posInicial.x, posInicial.y);
}

void Proyectil::actualizar(float deltaTime) {
    if(disponible == false) {
        float desplazamiento = velocidad * deltaTime;
        mover(direccion.x * desplazamiento, direccion.y * desplazamiento);
        distanciaRecorrida += desplazamiento;
    }

    if (distanciaRecorrida >= alcanceMax) {
        disponible = true;
    }
}
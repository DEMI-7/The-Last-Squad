#include "../include/Proyectil.h"
#include <cmath>

Proyectil::Proyectil(const sf::Texture& textura) : ObjetoGrafico(textura){
    velocidad = 0;
    alcanceMax = 0;
    danio = 0;
    idArma = -1.f;
    direccion.x = 0;
    direccion.y = 0;
    distanciaRecorrida = 0;

    this->activo = false;
}

void Proyectil::usarProyectil(sf::Vector2f posInicial, sf::Vector2f posicionObjetivo , float alcanceMax, float velocidad, float danio, int idArma) {
    this->velocidad = velocidad;
    this->alcanceMax = alcanceMax;
    this->danio = danio;
    this->idArma = idArma;
    this->distanciaRecorrida = 0;
    this->direccion = posicionObjetivo - posInicial;

    float longitud = std::sqrt(this->direccion.x * this->direccion.x + this->direccion.y * this->direccion.y);
    this->direccion.x /= longitud;
    this->direccion.y /= longitud;

    activar();

    float anguloRadianes = std::atan2(direccion.y, direccion.x);
    // Convertimos a grados
    float anguloGrados = anguloRadianes * 180.f / std::acos(-1.f);
    // +90.f compensa que el sprite original apunta hacia arriba
    setAngulo(anguloGrados + 90.f);

    
    setHitbox(5,5);
    centrarOrigen();
    setHitboxVisible();
    escalarSprite(0.3f,0.3f);
    
    setPosicionCentrado(posInicial.x, posInicial.y);
}

void Proyectil::actualizar(float deltaTime) {
    if(estaActivo()) {
        float desplazamiento = velocidad * deltaTime;
        mover(direccion.x * desplazamiento, direccion.y * desplazamiento);
        distanciaRecorrida += desplazamiento;
    }

    if (distanciaRecorrida >= alcanceMax) {
        desactivar();
    }
}

void Proyectil::dibujar(sf::RenderWindow& ventana) {
    if (estaActivo()){
        ObjetoGrafico::dibujar(ventana);
    }
}
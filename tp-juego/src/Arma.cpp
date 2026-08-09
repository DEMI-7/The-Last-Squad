#include "../include/Arma.h"
#include <cmath>

Arma::Arma(int id, std::string nombre, float cadencia, float danio, float alcance, float costo, int municionMaxima, int tamanioCargador){

    this->idArma = id;
    this->nombre = nombre;
    this->cadencia = cadencia;
    this->danio = danio;
    this->alcance = alcance;
    this->costo = costo;
    this->municionMaxima = municionMaxima;
    this->tamanioCargador = tamanioCargador;
    this->desbloqueada = false;

    std::string rutaTextura = "assets/armas/" + nombre + ".png";
    cargarTextura(rutaTextura);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({0.f, bounds.size.y / 2.f});

}

void Arma::actualizar(float deltaTime,const sf::Vector2f &posicionMouse, const sf::Vector2f &posicionJugador){
    
    this->deltaTime = deltaTime;

    // ----------------- Actualizar el ángulo de la mira
    float deltaX = posicionMouse.x - posicionJugador.x;
    float deltaY =  posicionJugador.y - posicionMouse.y;

    if (deltaX < 0) {
        escalarSprite(2.f, -2.f); // Voltear horizontalmente
        setPosicionCentrado(posicionJugador.x - 13, posicionJugador.y + 12.f);
    } else {
        escalarSprite(2.f, 2.f); // Escala normal
        setPosicionCentrado(posicionJugador.x + 13, posicionJugador.y + 12.f);
    }
        
    setAngulo(std::atan2(deltaY, deltaX) * -180.f / 3.14159f);


    disparar(posicionMouse, posicionJugador);
}

void Arma::disparar(const sf::Vector2f &posicionMouse, const sf::Vector2f &posicionJugador) {
    tiempoDesdeUltimoDisparo += deltaTime;
    tiempoRecarga += deltaTime;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tiempoDesdeUltimoDisparo >= cadencia && municionEnCargador > 0 && !enRecarga) {
        
    }
}

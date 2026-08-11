#include "../include/Arma.h"
#include <cmath>
#include <iostream>

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

    this->enRecarga = false;

    this->municionActual = municionMaxima; // Empieza con la mitad de la munición total
    this->municionEnCargador = tamanioCargador;

    std::string rutaTextura = "assets/armas/" + nombre + ".png";
    cargarTextura(rutaTextura);
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({0.f, bounds.size.y / 2.f});

}

void Arma::actualizar(float deltaTime,const sf::Vector2f &posicionMouse, const sf::Vector2f &posicionJugador, ProyectilPool& proyectiles){
    
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


    disparar(posicionMouse, posicionJugador, proyectiles);
    recargar();
}

void Arma::disparar(const sf::Vector2f &posicionMouse, const sf::Vector2f &posicionJugador, ProyectilPool& proyectiles) {
    tiempoDesdeUltimoDisparo += deltaTime;
    tiempoRecarga += deltaTime;

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && tiempoDesdeUltimoDisparo >= cadencia && municionEnCargador > 0 && !enRecarga) {
        proyectiles.disparar(posicionJugador, posicionMouse, alcance, 200, danio, idArma);
        std::cout << "disparo" << std::endl;
        municionEnCargador--;
        tiempoDesdeUltimoDisparo = 0.f;
    }
}

void Arma::recargar() {
    // ----------------- Lógica de recarga
        if (tiempoRecarga >= 1.f) {
            enRecarga = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && municionEnCargador < tamanioCargador && !enRecarga && municionActual > 0) {
            int cantidad = 0;

            if (municionActual >= (tamanioCargador - municionEnCargador)) {
                cantidad = tamanioCargador - municionEnCargador;
            } else {
                cantidad = municionActual;
            }
            municionActual -= cantidad;

            municionEnCargador += cantidad;

            tiempoRecarga = 0.f;
            enRecarga = true;

            // Reproducir sonido de recarga adecuado
            /*
            if (idArma == 2) {
                SoundManager::play("recargar_scopeta");
            } else if (idArma == 4 || getNombre() == "rifle" || getNombre() == "fal") {
                SoundManager::play("recargar_rifle");
            } else if (idArma == 0 || idArma == 7 || idArma == 5) {
                // cuchillo/katana/arco no recargan con sonido de arma de fuego
            } else {
                SoundManager::play("recargar_pistola");
            }
            */
        }
}

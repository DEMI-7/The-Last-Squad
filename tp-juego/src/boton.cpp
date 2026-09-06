#include "../include/Boton.h"
#include <iostream>

Boton::Boton(){
    id = -1;
    hover = false;
    presionado = false;
    mouseEstabaPresionado = false;
}

Boton::Boton(int tipo, int id, std::string direccionImagen){
    this->id = id;
    hover = false;
    presionado = false;
    mouseEstabaPresionado = false;

    if (tipo == 1){
        cargarTextura(direccionImagen);
    }
}

bool Boton::estaHover(const sf::RenderWindow& ventana) {
    sf::Vector2f mouse = ventana.mapPixelToCoords(sf::Mouse::getPosition(ventana));

    if(hitbox.contains(mouse)) {
        hover = true;
        return true;
    } else {
        hover = false;
        return false;
    }
}

bool Boton::estaPresionado() {
    if (hover && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        presionado = true;
        return true;
    }
    presionado = false;
    return false;
}

// Teclado/joystik
void Boton::actualizar(float deltaTime, const sf::RenderWindow& ventana, int seleccion) { 
    if (seleccion == this->id) {
        hover = true;
    }
    else {
        hover = false;
    }

    if(getEstaHover()) {
        seleccionarSprite(1, 0); // Cambiar a la segunda columna del sprite (
    } else {
        seleccionarSprite(0, 0); // Cambiar a la primera columna del sprite (normal)
    }
}

// Mouse
void Boton::actualizar(float deltaTime, const sf::RenderWindow& ventana) { 
    estaHover(ventana);
    estaPresionado();

    if(getEstaHover()) {
        seleccionarSprite(1, 0); // Cambiar a la segunda columna del sprite (
    } else {
        seleccionarSprite(0, 0); // Cambiar a la primera columna del sprite (normal)
    }
}

bool Boton::fueClickeado() {
    bool mousePresionado = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    bool clic = hover && mousePresionado && !mouseEstabaPresionado;
    mouseEstabaPresionado = mousePresionado;
    return clic;
}
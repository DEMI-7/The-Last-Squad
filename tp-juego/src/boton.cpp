#include"../include/Boton.h"

Boton::Boton(){
    id = -1;
    hover = false;
    presionado = false;
    mouseEstabaPresionado = false;
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
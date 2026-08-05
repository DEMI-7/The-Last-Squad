#include"../include/Boton.h"

Boton::Boton(float x, float y, float ancho, float alto, std::string rutaTextura) : ObjetoGrafico(rutaTextura) {
    
    setPosicion(x, y);
    //setearTamanioSprite(ancho, alto);
    //centrarOrigen();

    /*
    texto.setString(textoString);
    texto.setCharacterSize(16);
    texto.setFillColor(sf::Color::White);
    
    // Centrar el texto en el botón
    sf::FloatRect bounds = texto.getLocalBounds();
    texto.setOrigin({bounds.position.x + bounds.size.x/2.0f, bounds.position.y + bounds.size.y/2.0f});
    texto.setPosition({x + ancho/2.0f, y + alto/2.0f});
    */

    hover = false;
    presionado = false;
}

Boton::Boton(){

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
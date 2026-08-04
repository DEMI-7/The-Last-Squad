#include "../include/Gameplay.h"
#include <iostream>

Gameplay::Gameplay(Juego* juego) : Pantalla(juego), spriteEjemplo(texturaEjemplo){
    if(texturaEjemplo.loadFromFile("../assets/menu_bg.png")) {
        std::cout << "se importo bien" << std::endl;
    } else {
        std::cout << "fallo carga imagen" << std::endl;
    }

    //spriteEjemplo.setTexture(texturaEjemplo);

    spriteEjemplo.setTextureRect(
    sf::IntRect({0, 0}, {
        static_cast<int>(texturaEjemplo.getSize().x),
        static_cast<int>(texturaEjemplo.getSize().y)
    })
);

    std::cout << spriteEjemplo.getGlobalBounds().size.x << " "
          << spriteEjemplo.getGlobalBounds().size.y << std::endl;

    
}

void Gameplay::manejarEventos(const sf::Event&) {

}

void Gameplay::actualizar(float deltaTime) {

}

void Gameplay::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteEjemplo);
    //std::cout << "me dibujo" << std::endl;
}
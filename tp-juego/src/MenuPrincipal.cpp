#include "../include/MenuPrincipal.h"
#include "../include/Juego.h"
#include "../include/Gameplay.h"

#include <iostream>

MenuPrincipal::MenuPrincipal(Juego* juego) : Pantalla(juego), spriteFondoMenu(texturaFondoMenu) {
    if(texturaFondoMenu.loadFromFile("assets/menu_bg.png")) {
        std::cout << "se importo bien" << std::endl;
    } else {
        std::cout << "fallo carga imagen" << std::endl;
    }

    //spriteEjemplo.setTexture(texturaEjemplo);

    spriteFondoMenu.setTextureRect(sf::IntRect({ 0, 0 }, { static_cast<int>(texturaFondoMenu.getSize().x), static_cast<int>(texturaFondoMenu.getSize().y) }));
}

void MenuPrincipal::manejarEventos(const sf::Event& evento) {
    if (const auto* tecla = evento.getIf<sf::Event::KeyPressed>()) {
        if (tecla->code == sf::Keyboard::Key::Enter) {
            juego->cambiarPantalla(new Gameplay(juego));
        }
    }
}

void MenuPrincipal::actualizar(float deltaTime) {

}

void MenuPrincipal::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteFondoMenu);
}
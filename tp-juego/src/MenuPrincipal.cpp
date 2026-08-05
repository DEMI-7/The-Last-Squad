#include "../include/MenuPrincipal.h"
#include "../include/Juego.h"
#include "../include/Gameplay.h"
#include "../include/MenuSeleccionPersonaje.h"

#include <iostream>

MenuPrincipal::MenuPrincipal(Juego* juego) : Pantalla(juego), spriteFondoMenu(texturaFondoMenu) {
    if(texturaFondoMenu.loadFromFile("assets/menu_bg.png")) {
        std::cout << "se importo bien" << std::endl;
    } else {
        std::cout << "fallo carga imagen" << std::endl;
    }

    //spriteEjemplo.setTexture(texturaEjemplo);

    spriteFondoMenu.setTextureRect(sf::IntRect({ 0, 0 }, { static_cast<int>(texturaFondoMenu.getSize().x), static_cast<int>(texturaFondoMenu.getSize().y) }));

    botonJugar.cargarTextura("assets/varios/botonSheet_32x12.png");
    botonJugar.centrarOrigen();
    botonJugar.setearTamanioSprite(32, 12);
    botonJugar.setPosicionCentrado(960.f, 540.f); // Posición centrada en la ventana
    botonJugar.escalarSprite(5.f, 5.f); // Escalar el sprite a la mitad de su tamaño original
    botonJugar.ajustarHitboxAlSprite(); // Ajustar la hitbox al tamaño del sprite
}

void MenuPrincipal::manejarEventos(const sf::Event& evento) {
    if (const auto* tecla = evento.getIf<sf::Event::KeyPressed>()) {
        if (tecla->code == sf::Keyboard::Key::Enter) {
            juego->cambiarPantalla(new Gameplay(juego));
        }
    }

    if (botonJugar.getEstaPresionado()) {
        std::cout << "Botón Jugar presionado" << std::endl;
        juego->cambiarPantalla(new MenuSeleccionPersonaje(juego));
    }
}

void MenuPrincipal::actualizar(float deltaTime) {
    botonJugar.actualizar(deltaTime, juego->getVentana());
}

void MenuPrincipal::dibujar(sf::RenderWindow& ventana) {
    ventana.draw(spriteFondoMenu);
    botonJugar.dibujar(ventana); // Dibujar la hitbox del botón para depuración
}
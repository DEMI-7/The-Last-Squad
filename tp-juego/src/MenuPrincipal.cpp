#include "../include/MenuPrincipal.h"
#include "../include/Juego.h"
#include "../include/Gameplay.h"

MenuPrincipal::MenuPrincipal(Juego* juego) : Pantalla(juego){

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

}
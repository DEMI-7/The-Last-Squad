#include "../include/MenuSeleccionPersonaje.h"
#include "../include/Juego.h"
#include "../include/MenuPrincipal.h"
#include <iostream>

MenuSeleccionPersonaje::MenuSeleccionPersonaje(Juego* juego) : Pantalla(juego){
    botonEjemplo.cargarTextura("assets/varios/botonSheet_32x12.png");
    botonEjemplo.setearTamanioSprite(32, 12);
    botonEjemplo.centrarOrigen();
    botonEjemplo.escalarSprite(10,10);
    botonEjemplo.ajustarHitboxAlSprite();
    botonEjemplo.setPosicionCentrado(500,500);
}

void MenuSeleccionPersonaje::manejarEventos(const sf::Event&) {
    if (botonEjemplo.getEstaPresionado()) {
        std::cout << "Botón Jugar presionado" << std::endl;
        juego->cambiarPantalla(new MenuPrincipal(juego));
    }
}

void MenuSeleccionPersonaje::actualizar(float deltaTime) {
    botonEjemplo.actualizar(deltaTime, juego->getVentana());
}

void MenuSeleccionPersonaje::dibujar(sf::RenderWindow& ventana) {
    botonEjemplo.dibujar(ventana);
}
#include "../include/Juego.h"
#include "MenuPrincipal.h"

Juego::Juego() : ventana(sf::VideoMode({1280,720}), "The Last Squad") {
    pantallaActual = new MenuPrincipal(this);
}

void Juego::ejecutar() {
    sf::Clock reloj;

    while (ventana.isOpen()) {
        float deltaTime = reloj.restart().asSeconds();

        while (const auto evento = ventana.pollEvent()) {
            if (evento->is <sf::Event::Closed>()) {
                ventana.close();
            }

            pantallaActual->manejarEventos(*evento);
        }

        pantallaActual->actualizar(deltaTime);
        ventana.clear();
        pantallaActual->dibujar(ventana);
        ventana.display();
    }
}

void Juego::cambiarPantalla(Pantalla* pantalla){
    delete pantallaActual;
    pantallaActual = pantalla;
}

sf::RenderWindow& Juego::getVentana(){
    return ventana;
}
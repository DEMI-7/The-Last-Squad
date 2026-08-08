#include "../include/MenuSeleccionPersonaje.h"
#include "../include/Juego.h"
#include "../include/MenuPrincipal.h"
#include "../include/archivoPersonaje.h"
#include <iostream>

// TODO:
// Actualmente las posiciones son fijas para los 5 personajes.
// En el futuro reemplazar por un sistema automático
// con páginas o scroll para soportar cualquier cantidad.

MenuSeleccionPersonaje::MenuSeleccionPersonaje(Juego* juego) : Pantalla(juego){
    archivoPersonaje archivo("personajes.dat");

    std::vector<RegistroPersonaje> registroPers = archivo.devolverVectorPersonajes();
    int indice = 0;
    int x = 300;
    int y = 540;

    vectorBotones.resize(registroPers.size());

    for (auto& boton : vectorBotones) {
        boton.cargarTextura("assets/personajes/icon_" + std::to_string(registroPers[indice].id)+".png");
        boton.setearTamanioSprite(1254, 1254);
        boton.centrarOrigen();
        boton.escalarSprite(0.2f,0.2f);
        boton.ajustarHitboxAlSprite();
        boton.setPosicionCentrado(x, y);
        boton.setId(registroPers[indice].id);
        indice++;
        x += 300; // Ajusta la posición horizontal para el siguiente botón
    }
}

void MenuSeleccionPersonaje::manejarEventos(const sf::Event&) {
    for (auto& boton : vectorBotones) {
        if (boton.fueClickeado()) {
            std::cout << "Botón de personaje con ID " << boton.getId() << " clickeado" << std::endl;
            //juego->cambiarPantalla(new Gameplay(juego));
        }
    }
}

void MenuSeleccionPersonaje::actualizar(float deltaTime) {
    for (auto& boton : vectorBotones) {
        boton.actualizar(deltaTime, juego->getVentana());
    }
}

void MenuSeleccionPersonaje::dibujar(sf::RenderWindow& ventana) {
    //botonEjemplo.dibujar(ventana);
    for (auto& boton : vectorBotones) {
        boton.dibujar(ventana);
    }
}
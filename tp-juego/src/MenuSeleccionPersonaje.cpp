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
    //RegistroPersonaje registroPers = archivo.traerRegistro(0);
    //std::cout<<registroPers.nombre<<std::endl;

    /*
    botonEjemplo.cargarTextura("assets/personajes/icon_" + std::to_string(registroPers.id) + ".png");
    botonEjemplo.setearTamanioSprite(1254, 1254);
    botonEjemplo.centrarOrigen();
    botonEjemplo.escalarSprite(0.2f,0.2f);
    botonEjemplo.ajustarHitboxAlSprite();
    botonEjemplo.setPosicionCentrado(500,500);
    */

    std::vector<RegistroPersonaje> registroPers = archivo.devolverVectorPersonajes();
    int indice = 0;
    for (auto& boton : vectorBotones) {
        boton.cargarTextura("assets/personajes/icon_" + std::to_string(registroPers[indice].id)+".png");
        indice++;
    }

}

void MenuSeleccionPersonaje::manejarEventos(const sf::Event&) {
    if (botonEjemplo.fueClickeado()) {
        //std::cout << "Botón ejemplo clickeado" << std::endl;
        //juego->cambiarPantalla(new MenuPrincipal(juego));
    }
}

void MenuSeleccionPersonaje::actualizar(float deltaTime) {
    botonEjemplo.actualizar(deltaTime, juego->getVentana());
}

void MenuSeleccionPersonaje::dibujar(sf::RenderWindow& ventana) {
    botonEjemplo.dibujar(ventana);
}
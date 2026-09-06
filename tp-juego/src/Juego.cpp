#include "../include/Juego.h"
#include "MenuPrincipal.h"

Juego::Juego() : ventana(sf::VideoMode({1280,720}), "The Last Squad") {
    pantallaActual = new MenuPrincipal(this);

    //SDL_AddGamepadMappingsFromFile("gamecontrollerdb.txt");
    //SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt");

    sf::VideoMode modoEscritorio = sf::VideoMode::getDesktopMode();
    ventana.create(modoEscritorio, "The Last Squad", sf::State::Fullscreen);
    //ventana.setMouseCursorVisible(false); // Ocultar el cursor estándar para usar la mira personalizada
    ventana.setFramerateLimit(60);
    ventana.requestFocus(); // Forzar el foco de la ventana

    vista.setSize({1920.f, 1080.f});
    vista.setCenter({960.f, 540.f});
    ventana.setView(vista);
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
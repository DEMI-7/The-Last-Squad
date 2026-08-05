#pragma once
#include <SFML/Graphics.hpp>

class Pantalla;

class Juego {
    private:
        sf::RenderWindow ventana;
        Pantalla* pantallaActual;
        sf::View vista;

    public:
        Juego();
        void ejecutar();
        void cambiarPantalla(Pantalla* pantalla);
        sf::RenderWindow& getVentana();
};
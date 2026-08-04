#pragma once
#include <SFML/Graphics.hpp>

class Pantalla;

class Juego {
    private:
        sf::RenderWindow ventana;
        Pantalla* pantallaActual;

    public:
        Juego();
        void ejecutar();
        void cambiarPantalla(Pantalla* pantalla);
        sf::RenderWindow& getVentana();
};
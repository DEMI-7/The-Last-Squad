#pragma once
#include <SFML/Graphics.hpp>

class Input {
    private:
        bool arribaActual = false;
        bool abajoActual = false;
        bool izquierdaActual = false;
        bool derechaActual = false;

        bool aceptarActual = false;
        bool cancelarActual = false;

        bool arribaAnterior = false;
        bool abajoAnterior = false;
        bool izquierdaAnterior = false;
        bool derechaAnterior = false;

        bool aceptarAnterior = false;
        bool cancelarAnterior = false;

        bool usandoMouseActual = true;
        sf::Vector2i posicionMouseAnterior;
        sf::Vector2i posicionMouse;

        bool clickIzquierdoActual = false;
        bool clickIzquierdoAnterior = false;

        bool mouseSeMovio();

    public:
        void actualizar(const sf::RenderWindow& ventana);
        
        // teclado y joystik
        bool arriba() const;
        bool abajo() const;
        bool izquierda() const;
        bool derecha() const;

        bool aceptar() const;
        bool cancelar() const;

        // mouse
        sf::Vector2i getPosicionMouse() const;
        sf::Vector2f getPosicionMouseMundo(const sf::RenderWindow& ventana, const sf::View& vista) const;

        bool clickIzquierdo() const;
        bool usandoMouse() const;
};
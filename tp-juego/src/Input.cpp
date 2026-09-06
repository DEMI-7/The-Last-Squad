#include "../include/Input.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include <cmath>


bool Input::arriba() const
{
    return arribaActual && !arribaAnterior;
}

bool Input::abajo() const
{
    return abajoActual && !abajoAnterior;
}

bool Input::izquierda() const
{
    return izquierdaActual && !izquierdaAnterior;
}

bool Input::derecha() const
{
    return derechaActual && !derechaAnterior;
}

bool Input::aceptar() const
{
    return aceptarActual && !aceptarAnterior;
}

bool Input::cancelar() const
{
    return cancelarActual && !cancelarAnterior;
}

bool Input::usandoMouse() const {
    return usandoMouseActual;
}

bool Input::mouseSeMovio() {
    int diferenciaX = posicionMouse.x - posicionMouseAnterior.x;
    int diferenciaY = posicionMouse.y - posicionMouseAnterior.y;

    float distancia = std::sqrt(
        static_cast<float>(diferenciaX * diferenciaX) +
        static_cast<float>(diferenciaY * diferenciaY)
    );

    return distancia > 10.f;
}

void Input::actualizar(const sf::RenderWindow& ventana)
{
    // =========================================
    // ESTADOS ANTERIORES
    // =========================================
    arribaAnterior = arribaActual;
    abajoAnterior = abajoActual;
    izquierdaAnterior = izquierdaActual;
    derechaAnterior = derechaActual;

    aceptarAnterior = aceptarActual;
    cancelarAnterior = cancelarActual;

    clickIzquierdoAnterior = clickIzquierdoActual;

    posicionMouseAnterior = posicionMouse;


    // =====================================================
    // TECLADO
    // =====================================================

    bool tecladoArriba =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);

    bool tecladoAbajo =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);

    bool tecladoIzquierda =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);

    bool tecladoDerecha =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);

    bool tecladoAceptar =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);

    bool tecladoCancelar =
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);


    // =====================================================
    // JOYSTICK
    // =====================================================

    bool joystickArriba = false;
    bool joystickAbajo = false;
    bool joystickIzquierda = false;
    bool joystickDerecha = false;

    bool joystickAceptar = false;
    bool joystickCancelar = false;

    // Por ahora usamos el joystick 0
    if (sf::Joystick::isConnected(0))
    {
        // ---------------- D-PAD ----------------

        float povX = sf::Joystick::getAxisPosition(
            0,
            sf::Joystick::Axis::PovX
        );

        float povY = sf::Joystick::getAxisPosition(
            0,
            sf::Joystick::Axis::PovY
        );

        // joystick:
        // Arriba  = +100
        // Abajo   = -100
        // Izq.    = -100
        // Der.    = +100

        joystickArriba = povY > 50.f;
        joystickAbajo = povY < -50.f;

        joystickIzquierda = povX < -50.f;
        joystickDerecha = povX > 50.f;


        // ---------------- BOTONES ----------------

        // SFML 0 = A
        // SFML 1 = B

        joystickAceptar =
            sf::Joystick::isButtonPressed(0, 0);

        joystickCancelar =
            sf::Joystick::isButtonPressed(0, 1);
    }

    // =====================================================
    // ESTADO FINAL
    // =====================================================

    arribaActual =
        tecladoArriba ||
        joystickArriba;

    abajoActual =
        tecladoAbajo ||
        joystickAbajo;

    izquierdaActual =
        tecladoIzquierda ||
        joystickIzquierda;

    derechaActual =
        tecladoDerecha ||
        joystickDerecha;

    aceptarActual =
        tecladoAceptar ||
        joystickAceptar;

    cancelarActual =
        tecladoCancelar ||
        joystickCancelar;


    // =====================================================
    // MOUSE
    // =====================================================
    posicionMouse = sf::Mouse::getPosition(ventana);

    clickIzquierdoActual = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);

    // =========================================
    // MÉTODO DE INPUT
    // =========================================

    if (tecladoArriba ||
        tecladoAbajo ||
        tecladoIzquierda ||
        tecladoDerecha ||
        tecladoAceptar ||
        tecladoCancelar)
    {
        usandoMouseActual = false;
    }

    if (joystickArriba ||
        joystickAbajo ||
        joystickIzquierda ||
        joystickDerecha ||
        joystickAceptar ||
        joystickCancelar)
    {
        usandoMouseActual = false;
    }

    if (mouseSeMovio() || clickIzquierdoActual)
    {
        usandoMouseActual = true;
    }
}

sf::Vector2i Input::getPosicionMouse() const {
    return posicionMouse;
}

sf::Vector2f Input::getPosicionMouseMundo(const sf::RenderWindow& ventana, const sf::View& vista) const {
    return ventana.mapPixelToCoords(posicionMouse, vista);
}

bool Input::clickIzquierdo() const {
    return clickIzquierdoActual && !clickIzquierdoAnterior;
}
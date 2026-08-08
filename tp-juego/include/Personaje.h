#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Entidad.h"


class Personaje : public Entidad {
private:
    // ------ VARIABLES ------
    int idPersonaje;
    std::string nombre;
    float armaduraMax;
    float armaduraActual;
    float cooldownHabilidad;
    std::string habilidad;


    sf::Vector2f posicionAnterior;
    float movimientoX;
    float movimientoY;
    
    // ----- FUNCIONES PRIVADAS -----
    void guardarPosicionAnterior();

    void volverPosicionAnteriorX();

    void volverPosicionAnteriorY();

    sf::Vector2f getPosicionAnterior() const { return posicionAnterior; }

    float getMovimientoX() const;

    float getMovimientoY() const;

    void setVelocidad(float velocidad);
    
    public:
    // ------ FUNCIONES PUBLICAS ------
    Personaje();
    
    Personaje(int id, int idArmaEspecial, std::string nombre, float vida, float armadura, float velocidad, float cooldownHabilidad);
    
    //virtual void actualizar(float deltaTime, const std::vector<sf::FloatRect>& obstaculos, const std::vector<sf::FloatRect>& hitboxZombies, const sf::Vector2f &posicionMouse);

};
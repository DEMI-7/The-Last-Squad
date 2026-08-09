#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Entidad.h"
#include "Arma.h"
#include "archivoArma.h"


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

    float deltaTime;

    std::vector<Arma> inventarioArmas;
    int armaEquipada;
    
    // ----- FUNCIONES PRIVADAS -----
    void movimiento(const std::vector<sf::FloatRect>& vectorObjetosMapaHitbox);
    void elegirArma();
    
public:
    // ------ FUNCIONES PUBLICAS ------
    Personaje();
    
    Personaje(int id, int idArmaEspecial, std::string nombre, float vida, float armadura, float velocidad, float cooldownHabilidad);
    
    virtual void actualizar(float deltaTime, sf::Vector2f posMouse, const std::vector<sf::FloatRect>& vectorObjetosMapaHitbox);

    void dibujar(sf::RenderWindow& ventana) override;


};
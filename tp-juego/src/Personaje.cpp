#include "../include/Personaje.h"

Personaje::Personaje(int id, int idArmaEspecial, std::string nombre, float vida, float armadura, float velocidad, float cooldownHabilidad) {
    idPersonaje = id;
    this->nombre = nombre;
    vidaMax = vida;
    vidaActual = vida;
    armaduraMax = armadura;
    armaduraActual = armadura;
    this->velocidad = velocidad;
    velocidadNormal = velocidad;
    if (this->velocidad <= 0.f) this->velocidad = 200.f;
    this->cooldownHabilidad = cooldownHabilidad;
    habilidad = "-";

    mostrarHitbox = false;
    cargarTextura("assets/personajes/" + nombre + ".png");

    escalarSprite(0.8f,0.8f);
    
    centrarOrigen();

    setHitbox(13.f * 2.f, 16.f * 2.1f);
    setPosicionCentrado(900.f, 540.f);
    posicionAnterior = sf::Vector2f(1720.f, 1080.f);

}


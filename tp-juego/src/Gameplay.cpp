#include "../include/Gameplay.h"
#include <iostream>

Gameplay::Gameplay(Juego* juego) : Pantalla(juego), jugador(0,0, "recon", 100,100,200,10) {
    
}

void Gameplay::manejarEventos(const sf::Event&) {

}

void Gameplay::actualizar(float deltaTime) {
    //jugador.actualizar(deltaTime, obstaculosHitbox, hitboxZombies, sf::Vector2f({0,0}));
}

void Gameplay::dibujar(sf::RenderWindow& ventana) {
    jugador.dibujar(ventana);
}
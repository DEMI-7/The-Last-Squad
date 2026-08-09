#include "../include/Gameplay.h"
#include "../include/Juego.h"
#include <iostream>

Gameplay::Gameplay(Juego* juego) : Pantalla(juego), jugador(0,0, "recon", 100,100,200,10) {
    inicializarObstaculos(vectorObjetosMapa);
}

void Gameplay::manejarEventos(const sf::Event&) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        return;
    }
}

void Gameplay::actualizar(float deltaTime) {

    sf::Vector2f posMouse = juego->getVentana().mapPixelToCoords(sf::Mouse::getPosition(juego->getVentana()), juego->getVista());
    
    jugador.actualizar(deltaTime, posMouse, vectorObjetosMapaHitbox);
}

void Gameplay::dibujar(sf::RenderWindow& ventana) {
    jugador.dibujar(ventana);

    for (auto &obstaculo : vectorObjetosMapa) {
        obstaculo.dibujar(ventana);
    }
}


void Gameplay::inicializarObstaculos(std::vector<ObjetoMapa> &vectorObjetosMapa) {
  vectorObjetosMapa.reserve(40);

  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(1058.f, 258.f);
  vectorObjetosMapa.back().setPosicion(640.f, 540.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(1058.f, 258.f);
  vectorObjetosMapa.back().setPosicion(640.f, 1300.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(1058.f, 258.f);
  vectorObjetosMapa.back().setPosicion(2170.f, 1300.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(1058.f, 258.f);
  vectorObjetosMapa.back().setPosicion(2170.f, 540.f);
  

  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(1058.f, 146.f);
  vectorObjetosMapa.back().setPosicion(2170.f, 2014.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(1058.f, 146.f);
  vectorObjetosMapa.back().setPosicion(636.f, 2014.f);
  

  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(1058.f, 72.f);
  vectorObjetosMapa.back().setPosicion(2170.f, 0.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(1058.f, 72.f);
  vectorObjetosMapa.back().setPosicion(640.f, 0.f);
  

  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(168.f, 72.f);
  vectorObjetosMapa.back().setPosicion(0.f, 0.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(168.f, 258.f);
  vectorObjetosMapa.back().setPosicion(0.f, 540.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(168.f, 258.f);
  vectorObjetosMapa.back().setPosicion(0.f, 1300.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(168.f, 146.f);
  vectorObjetosMapa.back().setPosicion(0.f, 2014.f);
  

  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(168.f, 72.f);
  vectorObjetosMapa.back().setPosicion(3672.f, 0.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(168.f, 258.f);
  vectorObjetosMapa.back().setPosicion(3672.f, 540.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(168.f, 258.f);
  vectorObjetosMapa.back().setPosicion(3672.f, 1300.f);
  vectorObjetosMapa.emplace_back();
  vectorObjetosMapa.back().setHitbox(168.f, 146.f);
  vectorObjetosMapa.back().setPosicion(3672.f, 2014.f);


  for (auto &obstaculo : vectorObjetosMapa) {
        obstaculo.setHitboxVisible();
    }

    for (auto &obstaculo : vectorObjetosMapa) {
        vectorObjetosMapaHitbox.push_back(obstaculo.getHitbox());
    }
}
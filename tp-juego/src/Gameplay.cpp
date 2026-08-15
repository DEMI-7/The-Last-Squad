#include "../include/Gameplay.h"
#include "../include/Juego.h"
#include <iostream>

Gameplay::Gameplay(Juego* juego) : Pantalla(juego), jugador(0,4, "recon", 100,100,200,10) {
    inicializarObstaculos(vectorObjetosMapa);
    elMapa.cargarTextura("assets/varios/mapa.png");

    vectorhitboxZombies.push_back(pruebaEnemigo.getHitbox());
}

void Gameplay::manejarEventos(const sf::Event&) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        return;
    }
}

void Gameplay::actualizar(float deltaTime) {

    resolverColisionesJugadorZombies();

    vectorhitboxZombies.clear();
    vectorhitboxZombies.push_back(pruebaEnemigo.getHitbox());

    sf::Vector2f posMouse = juego->getVentana().mapPixelToCoords(sf::Mouse::getPosition(juego->getVentana()), juego->getVista());
    
    jugador.actualizar(deltaTime, posMouse, vectorObjetosMapaHitbox, proyectiles);

    proyectiles.actualizar(deltaTime);

    pruebaEnemigo.actualizar(deltaTime, jugador.getHitbox(), vectorObjetosMapaHitbox, vectorhitboxZombies);
}

void Gameplay::dibujar(sf::RenderWindow& ventana) {
    elMapa.dibujar(ventana);

    jugador.dibujar(ventana);

    for (auto &obstaculo : vectorObjetosMapa) {
        obstaculo.dibujar(ventana);
    }

    proyectiles.dibujar(ventana);

    pruebaEnemigo.dibujar(ventana);
}


void Gameplay::resolverColisionesJugadorZombies() {
    if(pruebaEnemigo.getHitbox().findIntersection(jugador.getHitbox())) {

        // Resolver la penetración entre ambos
        sf::FloatRect hitboxZombie = pruebaEnemigo.getHitbox();
        sf::FloatRect hitboxJugador = jugador.getHitbox();

        float overlapLeft = (hitboxZombie.position.x + hitboxZombie.size.x) - hitboxJugador.position.x;

        float overlapRight = (hitboxJugador.position.x + hitboxJugador.size.x) - hitboxZombie.position.x;

        float overlapTop = (hitboxZombie.position.y + hitboxZombie.size.y) - hitboxJugador.position.y;

        float overlapBottom = (hitboxJugador.position.y + hitboxJugador.size.y) - hitboxZombie.position.y;

        float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : -overlapRight;

        float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : -overlapBottom;

        if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
            // Separar horizontalmente
            jugador.mover(minOverlapX / 0.6f, 0.f);
            //pruebaEnemigo.mover(-minOverlapX / 0.4f, 0.f);
        } else {
            // Separar verticalmente
            jugador.mover(0.f, minOverlapY / 0.6f);
            //pruebaEnemigo.mover(0.f, -minOverlapY / 0.4f);
        }
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
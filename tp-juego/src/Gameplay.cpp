#include "../include/Gameplay.h"
#include "../include/Juego.h"
#include <iostream>
#include <algorithm>

Gameplay::Gameplay(Juego* juego) : Pantalla(juego), jugador(0,4, "recon", 100,100,200,10), oleada(vectorZombies) {

    inicializarObstaculos(vectorObjetosMapa);
    elMapa.cargarTextura("assets/varios/mapa.png");

    juego->getVista().setSize({1920,1080});

    vectorZombies.reserve(100);

}

void Gameplay::manejarEventos(const sf::Event&) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        juego->getVentana().close();
        return;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {

    }
}

void Gameplay::actualizar(float deltaTime) {

    // mouse e input
    input.actualizar(juego->getVentana());
    sf::Vector2f posMouse = input.getPosicionMouseMundo(juego->getVentana(), juego->getVista());
    
    // zombies
    oleada.actualizar(jugador.getPosicion(), deltaTime);

    for(auto& zombie : vectorZombies){
        vectorhitboxZombies.clear();
        vectorhitboxZombies.push_back(zombie.getHitbox());    
    }
    for(auto& zombie : vectorZombies){
        zombie.actualizar(deltaTime, jugador.getHitbox(), vectorObjetosMapaHitbox, vectorhitboxZombies);
    }
    
    //proyectiles
    proyectiles.actualizar(deltaTime);
    // jugador
    jugador.actualizar(deltaTime, posMouse, vectorObjetosMapaHitbox, proyectiles);
    
    
    actualizarVista();
    
    // resolucion de interacciones
    resolverColisionesJugadorZombies();
    resolverColisionesProyectilZombies();

    // limpieza vector zombies
    vectorZombies.erase(std::remove_if(vectorZombies.begin(), vectorZombies.end(), [](const Zombie &z) { return !z.estaVivo(); }), vectorZombies.end());
    
}

void Gameplay::dibujar(sf::RenderWindow& ventana) {

    elMapa.dibujar(ventana);
    
    jugador.dibujar(ventana);
    
    for (auto &obstaculo : vectorObjetosMapa) {
        obstaculo.dibujar(ventana);
    }
    
    proyectiles.dibujar(ventana);
    
    for (auto& zombie : vectorZombies) {
        zombie.dibujar(ventana);
    }

}

void Gameplay::resolverColisionesProyectilZombies() {
    for (auto& proyectil : proyectiles.getVectorProyectiles()){
        for (auto& zombie : vectorZombies) {
            if (zombie.getHitbox().findIntersection(proyectil.getHitbox()) && proyectil.estaActivo()) {
                zombie.recibirDanio(proyectil.getDanio());
                proyectil.desactivar();
                std::cout << "DISPARO RECIBIDO" << std::endl;
                break;
            }
        }
    }
}

void Gameplay::resolverColisionesJugadorZombies() {
    for (auto& zombie : vectorZombies) {
        if(zombie.getHitbox().findIntersection(jugador.getHitbox())) {
            
            // Resolver la penetración entre ambos
            sf::FloatRect hitboxZombie = zombie.getHitbox();
            sf::FloatRect hitboxJugador = jugador.getHitbox();

            float overlapLeft = (hitboxZombie.position.x + hitboxZombie.size.x) - hitboxJugador.position.x;
            
            float overlapRight = (hitboxJugador.position.x + hitboxJugador.size.x) - hitboxZombie.position.x;
            
            float overlapTop = (hitboxZombie.position.y + hitboxZombie.size.y) - hitboxJugador.position.y;
            
            float overlapBottom = (hitboxJugador.position.y + hitboxJugador.size.y) - hitboxZombie.position.y;
            
            float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : -overlapRight;
            
            float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : -overlapBottom;
            
            if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
                // Separar horizontalmente
                jugador.mover(minOverlapX / 1.f, 0.f);
                zombie.mover(-minOverlapX / 1.f, 0.f);
            } else {
                // Separar verticalmente
                jugador.mover(0.f, minOverlapY / 1.f);
                zombie.mover(0.f, -minOverlapY / 1.f);
            }
        }
    }
}

void Gameplay::actualizarVista(){
    float auxVistaX = jugador.getPosicion().x;
    float auxVistaY = jugador.getPosicion().y;
    
    if (auxVistaX < juego->getVista().getSize().x / 2.f)
    auxVistaX = juego->getVista().getSize().x / 2.f;
    
    if (auxVistaX > elMapa.getSprite().getGlobalBounds().size.x - juego->getVista().getSize().x / 2.f)
    auxVistaX = elMapa.getSprite().getGlobalBounds().size.x - juego->getVista().getSize().x / 2.f;
    
    if (auxVistaY < juego->getVista().getSize().y / 2.f)
    auxVistaY = juego->getVista().getSize().y / 2.f;
    if (auxVistaY > elMapa.getSprite().getGlobalBounds().size.y - juego->getVista().getSize().y / 2.f)
    auxVistaY = elMapa.getSprite().getGlobalBounds().size.y - juego->getVista().getSize().y / 2.f;
    
    juego->getVista().setCenter({auxVistaX, auxVistaY});
    juego->getVentana().setView(juego->getVista());
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
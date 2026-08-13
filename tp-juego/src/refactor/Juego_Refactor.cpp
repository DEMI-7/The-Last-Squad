#include "../include/Juego.h"
#include "../include/SoundManager.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstring>
#include <optional>

Juego::Juego()  : spriteMapa(texturaMapa), spriteFondoMenu(texturaFondoMenu),textoStats(fuenteMenu) {
  // Inicialización de sonidos
  SoundManager::cargarSonidos();

  texturaMapa.loadFromFile("assets/varios/mapa.png");

  // Zonas de spawn de zombies
  std::vector<sf::FloatRect> zonasSpawn = {
      sf::FloatRect({200.f, 100.f}, {400.f, 350.f}),  // Superior Izquierda
      sf::FloatRect({3250.f, 100.f}, {400.f, 350.f}), // Superior Derecha
      sf::FloatRect({200.f, 850.f}, {400.f, 350.f}),  // Central Izquierda
      sf::FloatRect({3250.f, 850.f}, {400.f, 350.f}), // Central Derecha
      sf::FloatRect({200.f, 1600.f}, {400.f, 350.f}), // Inferior Izquierda
      sf::FloatRect({3250.f, 1600.f}, {400.f, 350.f}) // Inferior Derecha
  };
  zombieManager.inicializarZonasSpawn(zonasSpawn);

  trazaMosin.setFillColor(sf::Color::White);
  trazaMosin.setSize(sf::Vector2f(3000.f, 3.f));
  trazaMosin.setOrigin({0.f, 1.5f});

  // Cargar estadísticas históricas
  cargarStats();

}

void Juego::iniciar() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));  
  trampas.emplace_back(sf::Vector2f(1920,1080));
  while (ventana.isOpen()) {
      deltaTime = relojDelta.restart().asSeconds();
      procesarEventos();
      actualizar();
      renderizar();
    }
}

void Juego::actualizar()
{
  std::vector<sf::FloatRect> hitboxesZombies = zombieManager.getHitboxesZombies();

  vista.setSize({1280.f * jugador.getMultiplicadorZoom(), 720.f * jugador.getMultiplicadorZoom()});
  procesarRayCast();

  // -------- Lógica de zombies y colisión de balas delegada en ZombieManager --------
  zombieManager.actualizar(deltaTime, jugador, obstaculos, proyectiles, trampas);

  auxVistaX = jugador.getPosicion().x;
  auxVistaY = jugador.getPosicion().y;

  if (auxVistaX < vista.getSize().x / 2.f)
    auxVistaX = vista.getSize().x / 2.f;
  if (auxVistaX > texturaMapa.getSize().x - vista.getSize().x / 2.f)
    auxVistaX = texturaMapa.getSize().x - vista.getSize().x / 2.f;

  if (auxVistaY < vista.getSize().y / 2.f)
    auxVistaY = vista.getSize().y / 2.f;
  if (auxVistaY > texturaMapa.getSize().y - vista.getSize().y / 2.f)
    auxVistaY = texturaMapa.getSize().y - vista.getSize().y / 2.f;

  vista.setCenter({auxVistaX, auxVistaY});
  ventana.setView(vista);

  hud.actualizar(jugador, zombieManager);
}

void Juego::renderizar()
{
  ventana.clear();
  ventana.setView(vista);
  ventana.draw(spriteMapa);

  if (mostrarTrazaMosin)
  {
    ventana.draw(trazaMosin);
  }

  zombieManager.dibujarZombies(ventana);
  mira.dibujar(ventana);

  ventana.setView(ventana.getDefaultView());
  hud.dibujar(ventana);
  ventana.display();
}

void Juego::procesarRayCast(){
  if(mostrarTrazaMosin) {
    tiempoTrazaMosin -= deltaTime;
    if(tiempoTrazaMosin <= 0.f) {
      mostrarTrazaMosin = false;
    }
  }
  
  if(jugador.getArma().spawnRayCast) {
    sf::Vector2f origen = jugador.getPosicion();
    sf::Vector2f direccion;
    direccion.x = mira.getPosicion().x - origen.x;
    direccion.y = mira.getPosicion().y - origen.y;
    
    float longitud = std::sqrt(direccion.x*direccion.x + direccion.y * direccion.y);
    
    direccion.x /= longitud;
    direccion.y /= longitud;

    float angulo = std::atan2(direccion.y, direccion.x)* 180.f / 3.14159f;
    trazaMosin.setPosition({origen.x,origen.y+10});
    trazaMosin.setRotation(sf::degrees(angulo));

    mostrarTrazaMosin = true;
    tiempoTrazaMosin = 0.05f;
    float distanciaImpacto;
    float alcance = jugador.getArma().getAlcance();
    
    for (float distancia = 0.f; distancia < alcance; distancia += 5.f) {
      sf::Vector2f punto;
      
      punto.x = origen.x + direccion.x * distancia;
      punto.y = origen.y + direccion.y * distancia;
      trazaMosin.setSize(sf::Vector2f(alcance, 3.f));
      for(auto& obstaculo : obstaculos) {
        if (obstaculo.getHitbox().contains(punto)) {
          distanciaImpacto = distancia;
          trazaMosin.setSize(sf::Vector2f(distanciaImpacto, 3.f));
          return;
        }
      }
      for(auto& zombie : zombieManager.getZombies()) {
        if(zombie.getHitbox().contains(punto)) {
          zombie.recibirDanio(jugador.getArma().getDanio());
        }
      }
    }
  }
}

void Juego::guardarStats() {
    std::ofstream archivo("stats.dat", std::ios::binary | std::ios::trunc);
    if (archivo) {
        archivo.write(reinterpret_cast<char*>(&statsHistoricas), sizeof(Estadistica));
        archivo.close();
    }
}

void Juego::cargarStats() {
    std::ifstream archivo("stats.dat", std::ios::binary);
    if (archivo) {
        archivo.read(reinterpret_cast<char*>(&statsHistoricas), sizeof(Estadistica));
        archivo.close();
    } else {
        statsHistoricas.setPartidasJugadas(0);
        statsHistoricas.setOleadaMaxima(0);
        statsHistoricas.setZombiesEliminados(0);
    }
}
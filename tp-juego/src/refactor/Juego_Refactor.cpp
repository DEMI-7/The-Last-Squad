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

  deltaTime = 0.f;
  indiceMenuSeleccionado = 0;

  // Inicialización de elementos del terreno
  inicializarObstaculos(obstaculos);

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

  texturaProyectil.loadFromFile("assets/armas/bala.png");

  trazaMosin.setFillColor(sf::Color::White);
  trazaMosin.setSize(sf::Vector2f(3000.f, 3.f));
  trazaMosin.setOrigin({0.f, 1.5f});

  // Cargar estadísticas históricas
  cargarStats();

  // Cargar fondo del menú personalizado
  tieneFondoMenu = texturaFondoMenu.loadFromFile("assets/menu_bg.png");
  if (tieneFondoMenu) {
    spriteFondoMenu.setTexture(texturaFondoMenu);
    sf::Vector2u size = texturaFondoMenu.getSize();
    spriteFondoMenu.setScale({ventana.getSize().x / size.x, ventana.getSize().y / size.y});
    std::cout << spriteFondoMenu.getScale().x << " " << spriteFondoMenu.getScale().y << std::endl;
    spriteFondoMenu.setOrigin({size.x/2.f, size.y/2.f});
    spriteFondoMenu.setPosition({ventana.getSize().x/2.f, ventana.getSize().y/2.f});

  estadoActual = EstadoJuego::MenuPrincipal;

}

void Juego::inicializarObstaculos(std::vector<ObjetoMapa> &obstaculos) {
  obstaculos.reserve(40);

  obstaculos.emplace_back();
  obstaculos.back().setHitbox(1058.f, 258.f);
  obstaculos.back().setPosicion(640.f, 540.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(1058.f, 258.f);
  obstaculos.back().setPosicion(640.f, 1300.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(1058.f, 258.f);
  obstaculos.back().setPosicion(2170.f, 1300.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(1058.f, 258.f);
  obstaculos.back().setPosicion(2170.f, 540.f);

  obstaculos.emplace_back();
  obstaculos.back().setHitbox(1058.f, 146.f);
  obstaculos.back().setPosicion(2170.f, 2014.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(1058.f, 146.f);
  obstaculos.back().setPosicion(636.f, 2014.f);

  obstaculos.emplace_back();
  obstaculos.back().setHitbox(1058.f, 72.f);
  obstaculos.back().setPosicion(2170.f, 0.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(1058.f, 72.f);
  obstaculos.back().setPosicion(640.f, 0.f);

  obstaculos.emplace_back();
  obstaculos.back().setHitbox(168.f, 72.f);
  obstaculos.back().setPosicion(0.f, 0.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(168.f, 258.f);
  obstaculos.back().setPosicion(0.f, 540.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(168.f, 258.f);
  obstaculos.back().setPosicion(0.f, 1300.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(168.f, 146.f);
  obstaculos.back().setPosicion(0.f, 2014.f);

  obstaculos.emplace_back();
  obstaculos.back().setHitbox(168.f, 72.f);
  obstaculos.back().setPosicion(3672.f, 0.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(168.f, 258.f);
  obstaculos.back().setPosicion(3672.f, 540.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(168.f, 258.f);
  obstaculos.back().setPosicion(3672.f, 1300.f);
  obstaculos.emplace_back();
  obstaculos.back().setHitbox(168.f, 146.f);
  obstaculos.back().setPosicion(3672.f, 2014.f);
}

void Juego::iniciar() {
  std::srand(static_cast<unsigned>(std::time(nullptr)));

  proyectiles.reserve(100);
  
  trampas.emplace_back(sf::Vector2f(1920,1080));
  while (ventana.isOpen()) {
      deltaTime = relojDelta.restart().asSeconds();
      procesarEventos();
      actualizar();
      renderizar();
    }
}

void Juego::procesarEventos()
{
}

void Juego::actualizar() {
  sf::Vector2f posMouse = ventana.mapPixelToCoords(sf::Mouse::getPosition(ventana), ventana.getDefaultView());
  
  // Actualizar siempre la mira para usarla como puntero con la vista correspondiente
  if (estadoActual == EstadoJuego::Jugando) {
      mira.actualizar(ventana, vista, deltaTime);
      ventana.setMouseCursorVisible(false);
  } else {
      mira.actualizar(ventana, ventana.getDefaultView(), deltaTime);
      ventana.setMouseCursorVisible(false);
  }

      std::vector<sf::FloatRect> hitboxesZombies = zombieManager.getHitboxesZombies();

      if (jugador.estaVivo()) {
        jugador.actualizar(deltaTime, obstaculos, hitboxesZombies, mira.getPosicion(), trampas, sf::Vector2f(texturaMapa.getSize().x, texturaMapa.getSize().y));

        // Lógica de compra automática de recarga si no le queda reserva al presionar 'R'
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && !jugador.getArma().getEnRecarga()) {
            Arma& armaActiva = jugador.getArma();
            int idArma = armaActiva.getIdArma();
            // Evitamos armas infinitas: Cuchillo (0), Arco (5), Katana (7)
            if (idArma != 0 && idArma != 5 && idArma != 7) {
                if (armaActiva.getMunicionActual() == 0 && armaActiva.getMunicionEnCargador() < armaActiva.getTamanioCargador()) {
                    if (jugador.getDinero() >= 350) {
                        jugador.sumarDinero(-350);
                        armaActiva.comprarMunicion(armaActiva.getTamanioCargador());
                    }
                }
            }
        }

        jugador.getArma().actualizar(deltaTime, mira.getPosicion(), jugador.getPosicion(), proyectiles, texturaProyectil);
        vista.setSize({1280.f * jugador.getMultiplicadorZoom(), 720.f * jugador.getMultiplicadorZoom()});
        
      } else {
        SoundManager::play("muerte");
        estadoActual = EstadoJuego::GameOver;
        ventana.setMouseCursorVisible(false);
      }
      
      procesarRayCast();

      for (auto &proyectil : proyectiles) {
        proyectil.actualizar(deltaTime, obstaculos);
      }
      proyectiles.erase(std::remove_if(proyectiles.begin(), proyectiles.end(), [](const Proyectil &p) { return p.debeDestruirse(); }), proyectiles.end());

      // -------- trampas (minas) --------
      for (auto &trampa : trampas) {
        trampa.actualizar(deltaTime, zombieManager.getHitboxesZombies());
      }
      trampas.erase(std::remove_if(trampas.begin(), trampas.end(), [](const Mina &m) { return m.debeDestruirse(); }), trampas.end());

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

void Juego::renderizar() {
    ventana.clear();
    ventana.setView(vista);
    ventana.draw(spriteMapa);

    for (auto &trampa : trampas) {
        trampa.dibujar(ventana);
    }

    for (auto &obstaculo : obstaculos) {
        obstaculo.dibujar(ventana);
    }

    for (auto &proyectil : proyectiles) {
        proyectil.dibujar(ventana);
    }

    if (mostrarTrazaMosin) {
        ventana.draw(trazaMosin);
    }

    if (jugador.estaVivo()) {
        jugador.dibujar(ventana);
        jugador.getArma().dibujar(ventana);
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
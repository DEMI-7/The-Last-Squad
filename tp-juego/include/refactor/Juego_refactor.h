#pragma once
#include "ObjetoMapa.h"
#include "Personaje.h"
#include "Puntero.h"
#include "ZombieManager.h"
#include "Hud.h"
#include "Mina.h"
#include "Boton.h"
#include "archivoPersonaje.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <optional>

enum class EstadoJuego { 
    MenuPrincipal,
    Estadisticas,
    SeleccionPersonaje,
    Jugando,
    GameOver
};


class Estadistica {
private:
    int _partidasJugadas;
    int _oleadaMaxima;
    int _zombiesEliminados;

public:
    Estadistica() : _partidasJugadas(0), _oleadaMaxima(0), _zombiesEliminados(0) {}

    int getPartidasJugadas() const { return _partidasJugadas; }
    void setPartidasJugadas(int valor) { _partidasJugadas = valor; }

    int getOleadaMaxima() const { return _oleadaMaxima; }
    void setOleadaMaxima(int valor) { _oleadaMaxima = valor; }

    int getZombiesEliminados() const { return _zombiesEliminados; }
    void setZombiesEliminados(int valor) { _zombiesEliminados = valor; }

    void registrarNuevaPartida() { _partidasJugadas++; }
    
    void registrarOleadaMaxima(int oleada) {
        if (oleada > _oleadaMaxima) {
            _oleadaMaxima = oleada;
        }
    }

    void sumarZombiesEliminados(int cantidad) { _zombiesEliminados += cantidad; }
};

class Juego {
private:
  // VENTANA Y VISTA
  sf::RenderWindow ventana;
  sf::View vista;

  float auxVistaX;
  float auxVistaY;

  // RELOJ PARA CONTROLAR EL TIEMPO ENTRE FRAMES
  sf::Clock relojDelta;
  float deltaTime;

  // INCIALIZACION DE ELEMENTOS DEL JUEGO
  Personaje jugador;

  std::vector<ObjetoMapa> obstaculos; // Vector para almacenar múltiples elementos del mapa/paredes/obstaculos
  std::vector<Proyectil> proyectiles; // Vector para almacenar múltiples proyectiles
  std::vector<Mina> trampas;
  
  ZombieManager zombieManager;
  Hud hud;

  sf::Texture texturaMapa;
  sf::Sprite spriteMapa;
  sf::Texture texturaProyectil;

  Puntero mira;

  // ELEMENTOS DE MENÚ Y MÁQUINA DE ESTADOS
  EstadoJuego estadoActual;
  sf::Font fuenteMenu;
  sf::Text tituloJuego;
  
  // Fondo personalizado
  sf::Texture texturaFondoMenu;
  sf::Sprite spriteFondoMenu;
  bool tieneFondoMenu;
  
  // Botones menú principal
  std::optional<Boton> btnMenuJugar;
  std::optional<Boton> btnMenuStats;
  std::optional<Boton> btnMenuSalir;
  

  
  // Selección personaje
  struct BotonPersonaje {
      Boton boton;
      RegistroPersonaje registro;
      sf::Texture textura;
      sf::Sprite sprite;

      BotonPersonaje(const Boton& botonBase, const sf::Texture& texturaBase, const RegistroPersonaje& registroBase)
                    : textura(texturaBase), sprite(textura), boton(botonBase), registro(registroBase) {

            sf::Vector2u texSize = textura.getSize();
            int frameW = texSize.x;
            int frameH = texSize.y;
            sprite.setTextureRect(sf::IntRect({0, 0}, {frameW, frameH}));
            // Escala adaptativa para que quepa bien en la tarjeta
            float scale = 90.f / frameH;
            if (scale > 3.0f) {
                scale = 3.0f;
            }
            sprite.setScale({scale, scale});
            sprite.setOrigin({frameW / 2.f, frameH / 2.f});
            sprite.setPosition({boton.getCaja().getPosition().x + 70.f, boton.getCaja().getPosition().y + boton.getCaja().getSize().y / 2.f}); // A la izquierda del recuadro
            

      }
  };
  

  std::vector<BotonPersonaje> botonesPersonajes;
  std::optional<Boton> btnVolverSeleccion;
  
  RegistroPersonaje personajeSeleccionado;

  // Estadísticas
  Estadistica statsHistoricas;
  sf::Text textoStats;
  std::optional<Boton> btnVolverStats;
  
  int indiceMenuSeleccionado;

  void procesarEventos();
  void actualizar();
  void renderizar();

  void inicializarObstaculos(std::vector<ObjetoMapa> &obstaculos);
  void procesarRayCast();
  
  sf::RectangleShape trazaMosin;
  bool mostrarTrazaMosin = false;
  float tiempoTrazaMosin = 0.f;

  // Métodos del Menú
  void inicializarMenus();
  void actualizarMenu(sf::Vector2f posMouse);
  void renderizarMenu();
  
  void actualizarEstadisticas(sf::Vector2f posMouse);
  void renderizarEstadisticas();

  void actualizarSeleccionPersonaje(sf::Vector2f posMouse);
  void renderizarSeleccionPersonaje();
  void iniciarPartidaDirecta();
  
  // Guardar y Cargar Estadísticas
  void guardarStats();
  void cargarStats();

public:
  Juego();
  void iniciar();
};
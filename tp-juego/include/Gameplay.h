#pragma once
#include "Pantalla.h"
#include "Personaje.h"
#include "ObjetoMapa.h"
#include "ProyectilPool.h"
#include "Zombie.h"

class Gameplay : public Pantalla {
    public:
        Gameplay(Juego* juego);

        void manejarEventos(const sf::Event&) override;

        void actualizar(float deltaTime) override;

        void dibujar(sf::RenderWindow&) override;

        
        private:
        
        Personaje jugador;
        
        Zombie pruebaEnemigo;
        
        //---- Vectores de elementos del juego ----
        std::vector<ObjetoMapa> vectorObjetosMapa;
        std::vector<sf::FloatRect> vectorObjetosMapaHitbox;
        std::vector<sf::FloatRect> vectorhitboxZombies;
        
        ProyectilPool proyectiles;
        
        // ------ MAPA
        ObjetoMapa elMapa;
        
        
        void inicializarObstaculos(std::vector<ObjetoMapa> &vectorObjetosMapa);
        void resolverColisionesJugadorZombies();
};
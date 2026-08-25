#pragma once
#include "ObjetoGrafico.h"
#include "ProyectilPool.h"


class Arma : public ObjetoGrafico {
    private:
        int idArma;
        std::string nombre;

        float cadencia;
        float danio;
        float alcance;
        float costo;

        int municionMaxima;
        int tamanioCargador;

        float deltaTime;

        bool desbloqueada;

        float tiempoDesdeUltimoDisparo;
        float tiempoRecarga;
        bool enRecarga;
        int municionActual;
        int municionEnCargador;


        void disparar(const sf::Vector2f &posicionMouse, const sf::Vector2f &posicionJugador, ProyectilPool& poolProyectiles);
        void recargar();

    public:
        Arma(int id, std::string nombre, float cadencia, float danio, float alcance, float costo, int municionMaxima, int tamanioCargador);

        void actualizar(float deltaTime,const sf::Vector2f &posicionMouse, const sf::Vector2f &posicionJugador, ProyectilPool& poolProyectiles);

        // Un id de -1 indica un arma no disponible
        bool estaDisponible() const { return desbloqueada;}

        void setDesbloqueo(bool estado) {desbloqueada = estado;}
};
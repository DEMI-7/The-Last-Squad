#pragma once
#include "ObjetoGrafico.h"


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


        void disparar(const sf::Vector2f &posicionMouse, const sf::Vector2f &posicionJugador);

    public:
        Arma(int id, std::string nombre, float cadencia, float danio, float alcance, float costo, int municionMaxima, int tamanioCargador);

        void actualizar(float deltaTime,const sf::Vector2f &posicionMouse, const sf::Vector2f &posicionJugador);

        // Un id de -1 indica un arma no disponible
        bool estaDisponible() const { return desbloqueada;}

        void setDesbloqueo(bool estado) {desbloqueada = estado;}
};
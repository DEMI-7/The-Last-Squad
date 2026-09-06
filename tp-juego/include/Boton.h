#pragma once

#include "ObjetoGrafico.h"

class Boton : public ObjetoGrafico {
    private:
        int id;
        bool hover;
        bool presionado;

        bool mouseEstabaPresionado;

    public:
        int getId() const { return id; }
        void setId(int nuevoId) { id = nuevoId; }

        Boton();

        Boton(int tipo, int id, std::string direccionImagen);

        void actualizar(float deltaTime, const sf::RenderWindow& ventana, int seleccion);

        void actualizar(float deltaTime, const sf::RenderWindow& ventana);

        bool estaPresionado();

        bool estaHover(const sf::RenderWindow& ventana);

        void activarHover();

        bool fueClickeado();


        // ----- Iniciar Configuración del Botón -----


        // ----- Getters y Setters -----
        bool getEstaHover() const { return hover; }
        bool getEstaPresionado() const { return presionado; }

};


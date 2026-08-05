#pragma once

#include "ObjetoGrafico.h"

class Boton : public ObjetoGrafico {
    private:
        int id;
        bool hover;
        bool presionado;

    public:
        int getId() const { return id; }
        void setId(int nuevoId) { id = nuevoId; }

        Boton(float x, float y, float ancho, float alto, std::string rutaTextura);
        Boton();

        void actualizar(float deltaTime, const sf::RenderWindow& ventana);

        bool estaPresionado();

        bool estaHover(const sf::RenderWindow& ventana);


        // ----- Iniciar Configuración del Botón -----


        // ----- Getters y Setters -----
        bool getEstaHover() const { return hover; }
        bool getEstaPresionado() const { return presionado; }

};


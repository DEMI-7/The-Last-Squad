#include "../include/ProyectilPool.h"
#include <iostream>

ProyectilPool::ProyectilPool(){
    if (!texturaProyectil.loadFromFile("assets/varios/bala_pistola.png")) {
        std::cout << "Error al cargar la textura desde: assets/varios/bala_pistola.png" << std::endl;
    }

    proyectilesVector.reserve(100);

    for (int i = 0; i <= 100; i++) {
        proyectilesVector.emplace_back(texturaProyectil);
    }
}

void ProyectilPool::disparar(sf::Vector2f posInicial, sf::Vector2f direccion, float alcance, float velocidad, float danio, int idArma) {
    //int posProyectil = buscarProyectilDisponible();
    //proyectilesVector[posProyectil].usarProyectil(posInicial, direccion, alcance, velocidad, danio, idArma);


    for (auto &proy : proyectilesVector) {
        if (proy.estaDisponible()) {
            proy.usarProyectil(posInicial, direccion, alcance, velocidad, danio, idArma);
            std::cout << "Proyectil usado" << std::endl;
            return;
        }
    }
}

void ProyectilPool::actualizar(float deltaTime) {
    for (int i = 0; i <= 100; i++) {
        proyectilesVector[i].actualizar(deltaTime);
    }
}

void ProyectilPool::dibujar(sf::RenderWindow& ventana) {
    for (int i = 0; i <= 100; i++) {
        proyectilesVector[i].dibujar(ventana);
    }
}

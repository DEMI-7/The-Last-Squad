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
    for (auto &proy : proyectilesVector) {
        if (!proy.estaActivo()) {
            proy.usarProyectil(posInicial, direccion, alcance, velocidad, danio, idArma);
            std::cout << "Proyectil usado" << std::endl;
            return;
        }
    }
}

void ProyectilPool::actualizar(float deltaTime) {
    for(auto& proyectil : proyectilesVector) {
        proyectil.actualizar(deltaTime);
    }
}

void ProyectilPool::dibujar(sf::RenderWindow& ventana) {
    for(auto& proyectil : proyectilesVector) {
        proyectil.dibujar(ventana);
    }
}

std::vector<Proyectil>& ProyectilPool::getVectorProyectiles() {
    
    return proyectilesVector;
}

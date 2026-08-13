#pragma once
#include "Entidad.h"

class Zombie : public Entidad{
    public:
        Zombie();
        void actualizar(float deltaTime, const sf::FloatRect& personajeHitbox,const std::vector<sf::FloatRect>& vectorObjetosMapaHitbox);
    private:  
};
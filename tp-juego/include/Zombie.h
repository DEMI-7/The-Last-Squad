#pragma once
#include "Entidad.h"

class Zombie : public Entidad{
    public:
        //Zombie();
        Zombie(const sf::Texture& texturaPrecargada, sf::Vector2f posInicial);

        void actualizar(float deltaTime, const sf::FloatRect& personajeHitbox,const std::vector<sf::FloatRect>& vectorObjetosMapaHitbox, const std::vector<sf::FloatRect>& vectorHitboxZombies);
    private:  
};
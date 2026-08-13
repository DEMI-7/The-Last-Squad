#include "../include/Zombie.h"
#include <cmath>

Zombie::Zombie() {
    cargarTextura("assets/zombie.png");
    setPosicion(500,500);

    this->vidaMax = 100;
    this->vidaActual = 100;
    this->velocidad = 80;

    ajustarHitboxAlSprite();

}

void Zombie::actualizar(float deltaTime,const sf::FloatRect& personajeHitbox,const std::vector<sf::FloatRect>& vectorObjetosMapaHitbox) {
    // 1. Resolver colisión física rectangular con el jugador para evitar cualquier superposición
    if (getHitbox().findIntersection(personajeHitbox)) {
        sf::FloatRect zombieHitbox = getHitbox();
        float overlapLeft = (zombieHitbox.position.x + zombieHitbox.size.x) - personajeHitbox.position.x;
        float overlapRight = (personajeHitbox.position.x + personajeHitbox.size.x) - zombieHitbox.position.x;
        float overlapTop = (zombieHitbox.position.y + zombieHitbox.size.y) - personajeHitbox.position.y;
        float overlapBottom = (personajeHitbox.position.y + personajeHitbox.size.y) - zombieHitbox.position.y;

        float minOverlapX = (overlapLeft < overlapRight) ? overlapLeft : -overlapRight;
        float minOverlapY = (overlapTop < overlapBottom) ? overlapTop : -overlapBottom;

        // Empujar hacia afuera en el eje de menor penetración para quedar al ras
        // exacto
        if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
            mover(-minOverlapX, 0.f);
        } else {
            mover(0.f, -minOverlapY);
        }
        return; // Detener persecución ya que está en contacto directo
    }

    // Posicion jugador centrada
    sf::Vector2f posJugadorCentrada({personajeHitbox.position.x + personajeHitbox.size.x / 2.f, personajeHitbox.position.y + personajeHitbox.size.y / 2.f});

    // 2 calcular la direccion hacia el jugador
    sf::Vector2f direccionDeseada = posJugadorCentrada - getPosicion();
    float distancia = std::sqrt(direccionDeseada.x * direccionDeseada.x + direccionDeseada.y * direccionDeseada.y);
    if (distancia < 5.f) {
        return;
    }
    direccionDeseada /= distancia; //Normalizar

    // 3 Evasion de obstaculos (steering behavior)
    float distanciaDeteccion = 60.f;
    sf::Vector2f antena = direccionDeseada * distanciaDeteccion;
    sf::Vector2f posicionAntena = getPosicion() + antena;

    sf::Vector2f fuerzaEvasion(0.f, 0.f);
    bool hayObstaculoCerca = false;

    for (const auto& obstaculo : vectorObjetosMapaHitbox) {
        if(obstaculo.contains(posicionAntena)) {
            sf::Vector2f centroObstaculo({obstaculo.position.x * obstaculo.position.x /2.f, obstaculo.position.y * obstaculo.position.y /2.f});

            sf::Vector2f vectorEvasion = getPosicion() - centroObstaculo;

            float distanciaEvasion = std::sqrt(vectorEvasion.x * vectorEvasion.x + vectorEvasion.y + vectorEvasion.y);

            if (distanciaEvasion > 0.f) {
                fuerzaEvasion += (vectorEvasion / distanciaEvasion);
            }
            hayObstaculoCerca = true;
        }
    }

    // 4. Comportamiento de separación perpendicular para rodear al jugador
    // para usar solo la componente perpendicular, forzando a los zombies a rodear
    // al jugador por los lados.


    // 5. Combinar dirección deseada, evasión de obstáculos y separación de zombies

    // 6. Mover y resolver colisiones físicas (Deslizamiento por hitboxes)
    float deltaMov = velocidad * deltaTime;
    sf::Vector2f movimiento = direccionDeseada * deltaMov; // direecion final por deseada
    sf::Vector2f posPrevia = getPosicion();

    // Movimiento horizontal con colisión
    mover(movimiento.x, 0.f);
    for (const auto &obstaculo : vectorObjetosMapaHitbox) {
      if (getHitbox().findIntersection(obstaculo)) {
        setPosicionCentrado(posPrevia.x, getPosicion().y);
        break;
      }
    }
    
    // Movimiento vertical con colisión
    posPrevia = getPosicion();
    mover(0.f, movimiento.y);
    for (const auto &obstaculo : vectorObjetosMapaHitbox) {
      if (getHitbox().findIntersection(obstaculo)) {
        setPosicionCentrado(getPosicion().x, posPrevia.y);
        break;
      }
    }


}
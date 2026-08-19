#include "../include/Zombie.h"
#include <cmath>

Zombie::Zombie() {
    cargarTextura("assets/zombie.png");
    setPosicion(500,500);

    this->vidaMax = 100;
    this->vidaActual = 100;
    this->velocidad = 80;
    setHitboxVisible();

    ajustarHitboxAlSprite();

}

void Zombie::actualizar(float deltaTime,const sf::FloatRect& personajeHitbox, const std::vector<sf::FloatRect>& vectorObjetosMapaHitbox, const std::vector<sf::FloatRect>& vectorHitboxZombies) {
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
            sf::Vector2f centroObstaculo({obstaculo.position.x + obstaculo.size.x /2.f, obstaculo.position.y + obstaculo.size.y /2.f});

            sf::Vector2f vectorEvasion = getPosicion() - centroObstaculo;

            float distanciaEvasion = std::sqrt(vectorEvasion.x * vectorEvasion.x + vectorEvasion.y * vectorEvasion.y);

            if (distanciaEvasion > 0.f) {
                fuerzaEvasion += (vectorEvasion / distanciaEvasion);
            }
            hayObstaculoCerca = true;
        }
    }

    // 4. Comportamiento de separación perpendicular para rodear al jugador
    // para usar solo la componente perpendicular, forzando a los zombies a rodear
    // al jugador por los lados.
    sf::Vector2f fuerzaSeparacion(0.f, 0.f);
    float radioSeparacion = 80.f;
    
    if (distancia < 150) {
        float factor = distancia / 150.f;
        // Bajamos el radio mínimo para que se peguen más al rodear al jugador
        radioSeparacion = 26.f + (80.f - 26.f) * factor; 
    }
    int zombiesCercanos = 0;

    sf::FloatRect miHitbox = getHitbox();

    sf::Vector2f miCentro({miHitbox.position.x + miHitbox.size.x /2.f, miHitbox.position.y + miHitbox.size.y /2.f});

    for (const auto& hitboxZombie : vectorHitboxZombies) {
        
        sf::Vector2f centroOtro({hitboxZombie.position.x + hitboxZombie.size.x / 2.f, hitboxZombie.position.y + hitboxZombie.size.y / 2.f});

        sf::Vector2f diferenciaPosicion = miCentro - centroOtro;

        float distZ = std::sqrt(diferenciaPosicion.x * diferenciaPosicion.x + diferenciaPosicion.y * diferenciaPosicion.y);

        if (distZ > 0.f && distZ < radioSeparacion) {
            sf::Vector2f empujeBase = (diferenciaPosicion / distZ) * (1.f - (distZ / radioSeparacion));

            // Proyectar sobre la direccion hacia el jugador
            float productoPunto = empujeBase.x * direccionDeseada.x + empujeBase.y * direccionDeseada.y;

            if (productoPunto < 0.f) {
                // Si nos empuja hacia atrás (alejándonos del jugador), nos quedamos
                // solo con la fuerza lateral/perpendicular
                sf::Vector2f proyeccion = direccionDeseada * productoPunto;
                sf::Vector2f perpendicular = empujeBase - proyeccion;
                fuerzaSeparacion += perpendicular; 
            } else {
                fuerzaSeparacion += empujeBase;
            }
            zombiesCercanos++;
        }
    }


    // 5. Combinar dirección deseada, evasión de obstáculos y separación de zombies
    sf::Vector2f direccionFinal = direccionDeseada;

    if(hayObstaculoCerca || zombiesCercanos > 0) {
        sf::Vector2f fuerzaCombinada = fuerzaEvasion;

        if (zombiesCercanos > 0) {
            float magnitudSeparacion = std::sqrt(fuerzaSeparacion.x * fuerzaSeparacion.x + fuerzaSeparacion.y * fuerzaSeparacion.y);

            if (magnitudSeparacion > 0.f) {
                fuerzaSeparacion /= magnitudSeparacion;
            }
            if (hayObstaculoCerca) {
                fuerzaCombinada = fuerzaEvasion * 0.5f + fuerzaSeparacion * 0.5f;
            } else {
                fuerzaCombinada = fuerzaSeparacion;
            }
        }
        float magnitudCombinada = std::sqrt(fuerzaCombinada.x * fuerzaCombinada.x + fuerzaCombinada.y * fuerzaCombinada.y);

        if (magnitudCombinada > 0.f) {
            fuerzaCombinada /= magnitudCombinada;
            direccionFinal = direccionDeseada * 0.4f + fuerzaCombinada * 0.6f;

            float magnitudFinal = std::sqrt(direccionFinal.x * direccionFinal.x + direccionFinal.y * direccionFinal.y);

            if (magnitudFinal > 0.f) {
                direccionFinal /= magnitudFinal;
            }
        }
    }


    // 6. Mover y resolver colisiones físicas (Deslizamiento por hitboxes)
    float deltaMov = velocidad * deltaTime;
    sf::Vector2f movimiento = direccionFinal * deltaMov; // direecion final por deseada
    sf::Vector2f posPrevia = getPosicion();

    // Movimiento horizontal con colisión
    mover(movimiento.x, 0.f);
    for (const auto &obstaculo : vectorObjetosMapaHitbox) {
      if (getHitbox().findIntersection(obstaculo)) {
        mover(posPrevia.x - getPosicion().x, 0.f);
        break;
      }
    }
    
    // Movimiento vertical con colisión
    posPrevia = getPosicion();
    mover(0.f, movimiento.y);
    for (const auto &obstaculo : vectorObjetosMapaHitbox) {
      if (getHitbox().findIntersection(obstaculo)) {
        mover(0.f, posPrevia.y - getPosicion().y);
        break;
      }
    }
}
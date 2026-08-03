#include "Zombie.h"
#include <cmath>
#include <iostream>

Zombie::Zombie() : Entidad() {
  tipo = 1;
  ataque = 10;

  // Inicializar campos de Entidad
  vidaMax = 100.0f;
  vidaActual = 100.0f;
  velocidad = 80.0f;

  tiempoDesdeUltimoAtaque = 0.f;
  cooldownAtaque = 1.0f; // 1 segundo de cooldown por defecto
}

Zombie::Zombie(int tipo, int vida, int ataque, float velocidad) : Entidad() {
  this->tipo = tipo;
  this->ataque = ataque;

  // Sincronizar campos de Entidad
  vidaMax = static_cast<float>(vida);
  vidaActual = static_cast<float>(vida);
  this->velocidad = velocidad;
  velocidadInicial = velocidad;

  tiempoDesdeUltimoAtaque = 0.f;
  cooldownAtaque = 1.0f; // 1 segundo

  empujado = false;
  tiempoEmpuje = 0;
  stuneado = false;
  tiempoStun = 0;
  direccion = 1;
}

int Zombie::getTipo() const { return tipo; }

void Zombie::setTipo(int tipo) { this->tipo = tipo; }

int Zombie::getVida() const { return static_cast<int>(vidaActual); }

void Zombie::setVida(int vida) {
  vidaActual = static_cast<float>(vida);
  vidaMax = static_cast<float>(vida);
}

int Zombie::getAtaque() const { return ataque; }

void Zombie::setAtaque(int ataque) { this->ataque = ataque; }

float Zombie::getVelocidad() const { return velocidad; }

void Zombie::setVelocidad(float velocidad) { this->velocidad = velocidad; }

void Zombie::atacar() {
  // Implementación del ataque (por ejemplo, mensaje de depuración)
  std::cout << "Zombie tipo " << tipo << " atacando con " << ataque
            << " de danio." << std::endl;
}

void Zombie::quitarVida(int cantidad) {
  recibirDanio(static_cast<float>(cantidad));
}

bool Zombie::muerto() const { return !estaVivo(); }

void Zombie::actualizar(float deltaTime, const Personaje &jugador,
                        const std::vector<ObjetoMapa> &obstaculos,
                        const std::vector<Zombie> &todosLosZombies) {
  if (muerto())
    return;

  if (jugador.getHitbox().size.x == 0.f && jugador.getHitbox().size.y == 0.f) {
    return; // Si el jugador esta muerto o desaparecio, el zombie no realiza movimientos
  }

  tiempoDesdeUltimoAtaque += deltaTime;

  // 1. Resolver colisión física rectangular con el jugador para evitar
  // cualquier superposición
  if (getHitbox().findIntersection(jugador.getHitbox()) && !jugador.esInvulnerable()) {
    sf::FloatRect zombieHitbox = getHitbox();
    float overlapLeft =
        (zombieHitbox.position.x + zombieHitbox.size.x) - jugador.getHitbox().position.x;
    float overlapRight =
        (jugador.getHitbox().position.x + jugador.getHitbox().size.x) - zombieHitbox.position.x;
    float overlapTop =
        (zombieHitbox.position.y + zombieHitbox.size.y) - jugador.getHitbox().position.y;
    float overlapBottom =
        (jugador.getHitbox().position.y + jugador.getHitbox().size.y) - zombieHitbox.position.y;

    float minOverlapX =
        (overlapLeft < overlapRight) ? overlapLeft : -overlapRight;
    float minOverlapY =
        (overlapTop < overlapBottom) ? overlapTop : -overlapBottom;

    // Empujar hacia afuera en el eje de menor penetración para quedar al ras
    // exacto
    if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
      mover(-minOverlapX, 0.f);
    } else {
      mover(0.f, -minOverlapY);
    }
    return; // Detener persecución ya que está en contacto directo
  }

  // Obtener la posición del centro del jugador
  sf::Vector2f posicionJugador({jugador.getHitbox().position.x + jugador.getHitbox().size.x / 2.f,
                               jugador.getHitbox().position.y + jugador.getHitbox().size.y / 2.f});

  // 2. Calcular dirección hacia el jugador
  sf::Vector2f dirDeseada = posicionJugador - getPosicion();
  float dist =
      std::sqrt(dirDeseada.x * dirDeseada.x + dirDeseada.y * dirDeseada.y);

  if (dist < 5.f)
    return;

  dirDeseada /= dist; // Normalizar

  // 3. Comportamiento de evasión de obstáculos (Steering Behavior)
  float distanciaDeteccion = 60.f;
  sf::Vector2f antena = dirDeseada * distanciaDeteccion;
  sf::Vector2f posicionAntena = getPosicion() + antena;

  sf::Vector2f fuerzaEvasion(0.f, 0.f);
  bool hayObstaculoCerca = false;

  for (const auto &obstaculo : obstaculos) {
    sf::FloatRect box = obstaculo.getHitbox();
    if (box.contains(posicionAntena)) {
      sf::Vector2f centroObstaculo({box.position.x + box.size.x / 2.f,
                                   box.position.y + box.size.y / 2.f});

      sf::Vector2f vectorEvasion = getPosicion() - centroObstaculo;
      float distEvasion = std::sqrt(vectorEvasion.x * vectorEvasion.x +
                                    vectorEvasion.y * vectorEvasion.y);
      if (distEvasion > 0.f) {
        fuerzaEvasion += (vectorEvasion / distEvasion);
      }
      hayObstaculoCerca = true;
    }
  }

  // 4. Comportamiento de separación perpendicular para rodear al jugador
  // para usar solo la componente perpendicular, forzando a los zombies a rodear
  // al jugador por los lados.
  sf::Vector2f fuerzaSeparacion(0.f, 0.f);
  float radioSeparacion = 80.f;
  if (dist < 150.f) {
    float factor = dist / 150.f;
    // Bajamos el radio mínimo para que se peguen más al rodear al jugador
    radioSeparacion = 26.f + (80.f - 26.f) * factor;
  }
  int zombiesCercanos = 0;

  for (const auto &otroZombie : todosLosZombies) {
    if (&otroZombie == this || otroZombie.muerto()) {
      continue;
    }

    sf::Vector2f diff = getPosicion() - otroZombie.getPosicion();
    float distZ = std::sqrt(diff.x * diff.x + diff.y * diff.y);

    if (distZ > 0.f && distZ < radioSeparacion) {
      sf::Vector2f empujeBase =
          (diff / distZ) * (1.f - (distZ / radioSeparacion));

      // Proyectar sobre la dirección hacia el jugador
      float productoPunto =
          empujeBase.x * dirDeseada.x + empujeBase.y * dirDeseada.y;

      if (productoPunto < 0.f) {
        // Si nos empuja hacia atrás (alejándonos del jugador), nos quedamos
        // solo con la fuerza lateral/perpendicular
        sf::Vector2f proyeccion = dirDeseada * productoPunto;
        sf::Vector2f perpendicular = empujeBase - proyeccion;
        fuerzaSeparacion += perpendicular;
      } else {
        fuerzaSeparacion += empujeBase;
      }
      zombiesCercanos++;
    }
  }

  // 5. Combinar dirección deseada, evasión de obstáculos y separación de
  // zombies
  sf::Vector2f direccionFinal = dirDeseada;

  if (hayObstaculoCerca || zombiesCercanos > 0) {
    sf::Vector2f fuerzaCombinada = fuerzaEvasion;

    if (zombiesCercanos > 0) {
      float magnSep = std::sqrt(fuerzaSeparacion.x * fuerzaSeparacion.x +
                                fuerzaSeparacion.y * fuerzaSeparacion.y);
      if (magnSep > 0.f) {
        fuerzaSeparacion /= magnSep;
      }
      if (hayObstaculoCerca) {
        fuerzaCombinada = fuerzaEvasion * 0.5f + fuerzaSeparacion * 0.5f;
      } else {
        fuerzaCombinada = fuerzaSeparacion;
      }
    }

    float magn = std::sqrt(fuerzaCombinada.x * fuerzaCombinada.x +
                           fuerzaCombinada.y * fuerzaCombinada.y);
    if (magn > 0.f) {
      fuerzaCombinada /= magn;
      direccionFinal = dirDeseada * 0.4f + fuerzaCombinada * 0.6f;
      float magnFinal = std::sqrt(direccionFinal.x * direccionFinal.x +
                                  direccionFinal.y * direccionFinal.y);
      if (magnFinal > 0.f) {
        direccionFinal /= magnFinal;
      }
    }
  }

  // 4. Mover y resolver colisiones físicas (Deslizamiento por hitboxes)
  float deltaMov = velocidad * deltaTime;
  sf::Vector2f movimiento = direccionFinal * deltaMov;
  sf::Vector2f posPrevia = getPosicion();
  if(!empujado){
    
    // Movimiento horizontal con colisión
    mover(movimiento.x, 0.f);
    for (const auto &obstaculo : obstaculos) {
      if (getHitbox().findIntersection(obstaculo.getHitbox())) {
        setPosicionCentrado(posPrevia.x, getPosicion().y);
        break;
      }
    }
    
    // Movimiento vertical con colisión
    posPrevia = getPosicion();
    mover(0.f, movimiento.y);
    for (const auto &obstaculo : obstaculos) {
      if (getHitbox().findIntersection(obstaculo.getHitbox())) {
        setPosicionCentrado(getPosicion().x, posPrevia.y);
        break;
      }
    }
  }
  else {
    switch(direccion){
      case 1: {
        mover(-500.f * deltaTime, 0);
        break;
      }
      case 2: {
        mover(0, -500.f * deltaTime);
        break;
      }
      case 3: {
        mover(500.f * deltaTime, 0);
        break;
      }
      case 4: {
        mover(0, 500.f * deltaTime);
        break;
      }
    }

    for (const auto &obstaculo : obstaculos) {
      if (getHitbox().findIntersection(obstaculo.getHitbox())) {
        setPosicionCentrado(posPrevia.x, getPosicion().y);
        break;
      }
    }
    for (const auto &obstaculo : obstaculos) {
      if (getHitbox().findIntersection(obstaculo.getHitbox())) {
        setPosicionCentrado(getPosicion().x, posPrevia.y);
        break;
      }
    }
  }
    
  recibirEstado(deltaTime, jugador);
}

void Zombie::recibirEstado(float deltaTime, const Personaje &jugador){
  if(jugador.habilidadActiva() && jugador.getId() == 1 &&jugador.getZonaHabilidad().findIntersection(getHitbox())){
    empujado = true;
    stuneado = true;
    tiempoEmpuje = 2.5f;
    tiempoStun = 5;
    velocidad = 0;
    direccion = jugador.getDireccion();
  }

  if(tiempoEmpuje > 0){
    tiempoEmpuje -= 10 * deltaTime;
  }
  if(tiempoEmpuje <= 0){
    empujado = false;
  }
  if(empujado == false && tiempoStun > 0){
    tiempoStun -= 10 * deltaTime;
  }
  if(tiempoStun <= 0){
    stuneado = false;
    velocidad = velocidadInicial;
  }
}


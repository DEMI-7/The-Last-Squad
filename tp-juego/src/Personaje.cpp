#include "../include/Personaje.h"

Personaje::Personaje(int id, int idArmaEspecial, std::string nombre, float vida, float armadura, float velocidad, float cooldownHabilidad) {
    // ---------- Variables de personaje
    this->idPersonaje = id;
    this->nombre = nombre;
    this->vidaMax = vida;
    this->vidaActual = vida;
    this->armaduraMax = armadura;
    this->armaduraActual = armadura;
    this->velocidad = velocidad;
    this->velocidadNormal = velocidad;
    this->cooldownHabilidad = cooldownHabilidad;
    
    this->deltaTime = 0;
    habilidad = "-";

    // ---------- Confiuracion de sprite y hitbox
    mostrarHitbox = true;
    cargarTextura("assets/personajes/" + nombre + ".png");
    escalarSprite(0.8f,0.8f);
    setHitbox(13.f * 2.f, 16.f * 2.1f);
    centrarOrigen();

    // ---------- Posicion
    setPosicionCentrado(900.f, 400.f);
    posicionAnterior = sf::Vector2f(900.f, 400.f);

    // ---------- Armas
    archivoArma archivo("armas.dat");

    inventarioArmas.reserve(5);

    for (int i = 0; i < 4; i++) {
        RegistroArma reg = archivo.entregarArma(i);
        inventarioArmas.emplace_back(reg.id, std::string(reg.nombre), reg.cadencia, reg.danio, reg.alcance, reg.costo, reg.municionMaxima, reg.tamanioCargador);
    }
    RegistroArma reg = archivo.entregarArma(idArmaEspecial);
    inventarioArmas.emplace_back(reg.id, std::string(reg.nombre), reg.cadencia, reg.danio, reg.alcance, reg.costo, reg.municionMaxima, reg.tamanioCargador);

    inventarioArmas[0].setDesbloqueo(true);
    inventarioArmas[1].setDesbloqueo(true);
    inventarioArmas[2].setDesbloqueo(true);
    inventarioArmas[3].setDesbloqueo(true);
    inventarioArmas[4].setDesbloqueo(true);
    

    this->armaEquipada = 0;
}

void Personaje::actualizar(float deltaTime, sf::Vector2f posMouse, const std::vector<sf::FloatRect>& vectorObjetosMapaHitbox, ProyectilPool& proyectiles) {
    this->deltaTime = deltaTime;
    movimiento(vectorObjetosMapaHitbox);
    elegirArma();


    inventarioArmas[armaEquipada].actualizar(deltaTime, posMouse, getPosicion(), proyectiles);

}

void Personaje::dibujar(sf::RenderWindow& ventana) {
    ObjetoGrafico::dibujar(ventana); // Dibuja al personaje

    inventarioArmas[armaEquipada].dibujar(ventana);   // Dibuja el arma
}


void Personaje::elegirArma() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
        armaEquipada = 0;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2) && inventarioArmas[1].estaDisponible()) {
        armaEquipada = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3) && inventarioArmas[2].estaDisponible()) {
        armaEquipada = 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4) && inventarioArmas[3].estaDisponible()) {
        armaEquipada = 3;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5) && inventarioArmas[4].estaDisponible()) {
        armaEquipada = 4;
    }
}

// Movimiento y deteccion de colisiones
void Personaje::movimiento(const std::vector<sf::FloatRect>& vectorObjetosMapaHitbox) {
    movimientoX = 0.f;
    movimientoY = 0.f;

    float movimiento = velocidad * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        movimientoX -= movimiento;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        movimientoX += movimiento;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        movimientoY -= movimiento;
    }
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        movimientoY += movimiento;
    }

    // movimiento horizontal jugador, chequeo de colisiones mediante bucle for
    
    posicionAnterior = getPosicion();
    mover(movimientoX, 0.f);
    bool colisionoX = false;
    for(auto& hitbox : vectorObjetosMapaHitbox) {
        if (getHitbox().findIntersection(hitbox)) {
            setPosicionCentrado(posicionAnterior.x, getPosicion().y);
            colisionoX = true;
            break;
        }
    }
    
    // movimiento vertical jugador
    posicionAnterior = getPosicion();
    mover(0.f, movimientoY);
    bool colisionoY = false;
    for(auto& hitbox : vectorObjetosMapaHitbox) {
        if (getHitbox().findIntersection(hitbox)) {
            setPosicionCentrado(getPosicion().x, posicionAnterior.y);
            colisionoY = true;
            break;
        }
    }
}
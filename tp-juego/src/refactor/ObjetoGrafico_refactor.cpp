#include "../include/ObjetoGrafico.h"

ObjetoGrafico::ObjetoGrafico() : sprite(textura)
{
    //------------HITBOX------------
    mostrarHitbox = false;
    hitboxDebug.setFillColor(sf::Color::Transparent);
    hitboxDebug.setOutlineColor(sf::Color::Red);
    hitboxDebug.setOutlineThickness(2.f);
    angulo = 0.f;

}

ObjetoGrafico::ObjetoGrafico(const ObjetoGrafico& otro) : sprite(textura) {
    textura = otro.textura;
    sprite = otro.sprite;
    sprite.setTexture(textura); // Volver a enlazar la textura copiada al sprite copiado
    hitbox = otro.hitbox;
    hitboxDebug = otro.hitboxDebug;
    mostrarHitbox = otro.mostrarHitbox;
    angulo = otro.angulo;
}

ObjetoGrafico& ObjetoGrafico::operator=(const ObjetoGrafico& otro) {
    if (this != &otro) {
        textura = otro.textura;
        sprite = otro.sprite;
        sprite.setTexture(textura); // Volver a enlazar la textura copiada al sprite copiado
        hitbox = otro.hitbox;
        hitboxDebug = otro.hitboxDebug;
        mostrarHitbox = otro.mostrarHitbox;
        angulo = otro.angulo;
    }
    return *this;
}


bool ObjetoGrafico::cargarTextura(const std::string& ruta)
{
    if (!textura.loadFromFile(ruta))
    {
        return false;
    }

    sprite.setTexture(textura);

    return true;
}

void ObjetoGrafico::setPosicionCentrado(float x, float y)
{
    sprite.setPosition({x, y});

    hitbox.position.x = x - hitbox.size.x / 2.f;
    hitbox.position.y = y - hitbox.size.y / 2.f;

    hitboxDebug.setPosition({hitbox.position.x, hitbox.position.y});
}

void ObjetoGrafico::setPosicion(float x, float y)
{
    sprite.setPosition({x, y});

    hitbox.position.x = x;
    hitbox.position.y = y;

    hitboxDebug.setPosition({hitbox.position.x, hitbox.position.y});
}

void ObjetoGrafico::mover(float offsetX, float offsetY)
{
    sprite.move({offsetX, offsetY});

    hitbox.position.x += offsetX;
    hitbox.position.y += offsetY;

    hitboxDebug.move({offsetX, offsetY});
}

void ObjetoGrafico::centrarOrigen()
{
    sf::FloatRect bounds = sprite.getLocalBounds();

    sprite.setOrigin({bounds.size.x / 2.f, bounds.size.y / 2.f});
}

void ObjetoGrafico::setearTamanioSprite(int ancho, int alto) {
    sprite.setTextureRect(sf::IntRect({0, 0}, {ancho, alto}));
    altoSprite = alto;
    anchoSprite = ancho;
}

void ObjetoGrafico::siguienteSprite(){
    frameActual ++;

    if (frameActual >= cantidadFrames){
        frameActual = 0;
    }

    sprite.setTextureRect(sf::IntRect({frameActual*anchoSprite, animacionActual * altoSprite}, {anchoSprite, altoSprite}));
}

void ObjetoGrafico::anteriorSprite(){
    frameActual = (frameActual - 1 + cantidadFrames) % cantidadFrames;

    sprite.setTextureRect(sf::IntRect({frameActual*anchoSprite, animacionActual * altoSprite}, {anchoSprite, altoSprite}));
}

void ObjetoGrafico::escalarSprite(float factorX, float factorY){
    sprite.setScale({factorX, factorY});
}

void ObjetoGrafico::actualizar(float deltaTime)
{

}

void ObjetoGrafico::dibujar(sf::RenderWindow& ventana)
{
    ventana.draw(sprite);

    if (mostrarHitbox)
    {
        ventana.draw(hitboxDebug);
    }
}

sf::Vector2f ObjetoGrafico::getPosicion() const
{
    return sprite.getPosition();
}

float ObjetoGrafico::getAngulo() const{
    return angulo;
}

void ObjetoGrafico::setAngulo(float nuevoAngulo){
    angulo = nuevoAngulo;
    sprite.setRotation(sf::degrees(angulo));
}


void ObjetoGrafico::setHitbox(float ancho, float alto)
{
    hitbox.size.x = ancho;
    hitbox.size.y = alto;

    hitboxDebug.setSize(sf::Vector2f(ancho, alto));
}

sf::FloatRect ObjetoGrafico::getHitbox() const {
    return hitbox;
}
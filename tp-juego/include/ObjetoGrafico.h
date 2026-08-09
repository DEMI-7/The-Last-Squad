#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class ObjetoGrafico {
protected:

    sf::Texture textura;
    sf::Sprite sprite;

    int altoSprite;
    int anchoSprite;
    /*
    int cantidadFrames;
    int frameActual = 0; //columa
    int animacionActual = 0; //fila
    float tiempoAnimacion = 0;
    float velocidadAnimacion = 0;
    */
    
    float angulo;

    //------------HITBOX------------
    sf::FloatRect hitbox;

    sf::RectangleShape hitboxDebug;

    bool mostrarHitbox;
    
    public:
    
    ObjetoGrafico(const std::string& rutaTextura);
    ObjetoGrafico();

    void cargarTextura(const std::string& rutaTextura);
    
    //------------POSICIONAMIENTO------------
    void setPosicionCentrado(float x, float y); //tiene en cuenta el origen centrado del sprite para posicionar
    void setPosicion(float x, float y);
    void mover(float offsetX, float offsetY);
    
    //------------CONFIGURACION DE SPRITE------------
    void centrarOrigen();
    void setearTamanioSprite(int ancho, int alto); //ajusta cuantos pixeles de la textura se muestran en el sprite
    void escalarSprite(float factorX, float factorY); //multiplica el tamaño del sprite por los factores dados

    //------------ACTUALIZACION Y DIBUJO------------
    virtual void actualizar(float deltaTime);
    virtual void dibujar(sf::RenderWindow& ventana);

    /*
    void siguienteSprite();
    void anteriorSprite();
    */

    void seleccionarSprite(int columna, int fila);

    //------------GETTERS------------
    sf::Vector2f getPosicion() const;
    float getAngulo() const;
    void setAngulo(float nuevoAngulo);
    const sf::Sprite& getSprite() const { return sprite; }

    //------------HITBOX------------
    void setHitbox(float ancho, float alto);
    sf::FloatRect getHitbox() const;
    void ajustarHitboxAlSprite();


public:
    void setHitboxVisible() {mostrarHitbox = true;}
};
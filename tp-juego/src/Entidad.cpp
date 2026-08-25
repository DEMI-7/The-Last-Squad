#include "../include/Entidad.h"

Entidad::Entidad()
{
    vidaMax = 100;
    vidaActual = vidaMax;
}

Entidad::Entidad(const sf::Texture& texturaPrecargada) : ObjetoGrafico(texturaPrecargada) {
    vidaMax = 100;
    vidaActual = vidaMax;
}

void Entidad::recibirDanio(float cantidad)
{
    vidaActual -= cantidad;

    if (vidaActual < 0)
    {
        vidaActual = 0;
    }
}

bool Entidad::estaVivo() const
{
    return vidaActual > 0;
}
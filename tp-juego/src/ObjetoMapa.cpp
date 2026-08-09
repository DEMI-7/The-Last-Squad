#include "../include/ObjetoMapa.h"

ObjetoMapa::ObjetoMapa()
{
    solido = true;
    mostrarHitbox = true;
}

void ObjetoMapa::setSolido(bool estado)
{
    solido = estado;
}

bool ObjetoMapa::esSolido() const
{
    return solido;
}
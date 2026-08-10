#include "../include/ProyectilPool.h"

ProyectilPool::ProyectilPool(){
    texturaProyectil.loadFromFile("assets/varios/bala_pistola.png");
    proyectilesVector.reserve(100);
}
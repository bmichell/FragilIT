#include "fragile.h"

Fragile::Fragile() : m_nbPerson(0), m_speed(0)
{
}

void Fragile::setNbPerson(int nb)
{
   this->m_nbPerson = nb;
}

void Fragile::setSpeed(float speed)
{
    this->m_speed =speed;
}

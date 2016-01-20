#ifndef FRAGILE_H
#define FRAGILE_H

class Fragile
{
public:
    Fragile();
    void setNbPerson(int Nb);
    void setSpeed(float speed);

private:
    unsigned int m_nbPerson;
    float m_speed;
};

#endif // FRAGILE_H

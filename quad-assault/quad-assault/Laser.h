#ifndef LASER_H
#define LASER_H
#include "Oruzje.h"

class Laser : public Oruzje
{
private:
public:
	void Init(GlavnoStanje* stanje);
	void Update(float deltaT);
	void Render();
	void Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik);
};

#endif
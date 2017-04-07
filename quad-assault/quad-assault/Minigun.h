#ifndef MINIGUN_H
#define MINIGUN_H
#include "Oruzje.h"

class Minigun : public Oruzje
{
private:
public:
	void Init(GlavnoStanje* stanje);
	void Update(float deltaT);
	void Render();
	void Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik);
};

#endif
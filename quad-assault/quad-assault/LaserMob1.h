#ifndef LM1_H
#define LM1_H

#include "Mob.h"

class LaserMob1 : public Mob
{
private:
public:
	void Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa);
	void Update(float deltaT);
	void Render(unsigned char stil);
	void PrimiStetu(Projektil* p);
	void Unisti();
	void Pucanje(Projektil* p, float deltaT);
};

#endif
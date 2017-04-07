#ifndef PM1_H
#define PM1_H

#include "Mob.h"

class PlazmaMob1 : public Mob
{
private:
public:
	void Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa);
	void Update(float deltaT);
	void Render(unsigned char stil);
	void PrimiStetu(Projektil* p);
	void Unisti();
};

#endif
#ifndef OP_H
#define OP_H
#include "Stvar.h"
#include "Svjetlo.h"

#define LASER1 0
#define PLAZMA1 1
#define MINIGUN1 2

class OruzjePickup : public Stvar
{
protected:
	float rotacija;
	Svjetlo* s;
	int id;
public:
	void Init(Vec2 poz, GlavnoStanje* stanje, int id);
	void Update(float deltaT);
	void Render(unsigned char stil);
	void Unisti();
	void Pokupi(Igrac* igrac);
};

#endif
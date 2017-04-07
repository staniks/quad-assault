#ifndef KP_H
#define KP_H
#include "Stvar.h"
#include "Svjetlo.h"

#define CRVENI 0
#define PLAVI 1
#define ZELENI 2

class KljucPickup : public Stvar
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
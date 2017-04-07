#ifndef SP_H
#define SP_H
#include "Stvar.h"
#include "SmeceCestica.h"
#include "Svjetlo.h"

class SmecePickup : public Stvar
{
protected:	
	Vec2 smjer;
	float brzina;

	float cesticaTimer; //dok dosegne 0, spawna cesticu

	Svjetlo* s;

public:
	void Init(Vec2 poz, GlavnoStanje* stanje);
	void Update(float deltaT);
	bool ProvjeraSudara();
	void Render(unsigned char stil);
	void Unisti();
	void Pokupi(Igrac* igrac);
};

#endif
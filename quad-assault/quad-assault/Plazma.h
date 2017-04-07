#ifndef PLAZMA_H
#define PLAZMA_H
#include "Oruzje.h"

class Plazma : public Oruzje
{
private:
public:
	void Init(GlavnoStanje* stanje);
	void Update(float deltaT);
	void Render();
	void Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik);
};

#endif
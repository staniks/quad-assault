#ifndef ORUZJE_H
#define ORUZJE_H
#include "Objekt.h"

class GlavnoStanje;
class Projektil;

class Oruzje : public Objekt
{
protected:
	GLuint tex, texN, texG;
	GlavnoStanje* stanje;

	Vec2 absPoz, smjer;
	unsigned char** mapa;
	bool vlasnik;
	
	float punjenje, trenutnoPunjenje;
	float brzinaPunjenja;
	float potrebnaEnergija;
	
public:
	virtual void Init(GlavnoStanje* stanje);
	virtual void Update(float deltaT);	
	virtual void Render();
	virtual void RenderNormal();
	virtual void RenderGlow();
	virtual void Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik);
	virtual void IspaliProjektil(Projektil* p);

	float DajPotrebnuEnergiju();
};

#endif
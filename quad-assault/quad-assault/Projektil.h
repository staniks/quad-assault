#ifndef PROJEKTIL_H
#define PROJEKTIL_H
#include "Objekt.h"
#include "Svjetlo.h"

#define IGRAC 0
#define NEPRIJATELJ 1

class GlavnoStanje;

class Projektil : public Objekt
{
protected:
	Vec2 smjer;
	float brzina;

	float domet, domet_timer;

	GlavnoStanje* stanje;
	Svjetlo* svjetlo;

	unsigned char** mapa;

	float steta;

public:
	Projektil();
	~Projektil();
	virtual void Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** mapa, bool vlasnik);
	virtual void Update(float deltaT);
	virtual void Render(unsigned char stil);
	virtual void Unisti();

	float DajStetu();

	bool unisten;
	bool vlasnik;
};

#endif
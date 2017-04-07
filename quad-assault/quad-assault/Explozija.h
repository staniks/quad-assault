#ifndef EXPLOZIJA_H
#define EXPLOZIJA_H
#include "Objekt.h"
#include "Svjetlo.h"

class GlavnoStanje;

class Explozija : public Objekt
{
protected:
	
	float radius;
	Svjetlo* svjetlo;

	bool umire; //ako umire, intenzitet se smanjuje, ako ne, onda se povecava

	float brzinaRasta; //brzina kojom se povezava intenzitet
	float brzinaUmiranja; //brzina kojom se smanjuje intenzitet
	float intenzitet, maxIntenzitet;

	Vec3 boja; //boja svjetla

	GlavnoStanje* stanje;

public:
	Explozija();
	~Explozija();
	void Init(Vec2 poz, float radius, GlavnoStanje* stanje);
	void Postavke(float intenzitet, float brzinaRasta, float brzinaUmiranja);
	void PostaviBoju(Vec3 boja);
	void Update(float deltaT);
	void Render();	

	bool unisten;
};

#endif
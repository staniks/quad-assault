#ifndef TRIGGER_H
#define TRIGGER_H
#include "Objekt.h"
#include "Mob.h"
#include "Poruka.h"

#define AKTIVIRAN 0
#define DEAKTIVIRAN 1

#define MOB 0
#define PORUKA 1
#define KRAJ 2

class GlavnoStanje;

class Trigger : public Objekt
{
private:
	GlavnoStanje* stanje;
	Mob* mob;
	Vec2 meta;

	Poruka* poruka;	
	
public:
	void InitMob(Vec2 v1, Vec2 v2, Vec2 meta, Mob* mob, GlavnoStanje* stanje);
	void InitPoruka(Vec2 v1, Vec2 v2, Poruka* poruka, GlavnoStanje* stanje);
	void InitKraj(Vec2 v1, Vec2 v2, GlavnoStanje* stanje);
	void Update(float deltaT);
	void Render();

	bool status; //aktiviran ili deaktiviran

	unsigned char tip; //tip triggera (mob, vrata, cinematic)
};

#endif
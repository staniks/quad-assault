#ifndef OBJEKT_H
#define OBJEKT_H
#include "Vec2.h"
#include "Ovisnosti.h"

#define DIFFUSE 0
#define NORMAL 1
#define GLOW 2

class Objekt
{
protected:
	Vec2 poz,dim;	
public:
	Objekt();
	~Objekt();
	Vec2 DajPoz(); //daje poziciju objekta
	Vec2 DajDim();
	Vec2 DajSredinu();
	virtual void PromijeniPoz(Vec2 poz); //mijenja poziciju objekta
	virtual void PromijeniDim(Vec2 dim);
};

#endif


#ifndef STVAR_H
#define STVAR_H
#include "Objekt.h"

class GlavnoStanje;
class Igrac;

class Stvar : public Objekt
{
protected:
	GlavnoStanje* stanje;
	GLuint tex, texN, texG;
public:
	virtual void Init(Vec2 poz, GlavnoStanje* stanje);
	virtual void Update(float deltaT);
	virtual void Render(unsigned char stil);
	virtual void Unisti();
	virtual void Pokupi(Igrac* igrac);

	bool unisten;
};

#endif
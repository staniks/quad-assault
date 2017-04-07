#ifndef CESTICA_H
#define CESTICA_H
#include "Objekt.h"

class GlavnoStanje;

class Cestica : public Objekt
{
protected:
	GLuint tex, texN;	
	GlavnoStanje* stanje;

	float zivot; //smanjuje se postepeno	
	float maxZivot; //za rendering
public:
	virtual void Init(Vec2 poz, GlavnoStanje* stanje);
	virtual void Update(float deltaT);
	virtual void Render(unsigned char stil);

	bool unisten; //ako je true, uklanja se iz igre
};

#endif
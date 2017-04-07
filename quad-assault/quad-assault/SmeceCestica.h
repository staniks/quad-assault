#ifndef SMECECESTICA_H
#define SMECECESTICA_H
#include "Cestica.h"

class SmeceCestica : public Cestica
{
public:
	virtual void Init(Vec2 poz, GlavnoStanje* stanje);
	virtual void Update(float deltaT);
	virtual void Render(unsigned char stil);
};

#endif
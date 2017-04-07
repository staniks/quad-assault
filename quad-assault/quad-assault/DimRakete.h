#ifndef DIMRAKETE_H
#define DIMRAKETE_H
#include "Cestica.h"

class DimRakete : public Cestica
{
public:
	virtual void Init(Vec2 poz, GlavnoStanje* stanje);
	virtual void Update(float deltaT);
	virtual void Render(unsigned char stil);
};

#endif
#include "Objekt.h"

Vec2 Objekt::DajPoz()
{
	return poz;
}
void Objekt::PromijeniPoz(Vec2 poz)
{
	this->poz=poz;
}
Vec2 Objekt::DajDim()
{
	return dim;
}
Vec2 Objekt::DajSredinu()
{
	return poz+Vec2(dim.x/2,dim.y/2);
}
void Objekt::PromijeniDim(Vec2 dim)
{
	this->dim=dim;
}
Objekt::Objekt()
{
}
Objekt::~Objekt()
{		
}
#include "Stvar.h"
#include "GlavnoStanje.h"
#include "Igrac.h"

void Stvar::Init(Vec2 poz, GlavnoStanje* stanje)
{
	this->poz=poz;
	this->stanje=stanje;

	dim.x=32;
	dim.y=32;	
}
void Stvar::Update(float deltaT)
{
	Kutija k1;
	k1.v1=poz;
	k1.v2=poz+dim;
	Kutija k2; 
	k2.v1=stanje->DajIgraca()->DajPoz();
	k2.v2=stanje->DajIgraca()->DajPoz()+stanje->DajIgraca()->DajDim();
	if(k1.Sudar(&k2))
	{
		Pokupi(stanje->DajIgraca());
	}
}
void Stvar::Render(unsigned char stil)
{
}
void Stvar::Unisti()
{
}
void Stvar::Pokupi(Igrac* igrac)
{
}
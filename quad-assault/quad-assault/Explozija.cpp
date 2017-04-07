#include "Explozija.h"
#include "GlavnoStanje.h"

Explozija::Explozija()
{
}
Explozija::~Explozija()
{
	svjetlo->Unisti();
}
void Explozija::Init(Vec2 poz, float radius, GlavnoStanje* stanje)
{
	this->poz=poz;
	this->radius=radius;
	this->stanje=stanje;
	umire=false;
	unisten=false;

	intenzitet=0;
	maxIntenzitet=4;
	brzinaRasta=35;
	brzinaUmiranja=10;

	boja=Vec3(1.0, 0.75, 0.5);

	svjetlo=stanje->DodajSvjetlo(false);
	svjetlo->Init(poz,radius,stanje);
	svjetlo->Postavke(boja, 0);			
}
void Explozija::Postavke(float intenzitet, float brzinaRasta, float brzinaUmiranja)
{
	maxIntenzitet=intenzitet;
	this->brzinaRasta=brzinaRasta;
	this->brzinaUmiranja=brzinaUmiranja;
}
void Explozija::PostaviBoju(Vec3 boja)
{
	this->boja=boja;
}
void Explozija::Update(float deltaT)
{
	if(umire==false)
	{
		if(intenzitet<maxIntenzitet)
			intenzitet+=brzinaRasta*deltaT;
		else
		{
			umire=true;
			intenzitet=maxIntenzitet;
		}
	}	
	if(umire==true)
	{
		if(intenzitet>0)
			intenzitet-=brzinaUmiranja*deltaT;
		else
		{			
			unisten=true;
			intenzitet=0;
		}
	}	
		
	svjetlo->Postavke(boja, intenzitet);	
}

void Explozija::Render()
{
}
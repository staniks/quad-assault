#include "GUI_Funkcije.h"

GlavnoStanje* extStanje;

///POSTAVLJANJE SVJETLA - GUMB FUNKCIJA
void PosSvjetGUI()
{
	extStanje->PostaviSvjetlo();
}
void PosTrigGUI()
{
	extStanje->PostaviMobTrigger();
}
void GlavnoStanje::PostaviSvjetlo()
{
	if(postavljaSvjetlo==false)
	{
		postavljaSvjetlo=true;
		postavljenoSvjetlo=DodajSvjetlo(true);
		postavljenoSvjetlo->Init(mis, 128, this);
		postavljenoSvjetlo->Postavke(Vec3(1.0, 1.0, 1.0), 8);
	}
}
void GlavnoStanje::PostaviMobTrigger()
{
	if(postavljaMobTrigger==0)
	{		
		postavljaMobTrigger=1;		
		triggeri.push_back(new Trigger());	
	}
}

///GENERIRANJE PRAzNOG LEVELA FUNKCIJA
void GenPrazniLevelGUI()
{
	extStanje->GenerirajPrazanLevel();
}

void SpremiLevelGUI()
{
	extStanje->SpremiBlokove();
}
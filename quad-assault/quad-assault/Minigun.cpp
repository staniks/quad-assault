#include "Minigun.h"
#include "GlavnoStanje.h"
#include "MinigunProjektil.h"

void Minigun::Init(GlavnoStanje* stanje)
{
	Oruzje::Init(stanje);
	tex=stanje->DajMT()->DajTexturu("oruzje1.tga")->id;
	texN=stanje->DajMT()->DajTexturu("oruzje1Normal.tga")->id;
	texG=stanje->DajMT()->DajTexturu("oruzje3Glow.tga")->id;
	brzinaPunjenja=1500;
	potrebnaEnergija=0.5;
}
void Minigun::Update(float deltaT)
{
	Oruzje::Update(deltaT);
}
void Minigun::Render()
{
	Oruzje::Render();
}
void Minigun::Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik)
{
	Oruzje::Pucaj(poz,smjer,mapa,vlasnik);
	if(trenutnoPunjenje==punjenje)
	{
		for(int i=0; i<1; i++)
		{
			absPoz.x-=smjer.x*4;
			absPoz.y-=smjer.y*4;		
			IspaliProjektil(new MinigunProjektil());				
		}
		trenutnoPunjenje=0;
	}
}
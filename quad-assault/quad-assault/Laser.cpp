#include "Laser.h"
#include "GlavnoStanje.h"
#include "LaserProjektil.h"

void Laser::Init(GlavnoStanje* stanje)
{
	Oruzje::Init(stanje);
	tex=stanje->DajMT()->DajTexturu("oruzje1.tga")->id;
	texN=stanje->DajMT()->DajTexturu("oruzje1Normal.tga")->id;
	texG=stanje->DajMT()->DajTexturu("oruzje1Glow.tga")->id;
	brzinaPunjenja=600;
	potrebnaEnergija=2;
}
void Laser::Update(float deltaT)
{
	Oruzje::Update(deltaT);
}
void Laser::Render()
{
	Oruzje::Render();
}
void Laser::Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik)
{
	Oruzje::Pucaj(poz,smjer,mapa,vlasnik);
	if(trenutnoPunjenje==punjenje)
	{
		for(int i=0; i<1; i++)
		{
			absPoz.x-=smjer.x*4;
			absPoz.y-=smjer.y*4;		
			IspaliProjektil(new LaserProjektil());				
		}
		trenutnoPunjenje=0;
	}
}
#include "Plazma.h"
#include "GlavnoStanje.h"
#include "PlazmaProjektil.h"

void Plazma::Init(GlavnoStanje* stanje)
{
	Oruzje::Init(stanje);
	tex=stanje->DajMT()->DajTexturu("oruzje1.tga")->id;
	texN=stanje->DajMT()->DajTexturu("oruzje1Normal.tga")->id;
	texG=stanje->DajMT()->DajTexturu("oruzje2Glow.tga")->id;
	brzinaPunjenja=100;
	potrebnaEnergija=6;
}
void Plazma::Update(float deltaT)
{
	Oruzje::Update(deltaT);
}
void Plazma::Render()
{
	Oruzje::Render();
}
void Plazma::Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik)
{
	Oruzje::Pucaj(poz,smjer,mapa,vlasnik);
	if(trenutnoPunjenje==punjenje)
	{
		IspaliProjektil(new PlazmaProjektil());
		trenutnoPunjenje=0;
	}
}
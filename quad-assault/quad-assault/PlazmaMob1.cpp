#include "PlazmaMob1.h"
#include "GlavnoStanje.h"
#include "PlazmaProjektil.h"

void PlazmaMob1::Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa)
{
	Mob::Init(poz,stanje,mapa);

	dim.x=64;
	dim.y=64;
	
	brzina=75;
	maxbrzina=75;
	brzinaPunjenja=50;	
	domet=512;

	hp=60;
	textura=stanje->DajMT()->DajTexturu("mob1Diffuse.tga")->id;
	texturaN=stanje->DajMT()->DajTexturu("mob1Normal.tga")->id;
	texturaG=stanje->DajMT()->DajTexturu("mob2Glow.tga")->id;	
}
void PlazmaMob1::Update(float deltaT)
{
	Mob::Update(deltaT);
	Mob::Pucanje(new PlazmaProjektil(),deltaT);	
	Vec2 smjer;
	smjer=stanje->DajIgraca()->DajSredinu()-poz-Vec2(dim.x/2, dim.y/2);
	if(smjer.Duljina()<300)
	{
		brzina-=100*deltaT;
		if(brzina<0)
			brzina=0;
	}
	else
	{
		brzina+=100*deltaT;
		if(brzina>maxbrzina)
			brzina=maxbrzina;
	}
}
void PlazmaMob1::Render(unsigned char stil)
{
	Mob::Render(stil);
}
void PlazmaMob1::Unisti()
{
	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(), stanje->DajMZ()->DajZvuk("Zvukovi/explozija1.wav"));		
	z->Play();	
	Mob::Unisti();
}
void PlazmaMob1::PrimiStetu(Projektil* projektil)
{
	Mob::PrimiStetu(projektil);
}
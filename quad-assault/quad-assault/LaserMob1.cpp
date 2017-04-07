#include "LaserMob1.h"
#include "GlavnoStanje.h"
#include "LaserProjektil.h"

void LaserMob1::Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa)
{
	Mob::Init(poz,stanje,mapa);

	dim.x=64;
	dim.y=64;
	
	maxbrzina=150;	
	brzinaPunjenja=250;	
	domet=512;

	hp=40;
	textura=stanje->DajMT()->DajTexturu("mob1Diffuse.tga")->id;
	texturaN=stanje->DajMT()->DajTexturu("mob1Normal.tga")->id;
	texturaG=stanje->DajMT()->DajTexturu("mob1Glow.tga")->id;		
}
void LaserMob1::Update(float deltaT)
{
	Mob::Update(deltaT);
	Pucanje(new LaserProjektil(),deltaT);	
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
void LaserMob1::Render(unsigned char stil)
{
	Mob::Render(stil);
}
void LaserMob1::Pucanje(Projektil* p, float deltaT)
{	
	Mob::Pucanje(p,deltaT);	
}
void LaserMob1::Unisti()
{
	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(), stanje->DajMZ()->DajZvuk("Zvukovi/explozija1.wav"));		
	z->Play();	
	Mob::Unisti();
}
void LaserMob1::PrimiStetu(Projektil* projektil)
{
	Mob::PrimiStetu(projektil);
}
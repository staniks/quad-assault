#include "LaserProjektil.h"
#include "GlavnoStanje.h"

void LaserProjektil::Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** mapa, bool vlasnik)
{
	Projektil::Init(poz,smjer,stanje,mapa,vlasnik);
	brzina=910;
	domet=600;
	steta=4;

	svjetlo->Init(poz,128,stanje);
	svjetlo->Postavke(Vec3(0.5, 1.0, 0.2),4);

	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(), stanje->DajMZ()->DajZvuk("Zvukovi/laser1.wav"));		
	z->Play();

	texG=stanje->DajMT()->DajTexturu("laser1Glow.tga")->id;
}
void LaserProjektil::Update(float deltaT)
{
	Projektil::Update(deltaT);
}
void LaserProjektil::Render(unsigned char stil)
{
	Projektil::Render(stil);
	if(stil==GLOW)
	{
		float rot=atan2(smjer.y,smjer.x)*180/3.14 + 90;	
		SpriteT(poz-Vec2(8,16),Vec2(16,32),rot,texG);
	}
}
void LaserProjektil::Unisti()
{
	unisten=true;
	svjetlo->Unisti();
	Explozija* e=stanje->DodajExploziju();
	e->Init(poz,128,stanje);
	e->Postavke(8,100,80);
	e->PostaviBoju(Vec3(1.0, 0.75, 0.5));	
}
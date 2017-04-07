#include "MinigunProjektil.h"
#include "GlavnoStanje.h"

void MinigunProjektil::Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** mapa, bool vlasnik)
{
	Projektil::Init(poz,smjer,stanje,mapa,vlasnik);
	brzina=1000;
	domet=500;
	steta=0.5;

	svjetlo->Init(poz,128,stanje);
	svjetlo->Postavke(Vec3(1.0, 1.0, 0.1),4);

	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(), stanje->DajMZ()->DajZvuk("Zvukovi/minigun1.wav"));		
	z->Play();

	texG=stanje->DajMT()->DajTexturu("minigun1Glow.tga")->id;
}
void MinigunProjektil::Update(float deltaT)
{
	Projektil::Update(deltaT);
}
void MinigunProjektil::Render(unsigned char stil)
{
	Projektil::Render(stil);
	if(stil==GLOW)
	{
		float rot=atan2(smjer.y,smjer.x)*180/3.14 + 90;	
		SpriteT(poz-Vec2(8,16),Vec2(16,32),rot,texG);
	}
}
void MinigunProjektil::Unisti()
{
	unisten=true;
	svjetlo->Unisti();
	Explozija* e=stanje->DodajExploziju();
	e->Init(poz,64,stanje);
	e->Postavke(4,100,80);
	e->PostaviBoju(Vec3(1.0, 0.75, 0.5));	
}
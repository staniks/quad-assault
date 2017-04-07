#include "PlazmaProjektil.h"
#include "GlavnoStanje.h"
#include "DimRakete.h"

void PlazmaProjektil::Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** mapa, bool vlasnik)
{
	Projektil::Init(poz,smjer,stanje,mapa,vlasnik);
	brzina=800;
	domet=800;
	steta=12;

	dim=Vec2(1,1);

	dimTimer=0.0;

	svjetlo->Init(poz,256,stanje);
	svjetlo->Postavke(Vec3(0.25, 0.5, 1.0),8);	

	tex=stanje->DajMT()->DajTexturu("granata1.tga")->id;

	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(),
		stanje->DajMZ()->DajZvuk("Zvukovi/plazma1.wav"));	
	z->Play();
}
void PlazmaProjektil::Update(float deltaT)
{
	Projektil::Update(deltaT);
	dimTimer+=deltaT*750;
	if(dimTimer>=10.0)
	{
		Cestica* c=stanje->DodajCesticu(new DimRakete());
		c->Init(poz+Vec2(dim.x/2,dim.y/2),stanje);
		dimTimer=0.0;
	}
}
void PlazmaProjektil::Render(unsigned char stil)
{
	Projektil::Render(stil);
	if(stil==DIFFUSE)
		SpriteT(poz,dim,0,tex);
}
void PlazmaProjektil::Unisti()
{		
	unisten=true;
	svjetlo->Unisti();
	Explozija* e=stanje->DodajExploziju();	
	e->Init(poz,256,stanje);
	e->Postavke(20,1000,50);
	e->PostaviBoju(Vec3(1.0, 0.75, 0.5));

	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(),
		stanje->DajMZ()->DajZvuk("Zvukovi/explozija1.wav"));		
	z->Play();	
}
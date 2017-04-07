#include "OruzjePickup.h"
#include "GlavnoStanje.h"
#include "Igrac.h"
#include "Laser.h"
#include "Plazma.h"
#include "Minigun.h"

void OruzjePickup::Init(Vec2 poz, GlavnoStanje* stanje, int id)
{
	Stvar::Init(poz,stanje);

	dim.x=32;
	dim.y=32;
	this->id=id;
	
	rotacija=0;
	if(id==LASER1)
	{
		tex=stanje->DajMT()->DajTexturu("oruzje1.tga")->id;
		texN=stanje->DajMT()->DajTexturu("oruzje1Normal.tga")->id;
		texG=stanje->DajMT()->DajTexturu("oruzje1Glow.tga")->id;
	}
	if(id==PLAZMA1)
	{
		tex=stanje->DajMT()->DajTexturu("oruzje1.tga")->id;
		texN=stanje->DajMT()->DajTexturu("oruzje1Normal.tga")->id;
		texG=stanje->DajMT()->DajTexturu("oruzje2Glow.tga")->id;
	}
	if(id==MINIGUN1)
	{
		tex=stanje->DajMT()->DajTexturu("oruzje1.tga")->id;
		texN=stanje->DajMT()->DajTexturu("oruzje1Normal.tga")->id;
		texG=stanje->DajMT()->DajTexturu("oruzje3Glow.tga")->id;
	}

	s=stanje->DodajSvjetlo(false);
	s->Init(poz+Vec2(dim.x/2,dim.y/2),256,stanje);
	if(id==LASER1)
		s->Postavke(Vec3(0.2,1.0,0.2),6);
	if(id==PLAZMA1)
		s->Postavke(Vec3(0.2,0.2,1.0),6);
}
void OruzjePickup::Update(float deltaT)
{
	Stvar::Update(deltaT);
	rotacija+=100*deltaT;
	if(rotacija>360)
		rotacija=0;
}
void OruzjePickup::Render(unsigned char stil)
{
	GLuint t;
	if(stil==DIFFUSE)
		t=tex;
	if(stil==NORMAL)
		t=texN;
	if(stil==GLOW)
		t=texG;
	SpriteT(poz+Vec2(dim.x/2-8,0),Vec2(16,32),rotacija,t);
}
void OruzjePickup::Unisti()
{
	s->Unisti();
}
void OruzjePickup::Pokupi(Igrac* igrac)
{
	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(), stanje->DajMZ()->DajZvuk("Zvukovi/pickup.wav"));		
	z->Play();
	if(id==LASER1)
		igrac->DodajOruzje(new Laser());
	if(id==PLAZMA1)
		igrac->DodajOruzje(new Plazma());
	if(id==MINIGUN1)
		igrac->DodajOruzje(new Minigun());
	unisten=true;
}
#include "KljucPickup.h"
#include "GlavnoStanje.h"
#include "Igrac.h"

void KljucPickup::Init(Vec2 poz, GlavnoStanje* stanje, int id)
{
	Stvar::Init(poz,stanje);

	dim.x=32;
	dim.y=32;
	this->id=id;
	
	rotacija=0;
	tex=stanje->DajMT()->DajTexturu("KljucDiffuse.tga")->id;
	texN=stanje->DajMT()->DajTexturu("KljucNormal.tga")->id;	
	texG=stanje->DajMT()->DajTexturu("KljucGlow.tga")->id;

	s=stanje->DodajSvjetlo(false);
	s->Init(poz+Vec2(dim.x/2,dim.y/2),128,stanje);
	if(id==CRVENI)
		s->Postavke(Vec3(1.0,0.1,0.1),4);	
	if(id==PLAVI)
		s->Postavke(Vec3(0.1,0.25,1.0),4);	
	if(id==ZELENI)
		s->Postavke(Vec3(0.1,1.0,0.1),4);	
}
void KljucPickup::Update(float deltaT)
{
	Stvar::Update(deltaT);
	rotacija+=100*deltaT;
	if(rotacija>360)
		rotacija=0;
}
void KljucPickup::Render(unsigned char stil)
{
	GLuint t;
	if(stil==DIFFUSE)
		t=tex;
	if(stil==NORMAL)
		t=texN;
	if(stil==GLOW)
	{
		t=texG;
		if(id==CRVENI)
			glColor3f(1.0, 0.1, 0.1);
		if(id==PLAVI)
			glColor3f(0.1, 0.1, 1.0);
		if(id==ZELENI)
			glColor3f(0.1, 1.0, 0.1);
	}
	SpriteT(DajPoz(),DajDim(),rotacija,t);
	glColor3f(1.0, 1.0, 1.0);
}
void KljucPickup::Unisti()
{
	s->Unisti();
}
void KljucPickup::Pokupi(Igrac* igrac)
{
	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(),
		stanje->DajMZ()->DajZvuk("Zvukovi/pickup.wav"));		
	z->Play();
	int vrata;
	if(id==CRVENI)	
		vrata=CRVENAVRATA;
	if(id==PLAVI)	
		vrata=PLAVAVRATA;
	if(id==ZELENI)
		vrata=ZELENAVRATA;

	for(int x=0; x<MX; x++)
	for(int y=0; y<MY; y++)
	{
		if(stanje->DajMapu()[x][y]==vrata)
		{
			stanje->DajMapu()[x][y]=POD;
			stanje->DajBlok(x,y)->Init(Vec2(x*BLOKDIM, y*BLOKDIM), POD, stanje);
			Explozija* e=stanje->DodajExploziju();
			e->Init(Vec2(x*BLOKDIM+BLOKDIM/2, y*BLOKDIM+BLOKDIM/2), 128, stanje);
			e->Postavke(20,1000,50);
			if(id==CRVENI)
				e->PostaviBoju(Vec3(1.0, 0.1, 0.1));
			if(id==PLAVI)
				e->PostaviBoju(Vec3(0.1, 0.1, 1.0));
			if(id==ZELENI)
				e->PostaviBoju(Vec3(0.1, 1.0, 0.1));
		}
	}
	
	
	unisten=true;
}
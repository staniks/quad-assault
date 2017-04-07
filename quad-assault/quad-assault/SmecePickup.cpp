#include "SmecePickup.h"
#include "GlavnoStanje.h"

void SmecePickup::Init(Vec2 poz, GlavnoStanje* stanje)
{
	Stvar::Init(poz,stanje);

	dim.x=16;
	dim.y=16;	

	smjer.x=stanje->DajIgru()->Rand(1,10)-5;
	smjer.x/=5;
	smjer.y=stanje->DajIgru()->Rand(1,10)-5;
	smjer.y/=5;
	smjer.Normaliziraj();

	brzina=200;

	cesticaTimer=1.0;

	s=stanje->DodajSvjetlo(false);
	s->Init(poz,64,stanje);
	s->Postavke(Vec3(1.0, 0.75, 0.5),4);	
	
	tex=stanje->DajMT()->DajTexturu("SmeceDiffuse.tga")->id;
	texN=stanje->DajMT()->DajTexturu("SmeceNormal.tga")->id;		
}
void SmecePickup::Update(float deltaT)
{
	Stvar::Update(deltaT);		
	
	if(brzina>0.0)
	{
		s->PromijeniPoz(DajSredinu());
		if(cesticaTimer>=1.0)
		{
			SmeceCestica* c=(SmeceCestica*)stanje->DodajCesticu(new SmeceCestica());
			c->Init(DajPoz(),stanje);		
			cesticaTimer=0.0;
		}
		else
			cesticaTimer+=deltaT*10;

		poz.y+=smjer.y*brzina*deltaT;
		if(ProvjeraSudara()==true)
		{
			poz.y-=smjer.y*brzina*deltaT;
			smjer.y=-smjer.y;
		}
		poz.x+=smjer.x*brzina*deltaT;
		if(ProvjeraSudara()==true)
		{
			poz.x-=smjer.x*brzina*deltaT;
			smjer.x=-smjer.x;
		}
		brzina-=100*deltaT;
	}
	else
	{
		brzina=0.0;
	}

	
}
bool SmecePickup::ProvjeraSudara()
{
	Kutija k1;
	k1.v1=poz;
	k1.v2=poz+dim;
	unsigned char** mapa=stanje->DajMapu();
	for(int x=(poz.x/BLOKDIM)-2; x<(poz.x/BLOKDIM)+2; x++)
	for(int y=(poz.y/BLOKDIM)-2; y<(poz.y/BLOKDIM)+2; y++)
	{
		if(x>=0 && x<MX && y>=0 && y<MY)
		if(mapa[x][y]!=POD)
		{
			Kutija k2;
			k2.v1=Vec2(x*BLOKDIM,y*BLOKDIM);
			k2.v2=Vec2(x*BLOKDIM,y*BLOKDIM)+Vec2(BLOKDIM,BLOKDIM);
			if(k1.Sudar(&k2))
				return true;
		}
	}
}
void SmecePickup::Render(unsigned char stil)
{
	if(stil!=GLOW)
	{
		GLuint t;
		if(stil==DIFFUSE)
			t=tex;
		if(stil==NORMAL)
			t=texN;
	
		SpriteT(poz,Vec2(dim.x,dim.y),0,t);
		glColor3f(1.0, 1.0, 1.0);
	}
	
}
void SmecePickup::Unisti()
{
	
}
void SmecePickup::Pokupi(Igrac* igrac)
{
	sf::Sound* z = stanje->DodajZvuk(new sf::Sound(),
		stanje->DajMZ()->DajZvuk("Zvukovi/pickup.wav"));		
	z->Play();
	unisten=true;

	s->Unisti();
	Explozija* e=stanje->DodajExploziju();
	e->Init(DajSredinu(),128,stanje);
	e->Postavke(12,100,50);
	e->PostaviBoju(Vec3(1.0, 0.75, 0.5));	

	igrac->DodajHP(2);
}
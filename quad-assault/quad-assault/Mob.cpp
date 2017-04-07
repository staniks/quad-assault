#include "Mob.h"
#include "GlavnoStanje.h"
#include "Projektil.h"
#include "LaserProjektil.h"
#include "SmecePickup.h"

void Mob::Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa)
{
	this->poz=poz;
	this->stanje=stanje;
	this->mapa=mapa;

	dim.x=64;
	dim.y=64;

	rotacija=0;
	akceleracija=0;
	brzina=100;
	maxbrzina=100;	

	brzinaPunjenja=250;
	punjenje=0;
	domet=512;

	hp=100;	
}
void Mob::Update(float deltaT)
{
	akceleracija=1;

	Vec2 smjer;
	smjer=stanje->DajIgraca()->DajSredinu()-poz-Vec2(dim.x/2, dim.y/2);
	smjer.Normaliziraj();

	rotacija=atan2(smjer.y,smjer.x)*180/3.14 + 90;

	Vec2 moment;
	moment.x=cos((rotacija-90)/180.0*3.14)*akceleracija;
	moment.y=sin((rotacija-90)/180.0*3.14)*akceleracija;	

	poz.y+=moment.y*brzina*deltaT;
	if(ProvjeraSudara())
		poz.y-=moment.y*brzina*deltaT;
	poz.x+=moment.x*brzina*deltaT;
	if(ProvjeraSudara())
		poz.x-=moment.x*brzina*deltaT;

	SudarProjektila();	

	if(hp<=0)
		unisten=true;

	akceleracija=0;
}
void Mob::Render(unsigned char stil)
{	
	GLuint tex;
	
	if(stil==DIFFUSE)
		tex=textura;
	if(stil==NORMAL)
		tex=texturaN;
	if(stil==GLOW)
		tex=texturaG;

	if(stil==DIFFUSE) //SJENA
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPushMatrix();		
		glColor4f(0.0, 0.0, 0.0, 0.6);			
		SpriteT(poz+Vec2(5,5),dim,rotacija,tex);			
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glPopMatrix();
		glDisable(GL_BLEND);
	}

	glPushMatrix();	
	SpriteT(poz,dim,rotacija,tex);	
	glPopMatrix();	
}
void Mob::Unisti()
{
	Explozija* e=stanje->DodajExploziju();
	e->Init(DajSredinu(),512,stanje);
	e->Postavke(128,3000,200);
	for(int i=0; i<4; i++)
	{
		SmecePickup* c=(SmecePickup*)stanje->DodajStvar(new SmecePickup());
		c->Init(DajSredinu(),stanje);
	}
}
void Mob::SpawnEfekt()
{
	Explozija* e=stanje->DodajExploziju();
	e->Init(DajSredinu(),512,stanje);
	e->Postavke(32,1000,100);
	e->PostaviBoju(Vec3(0.25,0.5,1.0));
}

void Mob::DodajMoment(float x)
{
	akceleracija=x;
}
void Mob::Rotiraj(float rot)
{
	rotacija+=rot;
	if(rotacija>360.0)
		rotacija=0.1;
	if(rotacija<0.0)
		rotacija=359.9;
}

bool Mob::ProvjeraSudara()
{
	Kutija k1;
	k1.v1=poz+Vec2(4,4);
	k1.v2=poz+dim-Vec2(4,4);
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
	for(int i=0; i<stanje->DajMobove()->size(); i++)
	{
		if(stanje->DajMobove()->at(i)!=this)
		{
			Kutija k2;
			k2.v1=stanje->DajMobove()->at(i)->DajPoz();
			k2.v2=stanje->DajMobove()->at(i)->DajPoz()+
				stanje->DajMobove()->at(i)->DajDim();
			if(k1.Sudar(&k2))
				return true;
		}
	}
	Kutija k2;
	k2.v1=stanje->DajIgraca()->DajPoz();
	k2.v2=stanje->DajIgraca()->DajPoz()+
		stanje->DajIgraca()->DajDim();
	if(k1.Sudar(&k2))
		return true;

	return false;
}
void Mob::SudarProjektila()
{
	Kutija k1;
	k1.v1=poz+Vec2(4,4);
	k1.v2=poz+dim-Vec2(4,4);
	for(int i=0; i<stanje->DajProjektile()->size(); i++)
	{
		if(stanje->DajProjektile()->at(i)->vlasnik==IGRAC)
		{
			Kutija k2;
			k2.v1=stanje->DajProjektile()->at(i)->DajPoz();
			k2.v2=stanje->DajProjektile()->at(i)->DajPoz()+
				stanje->DajProjektile()->at(i)->DajDim();
			if(k1.Sudar(&k2))
			{
				PrimiStetu(stanje->DajProjektile()->at(i));				
			}
		}
	}
}

void Mob::PrimiStetu(Projektil* projektil)
{
	hp-=projektil->DajStetu();
	projektil->unisten=true;
}
void Mob::Pucanje(Projektil* p, float deltaT)
{
	if(stanje->DajIgraca()->JeUnisten()==false)
	{
		if(punjenje<100)
			punjenje+=brzinaPunjenja*deltaT;
		if(punjenje>=100)
		{
			Vec2 smjerPucanja=stanje->DajIgraca()->DajSredinu()-poz-Vec2(dim.x/2, dim.y/2);
			float l=smjerPucanja.Duljina();
			if(l<domet)
			{
				smjerPucanja.Normaliziraj();
				Projektil* pr=stanje->DodajProjektil(p);
				pr->Init(DajSredinu(),smjerPucanja,stanje,mapa,NEPRIJATELJ);
				punjenje=0;
			}		
		}
	}
}
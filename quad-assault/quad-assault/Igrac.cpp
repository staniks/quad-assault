#include "Igrac.h"
#include "Likovi.h"
#include "GlavnoStanje.h"
#include "Laser.h"
#include "Plazma.h"
#include "Minigun.h"
#include "Svjetlo.h"

void Igrac::Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa)
{
	this->poz=poz;
	this->stanje=stanje;
	this->mapa=mapa;
	dim.x=64;
	dim.y=64;

	textura=stanje->DajMT()->DajTexturu("tenkTorzoDiffuse.tga")->id;	
	texturaN=stanje->DajMT()->DajTexturu("tenkTorzoNormal.tga")->id;

	podloga_tex=stanje->DajMT()->DajTexturu("tenkPodlogaDiffuse.tga")->id;
	podloga_normal=stanje->DajMT()->DajTexturu("tenkPodlogaNormal.tga")->id;

	tracnica_tex=stanje->DajMT()->DajTexturu("tracnicaDiffuse.tga")->id;	
	tracnica_normal=stanje->DajMT()->DajTexturu("tracnicaNormal.tga")->id;

	farovi=stanje->DodajSvjetlo(false);
	farovi->Init(Vec2(0.0, 0.0), 1024, stanje);
	farovi->Postavke(Vec3(1.0, 1.0, 1.0), 16);

	for(int i=0; i<4; i++)
		oruzja[i]=NULL;

	/*DodajOruzje(new Laser());		
	DodajOruzje(new Laser());		
	DodajOruzje(new Minigun());		
	DodajOruzje(new Plazma());		*/

	hp=100;
	energija=100.0;
	puca=false;
	unisten=false;

	pomak_tracnica=0.0;
	rotacija=0.0;

	brzina=200;
}

void Igrac::Pucaj(Vec2 misPoz, float deltaT)
{
	if(unisten==false)
	{
		Vec2 smjer;
		smjer=misPoz-poz-Vec2(dim.x/2, dim.y/2);
		smjer.Normaliziraj();

		for(int i=0; i<4; i++)
		{		
			if(oruzjeSlot[i]==true && oruzja[i]!=NULL)
			{
				if(energija>=oruzja[i]->DajPotrebnuEnergiju())
				{
					Vec2 oPoz=oruzja[i]->DajPoz();
		
					float kut=atan2(oPoz.y,oPoz.x)*180/3.14 + 90;

					Vec2 slot;
					slot.x=cos((rotacijaTorza+kut)/180.0*3.14);
					slot.y=sin((rotacijaTorza+kut)/180.0*3.14);
					slot.Mnozi(sqrt(oPoz.x*oPoz.x + oPoz.y*oPoz.y)); //oruzje x offset

					oruzja[i]->Pucaj(DajSredinu()+slot,smjer,mapa,IGRAC);									
				}
				puca=true;
			}
		}
	}
}
bool Igrac::ProvjeraSudara()
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
		Kutija k2;
		k2.v1=stanje->DajMobove()->at(i)->DajPoz();
		k2.v2=stanje->DajMobove()->at(i)->DajPoz()+
			stanje->DajMobove()->at(i)->DajDim();
		if(k1.Sudar(&k2))
			return true;		
	}

	return false;
}
void Igrac::SudarProjektila()
{
	Kutija k1;
	k1.v1=poz+Vec2(4,4);
	k1.v2=poz+dim-Vec2(4,4);
	for(int i=0; i<stanje->DajProjektile()->size(); i++)
	{
		if(stanje->DajProjektile()->at(i)->vlasnik==NEPRIJATELJ)
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
void Igrac::PrimiStetu(Projektil* p)
{
	if(unisten==false)
	{
		hp-=p->DajStetu();
		p->unisten=true;
	}
}
void Igrac::DodajOruzje(Oruzje* o)
{
	for(int i=0; i<4; i++)
	{
		if(oruzjeSlot[i]!=true)
		{
			oruzja[i]=o;
			oruzjeSlot[i]=true;
			o->Init(stanje);
			if(i==2)
				o->PromijeniPoz(Vec2(-24,0));
			if(i==0)
				o->PromijeniPoz(Vec2(-8,-12));
			if(i==1)
				o->PromijeniPoz(Vec2(8,-12));
			if(i==3)
				o->PromijeniPoz(Vec2(24,0));
			break;
		}
	}
}
bool Igrac::JeUnisten()
{
	return unisten;
}
void Igrac::OduzmiEnergiju(float e)
{
	energija-=e;
	if(energija<0.0)
		energija=0.0;
}
void Igrac::DodajHP(float kolicina)
{
	hp+=kolicina;
	if(hp>100.0)
		hp=100.0;
}
Igrac::Igrac()
{
}
Igrac::~Igrac()
{
	for(int i=0; i<4; i++)
		if(oruzjeSlot[i]==true && oruzja[i]!=NULL)
		{
			delete oruzja[i];	
			oruzja[i]=NULL;
		}
}
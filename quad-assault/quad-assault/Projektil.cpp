#include "Projektil.h"
#include "GlavnoStanje.h"
#include "Explozija.h"

void Projektil::Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** mapa, bool vlasnik)
{
	this->poz=poz;
	this->smjer=smjer;
	this->stanje=stanje;
	this->mapa=mapa;
	this->vlasnik=vlasnik;	

	svjetlo=stanje->DodajSvjetlo(false);	

	domet_timer=0;

	unisten=false;

	//NASLJEDJEN DIO:

	brzina=1000;
	domet=600;
	steta=50;

	dim.x=1;
	dim.y=1;

	svjetlo->Init(poz,64,stanje);
	svjetlo->Postavke(Vec3(1.0, 0.5, 0.25), 2);	
}
void Projektil::Update(float deltaT)
{
	for(int x=(poz.x/BLOKDIM)-2; x<(poz.x/BLOKDIM)+2; x++)
	for(int y=(poz.y/BLOKDIM)-2; y<(poz.y/BLOKDIM)+2; y++)
	{
		if(unisten==true)
		{
			break;break;
		}
		if(x>=0 && x<MX && y>=0 && y<MY)
		if(mapa[x][y]!=POD && mapa[x][y]!=PRAZNINA)
		{
			Kutija k1;
			k1.v1=poz;
			k1.v2=poz+dim;

			Kutija k2;
			k2.v1=Vec2(x*BLOKDIM,y*BLOKDIM);
			k2.v2=Vec2(x*BLOKDIM,y*BLOKDIM)+Vec2(BLOKDIM,BLOKDIM);
			if(k1.Sudar(&k2))
				unisten=true;
		}
	}
	if(unisten==false)
	{		
		poz.y+=smjer.y*brzina*deltaT;
		poz.x+=smjer.x*brzina*deltaT;
		svjetlo->PromijeniPoz(poz);		
		domet_timer+=1000*deltaT;
		if(domet_timer>domet)
			unisten=true;
	}
	
}
void Projektil::Render(unsigned char stil)
{
}
void Projektil::Unisti()
{
	unisten=true;
	svjetlo->Unisti();
	Explozija* e=stanje->DodajExploziju();
	e->Init(poz,128,stanje);
	e->Postavke(4,100,20);
	e->PostaviBoju(Vec3(0.25, 0.5, 1.0));	
}
Projektil::Projektil()
{
}
Projektil::~Projektil()
{	
}
float Projektil::DajStetu()
{
	return steta;
}
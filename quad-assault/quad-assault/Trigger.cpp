#include "Trigger.h"
#include "GlavnoStanje.h"
#include "ZajednickeVarijable.h"

void Trigger::InitMob(Vec2 v1, Vec2 v2, Vec2 meta, Mob* mob, GlavnoStanje* stanje)
{
	this->poz=v1;
	this->dim=v2-v1;
	this->meta=meta;
	this->mob=mob;
	this->stanje=stanje;
	status=AKTIVIRAN;
	tip=MOB;
}
void Trigger::InitPoruka(Vec2 v1, Vec2 v2, Poruka* poruka, GlavnoStanje* stanje)
{
	this->poz=v1;
	this->dim=v2-v1;
	this->stanje=stanje;
	status=AKTIVIRAN;
	tip=PORUKA;
	this->poruka=poruka;	
}
void Trigger::InitKraj(Vec2 v1, Vec2 v2, GlavnoStanje* stanje)
{
	this->poz=v1;
	this->dim=v2-v1;
	this->stanje=stanje;
	status=AKTIVIRAN;
	tip=KRAJ;
}
void Trigger::Update(float deltaT)
{
	if(status==AKTIVIRAN)
	{
		Kutija k1;
		k1.v1=poz;
		k1.v2=poz+dim;
		Kutija k2;
		k2.v1=stanje->DajIgraca()->DajPoz();
		k2.v2=stanje->DajIgraca()->DajPoz()+
			stanje->DajIgraca()->DajDim();
		if(k1.Sudar(&k2))
		{
			if(tip==MOB)
			{
				stanje->DodajMoba(mob);
				mob->Init(meta,stanje,stanje->DajMapu());
				mob->SpawnEfekt();
			}
			if(tip==PORUKA)
			{
				stanje->DodajPoruku(poruka);						
			}
			if(tip==KRAJ)
			{
				stanje->ZavrsiNivo();
				//SPREMANJE INFORMACIJA O OTKLJUCAVANJU				
				if(nivo_trenutni<BROJ_NIVOA-1)
					nivo_omogucen[nivo_trenutni+1]=true;
				
				ofstream of("nivoLock.gdf");	
				for(int i=0; i<BROJ_NIVOA; i++)
				{
					of << nivo_omogucen[i] << " ";	
				}
				of.close();
				//
			}
			status=DEAKTIVIRAN;
		}		
	}
}
void Trigger::Render()
{
	glColor3f(1,1,1);
	glBegin(GL_LINE_LOOP);
	glVertex2f(poz.x, poz.y);
	glVertex2f(poz.x+dim.x, poz.y);
	glVertex2f(poz.x+dim.x, poz.y+dim.y);
	glVertex2f(poz.x, poz.y+dim.y);
	glEnd();
}
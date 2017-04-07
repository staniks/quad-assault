#include "Igrac.h"
#include "Likovi.h"
#include "GlavnoStanje.h"
#include "Laser.h"
#include "Plazma.h"
#include "Svjetlo.h"

void Igrac::Update(float deltaT, Vec2 mis)
{
	if(unisten==false)
	{
		Vec2 moment;
		moment.x=cos((rotacija-90)/180.0*3.14)*akceleracija;
		moment.y=sin((rotacija-90)/180.0*3.14)*akceleracija;	

		poz.y+=moment.y*brzina*deltaT;
		if(ProvjeraSudara())
			poz.y-=moment.y*brzina*deltaT;
		poz.x+=moment.x*brzina*deltaT;
		if(ProvjeraSudara())
			poz.x-=moment.x*brzina*deltaT;
	
		if(moment.x!=0 || moment.y!=0)
		{
			if(akceleracija>0)
				pomak_tracnica+=deltaT;
			else
				pomak_tracnica-=deltaT;
			if(pomak_tracnica>1.0)
				pomak_tracnica=0.0;
			if(pomak_tracnica<0.0)
				pomak_tracnica=1.0;
		}
		akceleracija=0;

		SudarProjektila();

		rotacijaTorza=atan2((mis.y-poz.y-dim.y/2),(mis.x-poz.x-dim.x/2))*180/3.14;

		for(int i=0; i<4; i++)
		{
			if(unisten==false)
				if(oruzjeSlot[i]==true && oruzja[i]!=NULL)
					oruzja[i]->Update(deltaT);
		}

		UpdateFarove();

		if(puca==false)
		{
			if(energija<100.0)
				energija+=10*deltaT;
			if(energija>100.0)
				energija=100.0;		
		}
		else
			puca=false;

		if(hp<=0.0)
		{
			hp=0.0;
			unisten=true;
			
			Explozija* e=stanje->DodajExploziju();
			e->Init(DajSredinu(),512,stanje);
			e->Postavke(256,3000,200);

			sf::Sound* z = stanje->DodajZvuk(new sf::Sound(),
				stanje->DajMZ()->DajZvuk("Zvukovi/explozija1.wav"));		
			z->Play();

			gameOverPoruka=new Poruka();
			gameOverPoruka->Init("Baza", "Svim jedinicama, izgubili smo kod Q.", 4, "Zvukovi/blip.wav", stanje);
			stanje->DodajPoruku(gameOverPoruka);	

			farovi->Postavke(Vec3(0,0,0), 0);
		}
	}
}
void Igrac::UpdateFarove()
{
	Vec2 smjer;
	smjer.x=cos((rotacijaTorza+180)/180.0*3.14);
	smjer.y=sin((rotacijaTorza+180)/180.0*3.14);	
	smjer.Normaliziraj();	
	farovi->PostavkeKuta(smjer,2);

	Vec2 slot;
	slot.x=cos((rotacijaTorza)/180.0*3.14);
	slot.y=sin((rotacijaTorza)/180.0*3.14);
	slot.Mnozi(34);
	farovi->PromijeniPoz(DajSredinu()+slot);
}
void Igrac::DodajMoment(float x)
{
	akceleracija=x;
}
void Igrac::Rotiraj(float rot)
{
	rotacija+=rot;
	if(rotacija>360.0)
		rotacija=0.1;
	if(rotacija<0.0)
		rotacija=359.9;	
}
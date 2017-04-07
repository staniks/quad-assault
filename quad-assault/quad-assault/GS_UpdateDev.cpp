#include "GlavnoStanje.h"
#include "Igra.h"
#include "ZajednickeVarijable.h"

void GlavnoStanje::UpdateDev(float deltaT)
{	
	while(igra->DajRW()->PollEvent(event))
	{
		if(event.Type==sf::Event::Closed)
			gotovo=true;
		if(event.Type==sf::Event::MouseMoved)	
		{
			mis.x=event.MouseMove.X;
			mis.y=event.MouseMove.Y;
		}

		if(event.Type==sf::Event::MouseButtonPressed)
		{
			if(event.MouseButton.Button==sf::Mouse::Button::Left)
			{
				uim->LijeviKlik(mis);
				if(postavljaSvjetlo==true)
				{
					postavljaSvjetlo=false;
				}
				if(postavljaMobTrigger==3)
				{
					t3=mis+kamera->DajPoz();
					Mob* m=SpawnajMobPremaImenu("lasermob1");	
					triggeri.back()->InitMob(t1,t2,t3,m,this);
					postavljaMobTrigger=0;
				}
				if(postavljaMobTrigger==2)
				{
					t2=mis+kamera->DajPoz();
					postavljaMobTrigger=3;
				}
				if(postavljaMobTrigger==1)
				{
					t1=mis+kamera->DajPoz();
					postavljaMobTrigger=2;
				}

			}			
			if(event.MouseButton.Button==sf::Mouse::Button::Right)
			{					
				mapa[(int)(kamera->DajPoz().x+mis.x)/BLOKDIM][(int)(kamera->DajPoz().y+mis.y)/BLOKDIM]=PostavljanjeBloka;
				InitBlokove();
			}
		}
		if(event.Type==sf::Event::MouseButtonReleased)
		{
			if(event.MouseButton.Button==sf::Mouse::Button::Left)
			{
				uim->LijeviOtpust(mis);
			}
		}
		if(event.Type==sf::Event::KeyPressed)
		{		
			if(event.Key.Code==sf::Keyboard::Key::F1)
				DEVMODE=false;
			if(event.Key.Code==sf::Keyboard::Key::F4)
			{
				if(ambijentnoSvjetlo.x==0.1f)
					ambijentnoSvjetlo=Vec3(0.8f, 0.8f, 0.8f);
				else
					ambijentnoSvjetlo=Vec3(0.1f, 0.1f, 0.1f);

			}
			if(event.Key.Code==sf::Keyboard::Key::F6)
			{
				SpremiBlokove();				
				cout << "MAPA SPREMLJENA." << endl;
			}
			if(event.Key.Code==sf::Keyboard::Key::G)
			{				
				cout << "X: " << kamera->DajPoz().x+mis.x << endl;
				cout << "Y: " << kamera->DajPoz().y+mis.y << endl;
			}
			if(event.Key.Code==sf::Keyboard::Key::Num1)			
				PostavljanjeBloka=POD;			
			if(event.Key.Code==sf::Keyboard::Key::Num2)			
				PostavljanjeBloka=ZID;			
			if(event.Key.Code==sf::Keyboard::Key::Num3)			
				PostavljanjeBloka=PRAZNINA;			
			if(event.Key.Code==sf::Keyboard::Key::Num4)			
				PostavljanjeBloka=CRVENAVRATA;
			if(event.Key.Code==sf::Keyboard::Key::Num5)			
				PostavljanjeBloka=ZELENAVRATA;
			if(event.Key.Code==sf::Keyboard::Key::Num6)			
				PostavljanjeBloka=PLAVAVRATA;
			
		}
	}	
	if(postavljaSvjetlo==true)
	{
		postavljenoSvjetlo->radius=srad;
		postavljenoSvjetlo->Postavke(Vec3(sr,sg,sb),si);
		postavljenoSvjetlo->PromijeniPoz(mis+kamera->DajPoz());
	}

	uim->Update(deltaT, mis);
}
void GlavnoStanje::SpremiBlokove()
{
	ofstream of(nivo_datoteka_g);
	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{
		of << "blok " << i*BLOKDIM << " " << j*BLOKDIM << " " << (int)mapa[i][j] << "\n";		
	}
	for(int i=0; i<svjetla.size(); i++)
	{
		if(svjetla[i]->staticno==true)
		{
		of << "svjetlo " << svjetla[i]->DajPoz().x << " " << svjetla[i]->DajPoz().y 
			<< " " << svjetla[i]->radius << " " << svjetla[i]->intenzitet << " " << svjetla[i]->boja.x << " " << svjetla[i]->boja.y << 
			" " << svjetla[i]->boja.z << "\n";
		}
	}
	of.close ();
}


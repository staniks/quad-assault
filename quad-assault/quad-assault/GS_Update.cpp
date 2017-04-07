#include "GlavnoStanje.h"
#include "Igra.h"

void GlavnoStanje::Update(float deltaT)
{	
	if(DEVMODE==FALSE)
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
				
			}
			if(event.Type==sf::Event::MouseButtonReleased)
			{
				
			}
			if(event.Type==sf::Event::KeyPressed)
			{		
				if(event.Key.Code==sf::Keyboard::Key::F1)
				{
					DEVMODE=true;
				}				
			}
		}	
		if(igrac->JeUnisten() || nivoZavrsen)
			gameOverTimer-=deltaT;
		if(gameOverTimer<=0.0)
			tranzicija=T_FADEOUT;

		if(tranzicija==T_FADEIN)
		{
			tBoja+=brzinaFadeanja*deltaT;
			if(tBoja>1.0f)
			{
				tranzicija=T_NEMA;
				tBoja=1.0f;
			}
		}
		if(tranzicija==T_FADEOUT)
		{
			tBoja-=brzinaFadeanja*deltaT;
			if(tBoja<0.0f)
			{
				tBoja=0.0f;
			}
		}		
	
		igrac->Update(deltaT, mis+kamera->DajPoz());

		UpdateajNizove(deltaT);

		kamera->PromijeniPoz(igrac->DajSredinu()-Vec2(igra->DajRW()->GetWidth()/2, igra->DajRW()->GetHeight()/2));
		
	}

	if(DEVMODE==true)
		UpdateDev(deltaT);
}
Blok* GlavnoStanje::DajBlok(short x, short y)
{
	return &blokovi[x][y];
}



#include "MenuStanje.h"
#include "Igra.h"

void MenuStanje::Update(float deltaT)
{
	while(igra->DajRW()->PollEvent(event))
	{
		if(event.Type==sf::Event::Closed)
			gotovo=true;
		if(event.Type==sf::Event::KeyPressed)
		{
			if(event.Key.Code==sf::Keyboard::Key::Escape)
			{
				if(stanje==GLAVNI_MENU)
					gotovo=true;
				else
					stanje=GLAVNI_MENU;
			}
		}
		if(event.Type==sf::Event::MouseButtonReleased)
		{
			if(event.MouseButton.Button==sf::Mouse::Button::Left)
				misOtpusten=true;
		}
		if(event.Type==sf::Event::MouseMoved)	
		{
			mis.x=event.MouseMove.X;
			mis.y=event.MouseMove.Y;
		}		
	}	
	
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
	
	if(tranzicija==T_NEMA)
	{
		if(stanje==GLAVNI_MENU)
		{
			startGumb.Update(deltaT);
			oigriGumb.Update(deltaT);
			izlazGumb.Update(deltaT);	
		}
		if(stanje==NIVO_ODABIR)
		{
			natragGumb.Update(deltaT);
			for(int i=0; i<nivoi.size(); i++)
				nivoi[i].gumb.Update(deltaT);
		}
		if(stanje==O_IGRI)		
			natragGumb.Update(deltaT);
	}	
}

Vec2 MenuStanje::DajMis()
{
	return mis;
}
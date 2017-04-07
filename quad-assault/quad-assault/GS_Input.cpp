#include "GlavnoStanje.h"
#include "Igra.h"
#include "MenuStanje.h"

void GlavnoStanje::Input()
{
	float deltaT=igra->DajRW()->GetFrameTime()/1000.f;	

	if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Escape))
		tranzicija=T_FADEOUT;
	
	if(DEVMODE==false)
	{
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::A))
			igrac->Rotiraj(-150*deltaT);
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::D))
			igrac->Rotiraj(150*deltaT);
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::W))
			igrac->DodajMoment(1);
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::S))
			igrac->DodajMoment(-1);
		if(sf::Mouse::IsButtonPressed(sf::Mouse::Button::Left))
			igrac->Pucaj(mis+kamera->DajPoz(),deltaT);
	}
	if(DEVMODE==true)
	{
		float speed=250;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::LShift))
			speed=750;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::A))
			kamera->PromijeniPoz(kamera->DajPoz()+Vec2(-speed*deltaT,0));
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::D))
			kamera->PromijeniPoz(kamera->DajPoz()+Vec2(speed*deltaT,0));
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::W))
			kamera->PromijeniPoz(kamera->DajPoz()+Vec2(0, -speed*deltaT));
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::S))
			kamera->PromijeniPoz(kamera->DajPoz()+Vec2(0, speed*deltaT));

		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Numpad7))
			sr+=0.5*deltaT;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Numpad4))
			sr-=0.5*deltaT;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Numpad8))
			sg+=0.5*deltaT;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Numpad5))
			sg-=0.5*deltaT;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Numpad9))
			sb+=0.5*deltaT;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Numpad6))
			sb-=0.5*deltaT;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Numpad2))
			si+=50*deltaT;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::Numpad1))
			si-=50*deltaT;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::I))
			srad+=50*deltaT;
		if(sf::Keyboard::IsKeyPressed(sf::Keyboard::Key::K))
			srad-=50*deltaT;
		if(sr<0.0)
			sr=0.0;
		if(sr>1.0)
			sr=1.0;
		if(sg<0.0)
			sg=0.0;
		if(sg>1.0)
			sg=1.0;
		if(sb<0.0)
			sb=0.0;
		if(sb>1.0)
			sb=1.0;
		if(si<0.0)
			si=0.0;
	}
}
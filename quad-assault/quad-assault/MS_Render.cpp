#include "MenuStanje.h"
#include "Igra.h"
#include "Likovi.h"

void MenuStanje::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLoadIdentity();	

	if(stanje==GLAVNI_MENU)
	{
		Sprite(Vec2(0.0, 0.0), Vec2(igra->DajRW()->GetWidth(), igra->DajRW()->GetHeight()),mt->DajTexturu(1)->id);	
		startGumb.Render(fontovi[0]);
		oigriGumb.Render(fontovi[0]);
		izlazGumb.Render(fontovi[0]);
	}

	if(stanje==NIVO_ODABIR)
	{
		Sprite(Vec2(0.0, 0.0), Vec2(igra->DajRW()->GetWidth(), igra->DajRW()->GetHeight()),mt->DajTexturu(2)->id);
		natragGumb.Render(fontovi[0]);
		for(int i=0; i<nivoi.size(); i++)
			nivoi[i].gumb.Render(fontovi[0]);
	}
	if(stanje==O_IGRI)		
	{
		Sprite(Vec2(0.0, 0.0), Vec2(igra->DajRW()->GetWidth(), igra->DajRW()->GetHeight()),mt->DajTexturu(2)->id);
		natragGumb.Render(fontovi[0]);

		igra->DajRW()->SaveGLStates();	
			igra->DajRW()->Draw(oigriText);
		igra->DajRW()->RestoreGLStates();
	}	

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	Sprite(mis-Vec2(16,16),Vec2(32,32),mt->DajTexturu(0)->id);
	
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glColor3f(tBoja, tBoja, tBoja);
	Sprite(Vec2(0.0, 0.0), Vec2(igra->DajRW()->GetWidth(), igra->DajRW()->GetHeight()), NULL);

	glDisable(GL_BLEND);

	if(tranzicija==T_FADEOUT && tBoja==0.0 && gotovo==false)
	{
		gotovo=true;			
	}
}

void MenuStanje::RenderLoading()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLoadIdentity();
	Sprite(Vec2(0.0, 0.0), Vec2(igra->DajRW()->GetWidth(), igra->DajRW()->GetHeight()),mt->DajTexturu(2)->id);	

	igra->DajRW()->SaveGLStates();
	sf::Text t;
	t.SetFont(fontovi[0]);	
	t.SetColor(sf::Color(50,255,50));
	t.SetCharacterSize(35);
	t.SetString("Ucitavanje podataka...");
	t.SetPosition(igra->DajRW()->GetWidth()/2-t.GetRect().Width/2,igra->DajRW()->GetHeight()/2-t.GetRect().Height/2);
	igra->DajRW()->Draw(t);
	igra->DajRW()->RestoreGLStates();

	igra->DajRW()->Display();
}
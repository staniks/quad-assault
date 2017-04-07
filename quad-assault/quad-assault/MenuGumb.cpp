#include "MenuGumb.h"
#include "MenuStanje.h"
#include "Igra.h"
#include "Likovi.h"

void MenuGumb::Init(Vec2 p, Vec2 d, string text, sf::Font font, bool omogucen, MenuStanje* stanje)
{
	this->poz=p;
	this->dim=d;
	this->text=text;
	this->stanje=stanje;
	this->font=font;
	this->omogucen=omogucen;

	stanje->DajIgru()->DajRW()->SaveGLStates();	
	t.SetFont(this->font);	
	if(omogucen==true)
		t.SetColor(sf::Color(50,255,50));
	else
		t.SetColor(sf::Color(150,150,150));
	t.SetCharacterSize(30);
	t.SetString(text);
	t.SetPosition(poz.x+dim.x/2-t.GetRect().Width/2 , poz.y+dim.y/2-t.GetRect().Height/2 );	
	stanje->DajIgru()->DajRW()->RestoreGLStates();
}
void MenuGumb::Update(float deltaT)
{
	if(omogucen==true)
	{
		Vec2 mis=stanje->DajMis();	
		if(mis.x>=poz.x && mis.x<poz.x+dim.x
			&& mis.y>=poz.y && mis.y<poz.y+dim.y)	
			odabran=true;	
		else
			odabran=false;
	}
}
void MenuGumb::Render(sf::Font font)
{	
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	if(omogucen==true)
	{
		if(odabran==true)
			glColor3f(0.0, 0.5, 0.0);
		else
			glColor3f(0.0, 0.25, 0.0);
	}
	else
	{
		glColor3f(0.05, 0.05, 0.05);
	}

	glBegin(GL_QUADS);
	glVertex2f(poz.x, poz.y);
	glVertex2f(poz.x+dim.x, poz.y);
	glVertex2f(poz.x+dim.x, poz.y+dim.y);
	glVertex2f(poz.x, poz.y+dim.y);
	glEnd();

	if(omogucen==true)
	{
		if(odabran==true)
			glColor3f(0.0, 1.0, 0.0);
		else
			glColor3f(0.0, 0.5, 0.0);
	}
	else
	{
		glColor3f(0.1, 0.1, 0.1);
	}

	glBegin(GL_LINE_LOOP);
	glVertex2f(poz.x, poz.y);
	glVertex2f(poz.x+dim.x, poz.y);
	glVertex2f(poz.x+dim.x, poz.y+dim.y);
	glVertex2f(poz.x, poz.y+dim.y);
	glEnd();	

	glColor3f(1.0, 1.0, 1.0);

	stanje->DajIgru()->DajRW()->SaveGLStates();	
	stanje->DajIgru()->DajRW()->Draw(t);
	stanje->DajIgru()->DajRW()->RestoreGLStates();

	glDisable(GL_BLEND);
}
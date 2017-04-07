#include "UI_Gumb.h"
#include "UI_Prozor.h"
#include "UI_Menager.h"
#include "Likovi.h"

void UI_Gumb::Init(UI_Prozor* prozor, Vec2 poz, Vec2 dim, void (*funkcija)(), GLuint tex)
{
	UI_Element::Init(prozor,poz);
	this->funkcija=funkcija;	
	this->dim=dim;
	this->tex=tex;
}
void UI_Gumb::Update(float deltaT)
{	
}
void UI_Gumb::Render()
{		
	if(odabran==true)
		glColor3f(0.25, 0.25, 0.25);
	else
		glColor3f(1.0, 1.0, 1.0);
	Sprite(prozor->DajPoz()+poz,dim,tex);
	glColor3f(1.0, 1.0, 1.0);
}

void UI_Gumb::LijeviKlik(Vec2 mis)
{	
	if(mis.x>=prozor->DajPoz().x+poz.x && mis.y>=prozor->DajPoz().y+poz.y
		&& mis.y<prozor->DajPoz().y+poz.y+dim.y && mis.x<prozor->DajPoz().x+poz.x+dim.x)
		odabran=true;
}
void UI_Gumb::LijeviOtpust(Vec2 mis)
{	
	odabran=false;
	if(mis.x>=prozor->DajPoz().x+poz.x && mis.y>=prozor->DajPoz().y+poz.y
		&& mis.y<prozor->DajPoz().y+poz.y+dim.y && mis.x<prozor->DajPoz().x+poz.x+dim.x)
	(*funkcija)();
}
void UI_Gumb::DesniKlik(Vec2 mis)
{
}
void UI_Gumb::DesniOtpust(Vec2 mis)
{
}
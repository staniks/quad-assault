#include "Poruka.h"
#include "GlavnoStanje.h"
#include "Igra.h"

void Poruka::Init(string posiljatelj, string sadrzaj, float trajanje, string zvuk, GlavnoStanje* stanje)
{	
	this->trajanje=trajanje;
	this->stanje=stanje;
	timer=0.0;
	unisten=false;

	this->poz.x=64;
	this->poz.y=64;
		
	stanje->DajIgru()->DajRW()->SaveGLStates();
	p_text.SetString(posiljatelj);
	p_text.SetPosition(poz.x+48, poz.y+4);
	p_text.SetFont(stanje->DajFontove()->at(0));
	p_text.SetCharacterSize(24);	
	p_text.SetColor(sf::Color(25,255,25));

	text.SetString(sadrzaj);
	text.SetPosition(poz.x+48, poz.y+4+24);
	text.SetFont(stanje->DajFontove()->at(0));
	text.SetCharacterSize(24);
	text.SetColor(sf::Color(255,255,255));
	stanje->DajIgru()->DajRW()->RestoreGLStates();

	this->zvuk=zvuk;
	SvirajZvuk=true;	

	portret=stanje->DajMT()->DajTexturu("portret2.tga")->id;	
}
void Poruka::Update(float deltaT)
{
	if(timer<trajanje)
		timer+=deltaT;
	else
	{
		z->Stop();
		unisten=true;		
	}
	if(SvirajZvuk==true)
	{
		z = stanje->DodajZvuk(new sf::Sound(),
			stanje->DajMZ()->DajZvuk((char*)zvuk.c_str()));			
		z->Play();	
		
		SvirajZvuk=false;
	}
	
}
void Poruka::RenderOkvir()
{
	stanje->DajIgru()->DajRW()->SaveGLStates();
	float sirina=text.GetRect().Width;
	stanje->DajIgru()->DajRW()->RestoreGLStates();

	glColor3f(0.0, 0.25, 0.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);		
	glBegin(GL_QUADS); //PUNI KVADRAT PO CIJELOM
	glTexCoord2f(0.0, 0.0); glVertex2f(poz.x+32,poz.y);
	glTexCoord2f(1.0, 0.0); glVertex2f(poz.x+32+sirina+48,poz.y);
	glTexCoord2f(1.0, 1.0); glVertex2f(poz.x+32+sirina+48,poz.y+64);
	glTexCoord2f(0.0, 1.0);	glVertex2f(poz.x+32,poz.y+64);
	glEnd();
	glDisable(GL_BLEND);

	glColor3f(1.0, 1.0, 1.0);	

	glEnable(GL_TEXTURE_2D);//PORTRET
	glBindTexture(GL_TEXTURE_2D, portret);
	glBegin(GL_QUADS); 
	glTexCoord2f(0.0, 0.0); glVertex2f(poz.x-32,poz.y);
	glTexCoord2f(1.0, 0.0); glVertex2f(poz.x+32,poz.y);
	glTexCoord2f(1.0, 1.0); glVertex2f(poz.x+32,poz.y+64);
	glTexCoord2f(0.0, 1.0);	glVertex2f(poz.x-32,poz.y+64);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glColor3f(0.1, 1.0, 0.1);	

	glBegin(GL_LINE_LOOP); //ZELENI OBRUB
	glTexCoord2f(0.0, 0.0); glVertex2f(poz.x-32,poz.y);
	glTexCoord2f(1.0, 0.0); glVertex2f(poz.x-32+sirina+112,poz.y);
	glTexCoord2f(1.0, 1.0); glVertex2f(poz.x-32+sirina+112,poz.y+64);
	glTexCoord2f(0.0, 1.0);	glVertex2f(poz.x-32,poz.y+64);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);	
}
void Poruka::Render()
{		
	stanje->DajIgru()->DajRW()->SaveGLStates();
	stanje->DajIgru()->DajRW()->Draw(p_text);	
	stanje->DajIgru()->DajRW()->Draw(text);
	stanje->DajIgru()->DajRW()->RestoreGLStates();
}
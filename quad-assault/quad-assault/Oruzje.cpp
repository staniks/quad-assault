#include "Oruzje.h"
#include "GlavnoStanje.h"
#include "Projektil.h"

void Oruzje::Init(GlavnoStanje* stanje)
{	
	this->stanje=stanje;
	poz.x=0;
	poz.y=0;
	dim.x=16;
	dim.y=32;

	punjenje=100;
	trenutnoPunjenje=punjenje;
	brzinaPunjenja=250;	
	potrebnaEnergija=1;
}

void Oruzje::Update(float deltaT)
{	
	if(trenutnoPunjenje<punjenje)
	{
		trenutnoPunjenje+=brzinaPunjenja*deltaT;
	}
	else
	{
		trenutnoPunjenje=punjenje;
	}
}
void Oruzje::Pucaj(Vec2 poz, Vec2 smjer, unsigned char** mapa, bool vlasnik)
{
	this->absPoz=poz;
	this->smjer=smjer;
	this->mapa=mapa;
	this->vlasnik=vlasnik;	
}
void Oruzje::IspaliProjektil(Projektil* p)
{
	stanje->DodajProjektil(p);
	p->Init(absPoz,smjer,stanje,mapa,vlasnik);	
	stanje->DajIgraca()->OduzmiEnergiju(potrebnaEnergija);
}
void Oruzje::Render()
{
	float o=trenutnoPunjenje/punjenje*8;
	glPushMatrix();
	glTranslatef(0,-o,0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 0.0); glVertex2f(dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 1.0); glVertex2f(dim.x/2,dim.y/2);	
	glTexCoord2f(0.0, 1.0); glVertex2f(-dim.x/2,dim.y/2);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
void Oruzje::RenderNormal()
{
	float o=trenutnoPunjenje/punjenje*8;
	glPushMatrix();
	glTranslatef(0,-o,0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texN);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 0.0); glVertex2f(dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 1.0); glVertex2f(dim.x/2,dim.y/2);	
	glTexCoord2f(0.0, 1.0); glVertex2f(-dim.x/2,dim.y/2);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
void Oruzje::RenderGlow()
{
	float o=trenutnoPunjenje/punjenje*8;
	glPushMatrix();
	glTranslatef(0,-o,0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texG);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(-dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 0.0); glVertex2f(dim.x/2,-dim.y/2);	
	glTexCoord2f(1.0, 1.0); glVertex2f(dim.x/2,dim.y/2);	
	glTexCoord2f(0.0, 1.0); glVertex2f(-dim.x/2,dim.y/2);	
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
float Oruzje::DajPotrebnuEnergiju()
{
	return potrebnaEnergija;
}
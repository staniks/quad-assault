#include "Cestica.h"
#include "GlavnoStanje.h"
#include "Igra.h"

void Cestica::Init(Vec2 poz, GlavnoStanje* stanje)
{
	this->poz=poz;
	this->stanje=stanje;
	unisten=false;
	int xof=stanje->DajIgru()->Rand(2,4)-2;
	int yof=stanje->DajIgru()->Rand(2,4)-2;
	dim=Vec2(16+xof,16+yof);
	poz=poz+Vec2(xof,yof);
	zivot=100;
	maxZivot=zivot;	
}
void Cestica::Update(float deltaT)
{
	zivot-=deltaT*50;
	if(zivot<=0.0)
		unisten=true;
}
void Cestica::Render(unsigned char stil)
{
	GLuint t;
	if(stil==DIFFUSE)
		t=tex;
	if(stil==NORMAL)
		t=texN;
	if(stil==DIFFUSE || stil==NORMAL)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glColor3f(zivot/maxZivot, zivot/maxZivot, zivot/maxZivot );
		SpriteT(poz,dim,0,t);
		glColor3f(1.0, 1.0, 1.0);
		glDisable(GL_BLEND);
	}
}
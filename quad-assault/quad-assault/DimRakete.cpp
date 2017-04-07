#include "DimRakete.h"
#include "GlavnoStanje.h"
#include "Igra.h"

void DimRakete::Init(Vec2 poz, GlavnoStanje* stanje)
{
	Cestica::Init(poz,stanje);
	maxZivot=45;
	zivot=maxZivot;
	poz.x+=stanje->DajIgru()->Rand(8,16)-8;
	poz.y+=stanje->DajIgru()->Rand(8,16)-8;
	tex=stanje->DajMT()->DajTexturu("Dim1Diffuse.tga")->id;
	texN=stanje->DajMT()->DajTexturu("Dim1Normal.tga")->id;
}
void DimRakete::Update(float deltaT)
{
	Cestica::Update(deltaT);
}
void DimRakete::Render(unsigned char stil)
{
	if(stil==DIFFUSE || stil==NORMAL)
	{
		GLuint t;
		if(stil==DIFFUSE)
			t=tex;
		if(stil==NORMAL)
			t=texN;	

		float faktorSkaliranja=0.5+maxZivot/zivot*0.5;
		if(faktorSkaliranja>2)
			faktorSkaliranja=2;

		float faktorBoje=zivot/maxZivot;

		glPushMatrix();
		glTranslatef(poz.x+dim.x/2, poz.y+dim.y/2, 0);	
		glScalef(faktorSkaliranja,faktorSkaliranja,0);
		glTranslatef(-dim.x,-dim.y,0);	

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);
		glColor3f(faktorBoje,faktorBoje,faktorBoje);
	
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,t);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(dim.x, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(dim.x, dim.y);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0, dim.y);
		glEnd();
		glBindTexture(GL_TEXTURE_2D,0);
		glDisable(GL_TEXTURE_2D);	

		glDisable(GL_BLEND);
		glPopMatrix();	
	
		glColor3f(1.0, 1.0, 1.0);	
	}
}
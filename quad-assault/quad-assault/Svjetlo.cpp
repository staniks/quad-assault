#include "Svjetlo.h"
#include "Igra.h"
#include "Stanje.h"
#include "GlavnoStanje.h"

Svjetlo::Svjetlo()
{
}
Svjetlo::~Svjetlo()
{	
}

void Svjetlo::Init(Vec2 poz, float radius, GlavnoStanje* stanje)
{
	this->poz=poz;
	this->radius=radius;
	this->stanje=stanje;

	this->smjer=Vec2(0.0, 0.0);
	this->kut=0.0;

	unisteno=false;	
}
void Svjetlo::Postavke(Vec3 boja, float intenzitet)
{
	this->boja=boja;
	this->intenzitet=intenzitet;
}
void Svjetlo::PostavkeKuta(Vec2 smjer, float kut)
{
	this->smjer=smjer;
	this->kut=kut;
}
void Svjetlo::Update(float deltaT)
{
}
void Svjetlo::RenderNaFBO(Shader* s, Objekt* kamera, GLuint normalmapa)
{
	if(poz.x+radius>kamera->DajPoz().x && 
		poz.x-radius<kamera->DajPoz().x+stanje->DajIgru()->DajRW()->GetWidth()
		&& poz.y+radius>kamera->DajPoz().y && 
		poz.y-radius<kamera->DajPoz().y+stanje->DajIgru()->DajRW()->GetHeight())
	{
		s->Bind();

		glColor3f(1,1,1);		
		
		float lightX, lightY, lightZ;
	
		lightX=poz.x-kamera->DajPoz().x;
		lightY=poz.y-kamera->DajPoz().y;
		
		int svjetloLoc = glGetUniformLocation(s->ID, "pozSvjetla");
		glUniform2f(svjetloLoc, lightX, lightY);

		int bojaSvjetlaLoc = glGetUniformLocation(s->ID, "bojaSvjetla");
		glUniform3f(bojaSvjetlaLoc, boja.x, boja.y, boja.z);		

		int smjerLoc = glGetUniformLocation(s->ID, "smjer");
		glUniform2f(smjerLoc, smjer.x, smjer.y);	

		int kutLoc = glGetUniformLocation(s->ID, "kut");
		glUniform1f(kutLoc, kut);	

		int visinaZaslonaLoc = glGetUniformLocation(s->ID, "visinaZaslona");
		glUniform1f(visinaZaslonaLoc,stanje->DajIgru()->DajRW()->GetHeight());

		int radiusLoc = glGetUniformLocation(s->ID, "radius");
		glUniform1f(radiusLoc,radius);

		int intenzitetSvjetla = glGetUniformLocation(s->ID, "intenzitet");
		glUniform1f(intenzitetSvjetla,intenzitet);		

		int normalmapaLoc = glGetUniformLocation(s->ID, "nMapa");
		glActiveTextureARB(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, normalmapa);
		glUniform1i(normalmapaLoc, 0);		
			
		glBegin(GL_QUADS);
		glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 0.0);
		glTexCoord2f(1.0, 1.0); glVertex2f(stanje->DajIgru()->DajRW()->GetWidth(), 0.0);
		glTexCoord2f(1.0, 0.0); glVertex2f(stanje->DajIgru()->DajRW()->GetWidth(), stanje->DajIgru()->DajRW()->GetHeight());
		glTexCoord2f(0.0, 0.0); glVertex2f(0.0, stanje->DajIgru()->DajRW()->GetHeight());
		glEnd();	

		s->UnBind();	

		glActiveTextureARB(GL_TEXTURE0);
	}
}
void Svjetlo::Unisti()
{
	unisteno=true;
}

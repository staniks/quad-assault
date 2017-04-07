#include "Likovi.h"

void Sprite(Vec2 poz, Vec2 dim, GLuint tex)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(poz.x, poz.y);
	glTexCoord2f(1.0, 0.0); glVertex2f(poz.x+dim.x, poz.y);
	glTexCoord2f(1.0, 1.0); glVertex2f(poz.x+dim.x, poz.y+dim.y);
	glTexCoord2f(0.0, 1.0); glVertex2f(poz.x, poz.y+dim.y);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);
}
void SpriteT(Vec2 poz, Vec2 dim, float rot, GLuint tex)
{
	glPushMatrix();
	glTranslatef(poz.x+dim.x/2, poz.y+dim.y/2, 0);
	glRotatef(rot,0,0,1);
	glTranslatef(-dim.x/2,-dim.y/2,0);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER,0.5f);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0); glVertex2f(0.0, 0.0);
	glTexCoord2f(1.0, 0.0); glVertex2f(dim.x, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex2f(dim.x, dim.y);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.0, dim.y);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glPopMatrix();
}
bool Kutija::Sudar(Kutija* a)
{
	if(v2.x<a->v1.x)return false;
	if(v2.y<a->v1.y)return false;		

	if(v1.x>a->v2.x)return false;
	if(v1.y>a->v2.y)return false;		

	return true;
}
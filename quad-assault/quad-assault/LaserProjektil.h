#ifndef LASERP_H
#define LASERP_H
#include "Projektil.h"

class GlavnoStanje;

class LaserProjektil : public Projektil
{
private:
	GLuint texG;
public:	
	void Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** mapa, bool vlasnik);
	void Update(float deltaT);
	void Render(unsigned char stil);
	void Unisti();
};

#endif
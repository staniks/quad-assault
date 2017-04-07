#ifndef PLAZMAP_H
#define PLAZMAP_H
#include "Projektil.h"

class GlavnoStanje;

class PlazmaProjektil : public Projektil
{
private:
	float dimTimer; //dok ostvari 10, ostavlja cesticu dima

	GLuint tex;
	
public:	
	void Init(Vec2 poz, Vec2 smjer, GlavnoStanje* stanje, unsigned char** mapa, bool vlasnik);
	void Update(float deltaT);
	void Render(unsigned char stil);
	void Unisti();
};

#endif
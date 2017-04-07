#ifndef MOB_H
#define MOB_H
#include "Objekt.h"
#include "Blok.h"

class GlavnoStanje;
class Projektil;

class Mob : public Objekt
{
protected:			
	float akceleracija;	
	float rotacija;	
	GlavnoStanje* stanje;
	unsigned char** mapa;
	float punjenje;

	//NASLIJED:
	float brzina;
	float maxbrzina;
	GLuint textura, texturaN, texturaG;	
	short hp;
	float brzinaPunjenja;
	float domet;

public:
	
	virtual void Init(Vec2 poz, GlavnoStanje* stanje, unsigned char** mapa);
	virtual void SpawnEfekt();
	virtual void Update(float deltaT);
	virtual void Pucanje(Projektil* p, float deltaT);

	virtual void Render(unsigned char stil);	

	virtual void PrimiStetu(Projektil* p);
	virtual void Unisti();

	void DodajMoment(float x);
	void Rotiraj(float rot);	

	bool ProvjeraSudara();
	void SudarProjektila();	

	bool unisten;
};
#endif
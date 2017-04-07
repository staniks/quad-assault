#ifndef BLOK_H
#define BLOK_H
#include "Likovi.h"

#define MX 128
#define MY 128
#define BLOKDIM 64 //dimenzije bloka

enum tipBloka
{
	POD, ZID, PRAZNINA, CRVENAVRATA, PLAVAVRATA, ZELENAVRATA
};

struct Stranica
{
	Vec2 v1,v2;
	Vec2 okomica;
};

class GlavnoStanje;

class Blok
{
private:
	Vec2 poz; //pozicija bloka	
	Vec2 dim; //dimenzije
	unsigned char tip;
	GlavnoStanje* stanje;

	vector<Stranica> stranice;
	GLuint tex, texN, texG;

	static float voda_tok;
public:
	void Init(Vec2 poz, unsigned char tip, GlavnoStanje* stanje);

	void Render();	
	void RenderNormal();
	void RenderGlow();
};
#endif
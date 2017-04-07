#ifndef LIKOVI_H
#define LIKOVI_H
#include "Ovisnosti.h"
#include "Vec2.h"

struct Kutija
{
	Vec2 v1,v2;
	bool Sudar(Kutija* a);
};

void Sprite(Vec2 poz, Vec2 dim, GLuint tex);
void SpriteT(Vec2 poz, Vec2 dim, float rot, GLuint tex);

#endif
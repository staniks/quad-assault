#ifndef VEC2_H
#define VEC2_H
#include "Ovisnosti.h"

class Vec2
{
public:
	float x,y;

	Vec2();
	Vec2(float x, float y);
	~Vec2();

	Vec2 operator+ (Vec2 drugi);		
	Vec2 operator- (Vec2 drugi);
	void Mnozi(float faktor);
	void Normaliziraj();
	float Duljina();
};

class Vec3
{
public:
	float x,y,z;

	Vec3();
	Vec3(float x, float y, float z);
	~Vec3();
};

#endif
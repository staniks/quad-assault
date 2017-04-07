#include "Vec2.h"

Vec2::Vec2()
{
}
Vec2::Vec2(float x, float y)
{
	this->x=x;
	this->y=y;
}
Vec2::~Vec2()
{
}

Vec3::Vec3()
{
}
Vec3::Vec3(float x, float y, float z)
{
	this->x=x;
	this->y=y;
	this->z=z;
}
Vec3::~Vec3()
{
}

Vec2 Vec2::operator+ (Vec2 drugi)
{
	return Vec2(x+drugi.x,y+drugi.y);
}
Vec2 Vec2::operator- (Vec2 drugi)
{
	return Vec2(x-drugi.x,y-drugi.y);
}
void Vec2::Mnozi(float faktor)
{
	x*=faktor;
	y*=faktor;	
}
void Vec2::Normaliziraj()
{
	float d=(float)sqrt(x*x+y*y);
	if(d==0)
		d=1.0;
	x/=d;			
	y/=d;				
}
float Vec2::Duljina()
{
	return (float)sqrt(x*x+y*y);
}

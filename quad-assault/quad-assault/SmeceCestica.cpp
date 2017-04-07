#include "SmeceCestica.h"
#include "GlavnoStanje.h"

void SmeceCestica::Init(Vec2 poz, GlavnoStanje* stanje)
{
	Cestica::Init(poz,stanje);
	maxZivot=45;
	zivot=maxZivot;	
	tex=stanje->DajMT()->DajTexturu("Dim1Diffuse.tga")->id;
	texN=stanje->DajMT()->DajTexturu("Dim1Normal.tga")->id;
}
void SmeceCestica::Update(float deltaT)
{
	Cestica::Update(deltaT);
}
void SmeceCestica::Render(unsigned char stil)
{
	Cestica::Render(stil);
}
#ifndef STANJE_H
#define STANJE_H
#include "Ovisnosti.h"

class Igra;

class Stanje
{
protected:
	bool gotovo;	

	sf::Event event;

	Igra* igra;		
	
public:		
	virtual bool Init(Igra* igra)=0;	
	virtual void Input()=0;
	virtual void Update(float deltaT)=0;	
	virtual void Render()=0;
	virtual void Izlaz()=0;		

	bool Gotovo();
	Igra* DajIgru();

	bool PrviUpdate;
};

#endif
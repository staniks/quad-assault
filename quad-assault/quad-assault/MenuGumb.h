#ifndef MENUGUMB_H
#define MENUGUMB_H
#include "Objekt.h"
class MenuStanje;

class MenuGumb : public Objekt
{
private:	
	string text;
	sf::Text t;
	sf::Font font;
	Vec2 textPos;
	MenuStanje* stanje;	

	bool omogucen;
public:
	void Init(Vec2 p, Vec2 d, string text, sf::Font font, bool omogucen, MenuStanje* stanje);
	void Update(float deltaT);
	void Render(sf::Font font);

	bool odabran;
};

#endif
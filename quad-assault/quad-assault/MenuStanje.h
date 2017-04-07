#ifndef MS_H
#define MS_H
#include "Stanje.h"
#include "ManagerTextura.h"
#include "ManagerZvuka.h"
#include "Vec2.h"
#include "MenuGumb.h"

#define T_FADEIN 0 
#define T_FADEOUT 1
#define T_NEMA 2 //stanje izmeðu tranzicija

#define GLAVNI_MENU 0
#define O_IGRI 1
#define NIVO_ODABIR 2

struct Nivo
{
	string datoteka;
	string datoteka_g;
	MenuGumb gumb;
};

class MenuStanje : public Stanje
{
private:
	ManagerTextura* mt;	
	
	Vec2 mis;	
	
	vector<sf::Font> fontovi;	
	vector<Nivo> nivoi;

	unsigned char stanje;

	MenuGumb startGumb;
	MenuGumb oigriGumb;
	MenuGumb izlazGumb;
	MenuGumb natragGumb;

	bool misOtpusten;

	Vec2 mapa_offs;

	bool updateanoJednom;

	unsigned char tranzicija; //prelazak na tamno (fade to black, ne znak kak se to zove na hrvatskom)
	float tBoja; //boja tranzicije
	float brzinaFadeanja;

	sf::Text oigriText;
	
public:
	bool Init(Igra* igra);
	void Input();
	void Update(float deltaT);	
	void Render();
	void Izlaz();	

	void RenderLoading();

	Vec2 DajMis();
};
#endif
#ifndef GS_H
#define GS_H
#include "Stanje.h"
#include "Blok.h"
#include "Projektil.h"
#include "ManagerTextura.h"
#include "UI_Menager.h"
#include "Igrac.h"
#include "Explozija.h"
#include "Mob.h"
#include "LaserMob1.h"
#include "PlazmaMob1.h"
#include "Cestica.h"
#include "Trigger.h"
#include "Stvar.h"
#include "OruzjePickup.h"
#include "ManagerZvuka.h"
#include "Poruka.h"
#include "MenuStanje.h"

class GlavnoStanje : public Stanje
{
private:

	bool DEVMODE;
	
	Svjetlo* postavljenoSvjetlo;
	float sr,sg,sb, si, srad; //boja postavljenog svjetla

	int PostavljanjeBloka; //vrsta bloka koji se postavlja
	bool postavljaSvjetlo;

	unsigned char postavljaMobTrigger;	
	Trigger* postavljeniTrigger;
	Vec2 t1, t2, t3; //pocetak, kraj i spawnpoint triggera

	unsigned char** mapa;
	Blok** blokovi;

	float gameOverTimer; //dok dosegne nulu, igra odlazi na glavni menu
	bool nivoZavrsen;

	Igrac* igrac;

	vector<Projektil*> projektili;
	vector<Explozija*> explozije;	
	vector<Svjetlo*> svjetla;
	vector<Shader*> shaderi;
	vector<Mob*> mobovi;	

	UI_Menager* uim;

	ManagerTextura* mt;
	ManagerZvuka* mz;

	Objekt* kamera;
	Vec2 mis;

	GLuint fbo, fbo_rb;	
	
	GLuint lightmapa;
	GLuint normalmapa;
	GLuint geometrija;
	Vec3 ambijentnoSvjetlo;
	
	sf::Music muzika;

	vector<Cestica*> cestice;
	vector<Trigger*> triggeri;
	vector<Stvar*> stvari;
	vector<sf::Sound*> zvukovi;
	vector<sf::Font> fontovi;
	vector<Poruka*> poruke;

	unsigned char tranzicija; //prelazak na tamno (fade to black, ne znak kak se to zove na hrvatskom)
	float tBoja; //boja tranzicije
	float brzinaFadeanja;

public:
	bool Init(Igra* igra);
	void Input();
	void Update(float deltaT);	
	void UpdateDev(float deltaT);
	void Render();
	void Izlaz();	

	bool PostaviFBO();
	void IzbrisiFBO();

	void UcitajMapu();
	void InitBlokove();
	void SpremiBlokove();
	Mob* SpawnajMobPremaImenu(string ime);

	void UpdateajNizove(float deltaT);

	unsigned char** DajMapu();
	Blok* DajBlok(short x, short y);	
	Igrac* DajIgraca();
	vector<Mob*>* DajMobove();
	vector<Projektil*>* DajProjektile();
	vector<sf::Font>* DajFontove();

	Svjetlo* DodajSvjetlo(bool staticno);
	Explozija* DodajExploziju();
	Projektil* DodajProjektil(Projektil* p);
	Cestica* DodajCesticu(Cestica* c);
	sf::Sound* DodajZvuk(sf::Sound* z, Zvuk* zvuk);
	Mob* DodajMoba(Mob* m);
	Poruka* DodajPoruku(Poruka* p);
	Stvar* DodajStvar(Stvar* s);
	
	void RenderObjekte(unsigned char stil);

	void RenderGeometriju();
	void RenderGeometrijuNormal();
	void RenderGeometrijuGlow();

	void RenderNormalNaFBO();
	void RenderGeometrijuNaFBO();
	void RenderSvjetlostNaFBO();	
	void RenderScenu();	

	void ZavrsiNivo();
	void ObrisiMapu();

	ManagerTextura* DajMT();
	ManagerZvuka* DajMZ();

	///GUI - FUNKCIJE
	void PostaviSvjetlo();
	void PostaviMobTrigger();
	void GenerirajPrazanLevel();
};
#endif
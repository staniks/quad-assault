#include "GlavnoStanje.h"

Svjetlo* GlavnoStanje::DodajSvjetlo(bool staticno)
{
	svjetla.push_back(new Svjetlo());
	svjetla.back()->staticno=staticno;
	return svjetla.back();
}
Projektil* GlavnoStanje::DodajProjektil(Projektil* p)
{
	projektili.push_back(p);
	return projektili.back();
}
Explozija* GlavnoStanje::DodajExploziju()
{
	explozije.push_back(new Explozija());
	return explozije.back();
}
Cestica* GlavnoStanje::DodajCesticu(Cestica* c)
{
	cestice.push_back(c);
	return cestice.back();
}
Mob* GlavnoStanje::DodajMoba(Mob* m)
{
	mobovi.push_back(m);
	return mobovi.back();
}
Poruka* GlavnoStanje::DodajPoruku(Poruka* p)
{
	poruke.push_back(p);
	return poruke.back();
}
Stvar* GlavnoStanje::DodajStvar(Stvar* s)
{
	stvari.push_back(s);
	return stvari.back();
}
sf::Sound* GlavnoStanje::DodajZvuk(sf::Sound* z, Zvuk* zvuk)
{
	bool sadrzi=false;
	for(int i=0; i<zvukovi.size(); i++)
		if(zvukovi[i]->GetBuffer()==&zvuk->buffer)
		{
			sadrzi=true;
			delete z;
			z=zvukovi[i];
			z->Stop();
			break;
		}
	if(sadrzi==false)
	{		
		zvukovi.push_back(z);		
		zvukovi.back()->SetBuffer(zvuk->buffer);
		return zvukovi.back();
	}
	if(sadrzi==true)
		return z;
}
Igrac* GlavnoStanje::DajIgraca()
{
	return igrac;
}
vector<Mob*>* GlavnoStanje::DajMobove()
{
	return &mobovi;
}
vector<Projektil*>* GlavnoStanje::DajProjektile()
{
	return &projektili;
}
unsigned char** GlavnoStanje::DajMapu()
{
	return mapa;
}
ManagerZvuka* GlavnoStanje::DajMZ()
{
	return mz;
}
vector<sf::Font>* GlavnoStanje::DajFontove()
{
	return &fontovi;
}
void GlavnoStanje::ZavrsiNivo()
{
	nivoZavrsen=true;
}

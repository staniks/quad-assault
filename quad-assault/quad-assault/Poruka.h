#ifndef PORUKA_H
#define PORUKA_H
#include "Ovisnosti.h"
#include "Objekt.h"

class GlavnoStanje;

class Poruka : public Objekt
{
private:	
	sf::Text p_text;
	sf::Text text;
	float trajanje; //trajanje poruke u sekundama
	float timer; //pocinje od nule	

	GLuint portret;

	string zvuk;	

	bool SvirajZvuk;

	sf::Sound* z;

	GlavnoStanje* stanje;
public:
	void Init(string posiljatelj, string sadrzaj, float trajanje, string zvuk, GlavnoStanje* stanje);
	void Update(float deltaT);
	void RenderOkvir();
	void Render();
	bool unisten;
};

#endif
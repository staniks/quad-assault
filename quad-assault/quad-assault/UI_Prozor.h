#ifndef UI_PROZOR
#define UI_PROZOR
#include "Ovisnosti.h"
#include "Objekt.h"
#include "UI_Element.h"

class UI_Menager;

class UI_Prozor : public Objekt
{
private:
	UI_Menager* manager;

	string naziv;

	vector<UI_Element*> elementi;

	bool podignut;
	Vec2 misPrije;
public:
	UI_Prozor();
	~UI_Prozor();
	void Init(UI_Menager* manager, Vec2 poz, Vec2 dim, string naziv);
	void Update(float deltaT, Vec2 mis);
	void Render();

	void LijeviKlik(Vec2 mis);
	void LijeviOtpust(Vec2 mis);
	void DesniKlik(Vec2 mis);	
	void DesniOtpust(Vec2 mis);

	void DodajElement(UI_Element* e);
	vector<UI_Element*> DajElemente();

	UI_Menager* DajMenagera();
};

#endif
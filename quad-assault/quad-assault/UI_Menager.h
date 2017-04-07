#ifndef UI_MENAGER_H
#define UI_MENAGER_H
#include "Ovisnosti.h"
#include "ManagerTextura.h"
#include "Igra.h"
#include "UI_Prozor.h"

class UI_Menager
{
private:
	ManagerTextura* mt;
	Igra* igra;
	
	vector<UI_Prozor*> prozori;
public:
	UI_Menager();
	~UI_Menager();
	void Init(ManagerTextura* mt, Igra* igra);
	void Update(float deltaT, Vec2 mis);
	void Render();

	void LijeviKlik(Vec2 mis);
	void LijeviOtpust(Vec2 mis);
	void DesniKlik(Vec2 mis);	
	void DesniOtpust(Vec2 mis);

	void DodajProzor(UI_Prozor* p);
	vector<UI_Prozor*> DajProzore();

	ManagerTextura* DajMT();
};

#endif
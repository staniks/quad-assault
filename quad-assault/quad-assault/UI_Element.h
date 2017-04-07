#ifndef UI_ELEMENT
#define UI_ELEMENT
#include "Ovisnosti.h"
#include "Objekt.h"

class UI_Menager;
class UI_Prozor;

class UI_Element : public Objekt
{
protected:
	UI_Prozor* prozor;

	bool odabran; //je li kliknut
public:
	virtual void Init(UI_Prozor* prozor, Vec2 poz);
	virtual void Update(float deltaT);
	virtual void Render();

	virtual void LijeviKlik(Vec2 mis);
	virtual void LijeviOtpust(Vec2 mis);
	virtual void DesniKlik(Vec2 mis);	
	virtual void DesniOtpust(Vec2 mis);
};

#endif
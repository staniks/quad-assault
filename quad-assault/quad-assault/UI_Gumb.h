#ifndef UI_GUMB
#define UI_GUMB
#include "UI_Element.h"

class ManagerTextura;

class UI_Gumb : public UI_Element
{
private:
	void (*funkcija)();

	GLuint tex;
public:
	void Init(UI_Prozor* prozor, Vec2 poz, Vec2 dim, void (*funkcija)(), GLuint tex);
	void Update(float deltaT);
	void Render();

	void LijeviKlik(Vec2 mis);
	void LijeviOtpust(Vec2 mis);
	void DesniKlik(Vec2 mis);	
	void DesniOtpust(Vec2 mis);
};

#endif
#include "UI_Element.h"
#include "UI_Prozor.h"

void UI_Element::Init(UI_Prozor* prozor, Vec2 poz)
{
	this->prozor=prozor;
	this->poz=poz;
	odabran=false;
}
void UI_Element::Update(float deltaT)
{	
}
void UI_Element::Render()
{	
}

void UI_Element::LijeviKlik(Vec2 mis)
{
}
void UI_Element::LijeviOtpust(Vec2 mis)
{
}
void UI_Element::DesniKlik(Vec2 mis)
{
}
void UI_Element::DesniOtpust(Vec2 mis)
{
}
#include "UI_Menager.h"

UI_Menager::UI_Menager()
{
}
UI_Menager::~UI_Menager()
{	
	for(int i=0; i<prozori.size(); i++)
		delete prozori[i];
	prozori.clear();
}
void UI_Menager::Init(ManagerTextura* mt, Igra* igra)
{
	this->mt=mt;
	this->igra=igra;	
}
void UI_Menager::Update(float deltaT, Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->Update(deltaT, mis);
}
void UI_Menager::Render()
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->Render();
}

ManagerTextura* UI_Menager::DajMT()
{
	return mt;
}

void UI_Menager::DodajProzor(UI_Prozor* p)
{
	prozori.push_back(p);
}
vector<UI_Prozor*> UI_Menager::DajProzore()
{
	return prozori;
}

void UI_Menager::LijeviKlik(Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->LijeviKlik(mis);
}
void UI_Menager::LijeviOtpust(Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->LijeviOtpust(mis);
}
void UI_Menager::DesniKlik(Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->DesniKlik(mis);
}
void UI_Menager::DesniOtpust(Vec2 mis)
{
	for(int i=0; i<prozori.size(); i++)
		prozori[i]->DesniOtpust(mis);
}
#include "MenuStanje.h"
#include "Igra.h"

void MenuStanje::Izlaz()
{
	fontovi.clear();	
	nivoi.clear();	
	
	mt->Brisi();	
	
	delete mt;
}
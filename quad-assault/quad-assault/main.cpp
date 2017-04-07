#include "Igra.h"
#include "GlavnoStanje.h"
#include "MenuStanje.h"
int main()
{
	Igra* igra;
	igra= new Igra();
	if(igra->Init("config.txt"))
	{
		igra->DodajStanje(new MenuStanje(),false);
		igra->Loop();
		igra->Izlaz();
	}
	delete igra;

	return 0;
}
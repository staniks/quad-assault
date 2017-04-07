#include "Stanje.h"
#include "Igra.h"

bool Stanje::Gotovo()
{
	return gotovo;
}

Igra* Stanje::DajIgru()
{
	return igra;
}
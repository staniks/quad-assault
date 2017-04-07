#include "GlavnoStanje.h"

void GlavnoStanje::UpdateajNizove(float deltaT)
{
	for(int i=0; i<projektili.size(); i++)
	{
		projektili[i]->Update(deltaT);
		if(projektili[i]->unisten==true)
		{
			projektili[i]->Unisti();
			delete projektili[i];
			projektili.erase(projektili.begin()+i);
		}
	}
	for(int i=0; i<explozije.size(); i++)
	{
		explozije[i]->Update(deltaT);
		if(explozije[i]->unisten==true)
		{
			delete explozije[i];
			explozije.erase(explozije.begin()+i);
		}
	}
	for(int i=0; i<mobovi.size(); i++)
	{
		mobovi[i]->Update(deltaT);
		if(mobovi[i]->unisten==true)
		{
			mobovi[i]->Unisti();
			delete mobovi[i];
			mobovi.erase(mobovi.begin()+i);
		}
	}
	for(int i=0; i<cestice.size(); i++)
	{
		cestice[i]->Update(deltaT);
		if(cestice[i]->unisten==true)
		{
			delete cestice[i];
			cestice.erase(cestice.begin()+i);
		}
	}
	for(int i=0; i<triggeri.size(); i++)
	{
		triggeri[i]->Update(deltaT);
		if(triggeri[i]->status==DEAKTIVIRAN)
		{
			delete triggeri[i];
			triggeri.erase(triggeri.begin()+i);
		}
	}
	for(int i=0; i<stvari.size(); i++)
	{
		stvari[i]->Update(deltaT);
		if(stvari[i]->unisten==true)
		{
			stvari[i]->Unisti();
			delete stvari[i];
			stvari.erase(stvari.begin()+i);			
		}
	}
	for(int i=0; i<zvukovi.size(); i++)
	{
		if(zvukovi[i]->GetStatus()!=sf::Sound::Playing)
		{
			delete zvukovi[i];
			zvukovi.erase(zvukovi.begin()+i);				
		}
	}	
	if(poruke.size()!=0)
	{
		poruke[0]->Update(deltaT);
		if(poruke[0]->unisten==true)
		{
			delete poruke[0];
			poruke.erase(poruke.begin());
		}
	}
}
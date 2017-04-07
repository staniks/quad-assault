#include "ManagerZvuka.h"

vector<Zvuk>* ManagerZvuka::DajZvukove()
{
	return &zvukovi;
}		
Zvuk* ManagerZvuka::DajZvuk(char* ime)
{
	for(int i=0; i<zvukovi.size(); i++)
		if(zvukovi[i].file==ime)
		{
			return &zvukovi[i];
		}
	UcitajZvuk(ime);
	return &zvukovi.back();
}
bool ManagerZvuka::UcitajZvuk(char* ime)
{
	sf::SoundBuffer Buffer;
	if (!Buffer.LoadFromFile(ime))
	{
		MessageBox(NULL,L"Greska kod ucitavanja zvukova.",L"Error.",MB_OK);
		return false;
	}
	Zvuk z;
	z.file=ime;
	z.buffer=Buffer;	
	zvukovi.push_back(z);
	cout << "Zvuk ucitan : " << ime << endl;
	return true;
}
void ManagerZvuka::Brisi()
{
	zvukovi.clear();
}
ManagerZvuka::ManagerZvuka()
{
}
ManagerZvuka::~ManagerZvuka()
{
	zvukovi.clear();
}
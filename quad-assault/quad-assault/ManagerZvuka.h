#ifndef MZ_H
#define MZ_H
#include "Ovisnosti.h"

struct Zvuk
{
	char* file;
	sf::SoundBuffer buffer;			
};

class ManagerZvuka
{
private:
	vector<Zvuk> zvukovi;
public:	
	ManagerZvuka();
	~ManagerZvuka();
	vector<Zvuk>* DajZvukove();	
		
	Zvuk* DajZvuk(char* ime);	

	bool UcitajZvuk(char* ime);
	void Brisi();
};

#endif
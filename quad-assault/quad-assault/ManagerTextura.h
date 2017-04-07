#ifndef MT_H
#define MT_H
#include "Ovisnosti.h"

struct Textura
{
	Textura();
	Textura(char* file, GLuint id);
	~Textura();

	char* file;
	GLuint id;				
};

class ManagerTextura
{
private:
	vector<Textura> texture;
public:
	ManagerTextura();		
	~ManagerTextura();		

	vector<Textura>* DajTexture();		

	Textura* DajTexturu(int i);		
	Textura* DajTexturu(char* name);		

	void BrisiTexturu(int i);		
	void BrisiTexturu(char* name);

	bool UcitajTexturu(char* name);
	void Brisi();
};

#endif
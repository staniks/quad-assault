#include "ManagerTextura.h"
#include "Ovisnosti.h"

Textura::Textura()
{
}
Textura::~Textura()
{
}
Textura::Textura(char* file, GLuint id)
{
	this->file=file;
	this->id=id;
}		
	

ManagerTextura::ManagerTextura()
{
}
ManagerTextura::~ManagerTextura()
{
	for(int i=0; i<texture.size(); i++)
	glDeleteTextures(1,&texture[i].id);
	texture.clear();
}

vector<Textura>* ManagerTextura::DajTexture()
{
	return &texture;
}

Textura* ManagerTextura::DajTexturu(int i)
{
	return &texture[i];
}
Textura* ManagerTextura::DajTexturu(char* name)
{	
	for(int i=0; i<texture.size(); i++)
		if(texture[i].file==name)
		{
			return &texture[i];
		}
	UcitajTexturu(name);
	return &texture.back();
}

void ManagerTextura::BrisiTexturu(int i)
{
	texture.erase(texture.begin()+i);
	glDeleteTextures(1,&texture[i].id);
}
void ManagerTextura::BrisiTexturu(char* name)
{
	for(int i=0; i<texture.size(); i++)
		if(texture[i].file==name)
		{
			texture.erase(texture.begin()+i);
			glDeleteTextures(1,&texture[i].id);
			break;
		}
}

bool ManagerTextura::UcitajTexturu(char* name)
{
	GLuint id;
	sf::Image image;
	if(image.LoadFromFile(name))
	{
		glGenTextures(1,&id);
		glBindTexture(GL_TEXTURE_2D,id);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image.GetWidth(), image.GetHeight(), GL_RGBA, GL_UNSIGNED_BYTE, image.GetPixelsPtr());			
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);				
			
		texture.push_back(Textura(name,id));
		cout << "Textura ucitana : " << name << endl;
		return true;
	}
	else
	{
		MessageBox(NULL,L"Greska kod ucitavanja textura.",L"Error.",MB_OK);
		return false;
	}
}

void ManagerTextura::Brisi()
{
	for(int i=0; i<texture.size(); i++)
	glDeleteTextures(1,&texture[i].id);
	texture.clear();
}
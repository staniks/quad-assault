#ifndef SVJETLO_H
#define SVJETLO_H
#include "Objekt.h"
#include "Shader.h"

class GlavnoStanje;

class Svjetlo : public Objekt
{
private:	
	GlavnoStanje* stanje;
public:

	float radius;
	float intenzitet;
	Vec3 boja;

	Vec2 smjer; //normala u kojem smjeru je svjetlo okrenuto (baterija)
	float kut; //od 0.0 do 1.0, odredjuje kut djelovanja baterije

	bool staticno;

	Svjetlo();
	~Svjetlo();
	void Init(Vec2 poz, float radius, GlavnoStanje* stanje);
	void Postavke(Vec3 boja, float intenzitet);
	void PostavkeKuta(Vec2 smjer, float kut);
	void Update(float deltaT);
	void RenderNaFBO(Shader* s, Objekt* kamera, GLuint normalmapa);	
	void Unisti();	
	
	bool unisteno;
};

#endif
#include "GlavnoStanje.h"
#include "Igra.h"
#include "KljucPickup.h"
#include "ZajednickeVarijable.h"

void GlavnoStanje::UcitajMapu()
{
	mapa=new unsigned char*[MX];
	for(int i=0; i<MX; i++)
	{
		mapa[i]=new unsigned char[MY];
	}
	blokovi=new Blok*[MX];
	for(int i=0; i<MX; i++)
	{
		blokovi[i]=new Blok[MY];
	}

	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{		
			mapa[i][j]=0;
			if(i==0 || j==0 || i==MX-1 || j==MY-1)
				mapa[i][j]=1;
	}	

	kamera=new Objekt();
	kamera->PromijeniPoz(Vec2(0,0));	

	igrac=new Igrac();	

	ambijentnoSvjetlo=Vec3(0.0f, 0.0f, 0.0f);

	Vec2 igracPoz=Vec2(0,0);

	ifstream file_(nivo_datoteka_g,ios::in);
	string linija_;
	while(getline(file_,linija_))
	{
		istringstream lstring(linija_,ios::in);
		string vrijednost;
		while(getline(lstring,vrijednost,' '))
		{
			if(vrijednost=="blok")
			{
				getline(lstring,vrijednost,' ');
				int x=atoi(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int y=atoi(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int tip=atoi(vrijednost.c_str());
				if(x/BLOKDIM<MX && y/BLOKDIM<MY)
					mapa[x/BLOKDIM][y/BLOKDIM]=tip;
			}
			if(vrijednost=="svjetlo")
			{
				svjetla.push_back(new Svjetlo());
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float radius=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float intenzitet=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float r=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float g=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float b=atof(vrijednost.c_str());
				svjetla.back()->Init(Vec2(x,y),radius,this);
				svjetla.back()->Postavke(Vec3(r,g,b),intenzitet);
				svjetla.back()->staticno=true;
			}
		}
	}
	file_.close();

	ifstream file(nivo_datoteka,ios::in);
	string linija;
	while(getline(file,linija))
	{
		istringstream lstring(linija,ios::in);
		string vrijednost;
		while(getline(lstring,vrijednost,' '))
		{			
			if(vrijednost=="igrac")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				igracPoz=Vec2(x,y);
			}	
			if(vrijednost=="oruzje")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int id=atoi(vrijednost.c_str());
				stvari.push_back(new OruzjePickup());
				OruzjePickup* o=(OruzjePickup*)stvari.back();
				o->Init(Vec2(x,y),this,id);
			}
			if(vrijednost=="kljuc")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				int id=atoi(vrijednost.c_str());
				stvari.push_back(new KljucPickup());
				KljucPickup* k=(KljucPickup*)stvari.back();
				k->Init(Vec2(x,y),this,id);
			}
			if(vrijednost=="preload_zvuk")
			{
				getline(lstring,vrijednost,' ');
				mz->UcitajZvuk((char*)vrijednost.c_str());
			}
			if(vrijednost=="muzika")
			{
				getline(lstring,vrijednost,' ');				
				muzika.OpenFromFile((char*)vrijednost.c_str());	
				muzika.SetVolume(25);
				muzika.SetLoop(true);
				muzika.Play();
			}
			if(vrijednost=="mob")
			{
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				Mob* m=SpawnajMobPremaImenu(vrijednost);
				mobovi.push_back(m);
				mobovi.back()->Init(Vec2(x,y),this,mapa);
			}
			if(vrijednost=="mobtrigger")
			{
				triggeri.push_back(new Trigger());
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float x2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float mx=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float my=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				Mob* m=SpawnajMobPremaImenu(vrijednost);								
				triggeri.back()->InitMob(Vec2(x,y),Vec2(x2,y2),Vec2(mx,my),m,this);
			}
			if(vrijednost=="krajtrigger")
			{
				triggeri.push_back(new Trigger());
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float x2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y2=atof(vrijednost.c_str());											
				triggeri.back()->InitKraj(Vec2(x,y),Vec2(x2,y2),this);
			}
			if(vrijednost=="porukatrigger")
			{				
				getline(lstring,vrijednost,' ');
				float x=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float x2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,' ');
				float y2=atof(vrijednost.c_str());
				getline(lstring,vrijednost,';');
				string posiljatelj=vrijednost;
				getline(lstring,vrijednost,';');
				string text=vrijednost;
				getline(lstring,vrijednost,' ');
				float trajanje=atof(vrijednost.c_str());	
				getline(lstring,vrijednost,' ');
				string zvuk_file=vrijednost;
				triggeri.push_back(new Trigger());
				Poruka* p=new Poruka();
				p->Init(posiljatelj,text,trajanje,zvuk_file,this);
				triggeri.back()->InitPoruka(Vec2(x,y), Vec2(x2,y2), p, this);
			}
		}
	}
	file.close();
	igrac->Init(igracPoz,this,mapa);
	InitBlokove();
}
Mob* GlavnoStanje::SpawnajMobPremaImenu(string ime)
{
	if(ime=="lasermob1")				
		return new LaserMob1();	
	if(ime=="plazmamob1")				
		return new PlazmaMob1();	
}
void GlavnoStanje::InitBlokove()
{
	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{
		/*if(mapa[i][j]==0)
			blokovi[i][j].Init(Vec2(i*BLOKDIM, j*BLOKDIM),mapa[i][j],mt->DajTexturu("Pozadina1.tga")->id, this);
		if(mapa[i][j]==1)
			blokovi[i][j].Init(Vec2(i*BLOKDIM, j*BLOKDIM),mapa[i][j],mt->DajTexturu("Block.tga")->id, this);
		if(mapa[i][j]==2)*/
			blokovi[i][j].Init(Vec2(i*BLOKDIM, j*BLOKDIM),mapa[i][j], this);			
	}	
}
void GlavnoStanje::ObrisiMapu()
{
	for(int i=0; i<MX; i++)
		delete[] mapa[i];
	delete[] mapa;
	for(int i=0; i<MX; i++)
		delete[] blokovi[i];
	delete[] blokovi;
}
void GlavnoStanje::GenerirajPrazanLevel()
{
	for(int i=0; i<MX; i++)
	for(int j=0; j<MY; j++)
	{		
			mapa[i][j]=0;
			if(i==0 || j==0 || i==MX-1 || j==MY-1)
				mapa[i][j]=1;
	}	
	InitBlokove();
	for(int i=0; i<svjetla.size(); i++)
	{
		if(svjetla[i]->staticno==true)
		{
			delete svjetla[i];
			svjetla.erase(svjetla.begin()+i);
		}
	}
}
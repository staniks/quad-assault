#include "MenuStanje.h"
#include "Igra.h"
#include "ZajednickeVarijable.h"

bool MenuStanje::Init(Igra* igra)
{
	this->igra=igra;
	gotovo=false;	

	mt=new ManagerTextura();
	mt->UcitajTexturu("kurzor.tga");
	mt->UcitajTexturu("Menu1.tga");	
	mt->UcitajTexturu("MenuLoading1.tga");		
	
	fontovi.push_back(sf::Font());
	fontovi.back().LoadFromFile("DijalogFont.TTF");		

	Vec2 poz;
	poz.x=igra->DajRW()->GetWidth()/2 - 224;
	poz.y=igra->DajRW()->GetHeight()/2 + igra->DajRW()->GetHeight()/8;
	startGumb.Init(Vec2(poz.x, poz.y), Vec2(128, 64), "Start", fontovi[0], true, this);
	oigriGumb.Init(Vec2(poz.x+128+32, poz.y), Vec2(128, 64), "O igri", fontovi[0], true, this);
	izlazGumb.Init(Vec2(poz.x+256+64, poz.y), Vec2(128, 64), "Izlaz", fontovi[0], true, this);

	natragGumb.Init(Vec2(32, igra->DajRW()->GetHeight()-96), Vec2(128, 64), "Natrag", fontovi[0], true, this);

	mapa_offs=Vec2(0,0);

	updateanoJednom=false;
	misOtpusten=false;

	tranzicija=T_FADEIN;
	tBoja=0.0f;
	brzinaFadeanja=1;	

	stanje=GLAVNI_MENU;

	igra->DajRW()->SaveGLStates();	
		oigriText.SetFont(fontovi[0]);		
		oigriText.SetColor(sf::Color(50,255,25));
		oigriText.SetCharacterSize(30);
		string text="";
		text+="QuadAssault v1.0\n";
		text+="----------------\n";
		text+="Upravljate tenkom koji na sebi moze nositi razno naoruzanje.\n";		
		text+="Kretanje : W ili strelica gore, S ili strelica dolje\n";		
		text+="Okretanje : A ili strelica lijevo, D ili strelica desno\n";		
		text+="Pucanje: Lijeva tipka misa\n";		
		text+="---------------------\n";
		text+="Izradio : Marko Stanic, 4.A-2\n";
		text+="Mentor : Dario Jembrek, prof.\n";
		text+="Obrtnicka Skola Koprivnica\n";
		text+="---------------------\n";
		text+="Kontakt :\n";
		text+="Mail/MSN : mstani19@gmail.com\n";
		text+="Blog : staniks.blogspot.com\n";
		text+="Youtube : www.youtube.com/geomancer120\n";
		text+="\n";
		text+="Igra je pisana u C++ jeziku, koristenjem Microsoft Visual Studio IDE-a.\n";
		text+="Igra koristi biblioteke funkcija i klasa OpenGL i SFML, a za shadere je\n";
		text+="koristen scripting jezik GLSL. Nije koristen vanjski engine, nego je napisan\n";
		text+="vlastiti, poseban za igru.\n";
		oigriText.SetString(text);		
		oigriText.SetPosition(32, 32);	
	igra->DajRW()->RestoreGLStates();

	ifstream file("nivoLista.gdf",ios::in);
	string linija;
	while(getline(file,linija))
	{
		istringstream lstring(linija,ios::in);
		string vrijednost;
		while(getline(lstring,vrijednost,' '))
		{
			if(vrijednost=="[NIVO]")
			{				
				nivoi.push_back(Nivo());
			}
			if(vrijednost=="datoteka")
			{
				getline(lstring,vrijednost,' ');
				nivoi.back().datoteka=vrijednost;
			}
			if(vrijednost=="datoteka_g")
			{
				getline(lstring,vrijednost,' ');
				nivoi.back().datoteka_g=vrijednost;
			}
		}
	}
	file.close();
	if(odabir_levela_odmah==NULL)
		odabir_levela_odmah=false;
	if(odabir_levela_odmah==true)
		stanje=NIVO_ODABIR;
	ifstream in("nivoLock.gdf");	
	for(int i=0; i<BROJ_NIVOA; i++)
	{
		in >> nivo_omogucen[i];	
	}
	in.close();
	for(int i=0; i<nivoi.size(); i++)
	{		
		string text="Misija ";
		char brojString[16];
		itoa(i+1,brojString,10);
		text+=brojString;
		
		nivoi[i].gumb.Init(Vec2(igra->DajRW()->GetWidth()/2-64, 64+i*96), 
			Vec2(128,64), text, fontovi[0], nivo_omogucen[i], this);
	}

	return true;
}
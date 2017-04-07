#include "Igra.h"

bool Igra::Init(char* configFile)
{
	//OVO SPADA POD CONFIG***
	sirina=1024;
	visina=768;
	//sirina=1680;
	//visina=1050;
	char* ime="QuadAssault";
	int stil=sf::Style::Close;		
	stil=sf::Style::Fullscreen;
	//***************************
	cout << "----QuadAssault----" << endl;
	cout << "*******************" << endl;		

	cout << "Postavljanje prozora..." << endl;
	rw.Create(sf::VideoMode((int)sirina,(int)visina,32), ime, stil);	
	rw.SetFramerateLimit(120);	
	rw.ShowMouseCursor(false);
		
	gotovo=false;
	srand(time(NULL));
		
	cout << "Postavljanje OpenGL-a..." << endl;
	glViewport(0,0,(GLsizei)sirina,(GLsizei)visina);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,sirina,visina,0,0,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	glPushAttrib( GL_DEPTH_BUFFER_BIT | GL_LIGHTING_BIT );
	glDisable( GL_DEPTH_TEST );
	glDisable( GL_LIGHTING );	
	
	GLenum greska=glewInit();

	if(greska!=GLEW_OK)
	{
		MessageBox(NULL,
			L"Nemoguce je inicijalizirati GLEW. Vasa graficka kartica vjerojatno ne podrzava Shader Model 2.0.",
			L"Greska",MB_OK);
		return false;
	}

	/*cout << "Postava prvotnog stanja..." << endl;
	stanja.push_back(stanje);

	if(!stanja.back()->Init(this))
	{
		stanja.back()->PrviUpdate=true;
		return false;
	}*/
	cout << "Igra postavljena!" << endl;
	return true;
}
void Igra::DodajStanje(Stanje* stanje, bool unisti_trenutno)
{	
	if(unisti_trenutno==true)
	{
		stanja[stanja.size()-1]->Izlaz();
		delete stanja[stanja.size()-1];
		stanja.erase(stanja.begin()+stanja.size()-1);		
		cout << "Staro stanje izbrisano." << endl;
	}
	stanja.push_back(stanje);
	cout << "Postava novog stanja..." << endl;
	stanja.back()->Init(this);
	stanja.back()->PrviUpdate=true;
	
	cout << "Igra postavljena!" << endl;
}
void Igra::Loop()
{
	while(gotovo==false)
	{
		float deltaT=rw.GetFrameTime()/1000.f;			
		
		stanja.back()->Input();
		stanja.back()->Update(deltaT);			
				
		stanja.back()->Render();
		rw.Display();		

		if(stanja.back()->Gotovo())
		{
			stanja.back()->Izlaz();
			delete stanja.back();
			stanja.pop_back();
		}
		if(stanja.size()==0)
			gotovo=true;
	}
}
void Igra::Izlaz()
{
	for(int i=0; i<stanja.size(); i++)
	{
		stanja[i]->Izlaz();
		delete stanja[i];
	}
	stanja.clear();
	rw.Close();
}

sf::RenderWindow* Igra::DajRW()
{
	return &rw;
}

int Igra::Rand(int i1, int i2)
{
	return rand()%i2+i1;
}
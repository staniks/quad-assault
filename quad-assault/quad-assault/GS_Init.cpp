#include "GlavnoStanje.h"
#include "Igra.h"
#include "UI_Gumb.h"
#include "UI_Prozor.h"
#include "GUI_Funkcije.h"

bool GlavnoStanje::Init(Igra* igra)
{
	this->igra=igra;
	gotovo=false;

	extStanje=this;
	postavljaSvjetlo=false;
	postavljaMobTrigger=0;
	sr=1.0; sg=10; sb=1.0; si=8.0; srad=128.0;

	mt=new ManagerTextura();
	mt->UcitajTexturu("kurzor.tga");	

	mz=new ManagerZvuka();		

	shaderi.push_back(new Shader("SvjetloVS.txt", "SvjetloFS.txt"));	
	shaderi.push_back(new Shader("RenderScenuVS.txt", "RenderScenuFS.txt"));	

	fontovi.push_back(sf::Font());
	fontovi.back().LoadFromFile("DijalogFont.ttf");

	uim=new UI_Menager();
	uim->Init(mt,igra);

	uim->DodajProzor(new UI_Prozor());	
	
	UI_Prozor* p=uim->DajProzore().back();
	p->Init(uim,Vec2(32,32), Vec2(320, 240), "Alati");
	
	p->DodajElement(new UI_Gumb());	
	UI_Gumb* g=(UI_Gumb*)p->DajElemente().back();
	g->Init(uim->DajProzore().back(),Vec2(16,32),Vec2(32,32),PosSvjetGUI,mt->DajTexturu("gumb_svjetlo.tga")->id);

	p->DodajElement(new UI_Gumb());	
	g=(UI_Gumb*)p->DajElemente().back();
	g->Init(uim->DajProzore().back(),Vec2(64,32),Vec2(32,32),PosTrigGUI,mt->DajTexturu("gumb_svjetlo.tga")->id);

	p->DodajElement(new UI_Gumb());	
	g=(UI_Gumb*)p->DajElemente().back();
	g->Init(uim->DajProzore().back(),Vec2(16,72),Vec2(32,32),GenPrazniLevelGUI,mt->DajTexturu("gumb_gen.tga")->id);

	p->DodajElement(new UI_Gumb());	
	g=(UI_Gumb*)p->DajElemente().back();
	g->Init(uim->DajProzore().back(),Vec2(64,72),Vec2(32,32),SpremiLevelGUI,mt->DajTexturu("gumb_spremi.tga")->id);

	DEVMODE=false;

	PostaviFBO();	

	UcitajMapu();

	tranzicija=T_FADEIN;
	tBoja=0.0f;
	brzinaFadeanja=1;
	nivoZavrsen=false;

	gameOverTimer=3;

	return true;
}

bool GlavnoStanje::PostaviFBO()
{
	glGenFramebuffers(1,&fbo);	

	glGenTextures(1,&lightmapa);
	glBindTexture(GL_TEXTURE_2D,lightmapa);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
		igra->DajRW()->GetWidth(),
		igra->DajRW()->GetHeight(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1,&normalmapa);
	glBindTexture(GL_TEXTURE_2D,normalmapa);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
		igra->DajRW()->GetWidth(),
		igra->DajRW()->GetHeight(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glGenTextures(1,&geometrija);
	glBindTexture(GL_TEXTURE_2D,geometrija);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 
		igra->DajRW()->GetWidth(),
		igra->DajRW()->GetHeight(),
		0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); 
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);
		
	return true;
}
void GlavnoStanje::IzbrisiFBO()
{
	glDeleteFramebuffers(1,&fbo);
	glDeleteTextures(1,&lightmapa);
	glDeleteTextures(1,&normalmapa);
	glDeleteTextures(1,&geometrija);
}




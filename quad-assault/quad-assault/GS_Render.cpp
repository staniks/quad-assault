#include "GlavnoStanje.h"
#include "Igra.h"
#include "ZajednickeVarijable.h"

void GlavnoStanje::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glLoadIdentity();

	RenderSvjetlostNaFBO();	
	RenderGeometrijuNaFBO();	

	RenderScenu();		
	
	if(poruke.size()!=0)
		poruke[0]->RenderOkvir();
	if(poruke.size()!=0)
		poruke[0]->Render();	

	//glTranslatef(-kamera->DajPoz().x, -kamera->DajPoz().y, 0);
	//for(int i=0; i<triggeri.size(); i++)	
		//triggeri[i]->Render();

	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	Sprite(mis-Vec2(16,16),Vec2(32,32),mt->DajTexturu(0)->id);
	glDisable(GL_BLEND);

	glPushMatrix();
	glTranslatef(32, igra->DajRW()->GetHeight()-32, 0);
	igrac->RenderHP_Bar();
	glPopMatrix();	

	glPushMatrix();
	glTranslatef(igra->DajRW()->GetWidth()-232, igra->DajRW()->GetHeight()-32, 0);
	igrac->RenderEnergija_Bar();
	glPopMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glColor3f(tBoja, tBoja, tBoja);
	Sprite(Vec2(0.0, 0.0), Vec2(igra->DajRW()->GetWidth(), igra->DajRW()->GetHeight()), NULL);
	glDisable(GL_BLEND);	

	if(DEVMODE==true)
		uim->Render();

	if(tranzicija==T_FADEOUT && tBoja==0.0 && gotovo==false)
	{
		gotovo=true;	
		if(nivoZavrsen==true || igrac->JeUnisten()==true)
			odabir_levela_odmah=true;
		else
			odabir_levela_odmah=false;
		igra->DodajStanje(new MenuStanje(), true);
	}
}


void GlavnoStanje::RenderObjekte(unsigned char stil) 
{		
	for(int i=0; i<stvari.size(); i++)
		stvari[i]->Render(stil);
	for(int i=0; i<mobovi.size(); i++)
		mobovi[i]->Render(stil);
	igrac->Render(stil);
	for(int i=0; i<projektili.size(); i++)
		projektili[i]->Render(stil);
	for(int i=0; i<cestice.size(); i++)	
		cestice[i]->Render(stil);		
}
void GlavnoStanje::RenderGeometriju()
{		
	int kx1=kamera->DajPoz().x/BLOKDIM-1;
	int ky1=kamera->DajPoz().y/BLOKDIM-1;
	int kx2=igra->DajRW()->GetWidth()/BLOKDIM+2;
	int ky2=igra->DajRW()->GetHeight()/BLOKDIM+2;
	for(int i=kx1; i<kx1+kx2+1; i++)
	for(int j=ky1; j<ky1+ky2+1; j++)
	{		
		if(i>=0 && i<MX && j>=0 && j<MY)
		blokovi[i][j].Render();
	}
}
void GlavnoStanje::RenderGeometrijuNormal()
{		
	int kx1=kamera->DajPoz().x/BLOKDIM-1;
	int ky1=kamera->DajPoz().y/BLOKDIM-1;
	int kx2=igra->DajRW()->GetWidth()/BLOKDIM+2;
	int ky2=igra->DajRW()->GetHeight()/BLOKDIM+2;
	for(int i=kx1; i<kx1+kx2+1; i++)
	for(int j=ky1; j<ky1+ky2+1; j++)
	{		
		if(i>=0 && i<MX && j>=0 && j<MY)
		blokovi[i][j].RenderNormal();
	}	
}
void GlavnoStanje::RenderGeometrijuGlow()
{		
	int kx1=kamera->DajPoz().x/BLOKDIM-1;
	int ky1=kamera->DajPoz().y/BLOKDIM-1;
	int kx2=igra->DajRW()->GetWidth()/BLOKDIM+2;
	int ky2=igra->DajRW()->GetHeight()/BLOKDIM+2;
	for(int i=kx1; i<kx1+kx2+1; i++)
	for(int j=ky1; j<ky1+ky2+1; j++)
	{		
		if(i>=0 && i<MX && j>=0 && j<MY)
		blokovi[i][j].RenderGlow();
	}	
}


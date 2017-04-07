#include "GlavnoStanje.h"
#include "Igra.h"

void GlavnoStanje::RenderSvjetlostNaFBO()
{
	//LIGHTMAPA	
	RenderNormalNaFBO();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo);		
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
					GL_TEXTURE_2D, lightmapa, 0); 	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(ambijentnoSvjetlo.x, ambijentnoSvjetlo.y, ambijentnoSvjetlo.z, 1.0f);
	glLoadIdentity();	
		
	glEnable(GL_BLEND);	
	glBlendFunc(GL_ONE,GL_ONE);

	//RENDERIRA SE SVE GLOW
	glPushMatrix();
		glTranslatef(-kamera->DajPoz().x, -kamera->DajPoz().y, 0);
		RenderGeometrijuGlow();
		RenderObjekte(GLOW);
	glPopMatrix();

	//RENDERIRAJU SE SVJETLA
	for(int i=0; i<svjetla.size(); i++)
	{		
		svjetla[i]->RenderNaFBO(shaderi[0],kamera, normalmapa);	
		if(svjetla[i]->unisteno==true)
		{
			delete svjetla[i];
			svjetla.erase(svjetla.begin()+i);
		}				
	}
	glDisable(GL_BLEND);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);		
}

void GlavnoStanje::RenderNormalNaFBO()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo);		
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
					GL_TEXTURE_2D, normalmapa, 0); 	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glLoadIdentity();	

	glPushMatrix();	
	//Sprite(Vec2(0,0),Vec2(igra->DajRW()->GetWidth(), igra->DajRW()->GetHeight()),mt->DajTexturu(3)->id);
	glTranslatef(-kamera->DajPoz().x, -kamera->DajPoz().y, 0);			
		RenderGeometrijuNormal();		
		RenderObjekte(NORMAL);
	glPopMatrix();
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);		
}

void GlavnoStanje::RenderGeometrijuNaFBO()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,fbo);		
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, 
					GL_TEXTURE_2D, geometrija, 0); 	

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glLoadIdentity();	

	glPushMatrix();
	//Sprite(Vec2(0,0),Vec2(igra->DajRW()->GetWidth(), igra->DajRW()->GetHeight()),mt->DajTexturu(2)->id);
	glTranslatef(-kamera->DajPoz().x, -kamera->DajPoz().y, 0);	
		RenderGeometriju();
		RenderObjekte(DIFFUSE);			
	glPopMatrix();
	
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);	
}

void GlavnoStanje::RenderScenu()
{		
	shaderi[1]->Bind();
	
	int geometrijaLoc, lightmapaLoc, ambijentLoc;
		
	geometrijaLoc = glGetUniformLocation(shaderi[1]->ID, "geometrija");
	glActiveTextureARB(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, geometrija);
	glUniform1i(geometrijaLoc, 0);	

	lightmapaLoc = glGetUniformLocation(shaderi[1]->ID, "lightmapa");
	glActiveTextureARB(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, lightmapa);
	glUniform1i(lightmapaLoc, 1);

	ambijentLoc = glGetUniformLocation(shaderi[1]->ID, "ambijent");
	glUniform3f(ambijentLoc, ambijentnoSvjetlo.x, ambijentnoSvjetlo.y, ambijentnoSvjetlo.z);

	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0); glVertex2f(0.0, 0.0);
	glTexCoord2f(1.0, 1.0); glVertex2f(igra->DajRW()->GetWidth(), 0.0);
	glTexCoord2f(1.0, 0.0); glVertex2f(igra->DajRW()->GetWidth(), igra->DajRW()->GetHeight());
	glTexCoord2f(0.0, 0.0); glVertex2f(0.0, igra->DajRW()->GetHeight());
	glEnd();
	shaderi[1]->UnBind();

	glActiveTextureARB(GL_TEXTURE0);	
}
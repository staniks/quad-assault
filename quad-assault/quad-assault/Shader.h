#ifndef SHADER_H
#define SHADER_H
#include "Ovisnosti.h"

class Shader
{
public:
	Shader();
	Shader(char* vertex_program_file, char* fragment_program_file);
	~Shader();

	void Log(GLuint obj);
		
	const char* readFile(char* file);

	void Bind();
	void UnBind();

	unsigned int ID;

private:		
	unsigned int vertex_program;
	unsigned int fragment_program;
};
#endif
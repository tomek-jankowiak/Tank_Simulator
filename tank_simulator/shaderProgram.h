#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include "stdio.h"

class ShaderProgram 
{
private:
	GLuint shaderProgram; 
	GLuint vertexShader; 
	GLuint geometryShader; 
	GLuint fragmentShader; 
	char* readFile(const char* fileName); 
	GLuint loadShader(GLenum shaderType,const char* fileName); 

public:
	ShaderProgram(const char* vertexShaderFile,const char* geometryShaderFile,const char* fragmentShaderFile);
	~ShaderProgram();
	void use() const; 
	GLuint u(const char* variableName) const; 
	GLuint a(const char* variableName) const;

	static const ShaderProgram *terenShader, *tankShader, *trackShader, *particleShader, *skyboxShader;

	static void loadShaders();
	static void deleteShaders();
};

#endif

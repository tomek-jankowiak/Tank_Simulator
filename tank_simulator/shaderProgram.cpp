#include "shaderprogram.h"

const ShaderProgram *ShaderProgram::terenShader, *ShaderProgram::tankShader, *ShaderProgram::trackShader, *ShaderProgram::particleShader;

ShaderProgram::ShaderProgram(const char* vertexShaderFile, const char* geometryShaderFile, const char* fragmentShaderFile)
{
	shaderProgram = glCreateProgram();

	printf("Loading vertex shader from %s\n", vertexShaderFile);
	vertexShader = loadShader(GL_VERTEX_SHADER, vertexShaderFile);
	glAttachShader(shaderProgram, vertexShader);

	if (geometryShaderFile != NULL) {
		printf("Loading geometry shader from %s\n", geometryShaderFile);
		geometryShader = loadShader(GL_GEOMETRY_SHADER, geometryShaderFile);
		glAttachShader(shaderProgram, geometryShader);
	}
	else 
		geometryShader = 0;

	printf("Loading fragment shader from %s\n", fragmentShaderFile);
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentShaderFile);
	glAttachShader(shaderProgram, fragmentShader);
	
	glLinkProgram(shaderProgram);

	int infologLength = 0;
	int charsWritten = 0;
	char* infoLog;

	glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1)
	{
		infoLog = new char[infologLength];
		glGetProgramInfoLog(shaderProgram, infologLength, &charsWritten, infoLog);
		printf("%s\n", infoLog);
		delete[]infoLog;
	}

	printf("Shader program created \n");
}

ShaderProgram::~ShaderProgram()
{
	glDetachShader(shaderProgram, vertexShader);
	if (geometryShader != 0) 
		glDetachShader(shaderProgram, geometryShader);
	glDetachShader(shaderProgram, fragmentShader);

	glDeleteShader(vertexShader);
	if (geometryShader != 0) 
		glDeleteShader(geometryShader);
	glDeleteShader(fragmentShader);

	glDeleteProgram(shaderProgram);
}

char* ShaderProgram::readFile(const char* fileName) 
{
	int filesize;
	FILE *file;
	char* result;

	fopen_s(&file, fileName, "rb");
	if (file != nullptr) {
		fseek(file, 0, SEEK_END);
		filesize = ftell(file);
		fseek(file, 0, SEEK_SET);
		result = new char[filesize + 1];
		
		fread_s(result, filesize, 1, filesize, file);
		result[filesize] = 0;
		fclose(file);

		return result;
	}

	return nullptr;

}

GLuint ShaderProgram::loadShader(GLenum shaderType, const char* fileName) 
{
	GLuint shader = glCreateShader(shaderType);
	const GLchar* shaderSource = readFile(fileName);
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);
	delete []shaderSource;

	int infologLength = 0;
	int charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 1) {
		infoLog = new char[infologLength];
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		delete []infoLog;
	}

	return shader;
}

void ShaderProgram::use() const
{
	glUseProgram(shaderProgram);
}

GLuint ShaderProgram::u(const char* variableName) const
{
	return glGetUniformLocation(shaderProgram, variableName);
}

GLuint ShaderProgram::a(const char* variableName) const
{
	return glGetAttribLocation(shaderProgram, variableName);
}

void ShaderProgram::loadShaders()
{
	terenShader = new ShaderProgram("terenVertex.glsl", nullptr, "terenFragment.glsl");
	tankShader = new ShaderProgram("phongVertex.glsl", nullptr, "phongFragment.glsl");
	trackShader = new ShaderProgram("trackVertex.glsl", nullptr, "trackFragment.glsl");
	particleShader = new ShaderProgram("particleVertex.glsl", nullptr, "particleFragment.glsl");
}

void ShaderProgram::deleteShaders()
{
	delete terenShader;
	delete tankShader;
	delete trackShader;
	delete particleShader;
}

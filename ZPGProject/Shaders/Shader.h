#pragma once
#include <GL/glew.h>

class Shader
{
protected:
	GLuint shader;

	void compile();
	void setSource(const char* shaderSource);

public: 
	virtual ~Shader() = 0;
	GLuint get();
};


#include "Shader.h"

void Shader::compile()
{
	glCompileShader(shader);
}

void Shader::setSource(const char* shaderSource)
{
	glShaderSource(shader, 1, &shaderSource, nullptr);
}

GLuint Shader::get()
{
	return shader;
}

Shader::~Shader() {}

#include "VertexShader.h"

VertexShader::VertexShader(const char* shaderSource)
{
	shader = glCreateShader(GL_VERTEX_SHADER);
	this->setSource(shaderSource);
	this->compile();
}

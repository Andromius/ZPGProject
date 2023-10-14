#include "FragmentShader.h"

FragmentShader::FragmentShader(const char* shaderSource)
{
	shader = glCreateShader(GL_FRAGMENT_SHADER);
	this->setSource(shaderSource);
	this->compile();
}

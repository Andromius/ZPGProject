#include "FragmentShader.h"
#include "ShaderImporter.h"

FragmentShader::FragmentShader(std::string fileName)
{
	shader = glCreateShader(GL_FRAGMENT_SHADER);
	setSource(ShaderImporter::readFile(fileName + ".frag").c_str());
	compile();
}

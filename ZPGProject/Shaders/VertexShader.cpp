#include "VertexShader.h"
#include "ShaderImporter.h"

VertexShader::VertexShader(std::string fileName)
{
	shader = glCreateShader(GL_VERTEX_SHADER);
	setSource(ShaderImporter::readFile(fileName + ".vert").c_str());
	compile();
}

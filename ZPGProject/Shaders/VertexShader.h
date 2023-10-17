#pragma once
#include "Shader.h"
#include <string>

class VertexShader :
	public Shader
{
public:
	VertexShader(std::string fileName);
};


#pragma once
#include <GL/glew.h>
#include <vector>
#include "Shaders/ShaderProgram.h"

class Mesh
{
private:
	GLuint VBO;
	GLuint VAO;
	int pointCount;

public:
	Mesh(std::vector<std::vector<std::vector<float>>> points);
	Mesh(std::vector<float> points);
	void draw();
};

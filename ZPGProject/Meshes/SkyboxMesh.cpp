#include "SkyboxMesh.h"

SkyboxMesh::SkyboxMesh(std::vector<float> points)
{
	int step = 3;
	pointCount = points.size();
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, points.size() * sizeof(float), &points.front(), GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * step, (GLvoid*)0);
}

#pragma once
#include "Meshes/Mesh.h"
#include "Transforms/CompositeTransform.h"
#include "Shaders/ShaderProgram.h"
#include <typeinfo>
#include <memory>
#include "Material.h"
#include "Texture.h"

class DrawableObject
{
private:
	std::shared_ptr<Mesh> _mesh;
	std::unique_ptr<CompositeTransform> _transform;
	std::shared_ptr<ShaderProgram> _program;
	std::shared_ptr<Material> _material;
	std::shared_ptr<Texture> _texture;
	int _id = -1;
public:
	DrawableObject(std::shared_ptr<Mesh> _mesh, std::shared_ptr<ShaderProgram> _program, std::shared_ptr<Material> material);
	DrawableObject& addTransform(std::shared_ptr<Transform> transform);
	void setTexture(std::shared_ptr<Texture> texture);
	void draw();
	glm::mat4 getModelMatrix();
	int getId();
	void setId(int newId);
	bool equals(std::shared_ptr<Mesh> comparison);
};


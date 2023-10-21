#pragma once
#include "Meshes/Mesh.h"
#include "Transforms/CompositeTransform.h"
#include "Shaders/ShaderProgram.h"
#include <typeinfo>
#include <memory>

class DrawableObject
{
private:
	std::shared_ptr<Mesh> _mesh;
	std::unique_ptr<CompositeTransform> _transform;
	std::shared_ptr<ShaderProgram> _program;
public:
	DrawableObject(std::shared_ptr<Mesh> _mesh, std::shared_ptr<ShaderProgram> _program);
	DrawableObject& addTransform(std::shared_ptr<Transform> transform);
	void draw();
};


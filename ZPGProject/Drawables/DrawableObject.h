#pragma once
#include "Meshes/Mesh.h"
#include "Transforms/Transform.h"
#include "Transforms/CompositeTransform.h"
#include <typeinfo>

class DrawableObject
{
private:
	Mesh* _mesh;
	CompositeTransform* _transform;
	ShaderProgram* _program;
public:
	DrawableObject(Mesh* _mesh, ShaderProgram* _program);
	DrawableObject* addTransform(Transform* transform);
	void draw();
};


#include "DrawableObject.h"

DrawableObject::DrawableObject(Mesh* mesh, ShaderProgram* program)
{
	_mesh = mesh;
	_transform = new CompositeTransform();
	_program = program;
}

DrawableObject* DrawableObject::addTransform(Transform* transform)
{
	_transform->addTransform(transform);
	return this;
}

void DrawableObject::draw()
{
	//_transform->addRotationTransform(0.01f, { 0, 1, 0 });
	_program->useProgram();
	_program->setMatrixVariable(_transform->transform(), "modelMatrix");
	_mesh->draw();
	ShaderProgram::resetProgram();
}

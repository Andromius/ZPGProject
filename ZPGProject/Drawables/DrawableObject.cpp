#include "DrawableObject.h"

DrawableObject::DrawableObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<ShaderProgram> program)
{
	_mesh = mesh;
	_transform = std::make_unique<CompositeTransform>();
	_program = program;
}

DrawableObject& DrawableObject::addTransform(std::shared_ptr<Transform> transform)
{
	_transform->addTransform(transform);
	return *this;
}

void DrawableObject::draw()
{
	//_transform->addRotationTransform(0.01f, { 0, 1, 0 });
	_program->useProgram();
	_program->setMatrixVariable(_transform->transform(), "modelMatrix");
	_mesh->draw();
	ShaderProgram::resetProgram();
}

#include "DrawableObject.h"

DrawableObject::DrawableObject(std::shared_ptr<Mesh> mesh, std::shared_ptr<ShaderProgram> program, std::shared_ptr<Material> material)
{
	_mesh = mesh;
	_transform = std::make_unique<CompositeTransform>();
	_program = program;
	_material = material;
}

DrawableObject& DrawableObject::addTransform(std::shared_ptr<Transform> transform)
{
	_transform->addTransform(transform);
	return *this;
}

void DrawableObject::setTexture(std::shared_ptr<Texture> texture)
{
	_texture = texture;
}

void DrawableObject::draw()
{
	_program->useProgram();
	_transform->update();
	_program->setVariable(_transform->transform(), "modelMatrix");
	_program->setMaterial(*_material);
	if (_texture != nullptr)
		_program->setTexture(*_texture);
	_mesh->draw();
	ShaderProgram::resetProgram();
}

glm::mat4 DrawableObject::getModelMatrix()
{
	return _transform->transform();
}

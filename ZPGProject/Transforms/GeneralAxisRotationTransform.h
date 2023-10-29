#pragma once
#include "CompositeTransform.h"
#include <Drawables/DrawableObject.h>
class GeneralAxisRotationTransform : public CompositeTransform
{
private:
	std::shared_ptr<DrawableObject> _parent;
	glm::mat4 _childMatrix;
	glm::vec3 _axis;
	glm::vec3 _parentChildDistance;
	float _angle;
	float _speed;
public:
	GeneralAxisRotationTransform(std::shared_ptr<DrawableObject> parent, glm::mat4 childMatrix, glm::vec3 axis, float angle, float speed);
	glm::mat4 transform() override;
	void update() override;
};


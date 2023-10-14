#include "RotationTransform.h"

RotationTransform::RotationTransform(float angle, glm::vec3 axis)
{
    _angle = angle;
    _axis = axis;
}

glm::mat4 RotationTransform::transform()
{
    return glm::rotate(matrix, _angle, _axis);
}

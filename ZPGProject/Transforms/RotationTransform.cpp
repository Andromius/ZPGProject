#include "RotationTransform.h"
#include <glm/gtc/matrix_transform.hpp>

RotationTransform::RotationTransform(float angle, glm::vec3 axis)
{
    _angle = angle;
    _axis = axis;
}

glm::mat4 RotationTransform::transform()
{
    return glm::rotate(matrix, glm::radians(_angle), _axis);
}

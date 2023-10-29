#include "ContinuousRotationTransform.h"
#include <glm/gtc/matrix_transform.hpp>

ContinuousRotationTransform::ContinuousRotationTransform(float angle, glm::vec3 axis, float speed) : RotationTransform (angle, axis)
{
    _speed = speed;
}

glm::mat4 ContinuousRotationTransform::transform()
{
    _angle += _speed;
    return glm::rotate(matrix, glm::radians(_angle), _axis);
}

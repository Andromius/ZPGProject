#include "ContinuousLineTransform.h"
#include <glm/gtc/matrix_transform.hpp>

ContinuousLineTransform::ContinuousLineTransform(float delta, float start)
{
    _delta = delta;
    _start = start;
}

ContinuousLineTransform::ContinuousLineTransform(glm::vec3 point, glm::vec3 direction, float delta, float start)
{
    _point = point;
    _delta = delta;
    _start = start;
    _direction = direction;
}

glm::mat4 ContinuousLineTransform::transform()
{
    return glm::translate(matrix, _point + _direction * _start);
}

void ContinuousLineTransform::update()
{
    if (_start > 1) _goBack = !_goBack;
    else if (_start < 0) _goBack = !_goBack;

    if (!_goBack) _start += _delta;
    else _start -= _delta;
}

#include "ScaleTransform.h"

ScaleTransform::ScaleTransform(glm::vec3 scale)
{
    _scale = scale;
}

glm::mat4 ScaleTransform::transform()
{
    return glm::scale(matrix, _scale);
}

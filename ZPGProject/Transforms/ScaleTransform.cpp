#include "ScaleTransform.h"
#include <glm/gtc/matrix_transform.hpp>

ScaleTransform::ScaleTransform(glm::vec3 scale)
{
    _scale = scale;
}

glm::mat4 ScaleTransform::transform()
{
    return glm::scale(matrix, _scale);
}

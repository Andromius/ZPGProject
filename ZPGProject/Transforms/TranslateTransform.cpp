#include "TranslateTransform.h"
#include <glm/gtc/matrix_transform.hpp>

TranslateTransform::TranslateTransform(glm::vec3 vector)
{
	_translateVector = vector;
}

glm::mat4 TranslateTransform::transform()
{
	return glm::translate(matrix, _translateVector);
}

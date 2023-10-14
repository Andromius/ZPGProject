#include "TranslateTransform.h"

TranslateTransform::TranslateTransform(glm::vec3 vector)
{
	_translateVector = vector;
}

glm::mat4 TranslateTransform::transform()
{
	return glm::translate(matrix, _translateVector);
}

#include "ContinuousBezierTransform.h"
#include <glm/gtc/matrix_transform.hpp>

ContinuousBezierTransform::ContinuousBezierTransform(float delta, float start) : ContinuousLineTransform(delta, start)
{
    _baseFunctionCoefficients = glm::mat4(
        glm::vec4(-1.0, 3.0, -3.0, 1.0),
        glm::vec4(3.0, -6.0, 3.0, 0),
        glm::vec4(-3.0, 3.0, 0, 0),
        glm::vec4(1, 0, 0, 0));
}

ContinuousBezierTransform::ContinuousBezierTransform(std::vector<glm::mat4x3> points, glm::mat4 baseFunctionCoefficients, float start, float delta)
	: ContinuousLineTransform(start, delta)
{
	_points = points;
	_baseFunctionCoefficients = baseFunctionCoefficients;
    _hasFirstCurve = true;
}

glm::mat4 ContinuousBezierTransform::transform()
{
    if (!_hasFirstCurve) return matrix;

    int wholeProgress = static_cast<int>(_start);
    float t = _start - static_cast<float>(wholeProgress);
	glm::vec4 parameters = glm::vec4(glm::pow(t, 3) , glm::pow(t, 2), t, 1.0f);

    return glm::translate(matrix, parameters * _baseFunctionCoefficients * glm::transpose(_points[wholeProgress]));
}

void ContinuousBezierTransform::addPoint(glm::vec3 tangent, glm::vec3 point) {
    glm::vec3 lastTangent = _points.at(_points.size() - 1)[2];
    glm::vec3 lastPoint = _points.at(_points.size() - 1)[3];

    float distance = glm::distance(lastTangent, lastPoint);
    glm::vec3 direction = glm::normalize(lastPoint - lastTangent);
    glm::vec3 invertedTangent = lastPoint + direction * distance;

    _points.push_back(glm::mat4x3(lastPoint, invertedTangent, tangent, point));
}

void ContinuousBezierTransform::addPoints(glm::mat4x3 points)
{
    _points.push_back(points);
    _hasFirstCurve = true;
}

void ContinuousBezierTransform::update() {
    if (!_hasFirstCurve) return;

    const int max = (int)(_points.size());
    if (_start + _delta > (float)max && !_goBack) _goBack = !_goBack;
    else if (_start - _delta < 0 && _goBack) _goBack = !_goBack;
    
    if (!_goBack) _start += _delta;
    else _start -= _delta;
    printf("Delta %f, Start(t) %f\n", _delta, _start);
}

bool ContinuousBezierTransform::hasFirstCurve()
{
    return _hasFirstCurve;
}

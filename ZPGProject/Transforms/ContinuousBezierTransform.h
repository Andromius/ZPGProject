#pragma once
#include "ContinuousLineTransform.h"
#include <vector>
class ContinuousBezierTransform : public ContinuousLineTransform
{
private:
	std::vector<glm::mat4x3> _points;
	glm::mat4 _baseFunctionCoefficients;
	bool _hasFirstCurve = false;
public:
	ContinuousBezierTransform(float delta = 0.01f, float start = 0);
	ContinuousBezierTransform(std::vector<glm::mat4x3> points, glm::mat4 baseFunctionCoefficients, float delta = 0.01f, float start = 0);
	glm::mat4 transform() override;
	void addPoint(glm::vec3 tangent, glm::vec3 point);
	void addPoints(glm::mat4x3 points);
	void update() override;
	bool hasFirstCurve();
};
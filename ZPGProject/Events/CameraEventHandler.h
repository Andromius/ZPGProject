#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

class CameraEventHandler
{
public:
	virtual void onCameraPositionChanged(glm::vec3 position);
	virtual void onCameraViewMatrixChanged(glm::mat4 matrix);
	virtual void onCameraProjectionMatrixChanged(glm::mat4 matrix);
};
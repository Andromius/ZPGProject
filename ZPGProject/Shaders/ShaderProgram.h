#pragma once
#include <vector>
#include "Shader.h"
#include <string>
#include "glm/mat4x4.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "Events/EventHandlers.h"
#include "Events/EventNotifier.h"
#include "Camera.h"
#include <memory>

class ShaderProgram :
	public CameraChangedEventHandler
{
private:
	GLuint _program;
	glm::mat4 _projectionMatrix;
	glm::mat4 _viewMatrix;
	std::shared_ptr<Camera> _camera;

public:
	ShaderProgram(std::shared_ptr<Camera> camera);
	~ShaderProgram();
	void attachShaders(const std::vector<std::shared_ptr<Shader>>& shaders);
	void link();
	void useProgram();
	void checkStatus();
	void setMatrixVariable(glm::mat4 matrix, std::string name);
	static void resetProgram();

	// Inherited via CameraChangedEventHandler
	void onCameraChanged() override;
};

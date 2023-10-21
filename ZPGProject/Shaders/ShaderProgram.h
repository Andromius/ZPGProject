#pragma once
#include <vector>
#include <string>
#include <memory>
#include "VertexShader.h"
#include "FragmentShader.h"
#include "Camera.h"
#include "Events/ApplicationEventHandler.h"
#include "Events/CameraEventHandler.h"
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram :
	public CameraEventHandler,
	public ApplicationEventHandler
{
private:
	GLuint _program;
	std::shared_ptr<Camera> _camera;

public:
	ShaderProgram(std::shared_ptr<Camera> camera, VertexShader& vertexShader, FragmentShader& fragmentShader);
	~ShaderProgram();

	void link();
	void useProgram();
	void checkStatus();
	void setMatrixVariable(glm::mat4 matrix, std::string name);
	void setVec3Variable(glm::vec3 vector, std::string name);
	void setVec4Variable(glm::vec4 vector, std::string name);
	static void resetProgram();

	void onCameraPositionChanged(glm::vec3 position) override;
	void onCameraProjectionMatrixChanged(glm::mat4 matrix) override;
	void onCameraViewMatrixChanged(glm::mat4 matrix) override;

	void onSceneChanged(Scene& scene) override;
};

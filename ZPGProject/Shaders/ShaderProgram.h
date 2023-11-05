#pragma once
#include <vector>
#include <string>
#include <memory>
#include "VertexShader.h"
#include "FragmentShader.h"
#include "Camera.h"
#include "Events/ApplicationEventHandler.h"
#include "Drawables/Material.h"
#include "Events/CameraEventHandler.h"
#include "Events/SceneEventHandler.h"
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram :
	public CameraEventHandler,
	public ApplicationEventHandler,
	public SceneEventHandler
{
private:
	GLuint _program;
	std::shared_ptr<Camera> _camera;
	Scene* _scene;
	
	void setLightVariables(std::shared_ptr<Light> light, int i);
public:
	ShaderProgram(std::shared_ptr<Camera> camera, VertexShader& vertexShader, FragmentShader& fragmentShader);
	~ShaderProgram();

	void link();
	void useProgram();
	void checkStatus();
	void setVariable(glm::mat4 matrix, std::string name);
	void setVariable(glm::vec3 vector, std::string name);
	void setVariable(glm::vec4 vector, std::string name);
	void setVariable(float value, std::string name);
	void setVariable(int value, std::string name);
	
	void setMaterial(Material& material);
	
	static void resetProgram();

	void onCameraPositionChanged(glm::vec3 position) override;
	void onCameraProjectionMatrixChanged(glm::mat4 matrix) override;
	void onCameraViewMatrixChanged(glm::mat4 matrix) override;

	void onSceneChanged(Scene& scene) override;
	
	void onSceneLightPositionChanged(int index, glm::vec3 position) override;
	void onSceneLightColorChanged(int index, glm::vec4 color) override;
	void onSceneLightDirectionChanged(int index, glm::vec3 direction) override;
};

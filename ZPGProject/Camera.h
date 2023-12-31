#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Window.h"
#include "Events/CameraEventHandler.h"
#include <Lights/SpotLight.h>


class Camera : 
	public WindowEventHandler,
	public ObservableObject<CameraEventHandler>
{
private:
	std::shared_ptr<Window> _window;
	std::shared_ptr<SpotLight> _light;
	glm::vec3 _eye;
	glm::vec3 _target;
	glm::vec3 _up;
	float _fov;
	float _cursorPosX;
	float _cursorPosY;
	float _aspectRatio;
	float _sens;
	float _pitch;
	float _yaw;
	bool _canTurn;

public:
	Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, float fov, float sens, std::shared_ptr<Window> window);
	~Camera();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::vec3 getEye();

	void attachLight(std::shared_ptr<SpotLight> light);

	void onWindowSizeChanged(ScreenDimensions& dimensions) override;
	void onKey(GLFWwindow* window) override;
	void onCursorPositionChanged(CursorPos& cursorPos) override;
	void onMouseButton(GLFWwindow* window) override;
};


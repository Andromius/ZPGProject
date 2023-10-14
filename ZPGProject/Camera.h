#pragma once
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Events/EventHandlers.h"
#include "Events/EventNotifier.h"
#include "Observables/ObservableObject.h"
#include <list>


class Camera : 
	public WindowSizeChangedEventHandler,
	public ObservableObject<CameraChangedEventHandler>,
	public KeyEventHandler,
	public CursorPosChangedEventHandler
{
private:
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

public:
	Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, float fov, float width, float height, float sens);
	~Camera();
	glm::mat4 getCamera();
	glm::mat4 getPerspective();

	// Inherited via WindowSizeChangedEventHandler
	void onWindowSizeChanged(GLFWwindow* window, int width, int height) override;
	// Inherited via ObservableObject
	void notify() override;
	// Inherited via KeyEventHandler
	void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
	// Inherited via CursorPosChangedEventHandler
	void onCursorPosChanged(GLFWwindow* window, double x, double y) override;
};


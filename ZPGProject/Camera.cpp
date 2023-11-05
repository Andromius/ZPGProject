#include "Camera.h"
#include "Events/Messages/Message.h"

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, float fov, float sens, std::shared_ptr<Window> window)
{
	_eye = eye;
	_target = target;
	_up = up;
	_fov = fov;
	_pitch = -90.f;
	_yaw = -90.f;
	_sens = sens;
	_window = window;
	_canTurn = false;
	_window->subscribe(this);

	ScreenDimensions& dimensions = window->getDimensions();
	_cursorPosX = dimensions.width / float(2);
	_cursorPosY = dimensions.height / float(2);
	onWindowSizeChanged(dimensions);
}

Camera::~Camera()
{
	_window->unsubscribe(this);
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(_eye, _target + _eye, _up);
}

glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(glm::radians(_fov), _aspectRatio, 0.1f, 100.0f);
}

glm::vec3 Camera::getEye()
{
	return _eye;
}

void Camera::attachLight(std::shared_ptr<SpotLight> light)
{
	_light = light;
	_light->setPosition(getEye());
	_light->setDirection(_target);
}

void Camera::onWindowSizeChanged(ScreenDimensions& dimensions)
{
	if (dimensions.height == 0) return;

	_aspectRatio = float(dimensions.width) / float(dimensions.height);
	notify(&CameraEventHandler::onCameraProjectionMatrixChanged, getProjectionMatrix());
}

void Camera::onKey(GLFWwindow* window)
{
	float moveSpeed = 0.05f;
	bool keyPressed = false;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_eye.x += moveSpeed * cos(glm::radians(_yaw));
		_eye.z += moveSpeed * sin(glm::radians(_yaw));
		keyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_eye.x -= moveSpeed * cos(glm::radians(_yaw));
		_eye.z -= moveSpeed * sin(glm::radians(_yaw));
		keyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_eye.x -= moveSpeed * sin(glm::radians(_yaw));
		_eye.z += moveSpeed * cos(glm::radians(_yaw));
		keyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_eye.x += moveSpeed * sin(glm::radians(_yaw));
		_eye.z -= moveSpeed * cos(glm::radians(_yaw));
		keyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_eye.y += moveSpeed;
		keyPressed = true;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		_eye.y -= moveSpeed;
		keyPressed = true;
	}

	if (keyPressed)
	{
		_light->setPosition(_eye);
		notify(&CameraEventHandler::onCameraPositionChanged, getEye());
		notify(&CameraEventHandler::onCameraViewMatrixChanged, getViewMatrix());
	}
}

void Camera::onCursorPositionChanged(CursorPos& cursorPos)
{
	if (!_canTurn) return;

	float xOffset = (float(cursorPos.x) - _cursorPosX) * _sens;
	float yOffset = (_cursorPosY - float(cursorPos.y)) * _sens;
	_cursorPosX = float(cursorPos.x);
	_cursorPosY = float(cursorPos.y);

	_pitch += yOffset;
	_yaw += xOffset;
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	_target.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_target.y = sin(glm::radians(_pitch));
	_target.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_light->setDirection(_target);
	notify(&CameraEventHandler::onCameraViewMatrixChanged, getViewMatrix());
}

void Camera::onMouseButton(GLFWwindow* window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPos(window, _cursorPosX, _cursorPosY);
		_canTurn = true;
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		_canTurn = false;
	}
}
#include "Camera.h"
#include "Events/Messages/Message.h"

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, float fov, float sens, std::shared_ptr<Window> window)
{
	_eye = eye;
	_target = target;
	_up = up;
	_fov = fov;
	_cursorPosX = window->getWidth() / float(2);
	_cursorPosY = window->getHeight() / float(2);
	_pitch = -90.f;
	_yaw = -90.f;
	_sens = sens;
	_window = window;
	_canTurn = false;
	_window->subscribe(this);
	onWindowSizeChanged(_window->getWidth(), _window->getHeight());
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

void Camera::onWindowSizeChanged(int width, int height)
{
	if (height == 0) return;

	_aspectRatio = float(width) / float(height);
	notify(CAM_PROJ_MAT_CHANGED);
}

void Camera::onKey(GLFWwindow* window)
{
	float moveSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_eye.x += moveSpeed * cos(glm::radians(_yaw));
		_eye.z += moveSpeed * sin(glm::radians(_yaw));
		notify(CAM_POSITION_CHANGED | CAM_VIEW_MAT_CHANGED);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_eye.x -= moveSpeed * cos(glm::radians(_yaw));
		_eye.z -= moveSpeed * sin(glm::radians(_yaw));
		notify(CAM_POSITION_CHANGED | CAM_VIEW_MAT_CHANGED);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_eye.x -= moveSpeed * sin(glm::radians(_yaw));
		_eye.z += moveSpeed * cos(glm::radians(_yaw));
		notify(CAM_POSITION_CHANGED | CAM_VIEW_MAT_CHANGED);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_eye.x += moveSpeed * sin(glm::radians(_yaw));
		_eye.z -= moveSpeed * cos(glm::radians(_yaw));
		notify(CAM_POSITION_CHANGED | CAM_VIEW_MAT_CHANGED);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		_eye.y += moveSpeed;
		notify(CAM_POSITION_CHANGED | CAM_VIEW_MAT_CHANGED);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		_eye.y -= moveSpeed;
		notify(CAM_POSITION_CHANGED | CAM_VIEW_MAT_CHANGED);
	}
}

void Camera::onCursorPositionChanged(CursorPos cursorPos)
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

	notify(CAM_VIEW_MAT_CHANGED);
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

void Camera::notify(int message)
{
	for (auto& subscriber : _subscribers)
	{
		if (message & CAM_POSITION_CHANGED)
			subscriber->onCameraPositionChanged(getEye());
		
		if (message & CAM_PROJ_MAT_CHANGED)
			subscriber->onCameraProjectionMatrixChanged(getProjectionMatrix());

		if (message & CAM_VIEW_MAT_CHANGED)
			subscriber->onCameraViewMatrixChanged(getViewMatrix());
	}
}

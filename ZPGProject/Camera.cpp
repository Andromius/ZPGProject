#include "Camera.h"

Camera::Camera(glm::vec3 eye, glm::vec3 target, glm::vec3 up, float fov, float width, float height, float sens)
{
	_eye = eye;
	_target = target;
	_up = up;
	_fov = fov;
	_cursorPosX = width / 2;
	_cursorPosY = height / 2;
	_aspectRatio = width / height;
	_pitch = -90.f;
	_yaw = -90.f;
	_sens = sens;
	EventNotifier::GetInstance()->subscribeWindowSizeChanged(this);
	EventNotifier::GetInstance()->subscribeKey(this);
	EventNotifier::GetInstance()->subscribeCursorPosChanged(this);
}

Camera::~Camera()
{
	EventNotifier::GetInstance()->unsubscribeWindowSizeChanged(this);
	EventNotifier::GetInstance()->unsubscribeKey(this);
	EventNotifier::GetInstance()->unsubscribeCursorPosChanged(this);
}

glm::mat4 Camera::getCamera()
{
	return glm::lookAt(_eye, _target + _eye, _up);
}

glm::mat4 Camera::getPerspective()
{
	return glm::perspective(_fov, _aspectRatio, 0.1f, 100.0f);
}

void Camera::onWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	_aspectRatio = float(width) / float(height);
	notify();
}

void Camera::notify()
{
	for (auto& subsriber : _subscribers)
	{
		subsriber->onCameraChanged();
	}
}

void Camera::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	float moveSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_eye.x += moveSpeed * cos(glm::radians(_yaw));
		_eye.z += moveSpeed * sin(glm::radians(_yaw));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_eye.x -= moveSpeed * cos(glm::radians(_yaw));
		_eye.z -= moveSpeed * sin(glm::radians(_yaw));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_eye.x -= moveSpeed * sin(glm::radians(_yaw));
		_eye.z += moveSpeed * cos(glm::radians(_yaw));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_eye.x += moveSpeed * sin(glm::radians(_yaw));
		_eye.z -= moveSpeed * cos(glm::radians(_yaw));
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) _eye.y += moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) _eye.y -= moveSpeed;
	notify();
}

void Camera::onCursorPosChanged(GLFWwindow* window, double x, double y)
{
	float xOffset = (float(x) - _cursorPosX) * _sens;
	float yOffset = (_cursorPosY - float(y)) * _sens;
	_cursorPosX = float(x);
	_cursorPosY = float(y);

	_pitch += yOffset;
	_yaw += xOffset;
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;

	_target.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_target.y = sin(glm::radians(_pitch));
	_target.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	notify();
}



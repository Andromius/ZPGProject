#include "Window.h"

void Window::setHints()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
		GLFW_OPENGL_CORE_PROFILE);
}

void Window::initializeEvents()
{
	EventNotifier::getInstance().subscribeWindowSizeChanged(this);
	EventNotifier::getInstance().subscribeWindowIconifyChanged(this);
	EventNotifier::getInstance().subscribeWindowFocusChanged(this);
	EventNotifier::getInstance().subscribeKey(this);

	glfwSetWindowSizeCallback(window, EventNotifier::notifyWindowSizeChanged);
	glfwSetWindowIconifyCallback(window, EventNotifier::notifyWindowIconifyChanged);
	glfwSetWindowFocusCallback(window, EventNotifier::notifyWindowFocusChanged);
	glfwSetMouseButtonCallback(window, EventNotifier::notifyMouseButton);
	glfwSetCursorPosCallback(window, EventNotifier::notifyCursorPosChanged);
	glfwSetKeyCallback(window, EventNotifier::notifyKey);
}

Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	window = glfwCreateWindow(width, height, title, monitor, share);
	initializeEvents();
}

Window::~Window()
{
	unsubscribe();
	glfwDestroyWindow(window);
}

void Window::setAsCurrentContext()
{
	glfwMakeContextCurrent(window);
}

GLFWwindow* Window::get()
{
	return window;
}

#pragma region EventHandlers
void Window::onWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Window::onWindowIconifyChanged(GLFWwindow* window, int iconified)
{
	printf("iconfied: %d\n", iconified);
}

void Window::onWindowFocusChanged(GLFWwindow* window, int focused)
{
	printf("focused: %d\n", focused);
}

void Window::onKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}
#pragma endregion

void Window::unsubscribe()
{
	EventNotifier::getInstance().unsubscribeWindowSizeChanged(this);
	EventNotifier::getInstance().unsubscribeWindowIconifyChanged(this);
	EventNotifier::getInstance().unsubscribeWindowFocusChanged(this);
	EventNotifier::getInstance().unsubscribeKey(this);
}

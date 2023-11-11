#include "Window.h"

void Window::initializeEvents()
{
	glfwSetWindowSizeCallback(_window, glfwOnSizeChanged);
	glfwSetWindowIconifyCallback(_window, glfwOnIconifyChanged);
	glfwSetWindowFocusCallback(_window, glfwOnFocusedChanged);
	glfwSetMouseButtonCallback(_window, glfwOnMouseButton);
	glfwSetCursorPosCallback(_window, glfwOnCursorPosChanged);
	glfwSetKeyCallback(_window, glfwOnKey);
}

void Window::close()
{
	glfwSetWindowShouldClose(_window, 1);
}

void Window::setViewport()
{
	glViewport(0, 0, _dimensions.width, _dimensions.height);
}

void Window::glfwOnSizeChanged(GLFWwindow* window, int width, int height)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->_dimensions.width = width;
	w->_dimensions.height = height;
	w->setViewport();
	w->notify<ScreenDimensions&>(&WindowEventHandler::onWindowSizeChanged, w->_dimensions);
}

void Window::glfwOnIconifyChanged(GLFWwindow* window, int iconified)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->_iconified = iconified;
	w->notify(&WindowEventHandler::onWindowIconifyChanged, w->_iconified);
}

void Window::glfwOnFocusedChanged(GLFWwindow* window, int focused)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->_focused = focused;
	w->notify(&WindowEventHandler::onWindowFocusChanged, w->_focused);
}

void Window::glfwOnMouseButton(GLFWwindow* window, int button, int action, int mode)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->notify(&WindowEventHandler::onMouseButton, w->_window);
}

void Window::glfwOnCursorPosChanged(GLFWwindow* window, double x, double y)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->_cursorPos.x = x;
	w->_cursorPos.y = y;
	w->notify<CursorPos&>(&WindowEventHandler::onCursorPositionChanged, w->_cursorPos);
}

void Window::glfwOnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		w->close();
	w->notify(&WindowEventHandler::onKey, w->_window);
}


Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	_window = glfwCreateWindow(width, height, title, monitor, share);
	_dimensions.width = width;
	_dimensions.height = height;
	setViewport();
	glfwSetWindowUserPointer(_window, (void*)this);
	initializeEvents();
}

Window::~Window()
{
	glfwDestroyWindow(_window);
}

void Window::setAsCurrentContext()
{
	glfwMakeContextCurrent(_window);
}

#pragma region Getters
GLFWwindow* Window::getGLFWWindow()
{
	return _window;
}

ScreenDimensions& Window::getDimensions()
{
	return _dimensions;
}

bool Window::getIconified()
{
	return _iconified;
}

bool Window::getFocused()
{
	return _focused;
}

CursorPos Window::getCursorPos()
{
	return _cursorPos;
}
#pragma endregion

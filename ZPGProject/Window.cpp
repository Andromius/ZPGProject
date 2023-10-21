#include "Window.h"
#include "Events/Messages/Message.h"

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
	glViewport(0, 0, _width, _height);
}

void Window::glfwOnSizeChanged(GLFWwindow* window, int width, int height)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->_width = width;
	w->_height = height;
	w->setViewport();
	w->notify(WIN_SIZE_CHANGED);
}

void Window::glfwOnIconifyChanged(GLFWwindow* window, int iconified)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->_iconified = iconified;
	w->notify(WIN_ICONIFY_CHANGED);
}

void Window::glfwOnFocusedChanged(GLFWwindow* window, int focused)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->_focused = focused;
	w->notify(WIN_FOCUS_CHANGED);
}

void Window::glfwOnMouseButton(GLFWwindow* window, int button, int action, int mode)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->notify(WIN_MOUSE_BUTTON);
}

void Window::glfwOnCursorPosChanged(GLFWwindow* window, double x, double y)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;

	w->_cursorPos.x = x;
	w->_cursorPos.y = y;
	w->notify(WIN_CURSOR_POS_CHANGED);
}

void Window::glfwOnKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Window* w = (Window*)(glfwGetWindowUserPointer(window));
	if (w == nullptr) return;
	
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		w->close();

	w->notify(WIN_KEYBOARD_KEY);
}


Window::Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share)
{
	_window = glfwCreateWindow(width, height, title, monitor, share);
	_width = width;
	_height = height;
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

int Window::getWidth()
{
	return _width;
}

int Window::getHeight()
{
	return _height;
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

void Window::notify(int message)
{
	for (auto& subscriber : _subscribers)
	{
		if (message & WIN_CURSOR_POS_CHANGED)
			subscriber->onCursorPositionChanged(_cursorPos);

		if (message & WIN_FOCUS_CHANGED)
			subscriber->onWindowFocusChanged(_focused);

		if (message & WIN_ICONIFY_CHANGED)
			subscriber->onWindowIconifyChanged(_iconified);

		if (message & WIN_KEYBOARD_KEY)
			subscriber->onKey(_window);

		if (message & WIN_MOUSE_BUTTON)
			subscriber->onMouseButton(_window);

		if (message & WIN_SIZE_CHANGED)
			subscriber->onWindowSizeChanged(_width, _height);
	}
}

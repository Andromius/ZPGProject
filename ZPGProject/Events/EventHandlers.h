#pragma once
#include <GLFW/glfw3.h>

class ErrorEventHandler
{
public:
	virtual void onError(int error, const char* description) = 0;
};

class WindowSizeChangedEventHandler
{
public:
	virtual void onWindowSizeChanged(GLFWwindow* window, int width, int height) = 0;
};

class WindowFocusChangedEventHandler
{
public:
	virtual void onWindowFocusChanged(GLFWwindow* window, int focused) = 0;
};

class WindowIconifyChangedEventHandler
{
public:
	virtual void onWindowIconifyChanged(GLFWwindow* window, int iconified) = 0;
};

class MouseButtonEventHandler
{
public:
	virtual void onMouseButton(GLFWwindow* window, int button, int action, int mode) = 0;
};

class CursorPosChangedEventHandler
{
public:
	virtual void onCursorPosChanged(GLFWwindow* window, double x, double y) = 0;
};

class KeyEventHandler
{
public:
	virtual void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) = 0;
};

class CameraChangedEventHandler
{
public:
	virtual void onCameraChanged() = 0;
};
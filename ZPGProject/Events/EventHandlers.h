#pragma once
#include <GLFW/glfw3.h>
#include <type_traits>
#include "CursorPos.h"

class EventHandler
{
public:
	virtual void onEvent(int message) = 0;
};

class WindowSizeChangedEventHandler
{
public:
	virtual void onWindowSizeChanged(int width, int height) = 0;
};

class MouseButtonEventHandler
{
public:
	virtual void onMouseButton(GLFWwindow* window) = 0;
};

class CursorPosChangedEventHandler
{
public:
	virtual void onCursorPosChanged(CursorPos cursorPos) = 0;
};

class KeyEventHandler
{
public:
	virtual void onKey(GLFWwindow* window) = 0;
};
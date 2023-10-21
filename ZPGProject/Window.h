#pragma once
#include <GLFW/glfw3.h>  
#include <stdio.h>
#include "Observables/ObservableObject.h"
#include "Events/CursorPos.h"

class Window :
	public ObservableObject
{
private:
	GLFWwindow* _window;
	int _width;
	int _height;
	bool _iconified;
	bool _focused;

	CursorPos _cursorPos;
	
	void initializeEvents();
	void close();

	static void glfwOnSizeChanged(GLFWwindow* window, int width, int height);
	static void glfwOnIconifyChanged(GLFWwindow* window, int iconified);
	static void glfwOnFocusedChanged(GLFWwindow* window, int focused);
	static void glfwOnMouseButton(GLFWwindow* window, int button, int action, int mode);
	static void glfwOnCursorPosChanged(GLFWwindow* window, double x, double y);
	static void glfwOnKey(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	~Window();
	
	void setAsCurrentContext();
	void setViewport();
	#pragma region Getters
	GLFWwindow* getGLFWWindow();
	int getWidth();
	int getHeight();
	bool getIconified();
	bool getFocused();
	CursorPos getCursorPos();
	#pragma endregion
};


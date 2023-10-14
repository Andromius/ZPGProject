#pragma once
#include <GLFW/glfw3.h>  
#include <stdio.h>
#include "Events/EventHandlers.h"
#include "Events/EventNotifier.h"

class Window : 
	public WindowSizeChangedEventHandler,
	public WindowIconifyChangedEventHandler,
	public WindowFocusChangedEventHandler,
	public KeyEventHandler
{
private:
	GLFWwindow* window;
	
	void setHints();
	void initializeEvents();
public:
	Window(int width, int height, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	~Window();
	
	void setAsCurrentContext();
	GLFWwindow* get();
	
#pragma region EventHandlers
	// Inherited via OnWindowSizeChangedHandler
	void onWindowSizeChanged(GLFWwindow* window, int width, int height) override;

	// Inherited via WindowIconifyChangedEventHandler
	void onWindowIconifyChanged(GLFWwindow* window, int iconified) override;

	// Inherited via WindowFocusChangedEventHandler
	void onWindowFocusChanged(GLFWwindow* window, int focused) override;

	// Inherited via KeyEventHandler
	void onKey(GLFWwindow* window, int key, int scancode, int action, int mods) override;
#pragma endregion
	void unsubscribe();
};


#pragma once
#include <vector>
#include "EventHandlers.h"
#include <algorithm>
#include <memory>

class EventNotifier
{
private:	
	std::vector<ErrorEventHandler*> _errorSubscribers;
	std::vector<WindowFocusChangedEventHandler*> _windowFocusChangedSubscribers;
	std::vector<WindowIconifyChangedEventHandler*> _windowIconifyChangedSubscribers;
	std::vector<WindowSizeChangedEventHandler*> _windowSizeChangedSubscribers;
	std::vector<MouseButtonEventHandler*> _mouseButtonSubscribers;
	std::vector<CursorPosChangedEventHandler*> _cursorPosChangedSubscribers;
	std::vector<KeyEventHandler*> _keySubscribers;

public:
	static EventNotifier& getInstance();
	EventNotifier();

#pragma region Notifications
	static void notifyError(int error, const char* description);
	static void notifyWindowFocusChanged(GLFWwindow* window, int focused);
	static void notifyWindowIconifyChanged(GLFWwindow* window, int iconified);
	static void notifyWindowSizeChanged(GLFWwindow* window, int width, int height);
	static void notifyMouseButton(GLFWwindow* window, int button, int action, int mode);
	static void notifyCursorPosChanged(GLFWwindow* window, double x, double y);
	static void notifyKey(GLFWwindow* window, int key, int scancode, int action, int mods);
#pragma endregion

#pragma region Subscriptions
	void subscribeError(ErrorEventHandler* handler);
	void subscribeWindowFocusChanged(WindowFocusChangedEventHandler* handler);
	void subscribeWindowIconifyChanged(WindowIconifyChangedEventHandler* handler);
	void subscribeWindowSizeChanged(WindowSizeChangedEventHandler* handler);
	void subscribeMouseButton(MouseButtonEventHandler* handler);
	void subscribeCursorPosChanged(CursorPosChangedEventHandler* handler);
	void subscribeKey(KeyEventHandler* handler);
#pragma endregion

#pragma region Unsubscriptions
	void unsubscribeError(ErrorEventHandler* handler);
	void unsubscribeWindowFocusChanged(WindowFocusChangedEventHandler* handler);
	void unsubscribeWindowIconifyChanged(WindowIconifyChangedEventHandler* handler);
	void unsubscribeWindowSizeChanged(WindowSizeChangedEventHandler* handler);
	void unsubscribeMouseButton(MouseButtonEventHandler* handler);
	void unsubscribeCursorPosChanged(CursorPosChangedEventHandler* handler);
	void unsubscribeKey(KeyEventHandler* handler);
#pragma endregion
};


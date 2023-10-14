#pragma once
#include <list>
#include "EventHandlers.h"
#include <algorithm>

class EventNotifier
{
private:
	static EventNotifier* _instance;
	
	std::list<ErrorEventHandler*> _errorSubscribers;
	std::list<WindowFocusChangedEventHandler*> _windowFocusChangedSubscribers;
	std::list<WindowIconifyChangedEventHandler*> _windowIconifyChangedSubscribers;
	std::list<WindowSizeChangedEventHandler*> _windowSizeChangedSubscribers;
	std::list<MouseButtonEventHandler*> _mouseButtonSubscribers;
	std::list<CursorPosChangedEventHandler*> _cursorPosChangedSubscribers;
	std::list<KeyEventHandler*> _keySubscribers;

public:
	static EventNotifier* GetInstance();
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


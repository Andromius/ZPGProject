#include "EventNotifier.h"

EventNotifier& EventNotifier::getInstance()
{
	static EventNotifier instance = EventNotifier();
	return instance;
}

EventNotifier::EventNotifier()
{
	_errorSubscribers = std::vector<ErrorEventHandler*>();
	_windowFocusChangedSubscribers = std::vector<WindowFocusChangedEventHandler*>();
	_windowIconifyChangedSubscribers = std::vector<WindowIconifyChangedEventHandler*>();
	_windowSizeChangedSubscribers = std::vector<WindowSizeChangedEventHandler*>();
	_mouseButtonSubscribers = std::vector<MouseButtonEventHandler*>();
	_cursorPosChangedSubscribers = std::vector<CursorPosChangedEventHandler*>();
	_keySubscribers = std::vector<KeyEventHandler*>();
}

#pragma region Notifications
void EventNotifier::notifyError(int error, const char* description)
{
	for (auto& handler : getInstance()._errorSubscribers)
	{
		handler->onError(error, description);
	}
}

void EventNotifier::notifyWindowFocusChanged(GLFWwindow* window, int focused)
{
	for (auto& handler : getInstance()._windowFocusChangedSubscribers)
	{
		handler->onWindowFocusChanged(window, focused);
	}
}

void EventNotifier::notifyWindowIconifyChanged(GLFWwindow* window, int iconified)
{
	for (auto& handler : getInstance()._windowIconifyChangedSubscribers)
	{
		handler->onWindowIconifyChanged(window, iconified);
	}
}

void EventNotifier::notifyWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	for (auto& handler : getInstance()._windowSizeChangedSubscribers)
	{
		handler->onWindowSizeChanged(window, width, height);
	}
}

void EventNotifier::notifyMouseButton(GLFWwindow* window, int button, int action, int mode)
{
	for (auto& handler : getInstance()._mouseButtonSubscribers)
	{
		handler->onMouseButton(window, button, action, mode);
	}
}

void EventNotifier::notifyCursorPosChanged(GLFWwindow* window, double x, double y)
{
	for (auto& handler : getInstance()._cursorPosChangedSubscribers)
	{
		handler->onCursorPosChanged(window, x, y);
	}
}

void EventNotifier::notifyKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (auto& handler : getInstance()._keySubscribers)
	{
		handler->onKey(window, key, scancode, action, mods);
	}
}
#pragma endregion

#pragma region Subscriptions
void EventNotifier::subscribeError(ErrorEventHandler* handler)
{
	_errorSubscribers.push_back(handler);
}

void EventNotifier::subscribeWindowFocusChanged(WindowFocusChangedEventHandler* handler)
{
	_windowFocusChangedSubscribers.push_back(handler);
}

void EventNotifier::subscribeWindowIconifyChanged(WindowIconifyChangedEventHandler* handler)
{
	_windowIconifyChangedSubscribers.push_back(handler);
}

void EventNotifier::subscribeWindowSizeChanged(WindowSizeChangedEventHandler* handler)
{
	_windowSizeChangedSubscribers.push_back(handler);
}

void EventNotifier::subscribeMouseButton(MouseButtonEventHandler* handler)
{
	_mouseButtonSubscribers.push_back(handler);
}

void EventNotifier::subscribeCursorPosChanged(CursorPosChangedEventHandler* handler)
{
	_cursorPosChangedSubscribers.push_back(handler);
}

void EventNotifier::subscribeKey(KeyEventHandler* handler)
{
	_keySubscribers.push_back(handler);
}
#pragma endregion

#pragma region Unsubscriptions
void EventNotifier::unsubscribeError(ErrorEventHandler* handler)
{
	_errorSubscribers.erase(std::remove_if(_errorSubscribers.begin(), _errorSubscribers.end(), [&](ErrorEventHandler* h) { return h == handler; }));
}

void EventNotifier::unsubscribeWindowFocusChanged(WindowFocusChangedEventHandler* handler)
{
	_windowFocusChangedSubscribers.erase(std::remove_if(_windowFocusChangedSubscribers.begin(), _windowFocusChangedSubscribers.end(), [&](WindowFocusChangedEventHandler* h) { return h == handler; }));
}

void EventNotifier::unsubscribeWindowIconifyChanged(WindowIconifyChangedEventHandler* handler)
{
	_windowIconifyChangedSubscribers.erase(std::remove_if(_windowIconifyChangedSubscribers.begin(), _windowIconifyChangedSubscribers.end(), [&](WindowIconifyChangedEventHandler* h) { return h == handler; }));
}

void EventNotifier::unsubscribeWindowSizeChanged(WindowSizeChangedEventHandler* handler)
{
	_windowSizeChangedSubscribers.erase(std::remove_if(_windowSizeChangedSubscribers.begin(), _windowSizeChangedSubscribers.end(), [&](WindowSizeChangedEventHandler* h) { return h == handler; }));
}

void EventNotifier::unsubscribeMouseButton(MouseButtonEventHandler* handler)
{
	_mouseButtonSubscribers.erase(std::remove_if(_mouseButtonSubscribers.begin(), _mouseButtonSubscribers.end(), [&](MouseButtonEventHandler* h) { return h == handler; }));
}

void EventNotifier::unsubscribeCursorPosChanged(CursorPosChangedEventHandler* handler)
{
	_cursorPosChangedSubscribers.erase(std::remove_if(_cursorPosChangedSubscribers.begin(), _cursorPosChangedSubscribers.end(), [&](CursorPosChangedEventHandler* h) { return h == handler; }));
}

void EventNotifier::unsubscribeKey(KeyEventHandler* handler)
{
	_keySubscribers.erase(std::remove_if(_keySubscribers.begin(), _keySubscribers.end(), [&](KeyEventHandler* h) { return h == handler; }));
}
#pragma endregion

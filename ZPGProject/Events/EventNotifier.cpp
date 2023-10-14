#include "EventNotifier.h"

EventNotifier* EventNotifier::_instance = new EventNotifier();

EventNotifier* EventNotifier::GetInstance()
{
	return _instance;
}

EventNotifier::EventNotifier()
{
	_errorSubscribers = std::list<ErrorEventHandler*>();
	_windowFocusChangedSubscribers = std::list<WindowFocusChangedEventHandler*>();
	_windowIconifyChangedSubscribers = std::list<WindowIconifyChangedEventHandler*>();
	_windowSizeChangedSubscribers = std::list<WindowSizeChangedEventHandler*>();
	_mouseButtonSubscribers = std::list<MouseButtonEventHandler*>();
	_cursorPosChangedSubscribers = std::list<CursorPosChangedEventHandler*>();
	_keySubscribers = std::list<KeyEventHandler*>();
}

#pragma region Notifications
void EventNotifier::notifyError(int error, const char* description)
{
	for (auto handler : GetInstance()->_errorSubscribers)
	{
		handler->onError(error, description);
	}
}

void EventNotifier::notifyWindowFocusChanged(GLFWwindow* window, int focused)
{
	for (auto handler : GetInstance()->_windowFocusChangedSubscribers)
	{
		handler->onWindowFocusChanged(window, focused);
	}
}

void EventNotifier::notifyWindowIconifyChanged(GLFWwindow* window, int iconified)
{
	for (auto handler : GetInstance()->_windowIconifyChangedSubscribers)
	{
		handler->onWindowIconifyChanged(window, iconified);
	}
}

void EventNotifier::notifyWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	for (auto handler : GetInstance()->_windowSizeChangedSubscribers)
	{
		handler->onWindowSizeChanged(window, width, height);
	}
}

void EventNotifier::notifyMouseButton(GLFWwindow* window, int button, int action, int mode)
{
	for (auto handler : GetInstance()->_mouseButtonSubscribers)
	{
		handler->onMouseButton(window, button, action, mode);
	}
}

void EventNotifier::notifyCursorPosChanged(GLFWwindow* window, double x, double y)
{
	for (auto handler : GetInstance()->_cursorPosChangedSubscribers)
	{
		handler->onCursorPosChanged(window, x, y);
	}
}

void EventNotifier::notifyKey(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	for (auto handler : GetInstance()->_keySubscribers)
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
	_errorSubscribers.remove(handler);
}

void EventNotifier::unsubscribeWindowFocusChanged(WindowFocusChangedEventHandler* handler)
{
	_windowFocusChangedSubscribers.remove(handler);
}

void EventNotifier::unsubscribeWindowIconifyChanged(WindowIconifyChangedEventHandler* handler)
{
	_windowIconifyChangedSubscribers.remove(handler);
}

void EventNotifier::unsubscribeWindowSizeChanged(WindowSizeChangedEventHandler* handler)
{
	_windowSizeChangedSubscribers.remove(handler);
}

void EventNotifier::unsubscribeMouseButton(MouseButtonEventHandler* handler)
{
	_mouseButtonSubscribers.remove(handler);
}

void EventNotifier::unsubscribeCursorPosChanged(CursorPosChangedEventHandler* handler)
{
	_cursorPosChangedSubscribers.remove(handler);
}

void EventNotifier::unsubscribeKey(KeyEventHandler* handler)
{
	_keySubscribers.remove(handler);
}
#pragma endregion

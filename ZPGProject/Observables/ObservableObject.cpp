#include "ObservableObject.h"

void ObservableObject::notify(int message)
{
	for (auto& subscriber : _subscribers)
	{
		subscriber->onEvent(message);
	}
}

void ObservableObject::subscribe(EventHandler* handler)
{
	_subscribers.push_back(handler);
}

void ObservableObject::unsubscribe(EventHandler* handler)
{
	_subscribers.erase(std::remove_if(_subscribers.begin(), _subscribers.end(), [&](EventHandler* h) { return h == handler; }));
}

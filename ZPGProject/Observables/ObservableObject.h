#pragma once
#include <memory>
#include <vector>
#include "Events/EventHandlers.h"

class ObservableObject
{
protected:
	std::vector<EventHandler*> _subscribers;
	virtual void notify(int message);

public:
	void subscribe(EventHandler* handler);
	void unsubscribe(EventHandler* handler);
};

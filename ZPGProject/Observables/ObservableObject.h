#pragma once
#include <list>

template <typename TEventHandler>
class ObservableObject
{
protected:
	std::list<TEventHandler*> _subscribers;
	virtual void notify() = 0;

public:
	void subscribe(TEventHandler* handler);
	void unsubscribe(TEventHandler* handler);
};

template<typename TEventHandler>
inline void ObservableObject<TEventHandler>::subscribe(TEventHandler* handler)
{
	_subscribers.push_back(handler);
}

template<typename TEventHandler>
inline void ObservableObject<TEventHandler>::unsubscribe(TEventHandler* handler)
{
	_subscribers.remove(handler);
}

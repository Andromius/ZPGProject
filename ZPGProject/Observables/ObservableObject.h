#pragma once
#include <memory>
#include <vector>

template <typename TEventHandler>
class ObservableObject
{
protected:
	std::vector<TEventHandler*> _subscribers;
	
	template<typename... TArgs>
	void notify(void (TEventHandler::* func)(TArgs...), TArgs... args);

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
	_subscribers.erase(std::remove_if(_subscribers.begin(), _subscribers.end(), [&](TEventHandler* h) { return h == handler; }));
}

template<typename TEventHandler>
template<typename... TArgs>
inline void ObservableObject<TEventHandler>::notify(void(TEventHandler::* func)(TArgs...), TArgs... args)
{
	for (auto& subscriber : _subscribers)
	{
		(subscriber->*func)(args...);
	}
}

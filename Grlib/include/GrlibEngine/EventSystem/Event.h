#pragma once
#include <list>

#include "GrlibEngine/EventSystem/FunctorEventHandler.h"

// Class of abstract event
template <class ...TParams>
class Event {
public:
	// Create event
	Event();

	// Execute all subscribed event handlers
	void execute(TParams... params) const;

	// Subscribe functor
	template<class TFunctor>
	void add_func(TFunctor* func);

private:
	// List of event handlers
	std::list<AbstractEventHandler<TParams...>*> _handler_list;
};

#include "GrlibEngine/EventSystem/Event.tpp"
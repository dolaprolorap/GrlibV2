#pragma once
#include <list>

#include "GrlibEngine/Property.h"

// Class-interface of event handler
template <class ...TParams>
class AbstractEventHandler {
public:
	// Execute all properties binded to this event handler
	virtual void call(TParams... params);

protected:
	// First init
	AbstractEventHandler();
};

#include "AbstractEventHandler.tpp"
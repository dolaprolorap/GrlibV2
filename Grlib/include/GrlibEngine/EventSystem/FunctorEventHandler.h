#pragma once
#include <list>

#include "GrlibEngine/EventSystem/AbstractEventHandler.h"

// Event handler, using functors as handler
template<class TFunctor, class ...TParams>
class FunctorEventHandler : public AbstractEventHandler<TParams...> {
public:
	// Overrided call function
	void call(TParams... params) override;

	// Create handler for functor func
	FunctorEventHandler(TFunctor* func);

private:
	// Func of the handler
	TFunctor* _func;
};

#include "GrlibEngine/EventSystem/FunctorEventHandler.tpp"
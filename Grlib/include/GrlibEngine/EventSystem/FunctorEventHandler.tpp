#include "GrlibEngine/EventSystem/FunctorEventHandler.h"

template<class TFunctor, class ...TParams>
FunctorEventHandler<TFunctor, TParams...>::FunctorEventHandler(TFunctor* func) : AbstractEventHandler<TParams...>() { 
	this->_func = func;
}

template<class TFunctor, class ...TParams>
void FunctorEventHandler<TFunctor, TParams...>::call(TParams... params) {
	(*this->_func)(params...);
}
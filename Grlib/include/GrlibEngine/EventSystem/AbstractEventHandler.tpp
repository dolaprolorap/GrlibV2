#pragma once 
#include "GrlibEngine/EventSystem/AbstractEventHandler.h"

template <class ...TParams>
void AbstractEventHandler<TParams...>::call(TParams... params)  { }

template <class ...TParams>
AbstractEventHandler<TParams...>::AbstractEventHandler() { }
#pragma once
#include "GrlibExceptions/GrlibException.h"

class EventSystemException : GrlibException {
public:
	EventSystemException(const char* str);
};
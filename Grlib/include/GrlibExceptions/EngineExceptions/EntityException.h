#pragma once
#include "GrlibExceptions/GrlibException.h"

class EntityException : GrlibException {
public:
	EntityException(const char* str);
};
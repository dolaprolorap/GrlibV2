#pragma once
#include "GrlibExceptions/GrlibException.h"

class IdentifierException : GrlibException {
public:
	IdentifierException(const char* str);
};
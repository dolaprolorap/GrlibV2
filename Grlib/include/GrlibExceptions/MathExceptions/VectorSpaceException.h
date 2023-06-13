#pragma once
#include "GrlibExceptions/GrlibException.h"

class VectorSpaceException : GrlibException {
public:
	VectorSpaceException(const char* str);
};
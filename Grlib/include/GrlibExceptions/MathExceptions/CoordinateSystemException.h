#pragma once
#include "GrlibExceptions/GrlibException.h"

class CoordinateSystemException : GrlibException {
public:
	CoordinateSystemException(const char* str);
};
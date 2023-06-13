#pragma once
#include "GrlibExceptions/GrlibException.h"

class PointException : GrlibException {
public:
	PointException(const char* str);
};
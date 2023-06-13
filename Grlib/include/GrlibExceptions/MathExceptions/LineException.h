#pragma once
#include "GrlibExceptions/GrlibException.h"

class LineException : GrlibException {
public:
	LineException(const char* str);
};
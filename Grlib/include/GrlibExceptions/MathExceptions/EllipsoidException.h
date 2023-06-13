#pragma once
#include "GrlibExceptions/GrlibException.h"

class EllipsoidException : GrlibException {
public:
	EllipsoidException(const char* str);
};
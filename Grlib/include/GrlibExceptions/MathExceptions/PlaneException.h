#pragma once
#include "GrlibExceptions/GrlibException.h"

class PlaneException : GrlibException {
public:
	PlaneException(const char* str);
};
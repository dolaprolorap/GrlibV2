#pragma once
#include "GrlibExceptions/GrlibException.h"

class GeomOperationsException : GrlibException {
public:
	GeomOperationsException(const char* str);
};
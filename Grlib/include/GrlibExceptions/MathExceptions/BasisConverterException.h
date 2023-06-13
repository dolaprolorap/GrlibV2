#pragma once
#include "GrlibExceptions/GrlibException.h"

class BasisConverterException : GrlibException {
public:
	BasisConverterException(const char* str);
};
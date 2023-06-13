#pragma once
#include "GrlibExceptions/GrlibException.h"

class BilinearFormException : GrlibException {
public:
	BilinearFormException(const char* str);
};
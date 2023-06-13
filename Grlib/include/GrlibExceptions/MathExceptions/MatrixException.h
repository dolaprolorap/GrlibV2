#pragma once
#include "GrlibExceptions/GrlibException.h"

class MatrixException : GrlibException {
public:
	MatrixException(const char* str);
};
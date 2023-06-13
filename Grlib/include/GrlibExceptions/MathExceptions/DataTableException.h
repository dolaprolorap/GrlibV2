#pragma once
#include "GrlibExceptions/GrlibException.h"

class DataTableException : GrlibException {
public:
	DataTableException(const char* str);
};
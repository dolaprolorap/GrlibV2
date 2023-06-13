#pragma once
#include "GrlibExceptions/GrlibException.h"

class ConsoleDrawException : GrlibException {
public:
	ConsoleDrawException(const char* str);
};
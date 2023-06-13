#pragma once
#include "GrlibExceptions/GrlibException.h"

class SceneException : GrlibException {
public:
	SceneException(const char* str);
};
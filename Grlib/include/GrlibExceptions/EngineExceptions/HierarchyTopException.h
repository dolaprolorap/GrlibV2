#pragma once
#include "GrlibExceptions/GrlibException.h"

class HierarchyTopException : GrlibException {
public:
	HierarchyTopException(const char* str);
};
#include "GrlibExceptions/GrlibException.h"

GrlibException::GrlibException(const char* str) : std::exception(str) {}
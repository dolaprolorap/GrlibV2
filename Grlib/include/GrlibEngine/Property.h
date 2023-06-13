#pragma once
#include <string>

// Property with executable logic
class Property  {
public:
	// Create property
	Property();

	// Execute property logic
	void virtual execute();
};
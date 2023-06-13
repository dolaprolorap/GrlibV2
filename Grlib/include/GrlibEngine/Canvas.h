#pragma once
#include <iterator>

#include "GrlibMath/DataTable.h"

// Canvas with result of rendering
class Canvas : public DataTable {
public:
	// Create canvas with `rows` rows and `width` width
	Canvas(int rows, int columns);

	// Returns number of cells in the canvas
	int get_size() const;
};
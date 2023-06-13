#pragma once
#include "Point.h"
#include "VectorSpace.h"

// Class-container for coordinate system
class CoordinateSystem {
public:
	// Returns 0 point
	Point& get_init_point();

	// Create coordinate system with `init_point`
	CoordinateSystem(const Point& init_point);

private:
	// 0 point of coordinate system
	Point* _init_point;
};
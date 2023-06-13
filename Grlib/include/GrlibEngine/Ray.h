#pragma once
#include "GrlibMath/Vector.h"
#include "GrlibMath/Line.h"
#include "GrlibMath/Point.h"

// Class of ray
class Ray {
public:
	// Construct ray by direction vector 
	Ray(Vector dir_vector, Point init_point);

	// Copy constructor
	Ray(const Ray& ray);

	// Get direction vector of ray (normalized)
	Vector get_dir_vector() const;

	// Get init point of this ray
	Point get_init_point() const;

	// Get lay on line
	Line get_line() const;

private:
	// Normalized vector of ray
	Vector _dir_normalized_vector;

	// Init point of ray
	Point _init_point;
};
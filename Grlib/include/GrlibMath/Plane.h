#pragma once 
#include "GrlibMath/Vector.h"
#include "GrlibMath/Point.h"

#include "GrlibExceptions/MathExceptions/PlaneException.h"

// Class of plane
class Plane {
public:
	// Create plane by normal `normal_vector`, going through zero point
	Plane(const Vector& normal_vector);
	// Create plane by normal `normal_vector`, going through `init_point`
	Plane(const Vector& normal_vector, const Point& init_point);

	// Returns dimension of plane
	int get_dim() const;

	// Returns normal of this plane
	Vector get_normal_vector() const;
	// Returns normal of this plane
	Point get_init_point() const;

	// Rotate plane on `x`, `y` and `z` angles
	void rotate_3d(double x, double y, double z);
	// Rotate plane in the plane on angle `angle`
	void planar_rotate(int first_axis, int second_axis, double angle);

private:
	// Normal vector
	Vector _normal_vector;
	// Init point of this plane
	Point _init_point;
};
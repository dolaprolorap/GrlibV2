#pragma once 
#include "GrlibMath/Vector.h"
#include "GrlibMath/Plane.h"
#include "GrlibMath/Point.h"

#include "GrlibExceptions/MathExceptions/LineException.h"

class Line {
public:
	// Create line, going through zero point, by dir vector `dir_vector`
	Line(const Vector& dir_vector);
	// Create line, going through point `init_point`, by dir vector `dir_vector`
	Line(const Vector& dir_vector, const Point& init_point);
	// Create line, going through `first_point` and	`second_point`. Throughs exception if points match each other
	Line(const Point& first_point, const Point& second_point);

	// Return dimension of this line
	int get_dim() const;

	// Returns dir vector of this line
	Vector get_dir_vector() const;
	// Returns init point of this line
	Point get_init_point() const;

	// Rotate line on `x`, `y` and `z` angles
	void rotate_3d(double x, double y, double z);
	// Rotate line in the plane on angle `angle`
	void planar_rotate(int first_axis, int second_axis, double angle);

private:
	// Dir vector of this line
	Vector _dir_vector;
	// Init point 
	Point _init_point;
};
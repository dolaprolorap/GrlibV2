#pragma once
#include <vector>

#include "GrlibMath/Line.h"
#include "GrlibMath/Plane.h"
#include "GrlibMath/Point.h"
#include "GrlibMath/Ellipsoid.h"

#include "GrlibExceptions/MathExceptions/GeomOperationsException.h"

// Class with static funcs for actions with geom figures
class GeomOperations {
public:
	// Returns intersection points of plane and line
	static std::vector<Point> intersect(const Plane& plane, const Line& line);
	// Returns intersection point of ellipsoid and line
	static std::vector<Point> intersect(Ellipsoid ellipsoid, const Line& line);

	// Returns intersection line of two planes
	static Vector get_intersect_vector(const Plane& plane1, const Plane& plane2);

	// Checks if plane is orthogonal to line
	static bool is_orth(const Plane& plane, const Line& line);

	// Checks if two lines are parallel
	static bool is_parallel(const Line& line1, const Line& line2);
	// Checks if two planes are parallel
	static bool is_parallel(const Plane& plane1, const Plane& plane2);
	// Checks if two vectors lay on the same line (parallel)
	static bool is_parallel(const Vector& vector1, const Vector& vector2);

	// Rotate ellipsoid on `x`, `y` and `z` angles
	static void rotate_3d(Ellipsoid& ellipsoid, double x, double y, double z);
	// Rotate ellipsoid in the plane on angle `angle`
	static void planar_rotate(Ellipsoid& ellipsoid, int first_axis, int second_axis, double angle);
};
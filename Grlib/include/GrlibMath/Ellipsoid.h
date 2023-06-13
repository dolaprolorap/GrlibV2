#pragma once
#include <initializer_list>

#include "GrlibMath/Vector.h"
#include "GrlibMath/Point.h"

#include "GrlibExceptions/MathExceptions/EllipsoidException.h"

// Ñlass that provides methods for working with an ellipsoid 
class Ellipsoid {
public:
	// Create ellipsoid by its semiaxis with the center at zero point. They must form basis, otherwise EllipsoidException will be thrown
	Ellipsoid(const std::initializer_list<double>& semiaxes_lens);
	// Create ellipsoid by its semiaxis with the center at `init_point`. They must form basis, otherwise EllipsoidException will be thrown
	Ellipsoid(const std::initializer_list<double>& semiaxes_lens, const Point& init_point);

	// Returns dimension of ellipsoid
	int get_dim() const;

	// Returns semiaxis of this ellipsoid
	std::vector<Vector> get_semiaxes() const;
	// Returns init point of this ellipsoid
	Point get_init_point() const;

	// Make GeomOperations class friend in order to manipulate
	// inner state of ellipsoid
	friend class GeomOperations;
	
private:
	// Initializer list of ellipsoid axis
	std::vector<Vector> _semiaxes;
	// Ellipsoid center point
	Point _init_point;
};
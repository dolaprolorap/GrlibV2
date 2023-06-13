#pragma once
#include <initializer_list>

#include "GrlibMath/CoordinateSystem.h"
#include "GrlibMath/Plane.h"
#include "GrlibMath/GeomOperations.h"

#include "GrlibExceptions/MathExceptions/BasisConverterException.h"

// Static class for creating and converting bases
class BasisConverter {
public:
	// Create 3 dimension basis including `basis_vector` and other vectors of the basis
	// have length of `basis_vector`
	static std::vector<Vector> create_orth_3d(Vector basis_vector);

	// Create unit basis of dimension dim
	static std::vector<Vector>& create_unit(int dim);

	// Checks if `vectors` are lin independent. Throws BasisConverterException if vectors 
	static bool is_lin_independent(const std::initializer_list<Vector>& vectors);

private:

};
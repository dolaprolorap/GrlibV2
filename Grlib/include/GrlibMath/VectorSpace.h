#pragma once
#include <vector>

#include "GrlibMath/Vector.h"

#include "GrlibExceptions/math_exceptions.h"

class Vector;

// Class-container for basis
class VectorSpace {
public:
	// Creates vector space with basis vectors `basis_vectors`
	VectorSpace(const std::vector<Vector>& basis_vectors);
	// Creates vector space of dimension `dim`, constructed by unit vectors
	VectorSpace(int dim);

	// Returns dimension count of this space
	int get_dim() const;
	// Returns copy of basis vectors
	std::vector<Vector>& get_basis() const;
private:
	// Dim count of this space
	int dim;
	// Basis vectors 
	std::vector<Vector> basis_vectors;
};
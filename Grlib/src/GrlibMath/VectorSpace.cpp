#include "GrlibMath/VectorSpace.h"

VectorSpace::VectorSpace(int dim) : basis_vectors(), dim(dim) {
	if (dim <= 0) {
		std::string err_str = "Wrong dim number: " + std::to_string(dim);
		throw VectorSpaceException(err_str.c_str());
	}

	for (int i = 0; i < dim; i++) {
		Vector basis_vec = *new Vector(dim);
		basis_vec(i) = 1;
		VectorSpace::basis_vectors.push_back(basis_vec);
	}
}

VectorSpace::VectorSpace(const std::vector<Vector>& basis_vectors) : basis_vectors(), dim(basis_vectors.size()) {
	if (basis_vectors.size() == 0) {
		std::string err_str = "Wrong dim number: " + basis_vectors.size();
		throw VectorSpaceException(err_str.c_str());
	}

	for (int i = 0; i < basis_vectors.size(); i++) {
		this->basis_vectors.push_back(basis_vectors[i]);
	}
}

std::vector<Vector>& VectorSpace::get_basis() const {
	std::vector<Vector>& basis_copy = *new std::vector<Vector>();
	for (auto& vec : basis_vectors) {
		basis_copy.push_back(vec);
	}
	return basis_copy;
}

int VectorSpace::get_dim() const {
	return this->dim;
}
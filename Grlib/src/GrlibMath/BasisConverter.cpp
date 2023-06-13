#include "GrlibMath/BasisConverter.h"

// ONLY FOR HOR ROT
std::vector<Vector> BasisConverter::create_orth_3d(Vector basis_vector) {
	if (basis_vector.length() < EPS) {
		throw BasisConverterException("basis_vector can not be 0 vector");
	}

	std::vector<Vector> basis;
	basis.push_back(basis_vector);
	basis.push_back(Matrix::z_rotation_matrix(90) * basis_vector);
	basis.push_back(Vector(0., 0., 1.));

	return basis;
}

/*std::vector<Vector> BasisConverter::create_orth_3d(Vector basis_vector) {
	if (basis_vector.length() < EPS) {
		throw BasisConverterException("basis_vector can not be 0 vector");
	}

	std::vector<Vector>& basis = *new std::vector<Vector>();
	Plane basis_plane(basis_vector);
	Plane zy_plane(Vector(1.0, 0.0, 0.0));

	double basis_vector_len = basis_vector.length();
	basis.push_back(Vector(basis_vector));

	if (!GeomOperations::is_parallel(basis_plane, zy_plane)) {
		Vector intersect_vector = GeomOperations::get_intersect_vector(zy_plane, basis_plane);
		intersect_vector.normalize();
		intersect_vector = intersect_vector * basis_vector_len;
		Vector orth_vector = (basis_vector ^ intersect_vector) * (-1);
		orth_vector.normalize();
		orth_vector = orth_vector * basis_vector_len;
		basis.push_back(orth_vector);
		basis.push_back(intersect_vector);
	}
	else {
		basis.push_back(Vector(.0, basis_vector_len, .0));
		basis.push_back(Vector(.0, .0, basis_vector_len));
	}

	for (auto vec : basis) {
		std::cout << vec << std::endl;
	}

	return basis;
}*/

std::vector<Vector>& BasisConverter::create_unit(int dim) {
	std::vector<Vector> basis = *new std::vector<Vector>();
	for (int i = 0; i < dim; i++) {
		basis.push_back(Vector(dim));
		basis[i].operator()(i) = 1;
	}
	return basis;
}

bool BasisConverter::is_lin_independent(const std::initializer_list<Vector>& vectors) {
	if (vectors.size() == 0) {
		throw BasisConverterException("There is no vectors to check for lin independence");
	}

	int vectors_dim = vectors.begin()->get_dim();
	Matrix vector_matrix((int)vectors.size(), (int)vectors.size());
	int i = 0;
	for (auto& vec : vectors) {
		vector_matrix.set_column(i++, vec);
		if (vectors_dim != vec.get_dim()) {
			throw BasisConverterException("Vector dimensions do not equal to each other");
		}
	}

	if (vectors_dim != vectors.size()) {
		throw BasisConverterException("Dimensions of vectors do not equal to the size of `vectors` list");
	}

	return fabs(vector_matrix.det()) < EPS;
}
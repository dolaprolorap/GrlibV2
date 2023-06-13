#include "GrlibMath/GlobalFunctions.h"

double bilinear_form(const Matrix& scalar_matrix, const Vector& v1, const Vector& v2) {
	if (v1.rows_count() != v2.rows_count() ||
		!scalar_matrix.is_square() ||
		scalar_matrix.rows_count() != v1.rows_count()) {
		std::string err_str = "Invalid sizes of operands: v1 height: " + std::to_string(v1.rows_count()) +
			" | v2 height: " + std::to_string(v2.rows_count()) + " | scalar_matrix: (" +
			std::to_string(scalar_matrix.rows_count()) + ", " + std::to_string(scalar_matrix.columns_count()) + ")";
		throw BilinearFormException(err_str.c_str());
	}

	int n = v1.rows_count();
	double res = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res += scalar_matrix(i, j) * v1(i) * v2(j);
		}
	}

	return res;
}

Matrix& gram_matrix(const std::vector<Vector>& basis_vectors) {
	int n = basis_vectors.size();

	Matrix& res_matrix = *new Matrix(n, n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			res_matrix(i, j) = basis_vectors[i] * basis_vectors[j];
		}
	}

	return res_matrix;
}

double rad_to_deg(double rad) {
	return (rad * 180.0) / PI;
}

double deg_to_rad(double deg) {
	return (deg * PI) / 180.0;
}
#include "GrlibMath/Matrix.h"

//-------------------------------------------------------------------------------------------
// public
//-------------------------------------------------------------------------------------------

bool Matrix::is_square() const {
	return this->columns_count() == this->rows_count();
}

Matrix::Matrix(int rows, int columns) : DataTable(rows, columns) { }

Matrix::Matrix(const Matrix& m) : DataTable(m) { }

Matrix::Matrix(const DataTable& dt) : DataTable(dt) { }

Matrix Matrix::operator+(const Matrix& m) const {
	if (!this->dim_equality(m)) {
		std::string err_str = "Different dimensions of matrices: this: (" + std::to_string(this->rows_count()) + "; "
			+ std::to_string(this->columns_count()) + ") | m: (" + std::to_string(m.rows_count()) + "; "
			+ std::to_string(m.columns_count()) + ")";
		throw MatrixException(err_str.c_str());
	}

	// TODO: is there a coping of the Matix?
	Matrix new_matrix(*this);

	for (int i = 0; i < m.rows_count(); i++) {
		for (int j = 0; j < m.columns_count(); j++) {
			new_matrix(i, j) += m(i, j);
		}
	}

	// TODO: is it returning copy of matrix or it itself
	return new_matrix;
}

Matrix Matrix::operator-(const Matrix& m) const {
	return (*this) + m * (-1.0);
}

Matrix Matrix::operator*(double sc) const {
	// TODO: is there a coping of the Matix?
	Matrix new_matrix(*this);

	for (int i = 0; i < this->rows_count(); i++) {
		for (int j = 0; j < this->columns_count(); j++) {
			new_matrix(i, j) *= sc;
		}
	}

	// TODO: is it returning copy of matrix or it itself
	return new_matrix;
}

Matrix Matrix::operator/(double sc) const {
	return (*this) * (1 / sc);
}

bool Matrix::operator==(const Matrix& m) const {
	return this->val_equality(m);
}

bool Matrix::operator!=(const Matrix& m) const {
	return !((*this) == m);
}

Matrix Matrix::operator*(const Matrix& m) const {
	if (m.rows_count() != this->columns_count()) {
		std::string err_str = "Invalid sizes of matrices for matrix product: this: (" + std::to_string(this->rows_count()) + "; "
			+ std::to_string(this->columns_count()) + ") | m: (" + std::to_string(m.rows_count()) + "; "
			+ std::to_string(m.columns_count()) + ")";
		throw MatrixException(err_str.c_str());
	}

	Matrix new_matrix(this->rows_count(), m.columns_count());

	for (int i = 0; i < this->rows_count(); i++) {
		for (int j = 0; j < m.columns_count(); j++) {
			new_matrix(i, j) = 0;
			for (int k = 0; k < this->columns_count(); k++) {
				new_matrix(i, j) += (*this)(i, k) * m(k, j);
			}
		}
	}

	return new_matrix;
}

double Matrix::det() {
	if (!this->is_square()) {
		std::string err_str = "Not square matrix for calculate det: this: (" + std::to_string(this->rows_count())
			+ "; " + std::to_string(this->columns_count()) + ")";
		throw MatrixException(err_str.c_str());
	}

	return (*this)._inner_det();
}

Matrix Matrix::inverse() {
	double det = (*this).det();
	if (det == 0) {
		throw MatrixException("Det of the matrix equals 0");
	}

	Matrix& new_matrix = *new Matrix(this->columns_count(), this->columns_count());

	for (int i = 0; i < this->rows_count(); i++) {
		for (int j = 0; j < this->columns_count(); j++) {
			new_matrix(i, j) = (*this)._delete_cross(i, j)._inner_det() * ((i + j) % 2 == 0 ? 1 : -1);
		}
	}

	return new_matrix.transpose() / det;
}

Matrix Matrix::transpose() {
	int tr_height = this->columns_count();
	int tr_width = this->rows_count();

	Matrix& new_matrix = *(new Matrix(tr_height, tr_width));

	for (int i = 0; i < this->rows_count(); i++) {
		for (int j = 0; j < this->columns_count(); j++) {
			new_matrix(j, i) = (*this)(i, j);
		}
	}

	return new_matrix;
}

double Matrix::cofactor(int row, int column) const {
	if (!this->is_square()) {
		throw MatrixException("Can not find cofactor of not square matrix");
	}

	if (row < 0 || column < 0 || row >= this->rows_count() || column >= this->columns_count()) {
		std::string err_str = "Wrong matrix index: index: (" + std::to_string(row) + "; " + std::to_string(column)
			+ ") | matrix size: (" + std::to_string(this->rows_count()) + "; " + std::to_string(this->rows_count()) + ")";
		throw MatrixException(err_str.c_str());
	}

	return this->_inner_cofactor(row, column);
}

Matrix Matrix::identity(int n) {
	if (n <= 0) {
		throw MatrixException(("Wrong size of matrix: " + std::to_string(n)).c_str());
	}

	Matrix new_matrix(n, n);

	for (int i = 0; i < n; i++) {
		new_matrix(i, i) = 1;
	}

	return new_matrix;
}

Matrix Matrix::xyz_rotation_matrix(double x_angle, double y_angle, double z_angle) {
	Matrix x_matrix = x_rotation_matrix(x_angle);
	Matrix y_matrix = y_rotation_matrix(y_angle);
	Matrix z_matrix = z_rotation_matrix(z_angle);
	return x_matrix * y_matrix * z_matrix;
}

Matrix Matrix::x_rotation_matrix(double angle) {
	return Matrix::_inner_rot_matrix(angle, 3, 1, 2);
}

Matrix Matrix::y_rotation_matrix(double angle) {
	return Matrix::_inner_rot_matrix(angle, 3, 2, 0);
}

Matrix Matrix::z_rotation_matrix(double angle) {
	return Matrix::_inner_rot_matrix(angle, 3, 0, 1);
}

Matrix Matrix::rotation_matrix(double angle, int dim, int first_axis_num, int second_axis_num) {
	return Matrix::_inner_rot_matrix(angle, dim, first_axis_num, second_axis_num);
}

//-------------------------------------------------------------------------------------------
// private
//-------------------------------------------------------------------------------------------

double Matrix::_inner_det() const {
	double res = 0;
	if (this->rows_count() == 1 && this->columns_count() == 1) {
		return (*this)(0, 0);
	}
	else {
		for (int i = 0; i < this->rows_count(); i++) {
			res += (*this)(i, 0) * this->_inner_cofactor(i, 0);
		}
	}
	return res;
}

Matrix Matrix::_delete_cross(int row, int column) const{
	if (row < 0 || column < 0 || row >= this->rows_count() || column >= this->columns_count()) {
		std::string err_str = "Wrong matrix index: index: (" + std::to_string(row) + "; " + std::to_string(column)
			+ ") | matrix size: (" + std::to_string(this->rows_count()) + "; " + std::to_string(this->rows_count()) + ")";
		throw MatrixException(err_str.c_str());
	}

	Matrix new_matrix(this->rows_count() - 1, this->columns_count() - 1);
	int h_ptr = 0, w_ptr = 0;

	for (int i = 0; i < this->rows_count(); i++) {
		if (i != row) {
			for (int j = 0; j < this->columns_count(); j++) {
				if (j != column) {
					new_matrix(h_ptr, w_ptr) = (*this)(i, j);
					w_ptr++;
				}
			}
			w_ptr = 0;
			h_ptr++;
		}
	}

	return new_matrix;
}

Matrix Matrix::_inner_rot_matrix(double angle, int dim, int first_axis_num, int second_axis_num) {
	Matrix rot_matrix(Matrix::identity(dim));
	int a = first_axis_num, b = second_axis_num;
	if (a < 0 || a >= dim || b < 0 || b >= dim) {
		throw MatrixException("Wrong rotation axis");
	}

	double rad_angle = deg_to_rad(angle);
	rot_matrix(a, a) = cos(rad_angle);
	rot_matrix(b, b) = cos(rad_angle);
	rot_matrix(a, b) = -sin(rad_angle);
	rot_matrix(b, a) = sin(rad_angle);
	return rot_matrix;
}

double Matrix::_inner_cofactor(int row, int column) const {
	return this->_delete_cross(row, column)._inner_det() * ((row + column) % 2 == 0 ? 1 : -1);
}
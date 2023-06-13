#include "GrlibMath/Vector.h"

//-------------------------------------------------------------------------------------------
// public
//-------------------------------------------------------------------------------------------

Vector::Vector(const Vector& v) : DataTable(v.get_dim(), 1) {
	for (int i = 0; i < v.get_dim(); i++) {
		(*this)(i) = v(i);
	}
}

Vector::Vector(int dim) : DataTable(dim, 1) { }

Vector::Vector(const Matrix& m) : DataTable(m.rows_count(), 1) {
	if (m.columns_count() != 1) {
		throw VectorException(("Invalid width of matrix: " + std::to_string(m.columns_count()) + " to convert into vector").c_str());
	}

	for (int i = 0; i < m.rows_count(); i++) {
		(*this)(i) = m(i, 0);
	}
}

Vector::Vector(const DataTable& dt) : DataTable(dt) { }

double Vector::scalar_product(const Vector& v, const std::vector<Vector>& basis) const {
	return bilinear_form(gram_matrix(basis), (*this), v);
}

Vector& Vector::vector_product(const Vector& v, const std::vector<Vector>& basis) const {
	if (this->get_dim() != 3 || v.get_dim() != 3) {
		std::string err_str = "Vector product defined only for 3-dims vectors: this: " + std::to_string(this->get_dim()) +
			" | v: " + std::to_string(v.get_dim());
		throw VectorException(err_str.c_str());
	}

	if (basis.size() != 3) {
		std::string err_str = "Vector product defined only for 3-dims basis: basis.size(): " + std::to_string(basis.size());
		throw VectorException(err_str.c_str());
	}

	for (int i = 0; i < basis.size(); i++) {
		if (basis[i].get_dim() != 3) {
			std::string err_str = "Vector product defined only for 3-dims vectors: this: " + std::to_string(this->get_dim()) +
				" | v: " + std::to_string(v.get_dim());
			throw VectorException(err_str.c_str());
		}
	}

	Vector& new_vector = *(new Vector(3));

	double scalar_part_1 = (*this)(1) * v(2) - (*this)(2) * v(1);
	double scalar_part_2 = (*this)(2) * v(0) - (*this)(0) * v(2);
	double scalar_part_3 = (*this)(0) * v(1) - (*this)(1) * v(0);

	new_vector(0) = scalar_part_1;
	new_vector(1) = scalar_part_2;
	new_vector(2) = scalar_part_3;

	return new_vector;
}

double& Vector::operator() (int n) {
	if (n < 0 || n >= this->get_dim()) {
		throw VectorException("Invalid index of element in vector");
	}

	return DataTable::operator()(n, 0);
}

double Vector::operator() (int n) const {
	if (n < 0 || n >= this->get_dim()) {
		throw VectorException("Invalid index of element in vector");
	}

	return DataTable::operator()(n, 0);
}

Vector Vector::operator+(const Vector& v) const {
	if (this->get_dim() != v.get_dim()) {
		std::string err_str = "Incompatible vector sizes: this: " + std::to_string(this->get_dim()) + " | v: " + std::to_string(v.get_dim());
		throw VectorException(err_str.c_str());
	}

	Vector res_v(this->get_dim());

	for (int i = 0; i < this->get_dim(); i++) {
		res_v(i) = (*this)(i) + v(i);
	}
	
	return res_v;
}

Vector Vector::operator-(const Vector& v) const {
	return (*this) + v * (-1);
}

Vector Vector::operator*(double sc) const {
	Vector res_v(this->get_dim());

	for (int i = 0; i < this->get_dim(); i++) {
		res_v(i) = (*this)(i) * sc;
	}

	return res_v;
}

Vector Vector::operator/(double sc) const {
	return (*this) * (1/sc);
}

Vector& Vector::operator+=(const Vector& v) {
	if (this->get_dim() != v.get_dim()) {
		std::string err_str = "Incompatible vector sizes: this: " + std::to_string(this->get_dim()) + " | v: " + std::to_string(v.get_dim());
		throw VectorException(err_str.c_str());
	}

	for (int i = 0; i < this->get_dim(); i++) {
		(*this)(i) += v(i);
	}

	return *this;
}

Vector& Vector::operator-=(const Vector& v) {
	return (*this) += v * (-1);
}

Vector& Vector::operator*=(double sc) {
	for (int i = 0; i < this->get_dim(); i++) {
		(*this)(i) *= sc;
	}

	return *this;
}

Vector& Vector::operator/=(double sc) {
	return (*this) *= (1/sc);
}

double Vector::operator*(const Vector& v) const {
	return this->_orth_scalar_product(v);
}

Vector Vector::operator^(const Vector& v) const {
	return this->_original_vector_product(v);
}

bool Vector::operator==(const Vector& v) const {
	return this->val_equality(v);
}

bool Vector::operator!=(const Vector& v) const {
	return !((*this) == v);
}

Vector::operator Matrix () const {
	Matrix m(this->get_dim(), 1);
	for (int i = 0; i < this->get_dim(); i++) {
		m(i, 0) = (*this)(i);
	}
	return m;
}

Vector::operator Matrix () {
	Matrix m(this->get_dim(), 1);
	for (int i = 0; i < this->get_dim(); i++) {
		m(i, 0) = (*this)(i);
	}
	return m;
}

Vector& Vector::operator=(const Vector& vec) {
	return *this;
}

double Vector::length() const {
	return std::sqrt((*this) * (*this));
}

int Vector::get_dim() const {
	return this->rows_count();
}

void Vector::normalize() {
	double len = this->length();
	if (fabs(len) < EPS) {
		throw VectorException("Trying to normalize zero vector");
	}
	for (int i = 0; i < this->get_dim(); i++) {
		(*this)(i) /= len;
	}
}

//-------------------------------------------------------------------------------------------
// private
//-------------------------------------------------------------------------------------------

double Vector::_orth_scalar_product (const Vector& v) const {
	if (this->get_dim() != v.get_dim()) {
		throw VectorException("Operands of orth scalar product have different dimensions");
	}

	double res = 0;
	for (int i = 0; i < this->get_dim(); i++) {
		res += this->operator()(i) * v(i);
	}
	return res;
}

Vector& Vector::_original_vector_product(const Vector& v) const {
	if (this->get_dim() != 3 || v.get_dim() != 3) {
		std::string err_str = "Vector product defined only for 3-dims vectors: this: " + std::to_string(this->get_dim()) +
			" | v: " + std::to_string(v.get_dim());
		throw VectorException(err_str.c_str());
	}

	Vector& new_vector = *(new Vector(3));

	double scalar_part_1 = (*this)(1) * v(2) - (*this)(2) * v(1);
	double scalar_part_2 = (*this)(2) * v(0) - (*this)(0) * v(2);
	double scalar_part_3 = (*this)(0) * v(1) - (*this)(1) * v(0);

	new_vector(0) = scalar_part_1;
	new_vector(1) = scalar_part_2;
	new_vector(2) = scalar_part_3;

	return new_vector;
}
#include "GrlibMath/Point.h"

Point::Point(const Point& p) : DataTable(p) {
	for (int i = 0; i < p.get_dim(); i++) {
		(*this)(i) = p(i);
	}
}

Point::Point(int dim) : DataTable(dim, 1) { }

Point::Point(const Vector& v) : DataTable(v.get_dim(), 1) {
	for (int i = 0; i < v.get_dim(); i++) {
		(*this)(i) = v(i);
	}
}

Point::Point(const DataTable& dt) : DataTable(dt) { }

double& Point::operator()(int n) {
	return DataTable::operator()(n, 0);
}

double Point::operator()(int n) const {
	return DataTable::operator()(n, 0);
}

Point Point::operator+(Vector v) const {
	Point new_point(*this);
	for (int i = 0; i < v.rows_count(); i++) {
		new_point(i) += v(i);
	}
	return new_point;
}

Point& Point::operator+=(Vector v) {
	for (int i = 0; i < v.rows_count(); i++) {
		(*this)(i) += v(i);
	}
	return *this;
}

Point Point::operator-(Vector v) const {
	return (*this) + v * (-1);
}

Point::operator Vector&() const {
	return *new Vector(static_cast<DataTable>(*this));
}

Point::operator Vector () const {
	return Vector(static_cast<DataTable>(*this));
}

bool Point::operator==(const Point& p) const {
	return this->val_equality(p);
}

bool Point::operator!=(const Point& p) const {
	return !(*this == p);
}

int Point::get_dim() const {
	return this->rows_count();
}
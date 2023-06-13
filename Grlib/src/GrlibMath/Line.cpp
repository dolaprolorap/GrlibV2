#include "GrlibMath/Line.h"

Line::Line(const Vector& dir_vector) : _dir_vector(dir_vector), _init_point(dir_vector.get_dim()) { }

Line::Line(const Vector& dir_vector, const Point& init_point) : _dir_vector(dir_vector), _init_point(init_point) {
	if (dir_vector.get_dim() != init_point.get_dim()) {
		throw LineException("dir_vector and init_point must have equal dimensions");
	}
}

// NOTE: check for dimension equal is done in sub of vectors
Line::Line(const Point& first_point, const Point& second_point) : _dir_vector(first_point.operator Vector &() - second_point.operator Vector &()), _init_point(first_point) { }

int Line::get_dim() const {
	return _dir_vector.get_dim();
}

Vector Line::get_dir_vector() const {
	return _dir_vector;
}

Point Line::get_init_point() const {
	return _init_point;
}

void Line::rotate_3d(double x, double y, double z) {
	if (this->get_dim() < 3) {
		throw LineException("Line dimension must be bigger or equal to 3 to 3d rotate");
	}

	Matrix rot_matrix = Matrix::xyz_rotation_matrix(x, y, z);
	_dir_vector = rot_matrix * _dir_vector;
}

void Line::planar_rotate(int first_axis, int second_axis, double angle) {
	if (first_axis < 0 || second_axis < 0 || first_axis >= this->get_dim() || second_axis >= this->get_dim()) {
		throw LineException("Wrong axes");
	}

	Matrix rot_matrix = Matrix::rotation_matrix(angle, this->get_dim(), first_axis, second_axis);
	_dir_vector = rot_matrix * _dir_vector;
}

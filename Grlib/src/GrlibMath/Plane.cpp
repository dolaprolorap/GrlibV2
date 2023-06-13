#include "GrlibMath/Plane.h"

Plane::Plane(const Vector& normal_vector) : _normal_vector(normal_vector), _init_point(normal_vector.get_dim()) { }

Plane::Plane(const Vector& normal_vector, const Point& init_point) : _normal_vector(normal_vector), _init_point(init_point) {
	if (normal_vector.get_dim() != init_point.get_dim()) {
		throw PlaneException("Dimension of normal vector does not equal to dimension of init point");
	}
}

int Plane::get_dim() const {
	return _normal_vector.get_dim();
}

Vector Plane::get_normal_vector() const {
	return _normal_vector;
}

Point Plane::get_init_point() const {
	return _init_point;
}

void Plane::rotate_3d(double x, double y, double z) {
	if (this->get_dim() < 3) {
		throw LineException("Line dimension must be bigger or equal to 3 to 3d rotate");
	}

	Matrix rot_matrix = Matrix::xyz_rotation_matrix(x, y, z);
	_normal_vector = rot_matrix * _normal_vector;
}

void Plane::planar_rotate(int first_axis, int second_axis, double angle) {
	if (first_axis < 0 || second_axis < 0 || first_axis >= this->get_dim() || second_axis >= this->get_dim()) {
		throw LineException("Wrong axes");
	}

	Matrix rot_matrix = Matrix::rotation_matrix(angle, this->get_dim(), first_axis, second_axis);
	_normal_vector = rot_matrix * _normal_vector;
}

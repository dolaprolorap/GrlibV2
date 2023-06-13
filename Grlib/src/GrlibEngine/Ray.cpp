#include "GrlibEngine/Ray.h"

Ray::Ray(Vector dir_vector, Point init_point) : _dir_normalized_vector(dir_vector), _init_point(init_point) { 
	this->_dir_normalized_vector.normalize();
}

Ray::Ray(const Ray& ray) : _dir_normalized_vector(ray._dir_normalized_vector), _init_point(ray._init_point) { }

Vector Ray::get_dir_vector() const {
	return this->_dir_normalized_vector;
}

Point Ray::get_init_point() const {
	return this->_init_point;
}

Line Ray::get_line() const {
	return Line(this->_dir_normalized_vector, this->_init_point);
}
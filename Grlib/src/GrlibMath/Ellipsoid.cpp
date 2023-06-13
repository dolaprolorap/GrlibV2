#include "GrlibMath/Ellipsoid.h"

Ellipsoid::Ellipsoid(const std::initializer_list<double>& semiaxes_lens) : _semiaxes(), _init_point((int)semiaxes_lens.size()) { 
	if (semiaxes_lens.size() == 0) {
		throw EllipsoidException("Empty list of semiaxis len-s");
	}

	_semiaxes = std::vector<Vector>();
	int i = 0;
	for (auto len : semiaxes_lens) {
		Vector semiaxis((int)semiaxes_lens.size());
		semiaxis(i++) = len;
		_semiaxes.push_back(semiaxis);
	}
}

Ellipsoid::Ellipsoid(const std::initializer_list<double>& semiaxes_lens, const Point& init_point) : _semiaxes(), _init_point(init_point) {
	if (semiaxes_lens.size() == 0) {
		throw EllipsoidException("Empty list of semiaxis len-s");
	}

	if (semiaxes_lens.size() != init_point.get_dim()) {
		throw EllipsoidException("Dimension of semiaxes set do not equal to init_point dim");
	}

	_semiaxes = std::vector<Vector>();
	int i = 0;
	for (auto len : semiaxes_lens) {
		Vector semiaxis((int)semiaxes_lens.size());
		semiaxis(i++) = len;
		_semiaxes.push_back(semiaxis);
	}
}

int Ellipsoid::get_dim() const {
	return _init_point.get_dim();
}

std::vector<Vector> Ellipsoid::get_semiaxes() const {
	return _semiaxes;
}

Point Ellipsoid::get_init_point() const {
	return _init_point;
}
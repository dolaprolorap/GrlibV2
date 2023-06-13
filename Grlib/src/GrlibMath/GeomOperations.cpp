#include "GrlibMath/GeomOperations.h"

std::vector<Point> GeomOperations::intersect(const Plane& plane, const Line& line) {
	if (plane.get_dim() != line.get_dim()) {
		throw GeomOperationsException("Dimensions of plane and line are not the same");
	}

	std::vector<Point> intersections_points;
	Vector line_dir = line.get_dir_vector();
	Vector plane_normal = plane.get_normal_vector();
	Point line_init = line.get_init_point();
	Point plane_init = plane.get_init_point();
	double vec_prod = line_dir * plane_normal;

	if (fabs(vec_prod) >= EPS) {
		double t = (plane_normal * (plane_init.operator Vector&() - line_init.operator Vector&())) / vec_prod;
		Point intersect_point(plane.get_dim());
		for (int i = 0; i < plane.get_dim(); i++) {
			intersect_point(i) = line_dir(i) * t + line_init(i);
		}
		intersections_points.push_back(intersect_point);
	}
	return intersections_points;
}

std::vector<Point> GeomOperations::intersect(Ellipsoid ellipsoid, const Line& line) {
	if (ellipsoid.get_dim() != line.get_dim()) {
		throw GeomOperationsException("Dimensions of plane and line are not the same");
	}

	// Get transpose matrix
	Matrix matrix_b_2_el(ellipsoid.get_dim(), line.get_dim());
	auto ellipsoid_axes = ellipsoid.get_semiaxes();
	auto ellipsoid_lens = std::vector<double>();
	for (int i = 0; i < ellipsoid.get_dim(); i++) {
		ellipsoid_lens.push_back(ellipsoid_axes[i].length());
		matrix_b_2_el.set_column(i, ellipsoid_axes[i]);
	}
	Matrix matrix_el_2_b(matrix_b_2_el.inverse());
	
	// Transpose ellipsoid to zero coordinate, find line init point after that
	Point trans_line_init_point(line.get_init_point() - ellipsoid.get_init_point().operator Vector());

	// Scale and rotate ellipsoid to sphere, find line characteristics after that
	Point new_line_init_point((DataTable)(matrix_el_2_b * trans_line_init_point));
	Vector new_line_dir_vector((DataTable)(matrix_el_2_b * line.get_dir_vector()));

	// Find t
	double a = 0;
	double b = 0;
	double c = -1;
	for (int i = 0; i < ellipsoid.get_dim(); i++) {
		a += pow(new_line_dir_vector(i), 2);
		b += 2 * new_line_dir_vector(i) * new_line_init_point(i);
		c += pow(new_line_init_point(i), 2);
	}

	// Find intersection points
	double D = pow(b, 2) - 4 * a * c;
	auto intersection_points = std::vector<Point>();
	if (D > EPS) {
		double sqrt_D = sqrt(D);
		double t1 = (-b - sqrt_D) / (2 * a);
		double t2 = (-b + sqrt_D) / (2 * a);

		Vector vec_1(new_line_dir_vector * t1 + new_line_init_point.operator Vector());
		Vector vec_2(new_line_dir_vector * t2 + new_line_init_point.operator Vector());
		intersection_points.push_back((DataTable)(matrix_b_2_el * vec_1 + ellipsoid.get_init_point()));
		intersection_points.push_back((DataTable)(matrix_b_2_el * vec_2 + ellipsoid.get_init_point()));
	}
	else if(fabs(D) <= EPS){
		double t = (-b) / (2 * a);

		Vector vec = new_line_dir_vector * t + new_line_init_point.operator Vector &();
		intersection_points.push_back((DataTable)(matrix_b_2_el * vec));
	}

	ellipsoid_axes.clear();
	ellipsoid_lens.clear();

	return intersection_points;
}

Vector GeomOperations::get_intersect_vector(const Plane& plane1, const Plane& plane2) {
	return plane1.get_normal_vector() ^ plane2.get_normal_vector();
}

bool GeomOperations::is_orth(const Plane& plane, const Line& line) {
	return GeomOperations::is_parallel(plane.get_normal_vector(), line.get_dir_vector());
}

bool GeomOperations::is_parallel(const Plane& plane1, const Plane& plane2) {
	return GeomOperations::is_parallel(plane1.get_normal_vector(), plane2.get_normal_vector());
}

bool GeomOperations::is_parallel(const Line& line1, const Line& line2) {
	return GeomOperations::is_parallel(line1.get_dir_vector(), line2.get_dir_vector());
}

bool GeomOperations::is_parallel(const Vector& vector1, const Vector& vector2) {
	if (vector1.get_dim() != vector2.get_dim()) {
		std::string err_str = "Different dimensions vectors: vector1: "
			+ std::to_string(vector1.get_dim()) + " | vector2: "
			+ std::to_string(vector2.get_dim());
	}

	// Find proportion of line parameters
	double prop = vector1(0) / vector2(0);

	for (int i = 1; i < vector1.get_dim(); i++) {
		if (fabs(prop - vector1(i) / vector2(i)) >= EPS) {
			return false;
		}
	}

	return true;
}

void GeomOperations::rotate_3d(Ellipsoid& ellipsoid, double x, double y, double z) {
	if (ellipsoid.get_dim() < 3) {
		throw EllipsoidException("Ellipsoid dimension must be bigger or equal to 3 to 3d rotate");
	}

	std::vector<Vector> copy;
	for (int i = 0; i < ellipsoid._semiaxes.size(); i++) {
		copy.push_back(Vector(ellipsoid._semiaxes[i]));
	}
	ellipsoid._semiaxes.clear();

	Matrix rot_matrix = Matrix::xyz_rotation_matrix(x, y, z);
	for (int i = 0; i < copy.size(); i++) {
		ellipsoid._semiaxes.push_back(Vector(rot_matrix * copy[i]));
	}
}

void GeomOperations::planar_rotate(Ellipsoid& ellipsoid, int first_axis, int second_axis, double angle) {
	if (first_axis < 0 || second_axis < 0 || first_axis >= ellipsoid.get_dim() || second_axis >= ellipsoid.get_dim()) {
		throw EllipsoidException("Wrong axes");
	}

	Matrix rot_matrix = Matrix::rotation_matrix(angle, ellipsoid.get_dim(), first_axis, second_axis);
	for (int i = 0; i < ellipsoid.get_dim(); i++) {
		ellipsoid._semiaxes[i] = rot_matrix * ellipsoid._semiaxes[i];
	}
}
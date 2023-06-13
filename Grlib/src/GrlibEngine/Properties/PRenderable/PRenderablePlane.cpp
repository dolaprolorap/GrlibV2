#include "GrlibEngine/Properties/PRenderable/PRenderablePlane.h"

PRenderablePlane::PRenderablePlane(const Vector& normal_vec, const Point& init_point) : _visual_plane(normal_vec, init_point) { }

double PRenderablePlane::calc_dist(const Ray& ray) {
	Line ray_line = ray.get_line();
	auto intersect_points = GeomOperations::intersect(_visual_plane, ray_line);
	if (intersect_points.size() != 0) {
		Vector intersect_vec = intersect_points[0].operator Vector & () - ray.get_init_point();
		if (intersect_vec * ray.get_dir_vector() >= EPS) {
			return intersect_vec.length();
		}
		else {
			return -1;
		}
	}
	else {
		return -1;
	}
}
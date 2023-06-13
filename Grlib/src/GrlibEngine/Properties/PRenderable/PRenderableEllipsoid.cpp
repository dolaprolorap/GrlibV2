#include "GrlibEngine/Properties/PRenderable/PRenderableEllipsoid.h"

PRenderableEllipsoid::PRenderableEllipsoid(const Point& pos, double x_axis, double y_axis, double z_axis) : _visual_ellipsoid({x_axis, y_axis, z_axis}, pos) { }

double PRenderableEllipsoid::calc_dist(const Ray& ray) {
	Line ray_line(ray.get_dir_vector(), ray.get_init_point());
	auto intersected_points = GeomOperations::intersect(_visual_ellipsoid, ray_line);
	double intersect_dist = -1;
	for (auto& intersect_point : intersected_points) {
		Vector vec(intersect_point.operator Vector & ());
		Vector intersect_vec(vec - ray.get_init_point().operator Vector & ());
		if (intersect_vec * ray.get_dir_vector() < 0) return -1;
		if (intersect_dist < 0) {
			intersect_dist = intersect_vec.length();
		}
		else {
			intersect_dist = std::min(intersect_dist, intersect_vec.length());
		}
	}
	return intersect_dist;
}

void PRenderableEllipsoid::rotate(double x, double y, double z) {
	GeomOperations::rotate_3d(_visual_ellipsoid, x, y, z);
}
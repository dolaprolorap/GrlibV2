#pragma once 
#include "GrlibEngine/Properties/PRenderable.h"

#include "GrlibMath/Point.h"
#include "GrlibMath/Plane.h"
#include "GrlibMath/Line.h"
#include "GrlibMath/GeomOperations.h"

// Component for visualisation of 3d ellipsoid
class PRenderablePlane : public PRenderable {
public:
	// Create component
	PRenderablePlane(const Vector& normal_vec, const Point& init_point);

	// Overrided func for calculating distance
	double calc_dist(const Ray& ray) override;

private:
	// Ellipsoid for visualisation
	Plane _visual_plane;
};
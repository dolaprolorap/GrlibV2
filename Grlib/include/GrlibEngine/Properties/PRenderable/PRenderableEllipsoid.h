#pragma once 
#include "GrlibEngine/Properties/PRenderable.h"

#include "GrlibMath/Point.h"
#include "GrlibMath/Ellipsoid.h"
#include "GrlibMath/Line.h"
#include "GrlibMath/GeomOperations.h"

// Component for visualisation of 3d ellipsoid
class PRenderableEllipsoid : public PRenderable {
public:
	// Create component
	PRenderableEllipsoid(const Point& pos, double x_axis, double y_axis, double z_axis);

	// Overrided func for calculating distance
	double calc_dist(const Ray& ray) override;

	void rotate(double x, double y, double z);

private:
	// Ellipsoid for visualisation
	Ellipsoid _visual_ellipsoid;
};
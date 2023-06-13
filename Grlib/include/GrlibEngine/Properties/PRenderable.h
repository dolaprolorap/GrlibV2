#pragma once
#include "GrlibEngine/Property.h"
#include "GrlibEngine/Ray.h"

// Class-property of renderable entity
class PRenderable : public Property {
public:
	// Creates renderable property
	PRenderable();

	// Calculates distance from ray init point along ray dir vector to the nearest part of this object
	double virtual calc_dist(const Ray& ray) = 0;
};
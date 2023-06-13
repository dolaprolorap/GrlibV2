#pragma once
#include "GrlibEngine/Property.h"

#include "GrlibMath/Vector.h"
#include "GrlibMath/Point.h"

class PMovement : public Property {
public:
	PMovement(Point& entity_coord);

	double speed = 0.5;

	void move(Vector move_dir);

private:
	Point& _entity_coord;
};
#pragma once
#include "Identifier.h"
#include "GrlibMath/CoordinateSystem.h"
#include "GrlibExceptions/EngineExceptions/EntityException.h"
#include "GrlibEngine/PropertyContainer.h"

// Class of entity - blank which has only coordinates and optionally id and coords system
class Entity : public PropertyContainer {
public:
	// Create entity with coords, coordinate systemm it binds to and id
	Entity(Point& coords, const CoordinateSystem& cs, const Identifier& id);

	// Coordinates
	Point& coords;
	// Id of entity
	const Identifier& id;
	// Coordinate system of entity
	const CoordinateSystem& cs;

};
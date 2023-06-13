#pragma once
#include "IdentifierList.h"
#include "HierarchyTop.h"
#include "GrlibMath/CoordinateSystem.h"

class Scene : public HierarchyTop {
public:
	// Creates scene with identifier list `il` and coordinate system `cs`
	Scene(IdentifierList& il, CoordinateSystem& cs);

	// Returns identifier of this scene
	IdentifierList& get_id_list() const;
	// Returns coordinate system of this scene
	CoordinateSystem& get_coord_sys() const;

	// Creates entity in this scene
	Entity& create_entity(Point& entity_coords);

private:
	// Identifier list of this scene
	IdentifierList& _scene_il;
	// Coordinate system of this scene
	CoordinateSystem& _scene_cs;
};
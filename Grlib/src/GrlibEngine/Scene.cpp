#include "GrlibEngine/Scene.h"

Scene::Scene(IdentifierList& il, CoordinateSystem& cs) : HierarchyTop(), _scene_il(il), _scene_cs(cs) { }

IdentifierList& Scene::get_id_list() const {
	return this->_scene_il;
}

CoordinateSystem& Scene::get_coord_sys() const {
	return this->_scene_cs;
}

Entity& Scene::create_entity(Point& entity_coords) {
	Entity& new_entity = *new Entity(entity_coords, this->_scene_cs, this->_scene_il.create_identifier());
	this->add(new_entity);
	return new_entity;
}
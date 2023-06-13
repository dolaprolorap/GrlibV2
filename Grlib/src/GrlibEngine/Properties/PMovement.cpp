#include "GrlibEngine/Properties/PMovement.h"

PMovement::PMovement(Point& entity_coord) : _entity_coord(entity_coord) { }

void PMovement::move(Vector move_dir) {
	this->_entity_coord += move_dir * speed;
}
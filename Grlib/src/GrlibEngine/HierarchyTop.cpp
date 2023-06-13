#include "GrlibEngine/HierarchyTop.h"

HierarchyTop::HierarchyTop() : _children() { }

void HierarchyTop::add(Entity& entity) {
	auto iter = this->_children.find(entity.id);
	if (iter != this->_children.end()) {
		throw HierarchyTopException("Entity already in the list");
	}
	this->_children.insert({ entity.id, &entity });
}

void HierarchyTop::del(const Identifier& id) {
	auto iter = this->_children.find(id);
	if (iter == this->_children.end()) {
		throw HierarchyTopException("There is no entity with such id");
	}
	this->_children.erase(id);
}

void HierarchyTop::del(Entity& entity) {
	this->del(entity.id);
}

std::vector<Entity*> HierarchyTop::get_entity_list() const {
	std::vector<Entity*> _children_vector;
	for (auto e : this->_children) {
		_children_vector.push_back(e.second);
	}
	return _children_vector;
}
#pragma once
#include <vector>
#include <unordered_map>
#include "IdentifierList.h"
#include "Entity.h"
#include "GrlibExceptions/EngineExceptions/HierarchyTopException.h"

// Class of parent object
class HierarchyTop {
public:
	// Create HierarchyTop object with scene's IdentifierList
	HierarchyTop();
	// Returns std::vector of entities
	std::vector<Entity*> get_entity_list() const;

protected:
	// Add entity to the children list
	virtual void add(Entity& entity);
	// Delete entity from the children list by its id
	virtual void del(const Identifier& id);
	// Delete entity from the children list
	virtual void del(Entity& entity);

private:
	// std::vector of the children entities
	std::unordered_map<Identifier, Entity*> _children;
};
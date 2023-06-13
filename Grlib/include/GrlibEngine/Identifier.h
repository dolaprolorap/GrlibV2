#pragma once
#include "GrlibExceptions/EngineExceptions/IdentifierException.h"

class IdentifierList;

// Universal identifier
class Identifier {
public:
	// Constructs unique identifier in the scope of IdentifierList `il`
	Identifier(long long val, IdentifierList* il);

	// Checks if this identifier belongs to the IdentifierList `il`. Returns true if does and false otherwise
	bool belongs_to(IdentifierList* il) const;
	// Returns value of this identifier
	long long val() const;
	// Returns reference to the parent IdentifierList
	IdentifierList* parent_id_list() const;
	// Overriding equality operator, checks if identifiers are equal and have the same parent IdentifierList
	bool operator == (const Identifier& id) const;

private:
	// Reference to the parent IdentifierList
	IdentifierList* _parent_id_list;
	// Unique value of the identifier
	long long _val;
};

// Define hash func for identifier
template <>
struct std::hash<Identifier> {
	std::size_t operator()(const Identifier& id) const {
		return static_cast<size_t>(id.val());
	}
};
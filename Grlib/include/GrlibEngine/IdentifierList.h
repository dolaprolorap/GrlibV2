#pragma once
#include <vector>
#include "Identifier.h";

class IdentifierList {
public:
	// Creates identifier list
	IdentifierList();

	// Creates new identifier and binds it to this list
	Identifier& create_identifier();

private:
	// Gives next unique val
	long long _get_next_unique_val();

	// List of all identifiers which belongs to this identifier list
	std::vector<Identifier*> _id_list;
	// Next unique value
	long long _next_unique_val;
};
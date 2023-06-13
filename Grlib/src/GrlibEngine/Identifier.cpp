#include "GrlibEngine/Identifier.h"

Identifier::Identifier(long long val, IdentifierList* il) {
	this->_val = val;
	this->_parent_id_list = il;
}

bool Identifier::belongs_to(IdentifierList* il) const {
	return il == this->_parent_id_list;
}

long long Identifier::val() const {
	return this->_val;
}

IdentifierList* Identifier::parent_id_list() const {
	return this->_parent_id_list;
}

bool Identifier::operator ==(const Identifier& id) const {
	if (this->parent_id_list() != id.parent_id_list()) {
		throw IdentifierException("Ids have different parents");
	}
	return this->_val == id._val;
}
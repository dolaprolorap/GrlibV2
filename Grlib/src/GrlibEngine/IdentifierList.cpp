#include "GrlibEngine/IdentifierList.h"

IdentifierList::IdentifierList() : _id_list(), _next_unique_val(0) { }

Identifier& IdentifierList::create_identifier() {
	long long unique_val = this->_get_next_unique_val();
	Identifier* new_id = new Identifier(unique_val, this);
	this->_id_list.push_back(new_id);
	return *new_id;
}

// TODO: checks for overloading of unique val value and throw exception if it does
long long IdentifierList::_get_next_unique_val() {
	return this->_next_unique_val++;
}
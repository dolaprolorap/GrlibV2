#pragma once
#include "Property.h"
#include <unordered_map>
#include <typeinfo>

/*
// Define hash func for property TYPE
template <>
struct std::hash<const type_info&> {
	std::size_t operator()(const type_info& ti) const {
		return ti.hash_code();
	}
};

// Define TYPE comparison for properties
template <>
struct std::equal_to<const type_info&> {
	bool operator()(const type_info& rp, const type_info& lp) const {
		return rp == lp;
	}
};
*/

// Container of the properties
class PropertyContainer {
public:
	// Creates property container
	PropertyContainer();

	// Get property
	template <class P>
	P* get_property() const;

	// Add property
	template <class P>
	P* add_property(P* property);

	// Delete property
	template <class P>
	void del_property(P* property);

private:
	// Map of properties
	std::unordered_map<size_t, Property*>& _properties = *new std::unordered_map<size_t, Property*>();
};

template <class P>
P* PropertyContainer::get_property() const {
	auto iter = this->_properties.find(typeid(P).hash_code());
	if (iter != _properties.end()) {
		return (P*)iter->second;
	}
	return nullptr;
}

template <class P>
P* PropertyContainer::add_property(P* property) {
	this->_properties.insert({ typeid(P).hash_code(), property });
	return property;
}

template <class P>
void PropertyContainer::del_property(P* property) {
	this->_properties.erase(typeid(P).hash_code());
}
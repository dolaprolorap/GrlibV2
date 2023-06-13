template <class P>
P& PropertyContainer::get_property() const {
	return dynamic_cast<P&>((*this->_properties.find(typeid(P).hash_code())).second);
}

template <class P>
P& PropertyContainer::add_property(P& property) {
	return *this->_properties.insert({ typeid(property).hash_code(), property });
}

template <class P>
void PropertyContainer::del_property(P& property) {
	return *this->_properties.erase(typeid(property).hash_code());
}
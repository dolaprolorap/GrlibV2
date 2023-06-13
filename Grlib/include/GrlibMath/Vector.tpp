template <typename... vec_comps>
Vector::Vector(vec_comps... vc) : DataTable(sizeof...(vc), 1) {
	std::initializer_list<double> vc_init_list = { vc... };

	int i = 0;
	for (auto& coord : vc_init_list) {
		(*this)(i++) = coord;
	}
}
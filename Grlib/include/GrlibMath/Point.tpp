template <typename... point_coords>
Point::Point(point_coords... pc) : DataTable(sizeof...(pc), 1) {
	std::initializer_list<double> pc_init_list = { pc... };
	
	int i = 0;
	for (auto& coord : pc_init_list) {
		(*this)(i++) = coord;
	}
}
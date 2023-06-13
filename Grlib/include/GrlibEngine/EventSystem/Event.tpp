template<class ...TParams>
Event<TParams...>::Event() : _handler_list() { }

template<class ...TParams>
void Event<TParams...>::execute(TParams... params) const {
	for (auto handler : this->_handler_list) {
		(*handler).call(params...);
	}
}

template<class ...TParams>
template<class TFunctor>
void Event<TParams...>::add_func(TFunctor* func) {
	this->_handler_list.push_back(new FunctorEventHandler<TFunctor, TParams...>(func));
}
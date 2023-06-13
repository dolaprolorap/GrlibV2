#include "GrlibEngine/DrawSystem/ConsoleDraw.h"

ConsoleDraw::ConsoleDraw(Canvas* canvas, double grad_start, double grad_end) : RaycastDraw(canvas) {
	set_grad(grad_start, grad_end);
}

void ConsoleDraw::draw() {
	system("cls");
	for (int i = 0; i < this->_canvas->rows_count(); i++) {
		for (int j = 0; j < this->_canvas->columns_count(); j++) {
			double dist = this->_canvas->operator()(i, j);
			if (dist < 0) std::cout << no_symbol;
			else std::cout << _cell_symb(dist);
		}
		std::cout << std::endl;
	}
}

void ConsoleDraw::set_grad(double start, double end) {
	if (start >= end) {
		throw ConsoleDrawException("Grad start >= grad end");
	}
	_grad_start = start;
	_grad_end = end;
}

std::pair<double, double> ConsoleDraw::get_grad() const {
	return std::pair<int, int>(_grad_start, _grad_end);
}

char ConsoleDraw::_cell_symb(double val) {
	val = std::max(_grad_start, val);
	val = std::min(_grad_end, val);
	double grad_diff = _grad_end - _grad_start;
	val -= _grad_start;
	int symb_ind = (val / grad_diff) * symbols.length();
	if (symb_ind == symbols.length()) symb_ind--;
	return symbols[symb_ind];
}
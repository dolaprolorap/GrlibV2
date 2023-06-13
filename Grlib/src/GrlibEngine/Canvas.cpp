#include "GrlibEngine/Canvas.h"

Canvas::Canvas(int rows, int columns) : DataTable(rows, columns) { }

int Canvas::get_size() const {
	return this->columns_count() * this->rows_count();
}

#include "GrlibMath/DataTable.h"

//-------------------------------------------------------------------------------------------
// public 
//-------------------------------------------------------------------------------------------

DataTable::DataTable(int rows, int columns) {
	if (rows <= 0 || columns <= 0) {
		throw DataTableException(("Wrong rows or columns count: rows: " + std::to_string(rows) + " | columns: " + std::to_string(columns)).c_str());
	}

	this->_data = new double* [rows];
	for (int i = 0; i < rows; i++) {
		_data[i] = new double [columns];
		for (int j = 0; j < columns; j++) {
			_data[i][j] = 0;
		}
	}
	this->_rows_count = rows;
	this->_columns_count = columns;
}

DataTable::DataTable(const DataTable& dt) {
	int rows = dt.rows_count();
	int columns = dt.columns_count();

	this->_data = new double* [rows];
	for (int i = 0; i < rows; i++) {
		_data[i] = new double [columns];
		for (int j = 0; j < columns; j++) {
			_data[i][j] = dt(i, j);
		}
	}
	this->_rows_count = rows;
	this->_columns_count = columns;
}

DataTable::~DataTable() {
	for (int i = 0; i < _rows_count; i++) {
		delete[] _data[i];
	}
	delete[] _data;
}

bool DataTable::val_equality(const DataTable& dt) const {
	if (this->_inner_dim() != dt._inner_dim()) return false;
	for (int i = 0; i < this->_rows_count; i++) {
		for (int j = 0; j < this->_columns_count; j++) {
			// TODO: is it right to check values in table straightward from `data`?
			if (fabs(this->_data[i][j] - dt._data[i][j]) >= EPS) return false;
		}
	}
	return true;
}

bool DataTable::dim_equality(const DataTable& dt) const {
	return this->_inner_dim() == dt._inner_dim();
}

double& DataTable::operator()(int row, int column) {
	if (row < 0 || column < 0 || row >= this->_rows_count || column >= _columns_count) {
		throw DataTableException(("Wrong cell: row: " + std::to_string(row) + " | column: " + std::to_string(column)).c_str());
	}

	return this->_data[row][column];
}

double DataTable::operator()(int row, int column) const {
	if (row < 0 || column < 0 || row >= this->_rows_count || column >= _columns_count) {
		throw DataTableException(("Wrong cell: row: " + std::to_string(row) + " | column: " + std::to_string(column)).c_str());
	}

	return this->_data[row][column];
}

DataTable::operator std::string& () const {
	std::string dt_str = *new std::string();
	for (int i = 0; i < this->rows_count(); i++) {
		dt_str += "| ";
		for (int j = 0; j < this->columns_count(); j++) {
			dt_str += (*this)(i, j);
			dt_str += " ";
		}
		dt_str += "|\n";
	}
	return dt_str;
}

void DataTable::set_row(int row, const std::initializer_list<double>& elems) {
	if (row < 0 || row >= this->_rows_count) {
		throw DataTableException(("Wrong row: row: " + std::to_string(row)).c_str());
	}

	int min_len = std::min((int)elems.size(), this->_columns_count);
	int i = 0;

	for (double elem : elems) {
		if (i >= min_len) break;
		this->_data[row][i++] = elem;
	}
}

void DataTable::set_row(int row, const DataTable& dt) {
	if (row < 0 || row >= this->_rows_count) {
		throw DataTableException(("Wrong row: row: " + std::to_string(row)).c_str());
	}

	if (dt.rows_count() > 1) {
		std::string err_str = "Big amount of rows: " + dt.rows_count();
		throw DataTableException(err_str.c_str());
	}

	int min_len = std::min((int)dt.columns_count(), this->_columns_count);

	for (int i = 0; i < min_len; i++) {
		this->_data[row][i] = dt(0, i);
	}
}

void DataTable::set_column(int column, const std::initializer_list<double>& elems) {
	if (column < 0 || column >= this->_columns_count) {
		throw DataTableException(("Wrong row: row: " + std::to_string(column)).c_str());
	}

	int min_len = std::min((int)elems.size(), this->_rows_count);
	int i = 0;

	for (double elem : elems) {
		if (i >= min_len) break;
		this->_data[i++][column] = elem;
	}
}

void DataTable::set_column(int column, const DataTable& dt) {
	if (column < 0 || column >= this->_columns_count) {
		throw DataTableException(("Wrong row: row: " + std::to_string(column)).c_str());
	}

	if (dt.columns_count() > 1) {
		std::string err_str = "Big amount of columns: " + dt.columns_count();
		throw DataTableException(err_str.c_str());
	}

	int min_len = std::min((int)dt.rows_count(), this->_rows_count);

	for (int i = 0; i < min_len; i++) {
		this->_data[i][column] = dt(i, 0);
	}
}

int DataTable::rows_count() const {
	return this->_rows_count;
}

int DataTable::columns_count() const {
	return this->_columns_count;
}

std::pair<int, int> DataTable::dim() const {
	return this->_inner_dim();
}

//-------------------------------------------------------------------------------------------
// private
//-------------------------------------------------------------------------------------------

std::pair<int, int> DataTable::_inner_dim() const {
	return std::pair<size_t, size_t>(this->_rows_count, this->_columns_count);
}

//-------------------------------------------------------------------------------------------
// out of class
//-------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const DataTable& dt) {
	for (int i = 0; i < dt.rows_count(); i++) {
		os << "| ";
		for (int j = 0; j < dt.columns_count(); j++) {
			os << dt(i, j) << " ";
		}
		os << "|" << std::endl;
	}
	return os;
}
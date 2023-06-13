#pragma once
#include <initializer_list>
#include <string>
#include <iostream>

#include "GrlibExceptions/MathExceptions/DataTableException.h"

#include "grlib_consts.h"

// 2d data table that gives access to modify its data and to read it
class DataTable {
public:
	// Creates 0-filled data table of `rows` rows and `columns` columns
	DataTable(int rows, int columns);
	// Creates new data table with values from data table `dt`
	DataTable(const DataTable& dt);
	// Destruct data table
	~DataTable();
	
	// Returns true, if this data table and data table `dt` have same values and sizes. Returns false otherwise
	bool val_equality(const DataTable& dt) const;
	// Returns true, if this data table and data table `dt` have same sizes. Returns false otherwise
	bool dim_equality(const DataTable& dt) const;

	// Assign value to the cell at row `row` and column `column`. Throws `DataTableException` if specified cell is wrong
	double& operator ()(int row, int column);
	// Returns value from cell at row `row` and column `column`. Throws `DataTableException` if specified cell is wrong
	double operator ()(int row, int column) const;
	// Convert data table to string
	operator std::string& () const;

	// Rewrites cells of row `row` with values of list `elems`. `elems` is cut off to the lenght of the row. If `elems` shorter
	// than row length, change only first part of row.
	void set_row(int row, const std::initializer_list<double>& elems);
	// Rewrites cells of row `row` with values of data table `dt`. `dt` is cut off to the lenght of the row. If `dt` shorter
	// than row length, change only first part of row. Throws exception if width if the `dt` is bigger than 1
	void set_row(int row, const DataTable& dt);
	// Rewrites cells of column `column` with values of list `elems`. `elems` is cut off to the lenght of the column. If `elems` 
	// shorter than column length, change only first part of column.
	void set_column(int column, const std::initializer_list<double>& elems);
	// Rewrites cells of column `column` with values of data table `dt`. `dt` is cut off to the lenght of the column. If `dt` shorter
	// than column length, change only first part of column. Throws exception if height if the `dt` is bigger than 1
	void set_column(int column, const DataTable& dt);
	// Returns count of rows in this table
	int rows_count() const;
	// Returns count of columns in this table
	int columns_count() const;
	// Returns std::pair with rows (first) and columns (second) count
	std::pair<int, int> dim() const;

private:
	// Data of table
	double** _data;
	// Count of rows in data table
	int _rows_count;
	// Count of columns in data table
	int _columns_count;

	// Returns std::pair with rows (first) and columns (second) count, for inner class uses
	std::pair<int, int> _inner_dim() const;
};

// Define output operator for `DataTable`
// Output example:
// | 1 2 3 |
// | 3 5 6 |
// | 10 2 9 |
std::ostream& operator<<(std::ostream& os, const DataTable& dt);
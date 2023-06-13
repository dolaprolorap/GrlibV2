#pragma once
#include <vector>
#include <iostream>
#include <exception>
#include <string>

#include "grlib_consts.h"

#include "GrlibMath/DataTable.h"

#include "GrlibExceptions/math_exceptions.h"

double rad_to_deg(double rad);
double deg_to_rad(double deg);

// 2D matrix of arbitrary size in the sense of linear algebra 
class Matrix : public DataTable {
public:
	// Create 0-filled matrix with rows `rows` and columns `columns`
	Matrix(int rows, int columns);
	// Create copy of matrix `m`
	Matrix(const Matrix& m);
	// Create matrix from data table `dt`
	Matrix(const DataTable& dt);

	// Sums to matrices. If they have different sizes, throws `MatrixException`
	Matrix operator + (const Matrix& m) const;
	// Sub from this matrix matrix `m`. If they have different sizes, throws `MatrixException`
	Matrix operator - (const Matrix& m) const;
	// Mult matrix on scalar `sc`
	Matrix operator * (double sc) const;
	// Mult matrix on scalar 1/`sc`
	Matrix operator / (double sc) const;
	// Mult matrix on matrix 
	Matrix operator * (const Matrix& m) const;
	// Checks two matrices for equality
	bool operator == (const Matrix& m) const;
	// Checks two matrices for inequility
	bool operator != (const Matrix& m) const;

	// Returns true if matrices are squared
	bool is_square() const;
	// Returns determinant of matrix
	double det();
	// Returns inversed, if determinant is not 0, and throws `MatrixException` otherwise
	Matrix inverse();
	// Returns transposed matrix
	Matrix transpose();
	// Returns cofactor of cell (`row`, `column`)
	double cofactor(int row, int column) const;

	// Returns identity matrix of size `n`
	static Matrix identity(int n);
	// Returns rotation matrix in 3D space. Uses Euler angle
	static Matrix xyz_rotation_matrix(double x_angle, double y_angle, double z_angle);
	// Returns rotation matrix in `dim`D space. Uses Euler angle
	static Matrix rotation_matrix(double angle, int dim, int first_axis_num, int second_axis_num);
	// Returns rotation matrix in 3D dim space in YZ plain. Uses Euler angle
	static Matrix x_rotation_matrix(double angle);
	// Returns rotation matrix in 3D dim space XZ. Uses Euler angle
	static Matrix y_rotation_matrix(double angle);
	// Returns rotation matrix in 3D dim space XY. Uses Euler angle
	static Matrix z_rotation_matrix(double angle);

private:
	// Returns det without data validation. For inner class uses
	double _inner_det() const;
	// Returns matrix without cross with the center at row `row` and column `column`
	Matrix _delete_cross(int row, int column) const;
	// Returns rotation matrix in `dim`D space, for inner class uses
	static Matrix _inner_rot_matrix(double angle, int dim, int first_axis_num, int second_axis_num);
	// Returns cofactor of this matrix of cell (`row`, `column`), for inner class uses 
	double _inner_cofactor(int row, int column) const;
};
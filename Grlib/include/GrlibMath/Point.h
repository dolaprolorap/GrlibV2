#pragma once
#include "GrlibMath/Vector.h"

#include "GrlibExceptions/math_exceptions.h"

// Point of arbitary size
class Point : public DataTable {
public:
	// Copy constructor
	Point(const Point& point);
	// Create zero point of dimension `dim` 
	Point(int dim);
	// Create vector of size of `pc` filled with `pc` values
	template<typename... point_coords>
	Point(point_coords... pc);
	// Create point from vector `v`
	Point(const Vector& v);
	// Create point from data table `dt`
	Point(const DataTable& dt);
	
	// Assign value to coord `n` of point
	double& operator()(int n);
	// Return value of coord `n` of point
	double operator()(int n) const;
	// Sum point and vector
	Point operator+(Vector v) const;
	// Sum point and vector
	Point& operator+=(Vector v);
	// Sub vector from point
	Point operator-(Vector v) const;
	// Converts vector to point
	operator Vector& () const;
	operator Vector() const;
	// Compare points
	bool operator==(const Point& p) const;
	bool operator!=(const Point& p) const;

	// Returns dim of point
	int get_dim() const;
};

#include "Point.tpp"
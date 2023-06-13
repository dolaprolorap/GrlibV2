#pragma once
#include "GrlibMath/VectorSpace.h"
#include "GrlibMath/Matrix.h"
#include "GrlibMath/DataTable.h"

#include "GrlibExceptions/math_exceptions.h"

// Vector of arbitary size (matrix Nx1) in the sense of linear algebra
class Vector : public DataTable {
public:
	// Copy constructor
    Vector(const Vector& v);
    // Create 0-filled vector of size `dim`
    Vector(int dim);
    // Create vector of size of `vc`, filled with values of `vc`
    template<typename... vec_comps>
	Vector(vec_comps... vc);
    // Create vector of matrix `m`. If both dimensions of matrix bigger than 1, throws `VectorException`
	Vector(const Matrix& m);
    // Create vector from data table `dt`
    Vector(const DataTable& dt);

    // Dot product for arbitary basis
    double scalar_product(const Vector& v, const std::vector<Vector>& basis) const;
    // Vector product for arbitary basis
    Vector& vector_product(const Vector& v, const std::vector<Vector>& basis) const;

    // Assign value to the cell `n`. Throws `VectorException` if specified cell is wrong
    double& operator() (int n);
    // Returns value from cell `n`. Throws `VectorException` if specified cell is wrong
    double operator() (int n) const;
    // Sum to vectors, throws `VectorException` if vectors have different dims
    Vector operator+(const Vector& v) const;
    // Sub one vector from another, throws `VectorException` if vectors have different dims
    Vector operator-(const Vector& v) const;
    // Mult vector on scalar `sc`
    Vector operator*(double sc) const;
    // Mult vector on 1/`sc`
    Vector operator/(double sc) const;
    // Sum this vector with `v`
    Vector& operator+=(const Vector& v);
    // Sub this vector with `v`
    Vector& operator-=(const Vector& v);
    // Mult this vector on `sc`
    Vector& operator*=(double sc);
    // Mult this vector on 1/`sc`
    Vector& operator/=(double sc);
    // Shortcut for orthogonal matrix dot product
    double operator*(const Vector& v) const;
    // Shortcut for original vector product
    Vector operator^(const Vector& v) const;
    // Checks for equality of 2 vectors
    bool operator==(const Vector & v) const;
    // Checks for inequality of 2 vectors
    bool operator!=(const Vector & v) const;
    // Convert const vector into matrix
    operator Matrix () const;
    // Convert vector into matrix
    operator Matrix ();
    // Assigment operator
    Vector& operator=(const Vector& vec);

    // Length of vector in euclidean space
    double length() const;
    // Return dimension of vector
	int get_dim() const;
    // Normalize vector length
    void normalize();

private:
    // Orthogonal matrix dot product
    double _orth_scalar_product(const Vector& v) const;
    // Vector product for original 3-dim basis
    Vector& _original_vector_product(const Vector& v) const;
};

#include "Vector.tpp"

Matrix& gram_matrix(const std::vector<Vector>& basis_vector);
double bilinear_form(const Matrix& scalar_matrix, const Vector& v1, const Vector& v2);
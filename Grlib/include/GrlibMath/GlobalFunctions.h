#pragma once
#include "GrlibMath/Matrix.h"
#include "GrlibMath/Vector.h"

#include "GrlibExceptions/MathExceptions/BilinearFormException.h"

class Matrix;

double bilinear_form(const Matrix& scalar_matrix, const Vector& v1, const Vector& v2);
Matrix& gram_matrix(const std::vector<Vector>& basis_vector);
double rad_to_deg(double rad);
double deg_to_rad(double deg);
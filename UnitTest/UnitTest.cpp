#include "pch.h"
#include "CppUnitTest.h"
#include "Grlib.h"
#include <initializer_list>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testcppgrlib {
	const char* boolstr(bool val) {
		return val ? "true" : "false";
	}

	const char* intstr(int val) {
		std::string text = std::to_string(val);
		char* new_char = new char[text.length() + 1];
		strcpy_s(new_char, sizeof new_char, text.c_str());
		return new_char;
	}

	TEST_CLASS(MatrixTest) {
	public:
		TEST_METHOD(EqualityTest) {
			bool are_equal = false;
			Matrix& m1 = *new Matrix(3, 3);
			Matrix& m2 = *new Matrix(3, 3);
			Matrix& m3 = *new Matrix(2, 2);

			are_equal = m1 == m2;
			Assert::AreEqual("true", boolstr(are_equal));

			are_equal = m2 == m1;
			Assert::AreEqual("true", boolstr(are_equal));

			m1(1, 1) = 1000;
			are_equal = m1 == m2;
			Assert::AreEqual("false", boolstr(are_equal));

			are_equal = m3 == m1;
			Assert::AreEqual("false", boolstr(are_equal));

			are_equal = m1 == m3;
			Assert::AreEqual("false", boolstr(are_equal));

			are_equal = m1 == m1;
			Assert::AreEqual("true", boolstr(are_equal));
		}

		TEST_METHOD(OperationsTest) {
			Matrix* m1 = new Matrix(1, 1);
			Matrix* m2 = new Matrix(1000, 1);
			Matrix* m3 = new Matrix(1, 1000);

			Matrix& ml = *new Matrix(2, 2);
			Matrix& mr = *new Matrix(2, 2);
			Matrix& msum = *new Matrix(2, 2);
			Matrix& mdif = *new Matrix(2, 2);
			Matrix& mscdot = *new Matrix(2, 2);
			Matrix& mscdel = *new Matrix(2, 2);
			Matrix& mmprod = *new Matrix(2, 2);
			Matrix& mdet = Matrix::identity(3);

			ml(0, 0) = ml(1, 1) = 1;
			mr(0, 0) = mr(1, 1) = 2;

			msum(0, 0) = msum(1, 1) = 3;
			Assert::AreEqual("true", boolstr(msum == ml + mr));

			mdif(0, 0) = mdif(1, 1) = -1;
			Assert::AreEqual("true", boolstr(mdif == ml - mr));

			mscdot(0, 0) = mscdot(1, 1) = 2;
			Assert::AreEqual("true", boolstr(mscdot == ml * 2));

			mscdel(0, 0) = mscdel(1, 1) = 0.5;
			Assert::AreEqual("true", boolstr(mscdel == ml / 2));

			mmprod(0, 0) = mmprod(1, 0) = mmprod(1, 1) = 2;
			Assert::AreEqual("false", boolstr(mmprod == ml * mr));

			ml(1, 0) = 1;
			Assert::AreEqual("true", boolstr(mmprod == ml * mr));

			Assert::AreEqual("1", intstr(mdet.det()));

			mdet = mdet * 34;
			Assert::AreEqual("39304", intstr(mdet.det()));

			mdet(0, 0) = 0;
			Assert::AreEqual("0", intstr(mdet.det()));
		}

		TEST_METHOD(MatrixInverseTest)
		{
			Matrix m = *new Matrix(3, 3);
			m.set_row(0, { 2, 2, 0 });
			m.set_row(1, { 0, 2, 0 });
			m.set_row(2, { 1, 1, 1 });

			Matrix m_inv = *new Matrix(3, 3);
			m_inv.set_row(0, { 0.5, -0.5, 0 });
			m_inv.set_row(1, { 0, .5, 0 });
			m_inv.set_row(2, { -0.5, 0, 1 });

			Assert::AreEqual("true", boolstr(m_inv == m.inverse()));
		}

		TEST_METHOD(MatrixTransposeTest)
		{
			Matrix m = *new Matrix(3, 3);
			m.set_row(0, { 2, 2, 0 });
			m.set_row(1, { 0, 2, 0 });
			m.set_row(2, { 1, 1, 1 });

			Matrix m_tran = *new Matrix(3, 3);
			m_tran.set_row(0, { 2, 0, 1 });
			m_tran.set_row(1, { 2, 2, 1 });
			m_tran.set_row(2, { 0, 0, 1 });

			Assert::AreEqual("true", boolstr(m_tran == m.transpose()));
		}

		TEST_METHOD(RotationMatrix) {
			Matrix except_rot_0 = Matrix::identity(3);
			Matrix except_rot_x = Matrix::identity(3);
			except_rot_x(1, 1) = -1;
			except_rot_x(2, 2) = -1;
			Matrix except_rot_y = Matrix::identity(3);
			except_rot_y(0, 0) = -1;
			except_rot_y(2, 2) = -1;
			Matrix except_rot_z = Matrix::identity(3);
			except_rot_z(1, 1) = -1;
			except_rot_z(0, 0) = -1;

			Matrix except_rot90x = Matrix::identity(3);
			except_rot90x.set_row(1, { 0, 0, -1 });
			except_rot90x.set_row(2, { 0, 1, 0 });

			Matrix except_rot90x90z = Matrix::identity(3);
			except_rot90x90z.set_row(0, { 0, -1, 0 });
			except_rot90x90z.set_row(1, { 0, 0, -1 });
			except_rot90x90z.set_row(2, { 1, 0, 0 });

			double sqr = sqrt(2);
			Matrix except_rot90x45y90z = Matrix::identity(3);
			except_rot90x45y90z.set_row(0, { 0, -sqr, sqr });
			except_rot90x45y90z.set_row(1, { 0, -sqr, -sqr });
			except_rot90x45y90z.set_row(2, { 2, 0, 0 });
			except_rot90x45y90z = except_rot90x45y90z * 0.5;

			double sqr3 = sqrt(3);
			Matrix except_rot_90x45y_30z = Matrix::identity(3);
			except_rot_90x45y_30z.set_row(0, { sqr3 * sqr, sqr, 2 * sqr });
			except_rot_90x45y_30z.set_row(1, { -sqr3 * sqr, -sqr, 2 * sqr });
			except_rot_90x45y_30z.set_row(2, { 2, -2 * sqr3, 0 });
			except_rot_90x45y_30z = except_rot_90x45y_30z * 0.25;


			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(0, 0, 0) == Matrix::identity(3)));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(180, 0, 0) == except_rot_x));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(0, 180, 0) == except_rot_y));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(0, 0, 180) == except_rot_z));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(90, 0, 0) == except_rot90x));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(90, 0, 90) == except_rot90x90z));
			Assert::AreEqual("true", boolstr(Matrix::xyz_rotation_matrix(-90, 45, -30) == except_rot_90x45y_30z));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(90, 3, 1, 2) == Matrix::xyz_rotation_matrix(90, 0, 0)));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(90, 3, 2, 0) == Matrix::xyz_rotation_matrix(0, 90, 0)));
			Assert::AreEqual("true", boolstr(Matrix::rotation_matrix(45, 3, 0, 1) == Matrix::xyz_rotation_matrix(0, 0, 45)));
		}
	};

	TEST_CLASS(testvector)
	{
	public:
		TEST_METHOD(TestVectorOperations)
		{
			VectorSpace vs = *new VectorSpace(3);

			Vector v1 = *new Vector(1.0, 2.0, 4.0);
			Vector vcpy = *new Vector(v1);

			Assert::AreEqual("true", boolstr(v1 == vcpy));

			Vector v2 = *new Vector(2.0, 3.0, 5.0);

			Assert::AreEqual("28", intstr(v1 * v2));

			Vector crosprod = *new Vector(-2., 3., -1.);
			Assert::AreEqual("true", boolstr((v1 ^ v2) == crosprod));

			Assert::AreEqual("true", boolstr((fabs(v1.length() - 4.58257)) < 0.0001));
		}
	};

	TEST_CLASS(testpoint)
	{
	public:
		TEST_METHOD(TestPointOperations)
		{
			VectorSpace vs = *new VectorSpace(3);

			Vector v = *new Vector(1., 2., 3.);
			Vector shift = *new Vector(0., 2., 4.);

			Point p1 = *new Point(3);
			Point p2 = *new Point(v);
			Point p3 = *new Point(1., 2., 3.);
			Point p4 = *new Point(p2);

			Point pplus = *new Point(1., 4., 7.);
			Point pminus = *new Point(1., 0., -1.);

			Assert::AreEqual("true", boolstr(p2 == p3));
			Assert::AreEqual("true", boolstr(p2 == p4));
			Assert::AreEqual("true", boolstr(p2 == v));
			Assert::AreEqual("true", boolstr(pplus == p3 + shift));
			Assert::AreEqual("true", boolstr(pminus == p3 - shift));
		}
	};

	TEST_CLASS(globalobjects) 
	{
	public:
		TEST_METHOD(TestGlobalObjs) {
			VectorSpace vs = *new VectorSpace(3);
			CoordinateSystem cs = *new CoordinateSystem(*new Point(1., 3., 4.));
			Assert::AreEqual("true", "true");
		}
	};

	void TestBasisConverterException() {
		BasisConverter::create_orth_3d(*new Vector(0., 0., 0.));
	}

	void TestBilinearFormException() {
		Vector v1(3);
		Vector v2(3);
		Matrix m(3, 4);
		m.set_row(0, { 0, 2, 1, 3 });
		m.set_row(1, { 5, 3, 8, 2 });
		m.set_row(2, { 4, 2, 6, 8 });
		bilinear_form(m, v1, v2);
	}

	void TestDataTableException() {
		DataTable dt(1, 2);
		dt(3, 4) = 1;
	}

	void TestLineException() {
		Line line(Vector(1., 2., 4.), Point(1., 2.));
	}

	void TestMatrixException() {
		Matrix m1 = *new Matrix(2, 2);
		Matrix m2 = *new Matrix(3, 3);
		m1 + m2;
	}

	void TestPlaneException() {
		Plane plane(Vector(1., 2., 3.), Point(2., 6., 1., 3.));
	}

	void TestPointException() {
		Point point(1., 2., 3.);
		point(5);
	}

	void TestVectorException() {
		Vector v(1., 3., 4.);
		v(5);
	}

	void TestVectorSpaceException() {
		VectorSpace vs(-3);
	}

	TEST_CLASS(MatrixExceptionTest) {
	public:
		TEST_METHOD(General) {
			auto test1 = [] { TestBasisConverterException(); };
			Assert::ExpectException<BasisConverterException>(test1);

			auto test2 = [] { TestBilinearFormException(); };
			Assert::ExpectException<BilinearFormException>(test2);

			auto test4 = [] { TestDataTableException(); };
			Assert::ExpectException<DataTableException>(test4);

			auto test5 = [] { TestLineException(); };
			Assert::ExpectException<LineException>(test5);

			auto test6 = [] { TestMatrixException(); };
			Assert::ExpectException<MatrixException>(test6);

			auto test7 = [] { TestPlaneException(); };
			Assert::ExpectException<PlaneException>(test7);

			auto test9 = [] { TestVectorException(); };
			Assert::ExpectException<VectorException>(test9);

			auto test10 = [] { TestVectorSpaceException(); };
			Assert::ExpectException<VectorSpaceException>(test10);
		}
	};

	TEST_CLASS(GeomTest) {
	public:
		const char* check_points(std::vector<Point> points1, std::vector<Point> points2) {
			if (points1.size() != points2.size()) return "false";
			for (int i = 0; i < points1.size(); i++) {
				if (points1[i] != points2[i]) return "false";
			}
			return "true";
		}

		TEST_METHOD(EllipsoidTest1) {
			std::vector<Point> right_points = { Point(-0.57735, -0.57735, -0.57735), Point(0.57735, 0.57735, 0.57735) };
			Ellipsoid ellipsoid({ 1., 1., 1. }, Point(0., 0., 0.));
			Line line(Vector(1., 1., 1.), Point(0., 0., 0.));
			auto inter1 = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter1));
		}

		TEST_METHOD(EllipsoidTest2) {
			std::vector<Point> right_points = { Point(-0.666667, -0.666667, -0.666667), Point(0.666667, 0.666667, 0.666667) };
			Ellipsoid ellipsoid({ 2., 1., 1. }, Point(0., 0., 0.));
			Line line(Vector(1., 1., 1.), Point(0., 0., 0.));
			auto inter1 = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter1));
		}

		TEST_METHOD(EllipsoidTest3) {
			std::vector<Point> right_points = { Point(-0.478852, -0.478852, -0.478852), Point(0.478852, 0.478852, 0.478852) };
			Ellipsoid ellipsoid({ 2., 0.5, 3. }, Point(0., 0., 0.));
			Line line(Vector(1., 1., 1.), Point(0., 0., 0.));
			auto inter1 = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter1));
		}

		TEST_METHOD(EllipsoidTest4) {
			std::vector<Point> right_points = { };
			Ellipsoid ellipsoid({ 1., 1, 1. }, Point(1., 2., -0.5));
			Line line(Vector(1., 1., 1.), Point(0., 0., 0.));
			auto inter1 = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter1));
		}

		TEST_METHOD(EllipsoidTest5) {
			std::vector<Point> right_points = { };
			Ellipsoid ellipsoid({ 1., 1., 1. }, Point(1., 2., -0.5));
			Line line(Vector(1., 1., 1.), Point(0., 0., -3.));
			auto inter = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter));
		}

		// PRECISION SENSETIVE! EPS SHOULD BE >= 10E-4
		TEST_METHOD(EllipsoidTest6) {
			std::vector<Point> right_points = { Point(1.06981, 1.06981, -0.86038), Point(1.59686, 1.59686, 0.193713) };
			Ellipsoid ellipsoid({ 1., 1., 1. }, Point(1., 2., -0.5));
			Line line(Vector(1., 1., 2.), Point(0., 0., -3.));
			auto inter = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter));
		}

		// PRECISION SENSETIVE! EPS SHOULD BE >= 10E-4
		TEST_METHOD(EllipsoidTest7) {
			std::vector<Point> right_points = { Point(0.0553985, 0.0553985, -2.8892), Point(2.51278, 2.51278, 2.02557) };
			Ellipsoid ellipsoid({ 2., 3., 4. }, Point(1., 2., -0.5));
			Line line(Vector(1., 1., 2.), Point(0., 0., -3.));
			auto inter = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter));
		}

		TEST_METHOD(EllipsoidTestRotate1) {
			std::vector<Point> right_points = { Point(-2., 0., 0.), Point(2., 0., 0.) };
			Ellipsoid ellipsoid({ 1., 2., 1. }, Point(0., 0., 0.));
			GeomOperations::rotate_3d(ellipsoid, 0, 0, 90);
			Line line(Vector(1., 0., 0.), Point(0., 0., 0.));
			auto inter = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter));
		}

		TEST_METHOD(EllipsoidTestRotate2) {
			std::vector<Point> right_points = { Point(-1., 0., 0.), Point(1., 0., 0.) };
			Ellipsoid ellipsoid({ 1., 1., 1. }, Point(0., 0., 0.));
			GeomOperations::rotate_3d(ellipsoid, 10, 45, 90);
			Line line(Vector(1., 0., 0.), Point(0., 0., 0.));
			auto inter = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter));
		}

		TEST_METHOD(EllipsoidTestRotate3) {
			std::vector<Point> right_points = { Point(0., 0., 0.), Point(2., 0., 0.) };
			Ellipsoid ellipsoid({ 1., 1., 1. }, Point(1., 0., 0.));
			GeomOperations::rotate_3d(ellipsoid, 0, 0, 90);
			Line line(Vector(1., 0., 0.), Point(0., 0., 0.));
			auto inter = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter));
		}

		TEST_METHOD(EllipsoidTestRotate4) {
			std::vector<Point> right_points = { Point(0., 0., 0.), Point(2., 0., 0.) };
			Ellipsoid ellipsoid({ 1., 1., 1. }, Point(1., 0., 0.));
			GeomOperations::rotate_3d(ellipsoid, 30000, -170, 90);
			Line line(Vector(1., 0., 0.), Point(0., 0., 0.));
			auto inter = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter));		
		}

		TEST_METHOD(EllipsoidTestRotate5) {
			std::vector<Point> right_points = { Point(-1., 0., 0.), Point(1., 0., 0.) };
			Ellipsoid ellipsoid({ 3., 2., 1. }, Point(0., 0., 0.));
			GeomOperations::rotate_3d(ellipsoid, 0, 90, 0);
			Line line(Vector(1., 0., 0.), Point(0., 0., 0.));
			auto inter = GeomOperations::intersect(ellipsoid, line);
			Assert::AreEqual("true", check_points(right_points, inter));
		}
	};
}

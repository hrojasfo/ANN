#include "stdafx.h"
#include "CppUnitTest.h"
#include "Matrix.h"
#include "Image_parser.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ANN_tests
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(check_identity_matrix_4x4)
		{
			Matrix<double> m0(4, 4, "ident");
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::AreEqual((i == j) ? 1.0 : 0.0, m0.get(i, j));
				}
			}
		}
		TEST_METHOD(check_identity_matrix_1kx1k)
		{
			int size = 1000;
			Matrix<double> m0(size, size, "ident");
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					Assert::AreEqual((i == j) ? 1.0 : 0.0, m0.get(i, j));
				}
			}
		}
		TEST_METHOD(check_zeros_matrix_4x4)
		{
			Matrix<double> m0(4, 4, "zeros");
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::AreEqual(0.0, m0.get(i, j));
				}
			}
		}
		TEST_METHOD(check_ones_matrix_4x4)
		{
			Matrix<double> m0(4, 4, "ones");
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::AreEqual(1.0, m0.get(i, j));
				}
			}
		}
		TEST_METHOD(check_get_col_row)
		{
			Matrix<double> m0(4, 1);
			Matrix<double> m1(1, 4);

			Assert::AreEqual(4, m1.get_col());
			Assert::AreEqual(1, m1.get_row());

			Assert::AreEqual(1, m0.get_col());
			Assert::AreEqual(4, m0.get_row());
		}
		TEST_METHOD(check_get)
		{
			Matrix<double> m0(4, 1);
			Matrix<double> m1(1, 4);
			m0.get(0, 0) = 1;
			m0.get(1, 0) = 2;
			m0.get(2, 0) = 3;
			m0.get(3, 0) = 4;
			m1.get(0, 0) = 2;
			m1.get(0, 1) = 3;
			m1.get(0, 2) = 4;
			m1.get(0, 3) = 5;

			Assert::AreEqual(4.0, m0.get(3, 0));
			Assert::AreEqual(5.0, m1.get(0, 3));

		}
		TEST_METHOD(check_matrix_mult_result_dimension)
		{
			Matrix<double> m0(4, 1);
			Matrix<double> m1(1, 4);

			Matrix<double> result;
			result = m0 * m1;
			Assert::AreEqual(4, result.get_col());
			Assert::AreEqual(4, result.get_row());

		}
		TEST_METHOD(check_matrix_multiplication)
		{
			Matrix<double> m0(4, 1);
			Matrix<double> m1(1, 4);
			m0.get(0, 0) = 1;
			m0.get(1, 0) = 2;
			m0.get(2, 0) = 3;
			m0.get(3, 0) = 4;
			m1.get(0, 0) = 2;
			m1.get(0, 1) = 3;
			m1.get(0, 2) = 4;
			m1.get(0, 3) = 5;
			double expected[4][4]{ {2, 3,  4,  5},
			                       {4, 6,  8,  10},
								   {6, 9,  12, 15},
								   {8, 12, 16, 20} };
			Matrix<double> result;
			result = m0 * m1;
			Assert::AreEqual(4,result.get_col());
			Assert::AreEqual(4,result.get_row());
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::AreEqual(result.get(i, j), expected[i][j]);
				}
			}
		}
		TEST_METHOD(check_matrix_mult_identity)
		{
			Matrix<double> m0(5, 5, "ident");
			Matrix<double> m1(5, 5);

			Matrix<double> result;
			result = m0 * m1;
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 5; ++j) {
					Assert::AreEqual( m1.get(i, j), result.get(i, j) );
				}
			}
		}

		TEST_METHOD(check_matrix_mult_vector)
		{
			Matrix<double> m0(1, 2);
			Matrix<double> m1(2, 1);
			m0.get(0, 0) = 3; m0.get(0, 1) = 4;
			m1.get(0, 0) = 3; m1.get(1, 0) = 4;
			Matrix<double> result;

			result = m0 * m1;
			Assert::AreEqual(1, result.get_col());
			Assert::AreEqual(1, result.get_row());
			Assert::AreEqual(25.0, result.get(0,0));
		}
		TEST_METHOD(check_matrix_addition)
		{
			Matrix<double> m0(1, 4);
			m0.get(0, 0) = 1;
			m0.get(0, 1) = 2;
			m0.get(0, 2) = 3;
			m0.get(0, 3) = 4;
			double expected[1][4]{ { 2, 4,  6,  8 } };

			Matrix<double> result;
			result = m0 + m0;
			Assert::AreEqual(4, result.get_col());
			Assert::AreEqual(1, result.get_row());
			for (int i = 0; i < 1; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::AreEqual(expected[i][j], result.get(i, j));
				}
			}
		}
		TEST_METHOD(check_delta_function)
		{
			Matrix<double> m0(1, 4);
			m0.get(0, 0) = 1.5;
			m0.get(0, 1) = 2.5;
			m0.get(0, 2) = 3.5;
			m0.get(0, 3) = 4.5;
			double expected[1][4]{ { -0.75, -3.75,  -8.75,  -15.75 } };

			Matrix<double> result;
			result = m0.delta();
			Assert::AreEqual(4, result.get_col());
			Assert::AreEqual(1, result.get_row());
			for (int i = 0; i < 1; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::AreEqual(expected[i][j], result.get(i, j));
				}
			}
		}
		TEST_METHOD(check_matrix_scalar_multiplication)
		{
			Matrix<double> m0(2, 2);
			m0.get(0, 0) = 1;
			m0.get(0, 1) = 2;
			m0.get(1, 0) = 3;
			m0.get(1, 1) = 4;
			m0.scalar_mult(1.5);
			double expected[2][2]{ { 1.5, 3 },
								   { 4.5, 6 } };

			for (int i = 0; i < 2; ++i) {
				for (int j = 0; j < 2; ++j) {
					Assert::AreEqual(expected[i][j], m0.get(i,j));
				}
			}
		}
		TEST_METHOD(check_matrix_delta_out)
		{
			Matrix<double> m0(1, 4), m1(1,4);
			m0.get(0, 0) = 1;
			m0.get(0, 1) = 2;
			m0.get(0, 2) = 3;
			m0.get(0, 3) = 4;
			m1.get(0, 0) = 5;
			m1.get(0, 1) = 6;
			m1.get(0, 2) = 7;
			m1.get(0, 3) = 8;
			m0 = m0.delta_out(m1);
			double expected[1][4]{ { 0, 8, 24, 48 } };

			for (int i = 0; i < 1; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::AreEqual(expected[i][j], m0.get(i, j));
				}
			}
		}
		TEST_METHOD(check_matrix_one_to_one_mult)
		{
			Matrix<double> m0(1, 4), m1(1, 4);
			m0.get(0, 0) = 1;
			m0.get(0, 1) = 2;
			m0.get(0, 2) = 3;
			m0.get(0, 3) = 4;
			m1.get(0, 0) = 5;
			m1.get(0, 1) = 6;
			m1.get(0, 2) = 7;
			m1.get(0, 3) = 8;
			m0 = m0.one_to_one_mult(m1);
			double expected[1][4]{ { 5, 12, 21, 32 } };

			for (int i = 0; i < 1; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::AreEqual(expected[i][j], m0.get(i, j));
				}
			}
		}
		TEST_METHOD(check_matrix_sigmoid)
		{
			Matrix<double> m0(1, 5);
			m0.get(0, 0) = -2;
			m0.get(0, 1) = -1;
			m0.get(0, 2) =  0;
			m0.get(0, 3) =  1;
			m0.get(0, 4) = 10;

			m0.sigmoid();
			double expected[1][5]{ { 0.119202922, 0.268941, 0.5, 0.731059, 0.999955 } };

			for (int i = 0; i < 1; ++i) {
				for (int j = 0; j < 5; ++j) {
					Assert::
					Assert::AreEqual(expected[i][j], m0.get(i, j), 0.00001);
				}
			}
		}
	};
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(image_parser_contructor)
		{
			Image_parser parser;
			parser.read_bmp("..\\3_0.bmp");
		}
	};
}
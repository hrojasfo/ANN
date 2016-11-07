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
#include "stdafx.h"
#include "CppUnitTest.h"
#include "Matrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ANN_tests
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(check_identity_matrix_4x4)
		{
			Matrix<double> m0(4,4,"ident");
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 4; ++j) {
					Assert::AreEqual(m0.get(i,j), (i == j)? 1.0 : 0.0);
				}
			}
		}

	};
}
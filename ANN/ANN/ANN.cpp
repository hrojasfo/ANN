// ANN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"

int main()
{
	Matrix<float> w(4,4,"ident");

	w.print();

    return 0;
}


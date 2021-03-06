// Numbers_NN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include "Image_parser.h"
#include "Neural_network.h"

//#define _CRTDBG_MAP_ALLOC  
//#include <stdlib.h>  
//#include <crtdbg.h> 

int main()
{

	/*neural_network::Neural_network nn(std::vector<int>{2, 3, 1}, 0.5);
	nn.set_train_params(5000, 1);
	nn.train();

	Matrix<float> out0;
	Matrix<float> in0(1, 2);
	in0.get(0, 0) = 1;
	in0.get(0, 1) = 0;
	out0 = nn.run(in0);
	std::cout << "0 1\n";
	for (int i = 0; i < out0.get_col(); ++i) {
		std::cout << out0.get(0, i) << " ";
	}
	std::cout << '\n';

	in0.get(0, 0) = 0;
	in0.get(0, 1) = 0;
	out0 = nn.run(in0);
	std::cout << "0 0\n";
	for (int i = 0; i < out0.get_col(); ++i) {
		std::cout << out0.get(0, i) << " ";
	}
	std::cout << '\n';

	in0.get(0, 0) = 1;
	in0.get(0, 1) = 1;
	out0 = nn.run(in0);
	std::cout << "1 1\n";
	for (int i = 0; i < out0.get_col(); ++i) {
		std::cout << out0.get(0, i) << " ";
	}
	std::cout << '\n';

	in0.get(0, 0) = 0;
	in0.get(0, 1) = 1;
	out0 = nn.run(in0);
	std::cout << "1 0\n";
	for (int i = 0; i < out0.get_col(); ++i) {
		std::cout << out0.get(0, i) << " ";
	}
	std::cout << '\n';


	getchar();
	return 0;//*/

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	
	//_CrtSetBreakAlloc(2025);


	//Matrix<double> test_m(5,5,"ident");

	Image_parser train_data;
	train_data.read_images("..\\train-images.idx3-ubyte");
	train_data.read_labels("..\\train-labels.idx1-ubyte");
	std::cout << "Printing...\n";
	train_data.get_image();
	train_data.print_bmp();

	neural_network::Neural_network images_nn(std::vector<int>{784, 30, 10}, 0.05);

	//std::vector<Matrix<float>> weights = 
	images_nn.read_weights_and_bias();

	/*images_nn.set_train_params(20, 200);
	images_nn.train(&train_data);
	images_nn.store();//*/


	Matrix<float> out = images_nn.run(Matrix<float>(train_data.get_image(0,false)));


	// Read test data
	Image_parser test_data;
	test_data.read_images("..\\t10k-images-idx3-ubyte");
	test_data.read_labels("..\\t10k-labels-idx1-ubyte");

	char in = '0';
	int c = 0;
	while (in != 'q') {
		Matrix<float> image_in = test_data.get_image(c, false);
		out = images_nn.run(image_in);
		int max = 0;
		float max_val = 0.0;
		for (int i = 0; i < out.get_col(); ++i) {
			float temp = out.get(0, i);
			std::cout << temp << " ";
			if(temp > max_val) {
				max_val = temp;
				max = i;
			}
		}
		std::cout << '\n';
		test_data.get_image(c,true);
		int label = test_data.get_label(c);
		std::cout << "Guess " << max << '\n';
		++c;
		in = getchar();
	}//*/
	//_CrtDumpMemoryLeaks();
    return 0;
}


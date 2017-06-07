// Numbers_NN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include "Image_parser.h"
#include "Neural_network.h"

#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h> 

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

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	
	Image_parser parser;
	std::string file = "..\\train-images.idx3-ubyte";
	std::string label = "..\\train-labels.idx1-ubyte";
	parser.read_images(file);
	parser.read_labels(label);
	std::cout << "Printing...\n";
	parser.get_image();
	parser.print_bmp();

	neural_network::Neural_network images_nn(std::vector<int>{784, 30, 10}, 0.05);

	std::vector<Matrix<float>> weights = images_nn.read_weights_and_bias();
	//images_nn.load_weights(weights);

	images_nn.set_train_params(1, 1);
	images_nn.train(&parser);
	images_nn.store();//*/


	Matrix<float> out = images_nn.run(Matrix<float>(parser.get_image(0,false)));

	//getchar();
	char in = '0';
	int c = 0;
	while (in != 'q') {
		out = images_nn.run(Matrix<float>(parser.get_image(c, false)));
		for (int i = 0; i < out.get_col(); ++i) {
			std::cout << out.get(0, i)  << " ";
		}
		std::cout << '\n';
		std::vector<float> image = parser.get_image(c,true);
		int label = parser.get_label(c++);
		std::cout << "size " << image.size() << ", label " << label << '\n';
		in = getchar();
	}//*/
	_CrtDumpMemoryLeaks();
    return 0;
}


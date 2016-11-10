// Numbers_NN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include "Image_parser.h"
#include "Neural_network.h"
int main()
{
	Matrix<double> a0(1, 1);
	Image_parser parser;
	std::string file = "..\\train-images.idx3-ubyte";
	std::string label = "..\\train-labels.idx1-ubyte";
	parser.read(file);
	parser.read_labels(label);

	neural_network::Neural_network images_nn(std::vector<int>{784, 100, 10});
	//images_nn.train(&parser);
	//images_nn.store();
	std::vector<Matrix<float>> weights = images_nn.read_weights();
	/*std::cout << "Layers: " << result.size() << '\n';
	for (int i = 0; i < result.size(); ++i) {
		std::cout << "Rows: " << result[i].get_row() << ", Colums: " << result[i].get_col() << '\n';
		std::cout << "0 0: " << result[i].get(0, 0) << '\n';
	}//*/
	images_nn.load_weights(weights);
	Matrix<float> out = images_nn.run(Matrix<float>(parser.get_image(0,false)));

	getchar();
	char in = '0';
	int c = 0;
	while (in != 'q') {
		std::vector<float> image = parser.get_image(c,true);
		int label = parser.get_label(c++);
		std::cout << "size " << image.size() << ", label " << label << '\n';
		in = getchar();
	}//*/
    return 0;
}


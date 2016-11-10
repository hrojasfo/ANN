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
	std::string file = "C:\\Users\\rojashe\\Documents\\NNA\\train-images.idx3-ubyte";
	std::string label = "C:\\Users\\rojashe\\Documents\\NNA\\train-labels.idx1-ubyte";
	parser.read(file);
	parser.read_labels(label);

	neural_network::Neural_network images_nn(std::vector<int>{784, 100, 10});
	images_nn.train(parser);
	images_nn.store();
	std::vector<Matrix<float>> result = images_nn.read_weights();
	getchar();
	char in = '0';
	int c = 0;
	/*while (in != 'q') {
		std::vector<float> image = parser.get_image(c,true);
		int label = parser.get_label(c);
		std::cout << "size " << image.size() << ", label " << label << '\n';
		in = getchar();
	}//*/
    return 0;
}


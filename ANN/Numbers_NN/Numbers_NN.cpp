// Numbers_NN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include "Image_parser.h"
#include "Neural_network.h"
int main()
{

	try {
		neural_network::Neural_network nn(std::vector<int>{2, 4, 2});
		std::vector<Matrix<float>> w;
		w.push_back(Matrix<float>(3, 4, 0.5));
		w.push_back(Matrix<float>(5, 2, 0.5));

		nn.load_weights(w);
		nn.store();

		std::vector<Matrix<float>> w0 = nn.read_weights();
		for (int l = 0; l < w0.size(); ++l) {
			for (int r = 0; r < w0[l].get_row(); ++r) {
				for (int c = 0; c < w0[l].get_col(); ++c) {
					std::cout << w0[l].get(r, c) << ' ';
				}
				std::cout << '\n';
			}
			std::cout << '\n';
		}
	}
	catch (const std::exception& e) {
		std::cout << e.what();
	}
	//getchar();
	//return 0;
	Matrix<double> a0(1, 1);
	Image_parser parser;
	std::string file = "..\\train-images.idx3-ubyte";
	std::string label = "..\\train-labels.idx1-ubyte";
	parser.read(file);
	parser.read_labels(label);
	std::cout << "Printing...\n";
	parser.get_image();
	parser.print_bmp();

	neural_network::Neural_network images_nn(std::vector<int>{784, 100, 10});
	//images_nn.set_train_params(6, 1);
	//images_nn.train(&parser);
	//images_nn.store();
	//std::vector<Matrix<float>> weights = images_nn.read_weights();
	/*std::cout << "Layers: " << result.size() << '\n';
	for (int i = 0; i < result.size(); ++i) {
		std::cout << "Rows: " << result[i].get_row() << ", Colums: " << result[i].get_col() << '\n';
		std::cout << "0 0: " << result[i].get(0, 0) << '\n';
	}//*/
	images_nn.read_weights();
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
    return 0;
}


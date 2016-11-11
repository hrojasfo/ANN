#pragma once
#include "Matrix.h"
#include "Image_parser.h"
#include <vector>
#include <fstream>

namespace neural_network {
	typedef float base;

	class Neural_network
	{
		// layers_size first entry is the inputs size, last is output
		std::vector<int> layers_size; 
		std::vector<Matrix<base>> output;
		std::vector<Matrix<base>> weight;
		int layers = 0;
		base alpha = 0.5;
		int iterations = 10;
		int images = 10;

		void create_internals(const std::vector<int>& in);
		Matrix<base> run();
	public:
		Neural_network();
		Neural_network(const std::vector<int>& in);
		Neural_network(const std::vector<int>& in, base alpha);
		~Neural_network();
		void train(const Matrix<base>& input, const Matrix<base>& expected);
		void train(Image_parser* parser);
		Matrix<base> run(const Matrix<base>& input);
		void store(std::string path = "ann_weights.dat");
		std::vector<Matrix<base>> Neural_network::read_weights(std::string path = "ann_weights.dat");
		void load_weights(std::vector<Matrix<base>> weights);
		void set_train_params(int it = 10, int imgs = 10);

	};

}


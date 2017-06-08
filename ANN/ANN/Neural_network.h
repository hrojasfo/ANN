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
		std::vector<Matrix<base>> weights;
		std::vector<Matrix<base>> bias;
		int layers = 0;
		base alpha = 0.5;
		int epochs = 10;
		int batch_size = 10;

		void create_internals(const std::vector<int>& in);
		Matrix<base> forward();
	public:
		Neural_network();
		Neural_network(const std::vector<int>& in);
		Neural_network(const std::vector<int>& in, base alpha);
		~Neural_network();
		void train(const Matrix<base>& input, const Matrix<base>& expected);
		void train(Image_parser* parser);
		void train(std::string path = "train_data.txt");
		Matrix<base> run(const Matrix<base>& input);
		void store(std::string path = "ann_weights.dat");
		std::vector<Matrix<base>> Neural_network::read_weights_and_bias(std::string path = "ann_weights.dat");
		void load_weights_and_bias(const std::vector<Matrix<base>>& weights);
		void set_train_params(int it = 10, int imgs = 10);

	};

}


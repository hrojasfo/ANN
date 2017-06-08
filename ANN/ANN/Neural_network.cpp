#include "stdafx.h"
#include "Neural_network.h"
#include <iomanip>
#include <sstream>

namespace neural_network {
	// in contains the size for all the layers of the ANN
	void Neural_network::create_internals(const std::vector<int>& in)
	{
		if (in.size() < 2) {
			throw "Layers size must be more than 2";
		}
		layers = in.size();
		layers_size = in;
		// Add entry for inputs
		Matrix<base> out(1, in[0]);
		output.push_back(out);
		for (int i = 1; i < in.size(); ++i) {
			//Matrix<base> w(in[i - 1] + 1, in[i]);
			Matrix<base> w(in[i - 1], in[i], "rand");
			weights.push_back(w);
			Matrix<base> out(1, in[i]);
			output.push_back(out);
			Matrix<base> bia(1, in[i], "rand");
			bias.push_back(bia);
		}
	}

	Neural_network::Neural_network()
	{
	}

	Neural_network::Neural_network(const std::vector<int>& in)
	{
		create_internals(in);
	}

	Neural_network::Neural_network(const std::vector<int>& in, base alpha)
	{
		this->alpha = alpha;
		create_internals(in);
	}


	Neural_network::~Neural_network()
	{
		std::cout << "Destroying network...\n";
	}

	void Neural_network::train(const Matrix<base>& input, const Matrix<base>& expected)
	{
		output[0] = input;

		Matrix<base> last_delta;
		forward();
		for (int i = layers - 1; i > 0; --i) {
			Matrix<base> delta, deltai;
			output[i - 1].transpose_matrix();
			if (i == layers - 1) {
				deltai = output[i].delta_out((Matrix<base>)expected);
			}
			else {
				deltai = last_delta * weights[i].transpose_matrix();
				weights[i].transpose_matrix();
				deltai = deltai.one_to_one_mult(output[i].delta());
			}
			last_delta = deltai;
			deltai.scalar_mult(-alpha);
			delta = output[i - 1] * deltai;
			output[i - 1].transpose_matrix();
			weights[i - 1] = delta + weights[i - 1];
			bias[i - 1] = deltai + bias[i - 1];
			//weights[i - 1].add(delta);
			//bias[i - 1].add(deltai);
		}
	}

	void Neural_network::train(Image_parser* parser)
	{
		for (int i = 0; i < epochs; ++i) {
			std::cout << std::setbase(10) << "-I- Running training iteration " << i << "\n processing images ";
			for (int j = 0; j < batch_size; ++j) {
				//std::cout << j << ' ';
				Matrix<base> input(parser->get_image(j, false));
				Matrix<base> expected(1, layers_size[layers_size.size() - 1], "zeros");
				expected.get(0, parser->get_label(j)) = 1.0;
				int label = parser->get_label(j);
				train(input, expected);
			}
			std::cout << '\n';
		}
	}

	// The format for the train_data is the following:
	// <input entries> <output entries> <size of training data entries>
	// <entry 1 inputs> <entry 1 outputs>
	// <entry 2 inputs> <entry 2 outputs>
	// ...
	void Neural_network::train(std::string path)
	{
		std::ifstream train_data;
		train_data.open(path);
		std::stringstream ss;
		std::string line;
		int in_size;
		int out_size;
		int size;
		std::getline(train_data,line);
		ss.str(line);
		ss >> in_size >> out_size >> size;
		std::cout << "in = " << in_size << " out = " << out_size << " size = " << size << '\n';
		std::vector<Matrix<base>> input;
		std::vector<Matrix<base>> expected;
		// Read all training lines
		for (int t = 0; t < size; ++t) {
			std::getline(train_data, line);
			ss.clear();
			ss.str(line);
			Matrix<base> t_in(1,in_size);
			Matrix<base> t_out(1, out_size);
			// Read inputs
			for (int in = 0; in < in_size; ++in) {
				ss >> t_in.get(0, in);
			}
			// Read outputs
			for (int out = 0; out < out_size; ++out) {
				ss >> t_out.get(0, out);
			}
			input.push_back(t_in);
			expected.push_back(t_out);
		}
		train_data.close();

		// Train the NN
		std::cout << "Iteration ";
		for (int i = 0; i < epochs; ++i) {
			for (int entry = 0; entry < size; ++entry) {
				train(input[entry], expected[entry]);
			}
		}
	}

	Matrix<base> Neural_network::run(const Matrix<base>& input)
	{
		output[0] = input;
		return forward();

	}

	void Neural_network::store(std::string path)
	{
		std::ofstream outfile;
		outfile.open(path, std::ios::binary | std::ios::out);
		int size = weights.size() << 1; // by 2 to include bias
		int half = size >> 1;
		outfile.write((char*)&size, sizeof(int));
		for (int i = 0; i < size; ++i) {
			// store first the weights then the bias
			int row = (i < (size >> 1)) ? weights[i].get_row() : bias[i-half].get_row();
			int col = (i < (size >> 1)) ? weights[i].get_col() : bias[i-half].get_col();
			outfile.write((char*)&row, sizeof(int));
			outfile.write((char*)&col, sizeof(int));
			for (int r = 0; r < row; ++r) {
				for (int c = 0; c < col; ++c) {
					base val = (i < (size >> 1)) ? weights[i].get(r,c) : bias[i-half].get(r,c);
					outfile.write((char*)&val, sizeof(base));
				}
			}
		}
		outfile.close();
	}

	std::vector<Matrix<base>>& Neural_network::read_weights_and_bias(std::string path)
	{
		std::ifstream infile;
		infile.open(path, std::ios::binary | std::ios::in);
		std::vector<Matrix<base>> result;
		int size;
		infile.read((char*)&size, sizeof(int));
		for (int i = 0; i < size; ++i) {
			int row;
			int col;
			infile.read((char*)&row, sizeof(int));
			infile.read((char*)&col, sizeof(int));
			Matrix<base> wi(row,col);
			for (int r = 0; r < row; ++r) {
				for (int c = 0; c < col; ++c) {
					base val;
					infile.read((char*)&val, sizeof(base));
					wi.get(r, c) = val;
				}
			}
			result.push_back(wi);

		}
		infile.close();
		load_weights_and_bias(result);
		return result;
	}

	void Neural_network::load_weights_and_bias(const std::vector<Matrix<base>>& input)
	{
		weights.clear();
		bias.clear();
		int half = input.size() >> 1;
		// weights are in the lower half and bias in the top of the array
		for (int i = 0; i < input.size(); ++i) {
			if (i < half) {
				weights.push_back(input[i]);
			}
			else {
				bias.push_back(input[i]);
			}
		}
	}

	void Neural_network::set_train_params(int it, int imgs)
	{
		epochs = it;
		batch_size = imgs;
	}

	Matrix<base> Neural_network::forward()
	{
		for (int i = 1; i < layers; ++i) {
			output[i] = output[i - 1] * weights[i - 1];
			output[i] = output[i] + bias[i - 1];
			output[i].sigmoid();
		}
		return output[layers - 1];
	}
}

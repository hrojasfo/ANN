#include "stdafx.h"
#include "Image_parser.h"
#include <iomanip>

int Image_parser::get_info(char * arr, int offset, int size)
{
	if (size > 4) {
		std::cout << "Error cant read more that 4 bytes into integer\n";
		return -1;
	}
	int result = 0;
	for (int i = 0; i < size; ++i) {
		result |= arr[offset + i] << (8 * i);
	}
	return result;
}

int Image_parser::get_info_be(char * arr, int offset, int size)
{
	if (size > 4) {
		std::cout << "Error cant read more that 4 bytes into integer\n";
		return -1;
	}
	int result = 0;
	for (int i = 0; i < size; ++i) {
		result <<= 8;
		result |= arr[offset + i];
	}
	return result;
}

void Image_parser::read(std::string path)
{
	std::ifstream image;
	image.open(path, std::ios::binary | std::ios::ate);
	if (image.is_open()) {
		int size = image.tellg();
		memblock = new char[size];
		image.seekg(0, std::ios::beg);
		image.read(memblock, size);
		std::cout << "File size " << size << '\n';
		image.close();

		//images = get_info_be(memblock, 4, 4);
		rows = get_info_be(memblock, 8, 4);
		cols = get_info_be(memblock, 12, 4);
	}
	else {
		std::cout << "-E- Can't open file\n";
	}
}

void Image_parser::read_labels(std::string path)
{
	std::ifstream label_file;
	label_file.open(path, std::ios::binary | std::ios::ate);
	if (label_file.is_open()) {
		int size = label_file.tellg();
		labels = new char[size];
		label_file.seekg(0, std::ios::beg);
		label_file.read(labels, size);
		std::cout << "File size " << size << '\n';
		label_file.close();
	}
	else {
		std::cout << "-E- Can't open file\n";
	}
}

std::vector<float> Image_parser::get_image(int index, bool p)
{
	int offset = rows * cols * index + 16;
	if(p) std::cout << "rows: " << rows << ", columns: " << cols << '\n';
    std::vector<float> result;
	int c = 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			unsigned int temp = memblock[offset + i * rows + j] & 0xff;
			result.push_back( (float)temp );
			//if(p) std::cout << (char)((temp == 0) ? '.' : '*') << ' ';
			if (p) std::cout << std::setbase(16) << std::setfill('0') << std::setw(2) << temp;
		}
		if(p) std::cout << '\n';
	}
	if(p) std::cout << "label: " << (int)labels[index + 8] << '\n';
	return result;
}

std::vector<float> Image_parser::get_image()
{
	return get_image(pointer++,true);
}

int Image_parser::get_label(int index)
{
	return (int)labels[index + 8];
}

void Image_parser::print_bmp()
{
	int offset = get_info(memblock, 0xa, 4);
	int w = get_info(memblock, 0x12, 4);
	int h = get_info(memblock, 0x16, 4);
	int ps = get_info(memblock, 0x1c, 4);

	int row_size = floor((ps * w + 31) / 32) * 4;
	std::cout << "Row size " << row_size << '\n';
	for (int i = h - 1; i >= 0; --i) {
		for (int j = 0; j < w; ++j) {
			int pixel = (j % 2 == 0) ? memblock[offset + (row_size * i) + (j / 2)] >> 4 : memblock[offset + (row_size * i) + (j / 2)];
			pixel &= 0xf;
			std::cout << (char)((pixel == 15) ? '.' : '*') << ' ';
		}
		std::cout << '\n';
	}
}
Image_parser::Image_parser()
{
}


Image_parser::~Image_parser()
{
	if (memblock) {
		delete[] memblock;
	}
}

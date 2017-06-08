#pragma once
#include <fstream>
#include <iostream>
#include <vector>

class Image_parser
{
	char *memblock = nullptr;
	char *labels = nullptr;
	int rows = 0;
	int cols = 0;
	int size = 10000;
	int get_info(char *arr, int offset, int size);
	int get_info_be(char *arr, int offset, int size);
	int pointer = 0;
public:
	void print_bmp();
	void read_images(std::string path);
	void read_labels(std::string path);
    std::vector<float> get_image();
	int get_label(int index);
	std::vector<float> get_image(int index, bool p);
	Image_parser();
	~Image_parser();
};


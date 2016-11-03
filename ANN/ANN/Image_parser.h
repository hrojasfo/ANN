#pragma once
#include <fstream>
#include <iostream>

class Image_parser
{
	std::ifstream image;
	char *memblock;
	int get_info(char *arr, int offset, int size);
public:
	void read_bmp(std::string path);
	void print_bmp();
	Image_parser();
	~Image_parser();
};


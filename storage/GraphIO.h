#pragma once
#ifndef GRAPHIO_H
#define GRAPHIO_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

class GraphIO {
public:
	string filename;
	fstream file;

	GraphIO(string filename, bool overwrite=false, bool bin=true);
	~GraphIO();
	void open(bool overwrite=false);
	void close();
	bool isOpen();

	// Read data from db_file
	template<class T>
	void mapping(T* data, int offset, vector<int>& params) {
		data->readFromFile(file, offset, params);
	}

	// write data back to db_file
	template<class T>
	void unmapping(T* data, int offset, vector<int>& params) {
		data->writeToFile(file, offset, params);
	}

	template<class T>
	void mapping_sizes(T *block, int offset, int size)
	{
		file.seekg(offset);
		file.read((char*)block, size);
	}

	//批处理不需要转移指针
	template<class T>
	void unmapping_size(T* block, int offset, int size)
	{
		file.seekp(offset);
		file.write((char*)block, size);
	}
};

#endif
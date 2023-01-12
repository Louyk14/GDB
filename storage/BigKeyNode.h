#pragma once
#ifndef BIGKEYNODE_H
#define BIGKEYNODE_H

#define BIG_KEY_ORDER 10

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct value_t_int {
	int k;

	value_t_int(int kt = -1) : k(kt) {}

	bool operator <(const value_t_int& b) const {
		return k < b.k;
	}

	bool operator ==(const value_t_int& b) const {
		return k == b.k;
	}

	bool empty() const {
		return k == -1;
	}

	void clear() {
		k = -1;
	}

	int get() {
		return k;
	}
};



struct BigKeyMeta {
	int slot;

	void init(vector<int>& params) {
		slot = 0;
	}

	void readFromFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekg(offset);
		db_file.read((char*)this, sizeof(int));
	}

	void writeToFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.clear();
		db_file.seekp(offset);
		db_file.write((char*)this, sizeof(int));
	}
};

struct BigKeyNodeMeta {
	int next;
	int used_count;

	BigKeyNodeMeta()
	{
		next = 0;
		used_count = 0;
	}
	BigKeyNodeMeta(int n, int u)
	{
		next = n;
		used_count = u;
	}
};

template <class BIG_KEY_VALUE_TYPE>
class BigKeyNode {
public:
	BigKeyNodeMeta meta;
	BIG_KEY_VALUE_TYPE values[BIG_KEY_ORDER];

	void init(vector<int>& params) {
		meta.next = 0;
	}

	void readFromFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekg(offset);
		db_file.read((char*)this, sizeof(BigKeyNode));
	}

	void writeToFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.clear();
		db_file.seekp(offset);
		db_file.write((char*)this, sizeof(BigKeyNode));
	}
};

#endif
#pragma once
#ifndef BPLUSTREENODE_H
#define BPLUSTREENODE_H

#include "BPlusTreeUtils.h"

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

/* meta information of B+ tree */
struct MetaT {
	size_t order; /* `order` of B+ tree */
	size_t value_size; /* size of value */
	size_t key_size;   /* size of key */
					   //size_t internal_node_num; /* how many internal nodes */
					   //size_t leaf_node_num;     /* how many leafs */
	size_t height;            /* height of tree (exclude leafs) */
							  //int slot;        /* where to store new block */
	int root_offset; /* where is the root of internal nodes */
	int leaf_offset; /* where is the first leaf */

	void init(vector<int>& params) {
		
	}

	void readFromFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekg(offset);
		db_file.read((char*)this, sizeof(MetaT));
	}

	void writeToFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekp(offset);
		db_file.write((char*)this, sizeof(MetaT));
	}
};

/* internal nodes' index segment */
template<class KEY_TYPE>
struct index_t {
	KEY_TYPE key;
	int child; /* child's offset */
};

/***
* internal node block
***/
template<class KEY_TYPE>
struct InternalNode {
public:
	typedef index_t<KEY_TYPE> * child_t;

	int parent; /* parent node offset */
	int next;
	int prev;
	size_t n; /* how many children */
	bool is_leaf;
	InternalNode() {
		n = 1;
		parent = -1;
		next = -1;
		prev = -1;
		is_leaf = false;
	}
	index_t<KEY_TYPE> children[BP_ORDER];

	void init(vector<int>& params)
	{
		n = 1;
		parent = -1;
		next = -1;
		prev = -1;
		is_leaf = false;

		// Is it necessary to initialize children ?
	}

	void readFromFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekg(offset);
		db_file.read((char*)this, sizeof(InternalNode));
	}

	void writeToFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekp(offset);
		db_file.write((char*)this, sizeof(InternalNode));
	}
};

/* the final record of value */
template<class KEY_TYPE, class VALUE_TYPE>
struct record_t {
	KEY_TYPE key;
	VALUE_TYPE value;
};

/* leaf node block */
template<class KEY_TYPE, class VALUE_TYPE>
class LeafNode {
public:
	typedef record_t<KEY_TYPE, VALUE_TYPE> *child_t;

	int parent; /* parent node offset */
	int next;
	int prev;
	size_t n;
	bool is_leaf;
	LeafNode(int _n = 0, int par = -1, int nex = -1, int pre = -1, bool isleaf = true) {
		n = _n;
		parent = par;
		next = nex;
		prev = pre;
		is_leaf = isleaf;
	}
	record_t<KEY_TYPE, VALUE_TYPE> children[BP_ORDER];

	void init(vector<int>& params)
	{
		n = 0;
		parent = -1;
		next = -1;
		prev = -1;
		is_leaf = true;
	}

	void readFromFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekg(offset);
		db_file.read((char*)this, sizeof(LeafNode));
	}

	void writeToFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekp(offset);
		db_file.write((char*)this, sizeof(LeafNode));
	}
};

#endif
#pragma once
#ifndef IDPOOL_H
#define IDPOOL_H

#include "GraphIO.h"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;

class IDPool {
public:
	IDPool(bool zs=false);
	IDPool(string idfile, bool zs=false);

	int maxId;
	unordered_set<int> emptyIds;
	int idNum;
	bool zeroStart;
	bool createNew;

	void set(int mId);
	void set(int mId, vector<int>& existIds);
	bool existId(int node);
	int nextId();
	void removeId(int id);
	bool newAlloted() { return createNew; }
};

class IDPoolDisk {
public:
	IDPoolDisk(string sfile, bool overwrite=false, bool zs = false);
	IDPoolDisk(IDPoolDisk* pool, string newname);
	IDPoolDisk() { }

	~IDPoolDisk();

	int maxId;
	unordered_set<int> emptyIds;
	int idNum;
	bool zeroStart;
	bool createNew;
	string storefile;
	GraphIO* gIO;

	void set(int mId);
	void set(int mId, vector<int>& existIds);
	bool existId(int node);
	int nextId();
	void removeId(int id);
	bool newAlloted() { return createNew; }

	void readFromFile(fstream& db_file, int offset) {
		db_file.seekg(offset);
		db_file.read((char*)&maxId, sizeof(int));
		db_file.read((char*)&idNum, sizeof(int));
		int t;
		while (db_file.read(reinterpret_cast<char*>(&t), sizeof(int))) {
			emptyIds.insert(t);
		}
		// emptyindex.resize(maxId - idNum);
		// db_file.read(reinterpret_cast<char*>(&emptyindex[0]), sizeof(int)*(maxId - idNum));
		// emptyIds = unordered_set<int>(emptyindex.begin(), emptyindex.end());
	}

	void writeToFile(fstream& db_file, int offset) {
		db_file.clear();
		db_file.seekp(offset);
		db_file.write((char*)&maxId, sizeof(int));
		db_file.write((char*)&idNum, sizeof(int));
		for (const auto& t : emptyIds) {
			db_file.write(reinterpret_cast<const char*>(&t), sizeof(int));
		}
		//db_file.write(reinterpret_cast<char*>(&emptyindex[0], sizeof(int)*emptyindex.size()));
	}
};

#endif
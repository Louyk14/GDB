#pragma once

#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class StorageMeta {
public:
	int slot;
	int nodenum;
	int commnum;
	int idtype;
	int commtype;
	int istemporal;
	char iddefault[256];
	char commdefault[256];
	char schemaid[256];
	char createtime[256];

	StorageMeta(int s = 0, int nn = 0) : slot(s), nodenum(nn) {}
	StorageMeta(const StorageMeta& meta) { slot = meta.slot; nodenum = meta.nodenum;  commnum = meta.commnum;  }

	void init(vector<int>& params)
	{
		slot = 0;
		nodenum = 0;
		commnum = 0;
	}

	void readFromFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekg(offset);
		db_file.read((char*)(&slot), sizeof(int));
		db_file.read((char*)(&nodenum), sizeof(int));
		db_file.read((char*)&commnum, sizeof(int));
		db_file.read((char*)&idtype, sizeof(int));
		db_file.read((char*)&commtype, sizeof(int));
		db_file.read((char*)&istemporal, sizeof(int));
		db_file.read((char*)(iddefault), sizeof(char) * 256);
		db_file.read((char*)(commdefault), sizeof(char) * 256);
		db_file.read((char*)(schemaid), sizeof(char) * 256);
		db_file.read((char*)(createtime), sizeof(char) * 256);
	}

	void writeToFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.clear();
		db_file.seekp(offset);
		db_file.write((char*)(&slot), sizeof(int));
		db_file.write((char*)(&nodenum), sizeof(int));
		db_file.write((char*)(&commnum), sizeof(int));
		db_file.write((char*)(&idtype), sizeof(int));
		db_file.write((char*)(&commtype), sizeof(int));
		db_file.write((char*)&istemporal, sizeof(int));
		db_file.write((char*)(iddefault), sizeof(char) * 256);
		db_file.write((char*)(commdefault), sizeof(char) * 256);
		db_file.write((char*)(schemaid), sizeof(char) * 256);
		db_file.write((char*)(createtime), sizeof(char) * 256);
		// db_file.write((char*)this, sizeof(StorageMeta));
	}
};
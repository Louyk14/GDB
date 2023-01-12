#pragma once
#ifndef GRAPHSETMANAGER_H
#define GRAPHSETMANAGER_H

#include "GraphIO.h"
#include "../GraphDatabase.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
using namespace std;

class GraphDatabase;
class GraphManager;

class GraphSetManager {
public:
	string name;
	string base_dir;
	GraphDatabase* gdb;
	unordered_map<string, string> gManagers;
	unordered_map<string, int> graphAuth;
	GraphIO* gIO;

	GraphSetManager(string name, GraphDatabase* db);
	GraphSetManager(string name, GraphDatabase* db, vector<string>& aliasg);
	~GraphSetManager();

	bool registerGraphFirstTime(string gname, int auth = 0); // 0 - read only, 1 - read or write
	bool registerGraph(string gname, string gtime, int auth = 0); // 0 - read only, 1 - read or write
	bool returnGraph(string gname, int auth=0);
	void removeGraph(string gname);

	bool login();
	bool logout();
	void close();

	GraphManager* getGraph(string gname);

	void readFromFile(fstream& db_file, int offset, vector<int>& params) {
		string t;
		string gtime;
		while (db_file >> t >> gtime) {
			gManagers[t] = gtime;
		}
		// emptyindex.resize(maxId - idNum);
		// db_file.read(reinterpret_cast<char*>(&emptyindex[0]), sizeof(int)*(maxId - idNum));
		// emptyIds = unordered_set<int>(emptyindex.begin(), emptyindex.end());
	}

	void writeToFile(fstream& db_file, int offset, vector<int>& params) {
		for (auto& t : gManagers) {
			db_file << t.first << " " << t.second << endl;
		}
		//db_file.write(reinterpret_cast<char*>(&emptyindex[0], sizeof(int)*emptyindex.size()));
	}
};

#endif
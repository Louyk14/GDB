#pragma once
#ifndef RDB_H
#define RDB_H

#include "RDBHandler.h"
#include "GraphManager.h"

#include "sqlite3.h"
#include <string>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>

class GraphManager;

using namespace std;

class RDB {
public:
	sqlite3* db;
	string dbname;
	RDBHandler handler;

	unordered_map<string, int> attrType;
	unordered_map<string, vector<string>> defaultval;

	// 0 <-> undefined, start from 1
	vector<string> edgetype2tablename;
	unordered_map<string, int> tablename2edgetype;
	vector<string> nodetype2tablename;
	unordered_map<string, int> tablename2nodetype;

	RDB(string base_dir, string& dbname);
	~RDB();

	void connect_sqlite();
	void disconnect_sqlite();

	bool isOpen() { return db != 0; };

	string upper_str(string& str);
	void parseCreate(string& tablename, string& stmt, unordered_map<string, int>& attrType);

	void initNodeTable(string filename, unordered_map<int, int>& nodetypes);
	void initEdgeTable(string filename);

	void insertIntoNodeTable(string filename, GraphManager* gm);
	void insertIntoEdgeTable(string filename, GraphManager* gm);

	void createTable(GraphManager* gm);

	void insertNewKey(int type, vector<string>& attributes);
	void removeKey(int node_id, int type);

	string getType(int code);
};

#endif
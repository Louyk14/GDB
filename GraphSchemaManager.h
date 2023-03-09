#pragma once
#ifndef GRAPHSCHEMAMANAGER_H
#define GRAPHSCHEMAMANAGER_H

#include "GraphSchema.h"

#include <io.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

class GraphSchemaManager {
public:
	string base_dir;
	unordered_map<string, GraphSchema*> schemas;

	GraphSchemaManager(string dir);
	~GraphSchemaManager();
	bool loadSchema(string sname);
	bool loadAllSchema();
	void createSchema(string schemaname, unordered_map<string, vector<pair<string, string>>>& nodeAttrMap, unordered_map<string, vector<pair<string, string>>>& edgeAttrMap, unordered_map<string, vector<pair<string, string>>>& schemaNetwork);
	void createSchema(string filename);
	void dropSchema(string& schemaname);
	void dispatchSchema(string& gname, string& schemaname, GraphSchema*& gschema, int type); // 0: graph, 1: graph set

	bool hasSchema(string& schemaname);
};

#endif
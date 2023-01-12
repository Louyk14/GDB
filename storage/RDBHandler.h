#pragma once
#ifndef RDBHANDLER_H
#define RDBHANDLER_H

#include "sqlite3.h"

#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct RETURNTYPE {
	static const int INT_TYPE = 1;
	static const int DOUBLE_TYPE = 2;
	static const int BOOL_TYPE = 3;
	static const int STRING_TYPE = 4;
};

class RDBHandler {
public:
	int execute(sqlite3* &db, string& sql);
	string generateInsertSQL(string table, vector<string>& attributes, vector<string>& defaultVal);
	string generateDeleteSQL(string table, int node_id);
};

#endif
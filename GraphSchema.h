#pragma once
#ifndef GRAPHSCHEMA_H
#define GRAPHSCHEMA_H

#include "storage\GraphIO.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


class GraphSchema {
public:
	GraphSchema(string file);
	GraphSchema(string file, string base_dir, unordered_map<string, GraphSchema*>& schemas, bool& succ);
	GraphSchema(string file, string schemaname, unordered_map<string, vector<pair<string, string>>>& nodeAttrMap, unordered_map<string, vector<pair<string, string>>>& edgeAttrMap, unordered_map<string, vector<pair<string, string>>>& schemaNetwork);
	~GraphSchema();
	string name;
	int nodenum;
	int edgenum;
	int edgelabelnum;
	vector<string> nodelabels; // 10 chars at most
	vector<string> edgelabels;
	unordered_map<string, int> nodenamemap;
	unordered_map<string, int> edgenamemap;
	vector<unordered_map<int, vector<int>>> network;
	unordered_map<int, vector<pair<string, int>>> nodelabeltoattr;
	unordered_map<int, vector<pair<string, int>>> edgelabeltoattr;
	vector<string> relatedgraphs;
	vector<string> relatedgraphsets;

	GraphIO* gIO;

	void addRelatedGraph(string& gname) {
		relatedgraphs.push_back(gname);
	}

	void addRelatedGraphSet(string& gsname) {
		relatedgraphsets.push_back(gsname);
	}

	int returnTypeCode(string& typestr) {
		for (int i = 0; i < typestr.size(); ++i) {
			typestr[i] = toupper(typestr[i]);
		}
		if (typestr == "INT" || typestr == "INTEGER")
			return 0;
		else if (typestr == "CHAR")
			return 1;
		else if (typestr == "STRING")
			return 2;
		else if (typestr == "FLOAT")
			return 3;
		else if (typestr == "DOUBLE")
			return 4;
	}

	string returnTypeStr(int code) {
		if (code == 0)
			return "INTEGER";
		else if (code == 1)
			return "CHAR";
		else if (code == 2)
			return "STRING";
		else if (code == 3)
			return "FLOAT";
		else if (code == 4)
			return "DOUBLE";
	}

	void readFromFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekg(offset);
		db_file >> name;
		db_file >> nodenum >> edgenum >> edgelabelnum;
		network = vector<unordered_map<int, vector<int>>>(nodenum + 1);
		// unordered_map<string, int> nodenamemap;
		// unordered_map<string, int> edgenamemap;
		string tmp;
		int attrnum;
		string attrname;
		string attrtype;
		for (int i = 0; i < nodenum; ++i) {
			db_file >> tmp >> attrnum;
			nodelabels.push_back(tmp);
			nodenamemap[tmp] = i + 1;
			for (int j = 0; j < attrnum; ++j) {
				db_file >> attrname >> attrtype;
				nodelabeltoattr[i + 1].push_back(make_pair(attrname, returnTypeCode(attrtype)));
			}
		}
		for (int i = 0; i < edgelabelnum; ++i) {
			db_file >> tmp >> attrnum;
			edgelabels.push_back(tmp);
			edgenamemap[tmp] = i + 1;
			for (int j = 0; j < attrnum; ++j) {
				db_file >> attrname >> attrtype;
				edgelabeltoattr[i + 1].push_back(make_pair(attrname, returnTypeCode(attrtype)));
			}
		}
		for (int i = 0; i < edgenum; ++i) {
			string src, relation, dst;
			db_file >> src >> relation >> dst;
			int srcint = nodenamemap[src];
			int dstint = nodenamemap[dst];
			int relint = edgenamemap[relation];
			network[srcint][dstint].push_back(relint);
		}
		int relgnum, relgsnum;
		db_file >> relgnum;
		for (int i = 0; i < relgnum; ++i) {
			string g;
			db_file >> g;
			relatedgraphs.push_back(g);
		}
		db_file >> relgsnum;
		for (int i = 0; i < relgsnum; ++i) {
			string gs;
			db_file >> gs;
			relatedgraphsets.push_back(gs);
		}
	}

	void writeToFile(fstream& db_file, int offset, vector<int>& params) {
		db_file.seekp(offset);
		db_file << name << endl;
		db_file << nodenum << " " << edgenum << " " << edgelabelnum << endl;

		for (int i = 0; i < nodenum; ++i) {
			db_file << nodelabels[i] << " " << nodelabeltoattr[i + 1].size() << " ";
			for (int j = 0; j < nodelabeltoattr[i + 1].size(); ++j) {
				db_file << nodelabeltoattr[i + 1][j].first << " " << returnTypeStr(nodelabeltoattr[i + 1][j].second);
				if (j != nodelabeltoattr[i + 1].size() - 1)
					db_file << " ";
			}
			db_file << endl;
		}
		
		for (int i = 0; i < edgelabelnum; ++i) {
			db_file << edgelabels[i] << " " << edgelabeltoattr[i + 1].size() << " ";
			for (int j = 0; j < edgelabeltoattr[i + 1].size(); ++j) {
				db_file << edgelabeltoattr[i + 1][j].first << " " << returnTypeStr(edgelabeltoattr[i + 1][j].second);
				if (j != edgelabeltoattr[i + 1].size() - 1)
					db_file << " ";
			}
			db_file << endl;
		}
		
		for (int i = 0; i < network.size(); ++i) {
			if (network[i].empty())
				continue;
			for (const auto& n2 : network[i]) {
				for (const auto& el : n2.second) {
					db_file << nodelabels[i - 1] << " " << edgelabels[el - 1] << " " << nodelabels[n2.first - 1] << endl;
				}
			}
		}

		int relgnum = relatedgraphs.size();
		int relgsnum = relatedgraphsets.size();
		db_file << relgnum;
		for (int i = 0; i < relgnum; ++i) {
			db_file << relatedgraphs[i];
			if (i != relgnum)
				db_file << " ";
		}
		db_file << endl;
		db_file << relgsnum;
		for (int i = 0; i < relgsnum; ++i) {
			db_file << relatedgraphsets[i];
			if (i != relgsnum)
				db_file << " ";
		}
		db_file << endl;
	}
};

#endif
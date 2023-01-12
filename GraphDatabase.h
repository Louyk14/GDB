#pragma once
#ifndef GRAPHDATABASE_H
#define GRAPHDATABASE_H

#include "parser\GraphParser.h"
#include "storage\GraphSetManager.h"
#include "storage\GraphManager.h"
#include "GraphSchemaManager.h"
#include "GraphProcessor.h"
#include "storage\GraphLoader.h"
#include "GraphSchema.h"
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <iostream>
using namespace std;

class GraphSetManager;
class GraphProcessor;
class GraphLoader;

class GraphDatabase {
public:
	string gsetdir;
	string gdir;
	string schemadir;

	GraphDatabase();
	~GraphDatabase();
	void run();
	void close();

	void createGraph(string gname, vector<string>& filelist, string& schemaid);
	void loadGraph(string gname);
	bool dispatchGraph(string gname, string& gtime, GraphSetManager* gm, int auth=0);
	bool retrieveGraph(string gname, GraphSetManager* gm, int auth=0);
	void callbackGraph(string gname);

	void createGraphSet(string gsname, vector<string>& aliasgraph);
	bool loadGraphSet(string gsname);
	void addGraphSet(GraphSetManager* gm);
	void removeGraphSet(GraphSetManager* gm, unordered_map<string, int>& graphAuth);
	void linkGraphToGraphSet(string gname, string gsname);
	void dropGraphSet(string gsname);
	void dropGraph(string gname);
	void dropSchema(string schemaname);

	bool hasGraph(string gname);
	bool hasGraphSet(string gsname);
	bool getGraph(string gname, GraphManager*& gm);
	bool getGraphSet(string gsname, GraphSetManager*& gsm);

	void createSchema(string schemaname, SchemaAttrMap& nodeAttrMap, SchemaAttrMap& edgeAttrMap, SchemaNetwork& schemaNetwork);
	void createSchema(string filename);

	void insertIntoGraphSet(string gsname, vector<string>& gidlist);
	void removeFromGraphSet(string gsname, vector<string>& gidlist);

	void insertIntoGraph(GraphStat& gs, string& gid);
	void removeFromGraph(GraphStat& gs, string& gid);

	GraphParser* gParser;
	GraphProcessor* gProcessor;
	GraphLoader* gLoader;

	unordered_map<string, GraphSetManager*> gsetManager; //all the graph sets in the graph
	GraphSchemaManager* gschemaManager;
	unordered_map<string, GraphManager*> graphs; // all the graphs already maintained in the graph;
	unordered_map<string, unordered_set<GraphSetManager*>> readAuthority;
	unordered_map<string, unordered_set<GraphSetManager*>> writeAuthority;
};

#endif
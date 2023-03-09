#include <iostream>
#include <fstream>
#include <chrono>
//#include "colors.h"
#include "parser\GraphParser.h"
#include "storage\GraphManager.h"
#include "GraphDatabase.h"
#include"server/GDBServer.h"
//#include "JsonUtil.h"

using std::cerr;
using std::cout;
using std::endl;
using std::cin;
using std::ofstream;

#pragma comment(lib, "antlr4-runtime-d.lib")
//#pragma comment(lib, "antlr4-runtime.lib")

int main(int argc, char** argv) {
	GDBServer* server = new GDBServer();
	server->StartDatabase();
	//server->RunGreeterServer();
	server->StopDatabase();

	delete server;
	return 0;

	GraphDatabase* gdb = new GraphDatabase();
	
	gdb->run();

	gdb->close();
	delete gdb;
	return 0;
	//string data = "dataset/subgraphmatching/data/1000/network.dat";//string(argv[1]);
	//string tempdata = "dataset/temporal/college/network.txt";
	//string pattern = "dataset/subgraphmatching/pattern/p3.dat";//string(argv[2]);
	//string community = "dataset/subgraphmatching/data/1000/community.dat";
	string networkfile = "dataset/storage/100/network.dat";
	string communityfile = "dataset/storage/100/community.dat";

	string dbname = "g100";
	int block_listnum = 15;
	int list_edgenum = 15;
	double ava_threshold = 0.5;
	int cachesize = 100;

	// BPlusTree Index for NodeBlockPos
	string leaf_file = dbname;
	string internal_file = dbname;
	int leaf_cache_size = 3;
	int internal_cache_size = 3;
	bool tree_empty = false;
	bool overwrite = false;
	bool firsttime = false;

	string big_key_file = dbname;
	int big_key_cache_size = 10;

	GraphManager* graph = new GraphManager(dbname, block_listnum, list_edgenum, ava_threshold, cachesize,
		leaf_file, internal_file, leaf_cache_size, internal_cache_size,
		big_key_file, big_key_cache_size, tree_empty, overwrite, firsttime);

	//graph->setInMemory();

	if (overwrite) {
		graph->store(networkfile, communityfile);
	}

	//graph->loadMemoryGraph(1);

	GraphManager* g = new GraphManager();
	g->copyFrom(graph, "g100fake");

	delete graph;
	delete g;

	system("pause");
	return 0;
	cout << "finish Store " << endl;
	TempGraph newGraph;
	graph->gLoader->loadNetworkReg(*graph, newGraph, "insert.txt");
	graph->gUpdater->insertDataV1(*graph, newGraph);

	return 0;
}

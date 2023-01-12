#pragma once
#ifndef GRAPHLOADER_H
#define GRAPHLOADER_H

#include "GraphManager.h"
#include "..\MemoryGraph.h"
//#include "GDBDataGraph.h"
#include "TempGraph.h"

#include <string>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

class GraphManager;
class MemoryGraph;
class TempGraph;

class GraphLoader {
public:
	void readCommunity(MemoryGraph& graph, const string& pathFile, string idpath);
	void readGraphFromFile(MemoryGraph& graph, string file, string labelfile="");
	void readNetworkFromFile(MemoryGraph& graph, string file);
	void readLabelFromFile(MemoryGraph& graph, string file);
	void initAfterReadNetwork(MemoryGraph& graph, string labelfile="");

	void loadCommunityNodes(MemoryGraph& graph, string& community_nodes_path);
	void writeCommunityNodes(MemoryGraph& graph, string& community_nodes_path);

	void loadNodeBlocks(MemoryGraph& graph, string& node_block_path);
	void writeNodeBlocks(MemoryGraph& graph, string& node_block_path);

	void loadEdgeDestHead(MemoryGraph& graph, string& edh_path);
	void writeEdgeDestHead(MemoryGraph& graph, string& edh_path);

	// Load Into TempGraph
	void loadNetworkReg(GraphManager& g, TempGraph& graph, string filename);
};

#endif
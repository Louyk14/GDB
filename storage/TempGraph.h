#pragma once
#ifndef TEMPGRAPH_H
#define TEMPGRAPH_H

#include "IdAlloter.h"
#include "..\parser\definations.h"
#include "GraphManager.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
using namespace std;

class GraphManager;

class TempGraph
{
public:
	TempGraph() : maxNodeId(-1), maxCommId(-1) {};
	TempGraph(GraphStat& gs, GraphManager* gm);
	~TempGraph() {};

	unordered_map<int, unordered_map<int, vector<int>>> netWorkSet;
	unordered_map<int, int> nodeEdges;
	unordered_set<int> storedStarts; // All nodes already in DataGraph that is the src of an edge
	unordered_set<int> unstored;     // All nodes in netWorkSet that is new
	unordered_set<int> stored;       // All nodes already in DataGraph
	unordered_map<int, int> nodeCommunity;
	unordered_map<int, unordered_set<int>> lpaCommunityNode;

	// For Data Insert
	unordered_map<int, int> node_startEdge;
	unordered_map<int, unordered_map<int, vector<int>>::iterator> destIter;
	unordered_map<int, vector<int>::iterator> typeIter;

	void insertFirstNode(int node, bool newAlloted);
	void insertSecondNode(int node, bool newAlloted);

	int maxNodeId, maxCommId;
};

#endif
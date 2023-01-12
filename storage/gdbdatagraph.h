#pragma once
#ifndef GDBDATAGRAPH_H
#define GDBDATAGRAPH_H

#include "GDBEdge.h"
#include "IdAlloter.h"

#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

class GDBDataGraph
{
public:
	GDBDataGraph();
	~GDBDataGraph();
	void init(int n, int m);
	bool existNode(int node);
	void insertNode(int node, vector<int>& comm_id, bool resize = false);
	void removeNode(int node);
	bool nodeHasCommunity(int node);
	int getNodeFirstCommunity(int node);
	int nodeNum();
	int communityNum();
	void reAllotNodeSpace(int nodeId);
	void reAllotCommSpace(int commId);

//NodeId: 1, 2, ...
//CommunityId: 1, 2, ...

	IdAlloter<string> nodeIdAlloter;
	IdAlloter<string> communityIdAlloter;

	vector<unordered_set<int>> communityNodes;
	vector<unordered_set<int>> nodeCommunitySet;
	vector<unordered_map<int, vector<int>>> netWork;
	vector<unordered_map<int, vector<int>>::iterator> destIter;
	vector<vector<int>::iterator> typeIter;
	vector<int> nodeEdges;
	vector<int> initialNodes;
	unordered_set<int> graphNodes;
	//unordered_map<int, int> nodeEdges;
	unordered_map<int, unordered_map<int, unordered_set<int>>> commNetworkSet;
	unordered_map<int, unordered_set<int>> netWorkSet;//保存所有边便于查找

	vector<EdgePos> edge_dest_head;
	vector<unordered_set<int>> nodeblock; //结点在哪些block中
	unordered_map<int, int> nodeType;
};


#endif
#pragma once
#ifndef MEMORYGRAPH_H
#define MEMORYGRAPH_H

#include "storage\GraphLoader.h"
#include "storage\GDBEdge.h"
#include "storage\IdAlloter.h"
#include <iostream>
#include <map>
#include <unordered_map>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <algorithm>
using namespace std;

class GraphLoader;

struct LabelVList
{
public:
	int label;
	unordered_set<int> vList;
};

struct degmodel
{
	int degree;
	int node_id;
};

static bool mydegcomp(const degmodel& a, const degmodel& b)
{
	return a.degree < b.degree;
}

struct DegreePos {
	int degree;
	int pos;
};


class MemoryGraph {
public:
	MemoryGraph();
	MemoryGraph(vector<int> n, unordered_map<int, unordered_map<string, string>>* na
		, unordered_map<int, unordered_map<int, unordered_map<string, string>>>* ea
		, vector<unordered_map<int, vector<int>>>* oe, vector<unordered_map<int, vector<int>>>* ie, int labnum
		, vector<int>* nl = NULL);
	MemoryGraph(string file, string labelfile="");
	MemoryGraph(MemoryGraph* mg);
	~MemoryGraph();

	void setInfo(int nnum, int cnum, int nodetype, int commtype, string path, string ndval, string commdvale);
	void initIdAlloter();

	//void loadFromFile(string file, string labelfile="");
	//void loadNetworkFromFile(string file);
	void initAfterLoadNetwork();
	//void loadLabelFromFile(string file);
	void preprocess();

	int communityNum;
	int nodeNum;
	int labelnum;
	//int edgeNum;
	int maxCommSize;
	bool hasNodeLabel;
	bool hasEdgeLabel;
	GraphLoader* gLoader;

	vector<int> nodes;
	vector<int> communities;
	//set<int> graphNodes;
	//vector<vector<int>> communityNodes;
	// unordered_map<int, vector<int>> communityNodes;
	vector<vector<int>> nodeInfo; //0 - Community, 1 - Label
	vector<int> nodeLabels;
	vector<vector<vector<unordered_set<int>>>> commNetworkSet; // node - community - label - neighbours
	vector<unordered_map<int, vector<int>>> netWorkSet;//保存所有边便于查找
	vector<vector<int>> netWorkVec;
	//unordered_map<int, unordered_map<int, unordered_set<int>>> netWorkSetComm;
	//vector<unordered_set<int>> inNetWorkSet;
	//vector<vector<int>> inNetWorkVec;

	vector<vector<vector<vector<DegreePos>>>> degreePosOut;
	vector<vector<vector<vector<DegreePos>>>> degreePosIn;
	vector<vector<vector<vector<int>>>> commOutBoundary;
	vector<vector<vector<vector<int>>>> commInBoundary;
	//vector<vector<unordered_map<int, unordered_map<int, int>>>> twoHopLimitation;

	vector<vector<vector<unordered_map<int, int>*>>> twoHopLimitation;
	//vector<vector<vector<vector<int>>>> twoHopLimitation;
	vector<vector<vector<bool>>> hasTwoHopComms;
	vector<vector<vector<vector<bool>>>> len4Limitation;
	vector<vector<vector<bool>>> triangleLimitation;
	vector<vector<vector<vector<vector<bool>>>>> len5Limitation;
	//vector<vector<vector<vector<int>>>> hasTwoHopLabels;

	vector<vector<int>> commTotalNumTag, commMaxNumTag;
	//int** commTotalNumTag;
	//int** commMaxNumTag;

	unordered_map<int, unordered_map<int, unordered_map<int, degmodel>>> commOuts, commIns;

	//unordered_map<int, unordered_set<int>> graphEqualNodes;
	//unordered_set<int> includedNodes;
	//unordered_map<int, unordered_map<int, unordered_set<int>>> needMoreSet;

	void readCommunity(const string& pathFile);
	
	bool inMemory;
	int outMaxDegree;
	int inMaxDegree;
	int maxDegree;
	vector<vector<int>> labelList;
	//vector<vector<LabelVList*>> labelNetWorkVec; // include all labels, without is null

	unordered_map<int, unordered_map<string, string>>* nodeAttributes;
	unordered_map<int, unordered_map<int, unordered_map<string, string>>>* edgeAttributes;
	vector<unordered_map<int, vector<int>>>* outedges;
	vector<unordered_map<int, vector<int>>>* inedges;
	vector<vector<int>>* invec;
	vector<vector<int>>* outvec;
	vector<int>* outvecp;
	vector<vector<LabelVList*>>* labelEdgesVec;
	unordered_map<int, unordered_set<int>> neighLabels;

	// subgraph matching related
	int* degrees;;
	double avgdegree;
	int* largerbound;
	int edgenum;
	vector<int> idMapping;
	
	// Storage related
	
	int nodeIdAlloterType, communityIdAlloterType; // 0 - i2i, 1 - s2i
	union {
		IdAlloter<int>* i2iAlloter;
		IdAlloter<string>* s2iAlloter;
	} nodeIdAlloter;
	union {
		IdAlloter<int>* i2iAlloter;
		IdAlloter<string>* s2iAlloter;
	} communityIdAlloter;
	
	vector<vector<int>> communityNodes;
	vector<unordered_set<int>> nodeCommunitySet;
	vector<unordered_map<int, vector<int>>::iterator> destIter;
	vector<vector<int>::iterator> typeIter;
	vector<int> nodeEdges;
	vector<int> initialNodes;
	unordered_set<int> graphNodes;
	vector<EdgePos> edge_dest_head;
	vector<unordered_set<int>> nodeblock;
	unordered_map<int, int> nodeType;
	unordered_map<int, int> node_startEdge;

	void initNetwork(int n);
	void initCommunity(int m, int n);
	void init(int n, int m);
	bool existNode(int node);
	void insertNode(int node, vector<int>& comm_id, bool resize = false);
	void removeNode(int node);
	bool nodeHasCommunity(int node);
	int getNodeFirstCommunity(int node);
	int getNodeNum();
	int getCommunityNum();
	int getMaxNodeId();
	int getMaxCommunityId();
	void reAllotNodeSpace(int nodeId);
	void reAllotCommSpace(int commId);
	
	bool hasEdge(int src, int dst)
	{
		return (netWorkSet[src].find(dst) != netWorkSet[src].end());
	}

	bool HasEdge(int src, int dst) {
		return ((*outedges)[src].find(dst) != (*outedges)[src].end());
	}

	void addEdge(int src, int dst, int type) {
		netWorkSet[src][dst].push_back(type);
		netWorkVec[src].push_back(dst);
	}

	void getdegrees();
};

#endif
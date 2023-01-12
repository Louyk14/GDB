#pragma once
#ifndef GRAPHUPDATER_H
#define GRAPHUPDATER_H

#include "LPAT.h"
#include "GraphManager.h"
#include "TempGraph.h"

#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

class GraphManager;

class GraphUpdater {
public:
	GraphUpdater() {};
	~GraphUpdater() {};

	void buildTempGraph(GraphManager& g, TempGraph& d_graph);

	bool getNodeCommunity(GraphManager& g, TempGraph& d_graph);
	void getNodeEdgesInBlocks(GraphManager& g, unordered_set<int>& nodes, set<int>& blocks, unordered_map<int, int>& edgecount, unordered_map<int, unordered_set<int>>& network);
	int assignNodeToBlock(GraphManager& g, int node, GDBBlock* block, int blockIndex, unordered_map<int, unordered_map<int, vector<int>>>& newNetwork
		, unordered_map<int, int>& nodeedges, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, int&startEdge);
	
	void removeEdge(GraphManager& g, GDBBlock* block, int list_index, int edge_index, int blockIndex, int edge_num);
	void assignEdge(GraphManager& g, GDBBlock* block, int node, int dest_id, int list_index, int edge_index, int blockIndex);

	void insertDataV1(GraphManager& g, TempGraph& d_graph);
	bool insertData(GraphManager& g, TempGraph& d_graph);
	void insertNodeOneBlockExistList(GraphManager& g, int node, unordered_map<int, vector<int>>&edges, int &alledges, int& startEdge
		, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, int blockIndex);
	void insertNodeToBlocksExistList(GraphManager& g, int node, unordered_map<int, vector<int>>&edges, int& alledges, int& startEdge
		, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, unordered_set<int>&blocklist);
	void insertNodeOneBlockNewList(GraphManager& g, int node, int cid, unordered_map<int, vector<int>>&edges, int& alledges, int& startEdge
		, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, int offset);
	void insertNodeToBlocksNewList(GraphManager& g, int node, int cid, unordered_map<int, vector<int>>&edges, int& alledges, int& startEdge
		, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, unordered_set<int>&blocklist);

	int insertNodeToBlock(GraphManager& g, int comid, vector<int>&nodes, unordered_map<int, unordered_map<int, vector<int>>>& newNetwork
		, unordered_map<int, int>& nodeedges, unordered_map<int, unordered_map<int, vector<int>>::iterator>& destIter
		, unordered_map<int, vector<int>::iterator>& typeIter, unordered_map<int, int>&node_startEdge, unordered_map<int, unordered_set<int>>& blockedges
		, unordered_map<int, int>& blockedgenum, int blockIndex, CacheNode<GDBBlock>* avaBlock);

	int insertNewNode(GraphManager& g, int node_id, int type, vector<int>& comm_id, vector<string>& attributes, bool resize);
	void insertNewKey(GraphManager& g, int node_id, int type, vector<string>& attributes);

	void linkPreNext(GraphManager& g, GDBBlock* pre_block, GDBEdge* preEdge, GDBBlock* block, GDBEdge* delEdge, int blockIndex);
	void adjustPre(GraphManager& g, GDBBlock* block, int i, int j, int blockIndex, int tar_i, int tar_j, int tar_blockIndex);
	void removeRegionAvaBlock(GraphManager& g, int cid, GDBBlock* block, int blockIndex);
	void insertRegionAvaBlock(GraphManager& g, GDBRegion* region, GDBBlock* block, int blockIndex);

	void deleteEdgeFromBlocksNodes(GraphManager& g, unordered_set<int>& nodes, unordered_map<int, unordered_map<int, vector<int>>>&newNetwork, unordered_set<int>& blocklist);
	void deleteData(GraphManager& g, unordered_map<int, unordered_map<int, vector<int>>>& newNetwork);
	void deleteNodeEdges(GraphManager& g, int node_id);
	void deleteNodeInEdges(GraphManager& g, int node);
	bool deleteNode(GraphManager& g, int node_id);
};

#endif
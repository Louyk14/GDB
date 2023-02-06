#pragma once
#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H

#include "StorageMeta.h"
#include "GDBRegion.h"
#include "GDBBlock.h"
#include "GDBList.h"
#include "GDBEdge.h"
#include "GDBDataGraph.h"
#include "GraphLoader.h"
#include "RDB.h"
#include "GraphIO.h"
#include "CacheManager.h"
#include "IDPool.h"
#include "IdAlloter.h"
#include "BigKeyIndex.h"
#include "GraphUpdater.h"
#include "BPlusTree.h"
#include "BPlusTreeUtils.h"
#include "..\GraphSchemaManager.h"
#include "../MemoryGraph.h"

#include <stdio.h>
#include <io.h>
#include <time.h>
#include <random>
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>

using namespace std;

#define EDH_BLOCK_INDEX 0
#define EDH_LIST_INDEX 1
#define EDH_EDGE_INDEX 2

#define S_META_OFFSET 0

class GraphLoader;
class GraphUpdater;
class MemoryGraph;
class GraphSchemaManager;
class RDB;

class GraphManager {
public:

// Storage
	string db_name;
	string db_path;
	string base_dir;
	string graph_create_time;
	string schemaid;

	RDB* relDB;
	//GDBDataGraph* tempGraph;
	GraphLoader* gLoader;
	GraphUpdater* gUpdater;
	
	// fstream db_file;
	CacheNode<StorageMeta>* new_smeta;
	//StorageMeta new_smeta;
	double ava_threshold;
	int block_listnum;
	int list_edgenum;
	int block_size;
	int list_size;

	IDPoolDisk* blockIdPool;
	vector<GDBRegion> gRegion;
	int begin_of_block;

// Index
	string node_index_path;
	string big_node_index_path;
	string spd_index_path;         //´æË÷Òý
	string shortest_path_dist_path;//´æ×î¶ÌÂ·¾¶¾àÀë
	string c2n_index_path;
	string c2n_dist_path;

	unordered_map<int, int> updateBigIndex;
	unordered_map<int, deque<value_t_int>> node_map_block;
	BPlusTree<key_t_int, nodeBlockPos, value_t_int>* nodeBlockIndex;

	//BigKeyIndex<int>* bigKeyIndex;

	// Memory Part
	bool inMemory;
	MemoryGraph* mGraph;
	GraphSchema* gSchema;
	void setInMemory();
	void releaseInMemory();
	void loadMemoryGraph(int type); //type 0: from disk, type 1: from file
	void loadMemoryGraphFromDisk();
	void loadMemoryGraphFromFile();
	void printMemoryGraphFromDisk(string& str);
	void addBlockToGraph(GDBBlock* block);
	void addBlockToGraph(GDBBlock* block, unordered_set<int>& nodeset);
	void printBlockToString(GDBBlock* block, string& str);

	bool doBetweenness;

	int block_cache_size;
	bool ifUpdate;

// Disk
	string community_nodes_path;
	string node_block_path;
	string edh_path;
	bool opened;

	GraphManager();
	GraphManager(string& dbname, int block_listnum, int list_edgenum, double ava_threshold, int cache_size,
		string leaf_file, string internal_file, int leaf_cache_size, int internal_cache_size, 
		string big_key_file, int big_key_cache_size, bool tree_empty, bool overwrite, bool firsttime);
	~GraphManager();
	void copyFrom(GraphManager* gm, string newname);
	void copyFileFrom(string origraph);
	void init();
	bool isOpen();
	void setOpened(bool op);

	double store(int limit=200);
	double store(string networkfile, string commmunityfile, string nodeattributefile = "", string edgeattributefile = "", int limit=200);
	void connect();
	void disconnect();
	
	void storeAttributes(string nodeattributefile, string edgeattributefile);
	void initialNew();
	void storeGraphGreedy(MemoryGraph& graph, int limit);
	void storeCommunityGreedyRelation(MemoryGraph& graph, int comid, int limit);
	int getBlockIndex(int offset);
	int listNumofNode(int needNum, int list_edge_num);
	int assignNodeToBlockNew(MemoryGraph& graph, int thisoffset, int block_count, GDBBlock* block,
		int node, int& startEdgeCount, int listNum, bool real);
	
	CacheNode<GDBBlock>* allotNewBlock(int cid);
	void removeBlock(GDBBlock* block, int blockIndex, int comid, bool isAva);

	void setGraphTime();
	void setGraphSchema(GraphSchemaManager* gsm, string& schemaid);

// Cache
	CacheManager* cacheManager;

	int getNodenumFromDisk();
	void setStorageMeta();
	void setNodenumInDisk(int val);
	void setCommnumInDisk(int val);
	void clearCache();


// Query
	bool nodeHasCommunity(int node);
	int getNodeFirstCommunity(int node);

// DataGraph Handling
	int getEdgeDestHead(int destid, int type); // 0 - blockIndex, 1 - listIndex, 2 - edgIndex
	EdgePos* getEdgeDestHead(int destid);
	void setEdgeDestHead(int destid, int boff = -1, int lidx = -1, int eidx = -1);
	void setEdgeDestHead(int destid, EdgePos* ep);

	template<class T>
	int db_alloc_new(T& block)
	{
		int alloc_slot = new_smeta->data->slot;
		new_smeta->data->slot += sizeof(block);
		return alloc_slot;
	}

	int db_alloc_size_new(int size)
	{
		new_smeta->data->slot += size;
		return 0;
	}

	int patch_unmapping_block_new(int bid, int comid)
	{
		int block_offset = new_smeta->data->slot;
		new_smeta->data->slot++;

		CacheNode<GDBBlock>* block = cacheManager->createBlockCache(block_listnum, list_edgenum, comid, bid);
		cacheManager->releaseCache(block, blockIdPool);

		return block_offset;
	}
};

#endif
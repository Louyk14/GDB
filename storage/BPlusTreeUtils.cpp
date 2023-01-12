#include "BPlusTreeUtils.h"
#include "..\MemoryGraph.h"

void nodeBlockPos::bptInit(MemoryGraph* g, int node, int valueNum, vector<value_t_int>& valuelist) {
	cid = *(g->nodeCommunitySet[node].begin());
	type = g->nodeType[node];
	count = valueNum;
	for (int i = 0; i < valueNum; ++i)
		value[i] = valuelist[i].get();
}

void nodeBlockPos::bptInit(MemoryGraph* g, int node, int valueNum, deque<value_t_int>& valuelist) {
	cid = *(g->nodeCommunitySet[node].begin());
	type = g->nodeType[node];
	count = valueNum;
	for (int i = 0; i < valueNum; ++i)
		value[i] = valuelist[i].get();
}
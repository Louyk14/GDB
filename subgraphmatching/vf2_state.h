#ifndef VF2_STATE_H
#define VF2_STATE_H

//#include "MatchGraph.h"
#include "../MemoryGraph.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;

class VF2State
{
public:
	VF2State(MemoryGraph* data, int nodenum, vector<int>& n, unordered_map<int, unordered_map<string, string>>& na
		, unordered_map<int, unordered_map<int, unordered_map<string, string>>>& ea
		, unordered_map<int, unordered_set<int>>& oe
		, unordered_map<int, unordered_set<int>>& ie);
	VF2State(const VF2State &state);
	~VF2State();

	vector<int>* nodes;
	unordered_map<int, unordered_map<string, string>>* nodeAttributes;
	unordered_map<int, unordered_map<int, unordered_map<string, string>>>* edgeAttributes;
	unordered_map<int, unordered_set<int>>* outedges;
	unordered_map<int, unordered_set<int>>* inedges;

	int core_len, orig_core_len;
	int added_node1;
	int t1both_len, t2both_len, t1in_len, t1out_len, t2in_len, t2out_len;
	unordered_map<int, int>* core_1;
	unordered_map<int, int>* core_2;
	unordered_map<int, int>* in_1;
	unordered_map<int, int>* in_2;
	unordered_map<int, int>* out_1;
	unordered_map<int, int>* out_2;

	//int* core_1;
	//int* core_2;
	//int* in_1;
	//int* in_2;
	//int* out_1;
	//int* out_2;

	int* order;
	int n1, n2;

	int* share_count;

	bool CompareNodeAttribute(MemoryGraph* data, int n1, int n2);
	bool CompareEdgeAttribute(MemoryGraph* data, int src1, int dst1, int src2, int dst2);
	bool NextPair(MemoryGraph* data, int* pn1, int* pn2, int prev_n1 = -1, int prev_n2 = -1);
	bool IsFeasiblePair(MemoryGraph* data, int n1, int n2);
	void AddPair(MemoryGraph* data, int n1, int n2);
	bool IsGoal()
	{
		return core_len == n1;
	}
	bool IsDead()
	{
		return n1 > n2 || t1both_len > t2both_len
			|| t1out_len > t2out_len || t1in_len > t2in_len;
	}
	int CoreLen()
	{
		return core_len;
	}
	void GetCoreSet(vector<vector<int>>& ans);
	void GetCoreSet(vector<unordered_map<int, int>>& ans);
	VF2State* Clone();
	void BackTrack(MemoryGraph* data);
	bool HasEdge(int src, int dst);
};

#endif
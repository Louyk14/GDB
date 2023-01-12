#ifndef VF2_STATE_SUB_H
#define VF2_STATE_SUB_H

#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
//#include "MatchGraph.h"
#include "../MemoryGraph.h"
#include <assert.h>

using namespace std;

class VF2StateSub
{
public:
	VF2StateSub(MemoryGraph* ag1, MemoryGraph* ag2, bool degree = false, unordered_map<int, vector<int>>* boundary = NULL);
	VF2StateSub(const VF2StateSub &state);
	~VF2StateSub();

	MemoryGraph* g1;
	MemoryGraph* g2;

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

	bool degree;
	unordered_map<int, vector<int>>* nodeArea;

	int* order;
	int n1, n2;

	int* share_count;

	bool CompareNodeAttribute(int n1, int n2);
	bool CompareEdgeAttribute(int src1, int dst1, int src2, int dst2);
	bool NextPair(int* pn1, int* pn2, int prev_n1 = -1, int prev_n2 = -1);
	bool IsFeasiblePair(int n1, int n2);
	void AddPair(int n1, int n2);
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
	void GetCoreSet(string& ans, unordered_map<int, int>& mapper, bool iswrite);
	VF2StateSub* Clone();
	void BackTrack();
};

#endif
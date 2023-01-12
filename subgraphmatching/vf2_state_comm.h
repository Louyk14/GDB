#ifndef VF2_STATE_COMM_H
#define VF2_STATE_COMM_H

#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <assert.h>
//#include "MatchGraph.h"
#include "../MemoryGraph.h"

using namespace std;

class VF2StateComm
{
public:
	VF2StateComm(MemoryGraph* data, MemoryGraph* ag1, MemoryGraph* ag2, int pid = 0, bool islazy = false
		, bool degree = false, int cid = -1, map<int, int>* dp = NULL, unordered_map<int, vector<int>>* boundary = NULL, unordered_set<int>* blist = NULL
		, bool active = false, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oo = NULL
		, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oi = NULL
		, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* io = NULL
		, bool af = false, vector<int>* autonodes = NULL, vector<int>* all = NULL);
	VF2StateComm(const VF2StateComm &state);
	~VF2StateComm();

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
	map<int, int>* distributionplan;

	bool autofill;
	vector<int>* autofillnodes;
	vector<int>* allnodes;

	//int* core_1;
	//int* core_2;
	//int* in_1;
	//int* in_2;
	//int* out_1;
	//int* out_2;

	int* order;
	int n1, n2;
	int comm_id;
	bool lazy;
	int processId;
	bool degree;
	unordered_map<int, vector<int>>* nodeArea;
	unordered_set<int>* banlist;
	bool active;
	unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oomessage;
	unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oimessage;
	unordered_map<int, unordered_map<int, unordered_map<int, int>>>* iomessage;

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
	void GetCoreSet(vector<string>& ans);
	void GetCoreSet(vector<int>& ans);
	void GetCoreSet(MemoryGraph* data, vector<int>& ans);
	void GetCoreSet(vector<vector<int>>& ans, bool storeAns = true);
	void GetCoreSet(vector<unordered_map<int, int>>& ans);
	void GetCoreSet(set<map<int, int>>& ans);
	VF2StateComm* Clone();
	void BackTrack(MemoryGraph* data);
	void AutoFillFreeNodes(MemoryGraph* data, vector<int>& ans, int level);
};

#endif
#ifndef LPAT_H
#define LPAT_H

#include<iostream>
#include<map>
#include<vector>
#include<list>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<set>
using namespace std;

class LPAT {
public:
	struct Node {
		int id;
		int cid;
	};
	unordered_map<int, unordered_set<int>>communityNode;;


	LPAT(int itertime);
	~LPAT();

	void Proceed(unordered_map<int, vector<int>>&network);
	void Update(unordered_map<int, unordered_map<int, vector<int>>>&network, unordered_map<int, int>& nodeCommunity);
private:
	map<int, Node*> nodes;
	int iter_time;

	void Shuffle(int* seq, int n);
	int UpdateNaive(int id, unordered_map<int, vector<int>>&network);
	int UpdateNaive(int id, unordered_map<int, unordered_map<int, vector<int>>>&network, unordered_map<int, int>& nodeCommunity);
	int GetFrequentLabel(unordered_map<int, float>&count);
};

#endif
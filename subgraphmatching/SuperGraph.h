#ifndef SUPERGRAPH_H
#define SUPERGRAPH_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>

using namespace std;

class SuperGraph
{
public:
	SuperGraph(vector<int>& n, unordered_map<int, unordered_map<string, unordered_set<string>>>* na
		, unordered_map<int, unordered_map<int, unordered_map<string, unordered_set<string>>>>* ea
		, unordered_map<int, unordered_set<int>>* oe
		, unordered_map<int, unordered_set<int>>* ie)
	{
		nodes = n;
		nodeAttributes = na;
		edgeAttributes = ea;
		outedges = oe;
		inedges = ie;
	}
	vector<int> nodes;
	unordered_map<int, unordered_map<string, unordered_set<string>>>* nodeAttributes;
	unordered_map<int, unordered_map<int, unordered_map<string, unordered_set<string>>>>* edgeAttributes;
	unordered_map<int, unordered_set<int>>* outedges;
	unordered_map<int, unordered_set<int>>* inedges;

	bool HasEdge(int src, int dst)
	{
		return ((*outedges)[src].find(dst) != (*outedges)[src].end());
	}
};

#endif
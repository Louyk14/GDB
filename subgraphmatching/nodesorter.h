#pragma once
#ifndef NODE_SORTER_HPP
#define NODE_SORTER_HPP

#include <vector>
#include <algorithm>
#include "probability_strategy.h"
#include "../MemoryGraph.h"
//#include "MatchGraph.h"

//Structure used for the sorting of the pattern
struct snode_s
{
	float probability;
	int deg;
	int deg_neigh; //Summ of neighboors' degree
	int deg_m;
	bool used;
	bool in_candidate;
	int id;

	//Used for RI
	int vis_count;
	int neig_count;
	int unv_count;
};

typedef struct snode_s snode_t;

//Comparison functions for RI Sorting
class CompareNodeDegree {
public:
	bool operator()(snode_s* n1, snode_t* n2)
	{
		if (n1->deg > n2->deg) return true;
		return false;
	}
};

class CompareNodeRIScore {
public:
	bool operator()(snode_s* n1, snode_t* n2)
	{
		if (n1->used && n2->used)
			return true;
		if (n1->used && !n2->used)
			return false;
		if (!n1->used && n2->used)
			return true;

		if (n1->vis_count > n2->vis_count)
			return true;
		if (n1->vis_count == n2->vis_count &&
			n1->neig_count > n2->neig_count)
			return true;
		if (n1->vis_count == n2->vis_count &&
			n1->neig_count == n2->neig_count &&
			n1->unv_count > n2->unv_count)
			return true;
		return false;
	}
};


//Comparison function for the heap
class CompareNodeStar {
public:
	bool operator()(snode_t* n1, snode_t* n2)
	{
		if (n1->deg_m > n2->deg_m)
			return true;

		if (n1->deg_m == n2->deg_m &&
			n1->probability < n2->probability)
			return true;

		if (n1->deg_m == n2->deg_m &&
			n1->probability == n2->probability &&
			n1->deg > n2->deg)
			return true;

		return false;
	}
};

class FindUnused
{
public:
	bool operator()(snode_t* n)
	{
		return !n->used;
	}
};

class CompareNodeStarProbability {
public:
	bool operator()(snode_t* n1, snode_t* n2)
	{
		if (n1->probability < n2->probability) return true;
		if (n1->probability == n2->probability && n1->deg > n2->deg) return true;
		return false;
	}
};

class NodeSorter
{
public:
	virtual vector<int> SortNodes(MemoryGraph* pattern) = 0;
};

class SimpleNodeSorter :NodeSorter
{
public:
	vector<int> SortNodes(MemoryGraph* pattern)
	{
		int i;
		vector<int> sorted;
		for (i = 0; i < pattern->nodeNum; i++)
			sorted.push_back(i);
		return sorted;
	}
};

class DegreeNodeSorter :NodeSorter
{
public:
	vector<int> SortNodes(MemoryGraph* pattern);
};

class DegMNodeSorter :NodeSorter
{
public:
	vector<int> SortNodes(MemoryGraph* pattern);
};


//Node sorter class used to sort the pattern
//Complete Sorter used in VF3 - Use probability and degM connections
class VF3NodeSorter
{
private:
	SubIsoNodeProbability* probability;
	void AddNodeToSortedSet(MemoryGraph* pattern, int node, int level,
		snode_t* nodes, vector<snode_t*> &candidates, vector<int> &nodes_order);

public:
	vector<int> SortNodes(MemoryGraph* pattern);
	///VF3NodeSorter(MatchGraph* target);
	VF3NodeSorter(MemoryGraph* target);
	~VF3NodeSorter();

};


#endif

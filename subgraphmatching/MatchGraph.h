#pragma once

#ifndef GRAPH_H
#define GRAPH_H

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

struct LabelVList
{
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

class MatchGraph
{
public:
	MatchGraph() {
		inMemory = true;
		outMaxDegree = -1;
		inMaxDegree = -1;
		maxDegree = -1;
		edgeNum = 0;
	};
	~MatchGraph() {};

	int communityNum;
	int nodeNum;
	int labelnum;
	int edgeNum;
	int maxCommSize;

	vector<int> node_ids;
	set<int> graphNodes;
	vector<vector<int>> communityNodes;
	// unordered_map<int, vector<int>> communityNodes;
	vector<vector<int>> nodeInfo; //0 - Community, 1 - Label
	vector<int> nodeLabels;	
	vector<vector<vector<unordered_set<int>>>> commNetworkSet; // node - community - label - neighbours
	vector<unordered_set<int>> netWorkSet;//保存所有边便于查找
	vector<vector<int>> netWorkVec;
	//unordered_map<int, unordered_map<int, unordered_set<int>>> netWorkSetComm;
	vector<unordered_set<int>> inNetWorkSet;
	vector<vector<int>> inNetWorkVec;

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
	void readNetwork(const string& pathFile);

	bool inMemory;
	int outMaxDegree;
	int inMaxDegree;
	int maxDegree;
	vector<vector<int>> labelList;
	//vector<vector<LabelVList*>> labelNetWorkVec; // include all labels, without is null

	bool hasEdge(int src, int dst)
	{
		return (netWorkSet[src].find(dst) != netWorkSet[src].end());
	}
};

class TempMatchGraph
{
public:
	TempMatchGraph() {};
	TempMatchGraph(vector<int>* n, unordered_map<int, unordered_map<string, string>>* na
		, unordered_map<int, unordered_map<int, unordered_map<string, string>>>* ea
		, vector<unordered_set<int>>* oe, vector<unordered_set<int>>* ie, int labnum
		, vector<int>* nl = NULL)
	{
		nodes = n;
		nodeAttributes = na;
		edgeAttributes = ea;
		outedges = oe;
		inedges = ie;
		ifdelete = true;
		labelnum = labnum;

		nodenum = n->size();
		nodeLabels = *nl;
		invec = new vector<vector<int>>(nodenum + 1);
		outvec = new vector<vector<int>>(nodenum + 1);

		if (nl != NULL)
		{
			labelEdgesVec = new vector<vector<LabelVList*>>(nodenum + 1, vector<LabelVList*>(labelnum, NULL));
		}

		outMaxDegree = -1;
		inMaxDegree = -1;
		maxDegree = -1;

		edgenum = 0;
		for (int n1 = 1; n1 < inedges->size(); ++n1)
		{
			inMaxDegree = max(inMaxDegree, (int)(*inedges)[n1].size());
			for (const auto& n2 : (*inedges)[n1])
			{
				(*invec)[n1].push_back(n2);
			}
			sort((*invec)[n1].begin(), (*invec)[n1].end());
			edgenum += (*invec)[n1].size();
		}

		outvecp = new vector<int>[nodenum + 1];
		largerbound = new int[nodenum + 1];
		for (int n1 = 1; n1 < outedges->size(); ++n1)
		{
			int myout = (*outedges)[n1].size();
			int myin = (*inedges)[n1].size();
			outMaxDegree = max(outMaxDegree, myout);
			maxDegree = max(maxDegree, myout + myin);
			largerbound[n1] = outedges->size() - 1;

			for (const auto& n2 : (*outedges)[n1])
			{
				(*outvec)[n1].push_back(n2);
				if (nl != NULL)
				{
					int label = nodeLabels[n2];
					if ((*labelEdgesVec)[n1][label] != NULL)
					{
						(*labelEdgesVec)[n1][label]->vList.insert(n2);
					}
					else
					{
						LabelVList* l = new LabelVList();
						l->label = label;
						l->vList.insert(n2);
						(*labelEdgesVec)[n1][label] = l;
						neighLabels[n1].insert(label);
					}
				}
			}
			sort((*outvec)[n1].begin(), (*outvec)[n1].end());
			outvecp[n1] = vector<int>((*outvec)[n1].begin(), (*outvec)[n1].end());
			for (int i = 0; i < outvecp[n1].size(); ++i) {
				if (outvecp[n1][i] >= n1) {
					largerbound[n1] = i;
					break;
				}	
			}
		}

		getdegrees();
	}
	TempMatchGraph(vector<int> n, unordered_map<int, unordered_map<string, string>>* na
		, unordered_map<int, unordered_map<int, unordered_map<string, string>>>* ea
		, vector<unordered_set<int>>* oe, vector<unordered_set<int>>* ie, int labnum
		, vector<int>* nl = NULL)
	{
		nodes = new vector<int>(n);
		sort(nodes->begin(), nodes->end());
		nodeAttributes = na;
		edgeAttributes = ea;
		outedges = oe;
		inedges = ie;
		ifdelete = true;
		labelnum = labnum;

		nodenum = n.size();
		nodeLabels = *nl;
		invec = new vector<vector<int>>(nodenum + 1);
		outvec = new vector<vector<int>>(nodenum + 1);

		if (nl != NULL)
		{
			labelEdgesVec = new vector<vector<LabelVList*>>(nodenum + 1, vector<LabelVList*>(labelnum, NULL));
		}

		outMaxDegree = -1;
		inMaxDegree = -1;
		maxDegree = -1;

		edgenum = 0;
		for (int n1 = 1; n1 < inedges->size(); ++n1)
		{
			inMaxDegree = max(inMaxDegree, (int)(*inedges)[n1].size());
			for (const auto& n2 : (*inedges)[n1])
			{
				(*invec)[n1].push_back(n2);
			}
			sort((*invec)[n1].begin(), (*invec)[n1].end());
			edgenum += (*invec)[n1].size();
		}

		outvecp = new vector<int>[nodenum + 1];
		//fill(outvecp->begin(), outvecp->end(), vector<int>());
		largerbound = new int[nodenum + 1];
		fill(largerbound, largerbound + nodenum + 1, -1);
		for (int n1 = 1; n1 < outedges->size(); ++n1)
		{
			int myout = (*outedges)[n1].size();
			int myin = (*inedges)[n1].size();
			outMaxDegree = max(outMaxDegree, myout);
			maxDegree = max(maxDegree, myout + myin);
			largerbound[n1] = outedges->size() - 1;

			for (const auto& n2 : (*outedges)[n1])
			{
				(*outvec)[n1].push_back(n2);
				if (nl != NULL)
				{
					int label = nodeLabels[n2];
					if ((*labelEdgesVec)[n1][label] != NULL)
					{
						(*labelEdgesVec)[n1][label]->vList.insert(n2);
					}
					else
					{
						LabelVList* l = new LabelVList();
						l->label = label;
						l->vList.insert(n2);
						(*labelEdgesVec)[n1][label] = l;
						neighLabels[n1].insert(label);
					}
				}
			}
			sort((*outvec)[n1].begin(), (*outvec)[n1].end());
			outvecp[n1] = vector<int>((*outvec)[n1].begin(), (*outvec)[n1].end());
			for (int i = 0; i < outvecp[n1].size(); ++i) {
				if (outvecp[n1][i] >= n1) {
					largerbound[n1] = i;
					break;
				}	
			}
		}

		getdegrees();
	}
	~TempMatchGraph()
	{
		if (ifdelete)
		{
			(*nodes).clear();
			delete nodes;
			delete degrees;
		}
	}
	unordered_set<int>* nodeset;
	vector<int>* nodes;
	unordered_map<int, unordered_map<string, string>>* nodeAttributes;
	unordered_map<int, unordered_map<int, unordered_map<string, string>>>* edgeAttributes;
	vector<unordered_set<int>>* outedges;
	vector<unordered_set<int>>* inedges;
	vector<vector<int>>* invec;
	vector<vector<int>>* outvec;
	vector<int>* outvecp;
	vector<vector<LabelVList*>>* labelEdgesVec;
	unordered_map<int, unordered_set<int>> neighLabels;
	vector<int> nodeLabels;
	vector<int> idMapping;
	int* degrees;
	bool** edgemap;
	double avgdegree;
	int* largerbound;
	
	bool ifdelete;
	int nodenum;
	int labelnum;
	int outMaxDegree;
	int inMaxDegree;
	int maxDegree;
	int edgenum;

	bool HasEdge(int src, int dst)
	{
		return ((*outedges)[src].find(dst) != (*outedges)[src].end());
	}

	void getdegrees() {
		degrees = new int[nodenum + 1];
		int degree_sum = 0;
		for (const auto& nid : *nodes) {
			degrees[nid] = (*outedges)[nid].size();
			degree_sum += degrees[nid];
		}
		avgdegree = (double)degree_sum / nodenum;
	}
	/*void getedgemap() {
		edgemap = new bool*[nodenum + 1];
		for (int i = 0; i < nodenum + 1; ++i) {
			edgemap[i] = new bool[nodenum + 1];
			memset(edgemap[i], false, (nodenum + 1) * sizeof(bool));
		}
		for (int i = 1; i < nodenum + 1; ++i) {
			for (const auto& n : (*outvec)[i]) {
				edgemap[i][n] = true;
			}
		}
	}*/
};

#endif
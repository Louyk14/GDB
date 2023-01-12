#ifndef TURBOGRAPH_H
#define TURBOGRAPH_H

#include <iostream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <sstream>
#include <map>
#include <fstream>
#include <stdio.h>
#include <assert.h>
using namespace std;

typedef unsigned int Label;
typedef int Vid;
typedef int Eid;

class TurboChild
{
public:
	TurboChild(int _s = -1, int _e = -1) : s(_s), e(_e)
	{
	}
	int s;
	int e;
};

class NECTree
{
public:
	int vertexNum; // 顶点数
	vector<Vid> vList; //NECTree结点的Label
	vector < vector <Vid> > NEC; // NECTree节点对应的实际q节点
	vector<Vid> parent;	//parent节点
	vector<TurboChild> child; // child 节点
	vector<bool> isLinked;

	NECTree(int _v = 0) : vertexNum(_v)
	{
	}
};

class CRTree
{
public:
	vector < vector <Vid> >*CR;	//CRTree节点对应的实际g节点
	vector<Vid> *parent;	//parent节点

	//unordered_map<Vid, set<Vid>>* CR;

	void init(int num)
	{
		if (CR != NULL)
			delete[]CR;
		CR = new vector < vector <Vid> >[num];
		//CR = new unordered_map<Vid, set<Vid>>[num];
		parent = new vector<Vid>[num];
	}

	CRTree()
	{
		CR = NULL;
		parent = NULL;
	}
	~CRTree()
	{
		if (CR != NULL)
			delete[]CR;
		CR = NULL;
		if (parent != NULL)
			delete[]parent;
	}
};

class TurboNeighbor
{
public:
	int uc_prime;
	int pos;
	int NeighborN;
};

struct TurboElem
{
	int v;
	double value;
};

struct TurboComQ
{
	bool operator() (const TurboElem& a, const TurboElem& b)
	{
		if (b.value - a.value > 1e-6)
			return true;
		else if (a.value - b.value > 1e-6)
			return false;
		else if (a.v < b.v)
			return true;
		else if (a.v > b.v)
			return false;
		else return false;
	}
};

#endif
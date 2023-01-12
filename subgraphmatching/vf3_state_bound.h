#pragma once
//
//  vf3_sub_state.hpp
//  VF2Plus
//
//  Created by Vincenzo Carletti on 12/11/14.
//  Copyright (c) 2014 Vincenzo Carletti. All rights reserved.
//

#ifndef VF3_STATE_BOUND_H
#define VF3_STATE_BOUND_H

#include <assert.h>
#include "../MemoryGraph.h"
//#include "MatchGraph.h"
#include "Match.h"
#include <cstring>
#include <iostream>
#include <vector>

typedef unsigned char node_dir_t;
#define NODE_DIR_NONE 0
#define NODE_DIR_IN	1
#define NODE_DIR_OUT 2
#define NODE_DIR_BOTH 3

using namespace std;

/*----------------------------------------------------------
* class VF3State
* A representation of the SSR current state
* See vf2_state.cc for more details.
---------------------------------------------------------*/

class Match;

class VF3StateBound
{
public:
	//private:
	//Comparison functors for nodes and edges
	//NodeComparisonFunctor nf;
	//EdgeComparisonFunctor ef;

	//Graphs to analyze
	MemoryGraph *g1;
	MemoryGraph *g2;

	Match* gm;
	MemoryGraph* data;

	//Size of each graph
	int n1, n2;

	int *order;     //Order to traverse node on the first graph

					//CORE SET SIZES
	int core_len;       //Current lenght of the core set
	int orig_core_len;  //Core set lenght of the previous state
	int *core_len_c;    //Core set lenght for each class

	int added_node1;    //Last added node

	node_dir_t* dir;        //Node coming set. Direction into the terminal set.
	int* predecessors;  //Previous node in the ordered sequence connected to a node

						//TERMINAL SET SIZE
						//BE AWARE: Core nodes are also counted by these
						//GLOBAL SIZE
	int t2in_len, t2both_len, t2out_len; //Len of Terminal set for the second graph
	int *t1in_len, *t1both_len, *t1out_len; //Len of Terminal set for the first graph for each level
											//SIZE FOR EACH CLASS
	int *t2both_len_c, *t2in_len_c, *t2out_len_c;     //Len of Terminal set for the second graph for each class
	int **t1both_len_c, **t1in_len_c, **t1out_len_c;  //Len of Terminal set for the first graph for each class end level

													  //Used for terminal set size evaluation
	int *termout2_c, *termin2_c, *new2_c;
	int **termout1_c, **termin1_c, **new1_c;

	int *termin1, *termout1, *new1;

	int *core_1;
	int *core_2;

	//Terminal sets of the second graph
	//TERM IN
	int *in_2;
	//TERMI OUT
	int *out_2;

	//Vector of sets used for searching the successors
	//Each class has its set
	int last_candidate_index;

	/* Structures for classes */
	int *class_1;       //Classes for nodes of the first graph
	int *class_2;       //Classes for nodes of the first graph
	int classes_count;  //Number of classes

	long *share_count;  //Count the number of instances sharing the common sets

						//PRIVATE METHODS
	void BackTrack();
	void ComputeFirstGraphTraversing();
	void UpdateTerminalSetSize(int node, int level, bool* in_1, bool* out_1, bool* inserted);
	void print_terminal(int c);

public:
	vector<MemoryGraph*>* communityGraphs;
	vector<vector<int>*>* nodeArea;
	int* distributeplan;
	vector<vector<int>>* vvans;

	//static long long  instance_count;
	VF3StateBound(MemoryGraph *g1, MemoryGraph *g2, Match* gm, int nclass,
		int* order = NULL);
	VF3StateBound(const VF3StateBound &state);
	~VF3StateBound();
	MemoryGraph *GetGraph1() { return g1; }
	MemoryGraph *GetGraph2() { return g2; }
	bool NextPair(int *pn1, int *pn2,
		int prev_n1 = -1, int prev_n2 = -1);
	bool IsFeasiblePair(int n1, int n2);
	void AddPair(int n1, int n2);
	bool IsGoal() { return core_len == n1; };
	bool IsDead();
	int CoreLen() { return core_len; }
	void GetCoreSet();
	bool match_bound(VF3StateBound &s, int *pn);
	int match();

	void init();
};

#endif

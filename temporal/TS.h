#ifndef TS_H
#define TS_H

#include "CommGraphUtil.h"
#include "TemporalGraph.h"
#include <math.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <iostream>

using namespace std;

class TS {
public:
	CommGraphUtil CGU;

	double computeScore(TemporalGraph& g, double ev2);
	double computeTopoScore(TemporalGraph& g, double ev2);
	double computeIOScore(TemporalGraph& g, double ev2);
	double computeAvgV_ana(TemporalGraph& g, vector<TemporalEdge>& tstamps, int u, int v, int t_s, int t_e);
	double computeAvgV_both(TemporalGraph& g, vector<int>& nodes, vector<TemporalEdge>& tstamps, int u, int v, int t_s, int t_e);
	double computeAvgV_ab(TemporalGraph& g, vector<int>& nodes, vector<TemporalEdge>& tstamps, int u, int v, int t_s, int t_e);

	// double computeAvgExV(GraphInfo& g, int u, int v, int comm);
	double computeAvgV(TemporalGraph& g, int u, int v, int comm);
	double computeAvgV(TemporalGraph& g, int u, int v, int comm, int node, bool add);
	double computeExpV(TemporalGraph& g, int comm);
	double computeExpVwoE(TemporalGraph& g, int comm, int u, int v);
	double SExpV(TemporalGraph& g, int comm, int u, int v);
	double computeV(vector<int>& timestamp);
	double SV(int t, vector<int>& timestamp);
	double SV(TemporalGraph& g, int t, int comm);
	double SVs(TemporalGraph& g, vector<int>& timestamps);
	double SVs(TemporalGraph& g, int t, int comm);
	//double SV(int t, multiset<int>& timestamp);
	void randomSelect(vector<int>& timestamp, int k);
	double S(int t1, int t2, int t_max, int t_min, double t_avg);
	double Ssin(int t1, int t2, int t_max, int t_min, double t_avg);
	double computeTS(TemporalGraph& g);
	double addN2CTSFake(int node, int comm, int fromcomm, TemporalGraph& g);
	double removeN2CTSFake(int node, int comm, int tocomm, TemporalGraph& g);
	void moveTS(int node, int comm, double rectsto, double rectsfrom, TemporalGraph& g);
	double computeCommTS(int comm, TemporalGraph& g);
	bool traverseTS(TemporalGraph& g);
	void detectTS(TemporalGraph& g);

	void printTS(TemporalGraph& g);
	void writeTS(TemporalGraph& g, string filename);
};

#endif
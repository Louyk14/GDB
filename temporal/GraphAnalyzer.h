#ifndef GRAPHANALYZER_H
#define GRAPHANALYSER_H

#include "TemporalGraph.h"
#include "TS.h"
#include <time.h>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include<iomanip>

using namespace std;

class TemporalGraph;
class TemporalEdgeInfo;

class DNode {
public:
	vector<int> nodes;
	double ts;
	int max_time;
	int min_time;
	int last_enum;
	int last_sz;
	double save;
	unordered_map<int, int> ncore;

	bool kball;
	bool kbnt;
	bool kbnio;
	bool kbntopo;

	DNode(double s, vector<int>& c, int maxt, int mint) {
		ts = s;
		nodes = c;
		max_time = maxt;
		min_time = mint;
		kball = false;
		kbnt = false;
		kbnio = false;
		kbntopo = false;
	}
};

class tscmp {
public:
	bool operator() (DNode* a, DNode* b) {
		if (a->ts < b->ts)
			return true;
		else if(a->ts == b->ts)
			return a->nodes.back() < b->nodes.back();
		else
			return false;
	}
};

static bool compareEdgeInfo(const TemporalEdgeInfo& a, const TemporalEdgeInfo& b) {
	return a.max_time < b.max_time;
}

class Lattice {
public:
	Lattice() {
		next = NULL;
		parent = NULL;
	}

	Lattice (vector<int>& n) {
		next = NULL;
		parent = NULL;
		node = n;
	}

	void set(double ex, double ex2, double e) {
		commEx = ex;
		commEx2 = ex2;
		commEdge = e;
	}

	vector<int> node;
	Lattice* next;
	Lattice* parent;
	vector<Lattice*> child;
	double commEx;
	double commEx2;
	double commEdge;
};

class GraphAnalyzer {
public:
	GraphAnalyzer() {
		logger.open("data_log.log", ios::app);
	}

	void tsearch_reduce(TemporalGraph& g, int qv, double phi, int num, int t_s, int t_e);
	double analyze(TemporalGraph& g, vector<int>& nodes, int t_s, int t_e);
	double analyzeCase(TemporalGraph& g, vector<int>& nodes);
	void timeSeries(TemporalGraph& g, vector<int> nodes, int starttime, int dur, int endtime);
	void tsearch_enum(TemporalGraph& g, int qv, double phi, int num, int t_s, int t_e);
	void tsearch(TemporalGraph& g, int qv, double phi, int num, int t_s, int t_e);
	void tsearch_dfs(TemporalGraph& g, int qv, double phi, int num, int t_s, int t_e);
	void initNodes_dfs(TemporalGraph& g, int n, unordered_map<int, int>& degree, int t_s, int t_e);
	double analyzeIndex_enum(TemporalGraph& g, vector<int>& nodes, unordered_map<int, int>& degree, int t_s, int t_e, double& zeta_tmp, int& in_enum, int& in_sz, int& in_core, int& maxt, int& mint);
	double analyzeIndex_dfs(TemporalGraph& g, vector<int>& nodes, unordered_map<int, int>& degree, int t_s, int t_e, int tspan, double& zeta_tmp, int& in_enum, int& in_sz, int& in_core);
	double analyzeIndex_dfs_load(TemporalGraph& g, vector<int>& nodes, unordered_map<int, int>& degree, int t_s, int t_e, int tspan, double& zeta_tmp, int& in_enum, int& in_sz, int& in_core, unordered_map<int, int>& ncore, int& last_sz, int& last_enum);
	void dfs(TemporalGraph& g, double phi, priority_queue<DNode*, vector<DNode*>, tscmp>& Q, int num, int t_s, int t_e, unordered_map<int, int>& degree, vector<int>& window_edges);
	//void tsearch_mod(GraphInfo& g, int qv, double phi, int num, int t_s, int t_e);
	double analyzeIndex(TemporalGraph& g, vector<int>& nodes, string& signature, vector<TemporalEdge>& tstamps, unordered_map<int, int>& degree, int t_edge_num, int t_s, int t_e);
	double analyzeIndex_ab(TemporalGraph& g, vector<int>& nodes, string& signature, vector<TemporalEdge>& tstamps, unordered_map<int, int>& degree, int t_edge_num, int t_s, int t_e);
	void initNodes(TemporalGraph& g, int n, unordered_map<int, int>& degree, int& t_edge_num, int t_s, int t_e);
	int getEdgeNumInWindow(TemporalGraph& g, vector<int>& window_edges, int t_s, int t_e);
	void buildIndex(TemporalGraph& g, int t_s, int t_e);
	void connectedComponents(TemporalGraph& g, int t_s, int t_e, vector<vector<int>>& components, unordered_map<int, int>& cc_map);
	int getComponentEst(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& invalid_nodes, unordered_set<int>& cc, int& maxnode);
	double getMaxIO(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& cc, unordered_set<int>& invalid_nodes, int in_sz, int in_enum, int invalid_edge);
	double getMaxTopo(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& cc, unordered_set<int>& invalid_nodes, int lose_core);
	void getMaxTT(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& cc, unordered_set<int>& invalid_nodes, int in_sz, int in_enum, int invalid_edg, int lose_core, double& io, double& topo);
	void getMaxTT_noindex(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& cc, unordered_set<int>& invalid_nodes, int in_sz, int in_enum, int invalid_edg, int lose_core, double& io, double& topo);
	void getMaxTT_new(TemporalGraph& g, int t_s, int t_e, vector<int>& nodes, int maxt, int mint, int max_span, unordered_set<int>& cc, unordered_set<int>& invalid_nodes, int in_sz, int in_enum, int invalid_edg, int lose_core, double& io, double& topo);


	void computeMetric(TemporalGraph& g, vector<int>& nodes, int t_s, int t_e, double ts);
	void deleteTree(Lattice* root);

	bool isValidExtension(TemporalGraph& g, int qv, vector<int>& nodes, int v, vector<int>& distance);
	void enumerateCIS(TemporalGraph& g, int qv, vector<int>& nodes, vector<int>& distance, unordered_set<int>& neighs, unordered_map<int, int>& degree,
								 double phi, double max_span, int t_s, int t_e, int& ansnum, int num, bool& enough);

	void caseStudy(TemporalGraph& g, int mid);

	TS tseval;
	unordered_map<int, int> lastlevel;
	unordered_map<int, int> newlevel;

	time_t start, end;
	ofstream logger;
	ofstream slog;
	string filename;
	string filename_backup;
};

#endif
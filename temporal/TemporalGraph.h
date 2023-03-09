#ifndef TEMPORALGRAPH_H
#define TEMPORALGRAPH_H

#include "../TemporalParameters.h"
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <string>
#include <set>
#include <stack>

using namespace std;


class TemporalEdge {
public:
	TemporalEdge() {
		rel1 = 0;
		rel2 = 0;
		t= 0;
	}
	TemporalEdge(int r1t, int r2t, int tt) {
		t = tt;
		rel1 = r1t;
		rel2 = r2t;
	}

	int t;
	int rel1, rel2;
};

class TemporalEdgeInfo {
public:
	int num;
	int src;
	int dst;
	int max_time;
	int min_time;

	TemporalEdgeInfo (int n, int s, int d, int maxt, int mint) {
		num = n;
		src = s;
		dst = d;
		max_time = maxt;
		min_time = mint;
	}
};

struct MinCmp {
    MinCmp(vector<TemporalEdgeInfo>* ve) { this->v = ve; }
    bool operator () (int i, int j) { 
		if ((*v)[i].min_time < (*v)[j].min_time)
			return true;
		else if ((*v)[i].min_time == (*v)[j].min_time) {
			return (*v)[i].max_time < (*v)[j].max_time;
		}
		else
			return false;
	}

   vector<TemporalEdgeInfo>* v;
};

struct MaxCmp {
    MaxCmp(vector<TemporalEdgeInfo>* ve) { this->v = ve; }
    bool operator () (int i, int j) { 
		if ((*v)[i].max_time < (*v)[j].max_time)
			return true;
		else if ((*v)[i].max_time == (*v)[j].max_time) {
			return (*v)[i].min_time < (*v)[j].min_time;
		}
		else
			return false;
	}

   vector<TemporalEdgeInfo>* v;
};

class TemporalGraph {
public:
	//double th_interval;
	double th_score;
	double th_ev2;
	double th_alpha;
	double th_beta;
	double th_expect_ev2;

	double multi_rate;

	double kcore;

	double th_topo_half;
	double th_topo_alpha;
	double th_topo_beta;

	double th_io_half;
	double th_io_alpha;
	double th_io_beta;

	int window_span;
	int posnum;

	int t_edge_num;
	int edge_num;
	int nodenum;
	int t_gap;

	int handlenum;
	int positivenum;
	int negtivenum;

	int negt;
	int negio;
	int negtopo;
	int negall;
	int post;
	int posio;
	int postopo;

	unordered_map<int, vector<TemporalEdgeInfo>> eindex;
	vector<vector<int>> components;
	unordered_map<int, int> cc_map;
	unordered_map<int, vector<int>> cc_network;
	unordered_map<int, unordered_set<int>> temporal_network;
	vector<unordered_map<int, vector<int>>> temporal_graph;

	vector<int> distance;
	unordered_map<int, int> window_degree;
	double minimum_io;

	vector<unordered_map<int, vector<int>>*> graph;
	unordered_map<int, unordered_set<int>> network;
	vector<int> degree;
	vector<vector<int>> sum_t_vertex;
	unordered_map<int, vector<int>> communities;
	vector<int> comm_map;
	unordered_map<int, double> comm_ts;
	unordered_map<int, int> mapper;
	unordered_map<int, int> rev_mapper;
	vector<int> record_edges;

	vector<int> best_comm_map;
	double bestVal;

	unordered_map<int, int> indegree;
	unordered_map<int, int> inedge;
	unordered_map<int, multiset<int>> instamp;

	unordered_map<int, int> comm_edge;
	unordered_map<int, double> comm_Ex2;
	unordered_map<int, double> comm_Ex;

	stack<double> backup_ex2;
	stack<double> backup_ex;
	stack<double> backup_edge;

	unordered_map<int, vector<TemporalEdge>> in_edges;

	unordered_map<int, double> expect_index;

	int maxstamp;
	int minstamp;

	// TOM only
	// int r_all;
	double tom_all;
	double tspan;
	double iorate;
	double corerate;
	double corenumber;
	double avgts;
	int testnum;
	double timesum;

	unordered_map<int, double> comm_mod;

	vector<unordered_map<string, double>> sRecorder;
	int scode;

	bool debug;
	bool refine;

	int t_s;
	int t_e;
	int combonum;
	int duration;
	double phi;

	int window_width;
	int window_step;

	TemporalGraph() {
		//r_all = 0;
		tom_all = 0;
		debug = false;
		iorate = 0;
		tspan = 0;
		corerate = 0;
		testnum = 0;
		avgts = 0;

		sRecorder = vector<unordered_map<string, double>>(2);
		scode = 0;

		handlenum = 0;
		posnum = 0;
		timesum = 0;

		positivenum = 0;
		negtivenum = 0;

		negt = 0;
		negio = 0;
		negtopo = 0;
		negall = 0;
		post = 0;
		posio = 0;
		postopo = 0;

		th_score = 0.5;
		th_ev2 = 7;
		th_beta = 4;
		th_io_half = 0.3;
		th_io_beta = 0.9;
		kcore = 3;
		th_topo_half = 1 - 1.0 / kcore;
		th_topo_beta = 1;

		th_alpha = (exp(1.0 / th_score - 1) - 1) / (th_ev2 - th_beta);
		th_topo_alpha = (exp(1.0 / th_score - 1) - 1) / (th_topo_beta - th_topo_half);
		th_io_alpha = (exp(1.0 / th_score - 1) - 1) / (th_io_beta - th_io_half);

		window_width = 0;
		window_step = 0;
	}

	TemporalGraph(TemporalParameters& cpara) {
		//r_all = 0;
		tom_all = 0;
		debug = false;
		iorate = 0;
		tspan = 0;
		corerate = 0;
		testnum = 0;
		avgts = 0;

		sRecorder = vector<unordered_map<string, double>>(2);
		scode = 0;

		handlenum = 0;
		posnum = 0;
		timesum = 0;

		positivenum = 0;
		negtivenum = 0;

		negt = 0;
		negio = 0;
		negtopo = 0;
		negall = 0;
		post = 0;
		posio = 0;
		postopo = 0;

		th_score = 0.5;
		th_ev2 = cpara.th_ev2;
		th_beta = cpara.th_beta;
		th_io_half = cpara.th_io_half;
		th_io_beta = cpara.th_io_beta;
		kcore = cpara.kcore;
		th_topo_half = cpara.th_topo_half;
		th_topo_beta = cpara.th_topo_beta;

		t_s = cpara.t_s;
		t_e = cpara.t_e;
		duration = cpara.duration;
		combonum = cpara.combonum;
		phi = cpara.phi;
		window_width = cpara.window_width;
		window_step = cpara.window_step;

		th_alpha = (exp(1.0 / th_score - 1) - 1) / (th_ev2 - th_beta);
		th_topo_alpha = (exp(1.0 / th_score - 1) - 1) / (th_topo_beta - th_topo_half);
		th_io_alpha = (exp(1.0 / th_score - 1) - 1) / (th_io_beta - th_io_half);
	}

	void clear() {
		comm_edge.clear();
		comm_Ex.clear();
		comm_Ex2.clear();
	}

	void init(int n) {
		nodenum = n;
		t_edge_num = 0;
		edge_num = 0;
		temporal_graph = vector<unordered_map<int, vector<int>>>(nodenum + 1);
		temporal_network = unordered_map<int, unordered_set<int>>();
		degree = vector<int>(nodenum + 1, 0);
		sum_t_vertex = vector<vector<int>>(nodenum + 1);
		comm_map = vector<int>(nodenum + 1, 0);
	}

	int mapID(int& n, int index) {
		if (mapper.find(n) != mapper.end())
			n = mapper[n];
		else {
			mapper[n] = index;
			rev_mapper[index] = n;
			n = index;
			index += 1;
		}

		return index;
	}

	double getStd(int comm, int t) {
		double sx2 = comm_Ex[comm] / (double)comm_edge[comm];
		double ev1 = comm_Ex2[comm] / (double)comm_edge[comm] - sx2 * sx2;

		return sqrt(ev1);
	}

	void addT_actual(int comm, int t) {
		double dt = (double)t;
		comm_edge[comm]++;
		comm_Ex[comm] += dt;
		comm_Ex2[comm] += dt * dt;
	}

	void removeT_actual(int comm, int t) {
		double dt = (double)t;
		comm_edge[comm]--;
		comm_Ex[comm] -= dt;
		comm_Ex2[comm] -= dt * dt;
	}

	double addT(int comm, int t) {
		double dt = (double)t;
		double sx2 = (comm_Ex[comm] + dt) / (double)(comm_edge[comm] + 1);
		double ev2 = (comm_Ex2[comm] + dt * dt) / (double)(comm_edge[comm] + 1) - sx2 * sx2;

		return sqrt(ev2);
	}

	double removeT(int comm, int t) {
		if (comm_edge[comm] <= 1)
			return 0;

		double dt = (double)t;
		double sx2 = (comm_Ex[comm] - dt) / (double)(comm_edge[comm] - 1);
		double ev2 = (comm_Ex2[comm] - dt * dt) / (double)(comm_edge[comm] - 1) - sx2 * sx2;

		return sqrt(ev2);
	}

	void save(int comm) {
		backup_ex.push(comm_Ex[comm]);
		backup_ex2.push(comm_Ex2[comm]);
		backup_edge.push(comm_edge[comm]);
	}

	void load(int comm) {
		comm_Ex[comm] = backup_ex.top();
		backup_ex.pop();
		comm_Ex2[comm] = backup_ex2.top();
		backup_ex2.pop();
		comm_edge[comm] = backup_edge.top();
		backup_edge.pop();
	}

	void setPara(double score, double ev2, double beta, double io_half, double io_beta, double coreno, double topo_half, double topo_beta) {
		th_score = score;
		th_ev2 = ev2;
		th_beta = beta;
		th_io_half = io_half;
		th_io_beta = io_beta;
		kcore = coreno;
		th_topo_half = topo_half;
		th_topo_beta = topo_beta;

		th_alpha = (exp(1.0 / th_score - 1) - 1) / (th_ev2 - th_beta);
		th_topo_alpha = (exp(1.0 / th_score - 1) - 1) / (th_topo_beta - th_topo_half);
		th_io_alpha = (exp(1.0 / th_score - 1) - 1) / (th_io_beta - th_io_half);
	}

	void setPara(vector<double>& parameters_d) {
		if (parameters_d.empty())
			return;

		th_score = parameters_d[0];
		th_ev2 = parameters_d[1];
		th_beta = parameters_d[2];
		th_io_half = parameters_d[3];
		th_io_beta = parameters_d[4];
		kcore = parameters_d[5];
		th_topo_beta = parameters_d[6];
		th_topo_half = 1 - 1.0 / kcore;

		th_alpha = (exp(1.0 / th_score - 1) - 1) / (th_ev2 - th_beta);
		th_topo_alpha = (exp(1.0 / th_score - 1) - 1) / (th_topo_beta - th_topo_half);
		th_io_alpha = (exp(1.0 / th_score - 1) - 1) / (th_io_beta - th_io_half);
	}
};

#endif
#pragma once
#ifndef GRAPHQUERYENGINEMEMORY_H
#define GRAPHQUERYENGINEMEMORY_H

#include "storage\GraphManager.h"
#include "subgraphmatching\Match.h"
#include "temporal\TemporalSearch.h"

enum SubgraphMatchType {
	TURBOTYPE, VF3TYPE, DAFTYPE
};

struct ComboParameters {
	ComboParameters() {
		th_score = 0;
		th_ev2 = 0;
		th_beta = 0;
		th_io_half = 0;
		th_io_beta = 0;
		kcore = 0;
		th_topo_beta = 0;
		th_topo_half = 0;

		th_alpha = 0;
		th_topo_alpha = 0;
		th_io_alpha = 0;
	}
	ComboParameters(double score, double ev2, double beta, double io_half, double io_beta, double coreno, double topo_half, double topo_beta) {
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
	void setPara(vector<double>& parameters);

	double th_score;
	double th_ev2;
	double th_beta;
	double th_io_half;
	double th_io_beta;
	int kcore;
	double th_topo_beta;
	double th_topo_half;
	
	double th_alpha;
	double th_topo_alpha;
	double th_io_alpha;
};

class GraphQueryEngineMemory {
public:
	GraphQueryEngineMemory();
	~GraphQueryEngineMemory();
	void subgraphMatchingQuery(GraphManager* gm, SubgraphMatchType smtype);
	void comboSearching(GraphManager* gm, ComboParameters* cpara, int qv, int combonum, int t_s, int duration, int t_e, double phi);

	ComboParameters* comboParamemters;
};

#endif`
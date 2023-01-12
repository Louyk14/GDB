#include "GraphQueryEngineMemory.h"

void ComboParameters::setPara(vector<double>& parameters) {
	if (parameters.empty())
		return;

	th_score = parameters[0];
	th_ev2 = parameters[1];
	th_beta = parameters[2];
	th_io_half = parameters[3];
	th_io_beta = parameters[4];
	kcore = parameters[5];
	th_topo_beta = parameters[6];
	th_topo_half = 1 - 1.0 / kcore;

	th_alpha = (exp(1.0 / th_score - 1) - 1) / (th_ev2 - th_beta);
	th_topo_alpha = (exp(1.0 / th_score - 1) - 1) / (th_topo_beta - th_topo_half);
	th_io_alpha = (exp(1.0 / th_score - 1) - 1) / (th_io_beta - th_io_half);
}

GraphQueryEngineMemory::GraphQueryEngineMemory() {
	comboParamemters = new ComboParameters();
}

GraphQueryEngineMemory::~GraphQueryEngineMemory() {
	delete comboParamemters;
}

void GraphQueryEngineMemory::subgraphMatchingQuery(GraphManager* gm, SubgraphMatchType smtype) {
	if (!gm->inMemory) {
		cout << "Apply memory subgraph matching algorithm to graph not in the memory!" << endl;
		return;
	}

	//GraphSet patternGraphSet;
	//evalToGraphSet(*selectstat.whereCondition, patternGraphSet);

	string graphpath, commpath, pattenpath;
	Match match(graphpath, commpath, pattenpath);
	
	if (smtype == TURBOTYPE) {
		match.GoMatch_Turbo_comm();
	}
	else if (smtype == VF3TYPE) {
		match.GoMatch_vf3_comm();
	}
	else if (smtype == DAFTYPE) {
		match.GoMatch_DAF_comm();
	}
}

void GraphQueryEngineMemory::comboSearching(GraphManager* gm, ComboParameters* cpara, int qv, int combonum, int t_s, int duration, int t_e, double phi) {
	TemporalSearch ts;
	TemporalGraph tg;
	string inputfile, outputfile;

	ts.comboSearching(tg, inputfile, outputfile, qv, combonum, t_s, duration, t_e, phi);
}
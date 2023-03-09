#include "GraphQueryEngineMemory.h"


GraphQueryEngineMemory::GraphQueryEngineMemory() {
	temporalParamemters = new TemporalParameters();
}

GraphQueryEngineMemory::~GraphQueryEngineMemory() {
	delete temporalParamemters;
}

void GraphQueryEngineMemory::subgraphMatchingQuery(GraphManager* gm, MemoryGraph* p, SubgraphMatchType smtype) {
	if (!gm->inMemory) {
		cout << "Apply memory subgraph matching algorithm to graph not in the memory!" << endl;
		// return;
		gm->setInMemory();
	}

	//GraphSet patternGraphSet;
	//evalToGraphSet(*selectstat.whereCondition, patternGraphSet);

	// string graphpath, commpath, pattenpath;
	// Match match(graphpath, commpath, pattenpath);

	Match match(gm, p);
	
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

void GraphQueryEngineMemory::comboSearching(GraphManager* gm, string& configfile, int qv) {
	gm->gLoader->loadTemporalInfo(*gm->mGraph, gm->temporal_info_path);

	TemporalParameters cpara(configfile);
	TemporalSearch ts(gm->mGraph, cpara);
	
	ts.analyze();

	ts.comboSearching(qv);
}

void GraphQueryEngineMemory::evolutionTracking(GraphManager* gm, string& configfile, vector<int>& qvs) {
	gm->gLoader->loadTemporalInfo(*gm->mGraph, gm->temporal_info_path);

	TemporalParameters epara(configfile);
	TemporalSearch ts(gm->mGraph, epara);

	ts.analyze();

	ts.evolutionTracking(qvs);
}
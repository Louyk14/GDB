#pragma once
#ifndef GRAPHQUERYENGINEMEMORY_H
#define GRAPHQUERYENGINEMEMORY_H

#include "storage\GraphManager.h"
#include "subgraphmatching\Match.h"
#include "temporal\TemporalSearch.h"
#include "TemporalParameters.h"

enum SubgraphMatchType {
	TURBOTYPE, VF3TYPE, DAFTYPE
};

class GraphQueryEngineMemory {
public:
	GraphQueryEngineMemory();
	~GraphQueryEngineMemory();
	void subgraphMatchingQuery(GraphManager* gm, MemoryGraph* p, SubgraphMatchType smtype);
	void comboSearching(GraphManager* gm, string& configfile, int qv);
	void evolutionTracking(GraphManager* gm, string& configfile, vector<int>& qvs);

	TemporalParameters* temporalParamemters;
};

#endif`
#pragma once
#ifndef TEMPORALSEARCH_H
#define TEMPORALSEARCH_H

#include "../TemporalParameters.h"
#include "CommGraphUtil.h"
#include "GraphAnalyzer.h"
#include "TemporalGraph.h"
#include "../MemoryGraph.h"
#include <string>
#include <fstream>
#include <time.h>
#include <unordered_map>
#include <vector>
#include <iostream>

class MemoryGraph;

class TemporalSearch {
public:

	MemoryGraph* mGraph;
	TemporalGraph* temporalGraph;

	TemporalSearch(MemoryGraph* g, TemporalParameters& cpara) {
		mGraph = g;

		temporalGraph = new TemporalGraph(cpara);
	}

	int mapID(int& n, unordered_map<int, int>& mapper, unordered_map<int, int>& rev_mapper, int index);
	void analyze();

	void loadGraph(TemporalGraph& g, string file_path, unordered_map<int, int>& rev_mapper, bool isdouble);
	void refineGraphTimestamps(TemporalGraph& g);
	void loadCommunity(TemporalGraph& g, string file_path);
	void printCommunityFile(TemporalGraph& g, string filename);
	void writeRelated(TemporalGraph& g, vector<int>& nodes);
	void detectDiff();
	void loadIndex(GraphAnalyzer& ga, TemporalGraph& g, int t_s, int t_e);
	void comboSearching(int qv);
	void evolutionTracking(vector<int>& qvs);
};

#endif
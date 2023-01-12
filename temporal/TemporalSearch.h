#pragma once
#ifndef TEMPORALSEARCH_H
#define TEMPORALSEARCH_H

#include "CommGraphUtil.h"
#include "GraphAnalyzer.h"
#include "TemporalGraph.h"
#include <string>
#include <fstream>
#include <time.h>
#include <unordered_map>
#include <vector>
#include <iostream>

class TemporalSearch {
public:
	int mapID(int& n, unordered_map<int, int>& mapper, unordered_map<int, int>& rev_mapper, int index);
	void loadGraph(TemporalGraph& g, string file_path, unordered_map<int, int>& rev_mapper, bool isdouble);
	void refineGraphTimestamps(TemporalGraph& g);
	void loadCommunity(TemporalGraph& g, string file_path);
	void printCommunityFile(TemporalGraph& g, string filename);
	void writeRelated(TemporalGraph& g, vector<int>& nodes);
	void detectDiff();
	void loadIndex(GraphAnalyzer& ga, TemporalGraph& g, int t_s, int t_e);
	void comboSearching(TemporalGraph& g, string inputfile, string outputfile, int qv, int combonum, int t_s, int duration, int t_p, double phi);
	void evolutionTracking(TemporalGraph& g, string inputfile, string outputfile, vector<int>& relnodes, int qv, int combonum, int t_s, int duration, int t_e);
};

#endif
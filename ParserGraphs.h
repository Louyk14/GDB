#pragma once
#ifndef PARGERGRAPHS_H
#define PARSERGRAPHS_H

#include "parser\definations.h"
#include "GraphDatabase.h"
#include "MemoryGraph.h"
#include "GraphSchema.h"

class FromConditionGraph;
class MemoryGraph;

class WhereConditionGraph {
public:
	MemoryGraph* mGraph;
	FromConditionGraph* fcg;
	int type = 0;

	vector<string> paras; // of the func
	string querytype;
	string related_file;

	vector<int> nodes;
	unordered_map<int, unordered_map<string, string>>* nodeAttributes;
	unordered_map<int, unordered_map<int, unordered_map<string, string>>>* edgeAttributes;
	vector<unordered_map<int, vector<string>>>* outedges;
	vector<unordered_map<int, vector<string>>>* inedges;
	vector<string>* nodeLabels;

	WhereConditionGraph() { mGraph = NULL; };
	void init(WhereCondition* wc);

	void loadPatternGraph(string filename, vector<int>& nodes
		, unordered_map<int, unordered_map<string, string>>& nodeAttributes
		, unordered_map<int, unordered_map<int, unordered_map<string, string>>>& edgeAttributes
		, vector<unordered_map<int, vector<string>>>& outedges
		, vector<unordered_map<int, vector<string>>>& inedges, vector<string>* nodeLabels);

	void loadComboParameter(string filename, unordered_map<string, string>& paras);

	void convert(GraphSchema& gschema);

	void generateFirstOrderStatGraph(FirstOrderStat* fos);

	void analyzeFirstOrderUnit(FirstOrderUnit* fou);
};

class FromConditionGraph {
public:
	FromConditionGraph() {};
	void init(FromCondition* fc);

	int type;
	string gsid;
};


#endif
//
// Created by Henry Fox on 2019-12-18.
//

#ifndef ANTLR_GRAPHDB_EVAL_H
#define ANTLR_GRAPHDB_EVAL_H

#include "definations.h"
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <sstream>
#include "graphException.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <fstream>

using std::map;
using std::set;
using std::unordered_map;

/*extern map<string, GDBGraph> graphMap;
extern unordered_map<string, GraphSet> graphSetMap;
extern string history;

//Graph evalToGraph(const Graph &g);

void evalToGraphSet(const GSID &gid, GraphSet& graphset);

void evalToGraphSet(const Statement &q, GraphSet& graphset);

void evalToGraphSet(const DMLStatement& dml, GraphSet& graphset);

void evalToGraphSet(const QueryStatement& querystat, GraphSet& graphset);

void evalToGraphSet(const SelectStatement& selectstat, GraphSet& graphset);

void evalToGraphSet(const FromCondition& fromcondition, GraphSet& graphset);

void evalToGraphSet(const OperatorGSet& operatorgset, GraphSet& graphset);

void evalToGraphSet(const WhereCondition& wherecondition, GraphSet& graphset);

void evalToGraphSetFile(const FileName& filename, GraphSet& graphset);

void evalToGraphSetFileList(const vector<FileName>& filenamelist, GraphSet& graphset);

void evalFirstOrderUnit(const FirstOrderUnit& fou, GraphSet& queryGraph, GraphSet& graphset);

void evalFuncStat(const FuncStat& fs, GraphSet& queryGraph, GraphSet& graphset);



//void subgraphMatching

//Graph evalToGraph(const OperationUnit &o);

/*Graph evalToGraph(const OperationStatement &o);

Graph evalToGraph(const UnionStatement &u);

Graph evalToGraph(const MinusStatement &m);*/

#endif //ANTLR_GRAPHDB_EVAL_H

//
// Created by Henry Fox on 2019-12-18.
//

#include "eval.h"
#include "..\subgraphmatching\Match.h"
#include "..\temporal\TemporalGraph.h"
#include "..\temporal\TemporalSearch.h"

/*
map<string, GDBGraph> graphMap;
unordered_map<string, GraphSet> graphSetMap;
string history;

/*Graph evalToGraph(const GraphSet &g) {
    set<VID> vertex;
    for (auto v = g.vertexInfo.begin(); v != g.vertexInfo.end(); v++) {
        if (vertex.count(*v) > 0) {
            throw GraphException("VID duplicate in Graph!");
        }
        vertex.insert(*v);
    }
    for (auto edge = g.edgeInfo.begin(); edge != g.edgeInfo.end(); edge++) {
        set<VID> edgeVertex;
        const auto &vertexInfo = (*edge).vertexInfo;
        for (auto v = vertexInfo.begin(); v != vertexInfo.end(); v++) {
            if (vertex.count(*v) == 0) {
                throw GraphException("Edge vertex not in Vertex list!");
            }
            if (edgeVertex.count(*v) > 0) {
                throw GraphException("VID duplicate in Edge!");
            }
            edgeVertex.insert(*v);
        }
        const auto &edgeInfo = (*edge).edgeLable;
        // TODO Check duplicate edge
        for (auto e = edgeInfo.begin(); e != edgeInfo.end(); e++) {
            const auto a = get<0>(*e);
            const auto b = get<1>(*e);
            if (edgeVertex.count(a) == 0) {
                throw GraphException("Vertex not in Edge Vertex!");
            }
            if (edgeVertex.count(b) == 0) {
                throw GraphException("Vertex not in Edge Vertex!");
            }
        }
    }
    // TODO Check attribute
    return Graph(g);
}*/

/*
void evalToGraphSet(const GSID &gid, GraphSet& graphset) {
	GDBGraph graph;
	graph.location = gid;
	graphset.push_back(graph);
	/*if (graphSetMap.find(gid) != graphSetMap.end()) {
        graphset = GraphSet(graphSetMap[gid]);
    }
    throw GraphException("GID not exist!");*/
/*}

void evalToGraphSet(const Statement &q, GraphSet& graphset) {
	switch (q.type) {
		case DML_STATEMENT_TYPE:
			evalToGraphSet(*q.dmlStatement, graphset);
		case DDL_STATEMENT_TYPE:
			return;
	}
    /*switch (q.sourceGraph.type) {
        case GRAPH_DEFINITION_TYPE:
            graph = evalToGraph(*q.sourceGraph.graph);
            if (q.graphAlias.haveAlias) {
                graphMap[q.graphAlias.gid] = Graph(graph);
            }
            graphMap[""] = Graph(graph);
            return graph;
        case QUERY_STATEMENT_TYPE:
            graph = evalToGraph(*q.sourceGraph.query);
            if (q.graphAlias.haveAlias) {
                graphMap[q.graphAlias.gid] = Graph(graph);
            }
            graphMap[""] = Graph(graph);
            return graph;
        case GID_TYPE:
            graph = evalToGraph(*q.sourceGraph.gid);
            if (q.graphAlias.haveAlias) {
                graphMap[q.graphAlias.gid] = Graph(graph);
            }
            graphMap[""] = Graph(graph);
            return graph;
    }
    throw GraphException("Operation Unit Type Error in QueryStatement");*/
/*}

void evalToGraphSet(const DMLStatement& dml, GraphSet& graphset) {
	switch (dml.type) {
		case QUERY_TYPE:
			evalToGraphSet(*dml.queryStatement, graphset);
	}
}

void evalToGraphSet(const QueryStatement& querystat, GraphSet& graphset) {
	switch (querystat.type) {
		case SELECT_OPERATION_TYPE:
			evalToGraphSet(*querystat.selectStatement, graphset);
			break;
	}
}

void evalFuncStat(const FuncStat& fs, GraphSet& queryGraph, GraphSet& graphset) {
	if (fs.funcName == "tdensesub") {
		vector<string> graph_parameters(fs.objList.begin() + 6, fs.objList.end());
		TemporalSearch ts;
		TemporalGraph g;
		vector<double> parameters_d;
		for (int i = 0; i < graph_parameters.size(); ++i) {
			parameters_d.push_back(stod(graph_parameters[i]));
		}
		g.setPara(parameters_d);
		ts.comboSearching(g, queryGraph[0].location, "tdensesub.log", stoi(fs.objList[0]), stoi(fs.objList[1]), stoi(fs.objList[2]), stoi(fs.objList[3]), stoi(fs.objList[4]), stod(fs.objList[5]));
	}
	else if (fs.funcName == "evotracking") {
		vector<string> graph_parameters(fs.objList.begin() + 6, fs.objList.end());
		TemporalSearch ts;
		TemporalGraph g;
		vector<double> parameters_d;
		for (int i = 0; i < graph_parameters.size(); ++i) {
			parameters_d.push_back(stod(graph_parameters[i]));
		}
		g.setPara(parameters_d);

		vector<int> relnodes;
		string nodesstr = fs.objList[0];
		string cur = "";
		for (int i = 0; i < nodesstr.size(); ++i) {
			if (nodesstr[i] == '-') {
				relnodes.push_back(stoi(cur));
				cur.clear();
			}
			else {
				cur += nodesstr[i];
			}
		}
		if (!cur.empty()) {
			relnodes.push_back(stoi(cur));
			cur.clear();
		}
		ts.evolutionTracking(g, queryGraph[0].location, "evotracking.log", relnodes, stoi(fs.objList[1]), stoi(fs.objList[2]), stoi(fs.objList[3]), stoi(fs.objList[4]), stoi(fs.objList[5]));
	}
}

void evalFirstOrderUnit(const FirstOrderUnit& fou, GraphSet& queryGraph, GraphSet& graphset) {
	switch (fou.type) {
		case FUNC_TYPE:
			evalFuncStat(*fou.funcstat, queryGraph, graphset);
			break;
	}
}

void evalToGraphSet(const SelectStatement& selectstat, GraphSet& graphset) {
	GraphSet inputGraphSet;
	evalToGraphSet(*selectstat.fromCondition, inputGraphSet);

	if (selectstat.whereCondition->type == WHERE_FIRSTORDER_TYPE) {	
		if (selectstat.whereCondition->firstOrderStat->type == FIRST_ORDER_STAT_UNIT_TYPE) {
			evalFirstOrderUnit(*selectstat.whereCondition->firstOrderStat->firstOrderUnit, inputGraphSet, graphset);
		}
	}
	else if (selectstat.whereCondition->type == WHERE_FILENAMELIST_TYPE) {
		GraphSet patternGraphSet;
		evalToGraphSet(*selectstat.whereCondition, patternGraphSet);

		Match match(inputGraphSet[0].location, patternGraphSet[0].location, patternGraphSet[1].location);
		match.logger << inputGraphSet[0].location + " " + patternGraphSet[0].location + " ";
		vector<vector<int>> ans;
		//match.GoMatch_DAF();
		match.GoMatch_DAF_comm();
		//match.GoMatch_vf3();
		//match.GoMatch_vf3_comm();
		//match.GoMatch_Turbo();
		//match.GoMatch_Turbo_comm();
	}

	
	/*string cmd = "SubgraphMatching -d " + inputGraphSet[0].location + " -q " + patternGraphSet[0].location + " -filter DPiso -order DPiso -engine DPiso";
	std::array<char, 4096> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}

	string timecost = "";
	string num = "";
	int index = 0;
	for (index = 0; index < result.size(); ++index) {
		if (result[index] != ' ') {
			timecost += result[index];
		}
		else
			break;
	}
	index++;
	for (; index < result.size(); ++index) {
		num += result[index];
	}

	std::cout << timecost << " " << num << " ";// std::endl;*/
/*
}

void evalToGraphSet(const FromCondition& fromcondition, GraphSet& graphset) {
	switch (fromcondition.type) {
		case FROM_OPERATOR_GSET:
			evalToGraphSet(*fromcondition.operatorGSet, graphset);
	}
}

void evalToGraphSet(const OperatorGSet& operatorgset, GraphSet& graphset) {
	switch (operatorgset.type) {
		case GSET_GSID_TYPE:
			evalToGraphSet(*operatorgset.gsid, graphset);
	}
}

void evalToGraphSet(const WhereCondition& wherecondition, GraphSet& graphset) {
	switch (wherecondition.type) {
		case WHERE_FILENAME_TYPE:
			evalToGraphSetFile(*wherecondition.filename, graphset);
			break;
		case WHERE_FILENAMELIST_TYPE:
			evalToGraphSetFileList(*wherecondition.filenamelist, graphset);
			break;
	}
}

void evalToGraphSetFile(const FileName& filename, GraphSet& graphset) {
	GDBGraph graph;
	graph.location = filename;
	graphset.push_back(graph);
}

void evalToGraphSetFileList(const vector<FileName>& filenamelist, GraphSet& graphset) {
	for (int i = 0; i < filenamelist.size(); ++i) {
		GDBGraph graph;
		graph.location = filenamelist[i];
		graphset.push_back(graph);
	}
}

template<typename T>
vector<T> doUnion(const vector<T> &a, const vector<T> &b) {
    vector<T> ans;
    for (const T &v : a) {
        if (find(ans.begin(), ans.end(), v) == ans.end()) {
            ans.push_back(v);
        }
    }
    for (const T &v : b) {
        if (find(ans.begin(), ans.end(), v) == ans.end()) {
            ans.push_back(v);
        }
    }
    return ans;
}

template<typename T>
vector<T> doMinus(const vector<T> &a, const vector<T> &b) {
    vector<T> ans;
    for (const T &v : a) {
        if (find(b.begin(), b.end(), v) == b.end()) {
            ans.push_back(v);
        }
    }
    return ans;
}

/*Graph evalToGraph(const UnionStatement &u) {
    Graph a = evalToGraph(u.unit_a);
    Graph b = evalToGraph(u.unit_b);

    Graph ans;

    ans.vertexInfo = doUnion(a.vertexInfo, b.vertexInfo);
    ans.edgeInfo = doUnion(a.edgeInfo, b.edgeInfo);
    ans.attributeInfo = AttributeInfo(doUnion(get<0>(a.attributeInfo), get<0>(b.attributeInfo)),
                                      doUnion(get<1>(a.attributeInfo), get<1>(b.attributeInfo)));

    return ans;
}*/

/*Graph evalToGraph(const MinusStatement &m) {
    Graph a = evalToGraph(m.unit_a);
    Graph b = evalToGraph(m.unit_b);

    Graph ans;

    ans.vertexInfo = a.vertexInfo;
    ans.edgeInfo = doMinus(a.edgeInfo, b.edgeInfo);
    ans.attributeInfo = AttributeInfo(doMinus(get<0>(a.attributeInfo), get<0>(b.attributeInfo)),
                                      doMinus(get<1>(a.attributeInfo), get<1>(b.attributeInfo)));

    return ans;
}*/

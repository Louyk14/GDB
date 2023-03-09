#include "ParserGraphs.h"

void WhereConditionGraph::init(WhereCondition* wc) {
	mGraph = NULL;
	if (wc->type == WHERE_FILENAME_TYPE) {
		type = wc->type;
		
		nodeAttributes = new unordered_map<int, unordered_map<string, string>>();
		edgeAttributes = new unordered_map<int, unordered_map<int, unordered_map<string, string>>>();
		outedges = new vector<unordered_map<int, vector<string>>>();
		inedges = new vector<unordered_map<int, vector<string>>>();
		nodeLabels = new vector<string>();

		unordered_map<int, unordered_map<string, unordered_set<string>>> commna;
		unordered_map<int, unordered_map<int, unordered_map<string, unordered_set<string>>>> commea;
		
		string filename = wc->filename->substr(1, (int)wc->filename->size() - 2);
		loadPatternGraph(filename, nodes, *nodeAttributes, *edgeAttributes, *outedges, *inedges, nodeLabels);
	}
	else if (wc->type == WHERE_FIRSTORDER_TYPE) {
		type = wc->type;
		// generateFirstOrderStatGraph(wc->firstOrderStat);
	}
}

void WhereConditionGraph::loadPatternGraph(string filename, vector<int>& nodes
	, unordered_map<int, unordered_map<string, string>>& nodeAttributes
	, unordered_map<int, unordered_map<int, unordered_map<string, string>>>& edgeAttributes
	, vector<unordered_map<int, vector<string>>>& outedges
	, vector<unordered_map<int, vector<string>>>& inedges, vector<string>* nodeLabels)
{
	fstream infile(filename);
	string buff = "";

	int nodenum, edgenum, type;
	infile >> nodenum >> edgenum >> type;
	nodeLabels->resize(nodenum + 1);
	outedges.resize(nodenum + 1);
	inedges.resize(nodenum + 1);
	nodeAttributes.clear();
	edgeAttributes.clear();

	for (int i = 1; i <= nodenum; ++i) {
		int nodeid, attrnum;
		string nlabel;
		infile >> nodeid >> nlabel >> attrnum;
		(*nodeLabels)[nodeid] = nlabel;
		if (attrnum != 0) {
			for (int j = 0; j < attrnum; ++j) {
				string attrname;
				string attrval;
				infile >> attrname >> attrval;
				nodeAttributes[nodeid][attrname] = attrval;
			}
		}
		nodes.push_back(nodeid);
	}

	if (type == 0) {
		for (int i = 0; i < edgenum; ++i) {
			int src, dst, eattrnum;
			string elabel;
			infile >> src >> dst >> elabel >> eattrnum;
			outedges[src][dst].push_back(elabel);
			outedges[dst][src].push_back(elabel);

			if (eattrnum != 0) {
				for (int j = 0; j < eattrnum; ++j) {
					string attrname;
					string attrval;
					infile >> attrname >> attrval;
					edgeAttributes[src][dst][attrname] = attrval;
					edgeAttributes[dst][src][attrname] = attrval;
				}
			}
		}
	}
	else {
		for (int i = 0; i < edgenum; ++i) {
			int src, dst, eattrnum;
			string elabel;
			infile >> src >> dst >> elabel >> eattrnum;
			outedges[src][dst].push_back(elabel);

			if (eattrnum != 0) {
				for (int j = 0; j < eattrnum; ++j) {
					string attrname;
					string attrval;
					infile >> attrname >> attrval;
					edgeAttributes[src][dst][attrname] = attrval;
				}
			}
		}
	}
}

void WhereConditionGraph::loadComboParameter(string filename, unordered_map<string, string>& paras) {
	ifstream input(filename, ios::in);

	string item, value;
	while (input >> item >> value) {
		paras[item] = value;
	}

	input.close();
}

void WhereConditionGraph::convert(GraphSchema& gschema) {
	vector<unordered_map<int, vector<int>>> outedges_i(outedges->size());
	vector<unordered_map<int, vector<int>>> inedges_i(inedges->size());
	vector<int> nodeLabels_i(nodeLabels->size());

	for (int i = 0; i < outedges->size(); ++i) {
		for (const auto& oe : (*outedges)[i]) {
			int node1 = i;
			int node2 = oe.first;
			for (int j = 0; j < oe.second.size(); ++j) {
				outedges_i[node1][node2].push_back(gschema.edgenamemap[oe.second[j]]);
			}
		}
	}
	for (int i = 0; i < inedges->size(); ++i) {
		for (const auto& ie : (*inedges)[i]) {
			int node1 = i;
			int node2 = ie.first;
			for (int j = 0; j < ie.second.size(); ++j) {
				inedges_i[node1][node2].push_back(gschema.edgenamemap[ie.second[j]]);
			}
		}
	}
	for (int i = 1; i < nodeLabels->size(); ++i) {
		nodeLabels_i[i] = gschema.nodenamemap[(*nodeLabels)[i]];
	}

	if (mGraph != NULL)
		delete mGraph;
	mGraph = new MemoryGraph(nodes, nodeAttributes, edgeAttributes, &outedges_i, &inedges_i, gschema.nodenum, &nodeLabels_i, true);
}

void WhereConditionGraph::generateFirstOrderStatGraph(FirstOrderStat* fos) {
	if (fos->type == FIRST_ORDER_STAT_UNIT_TYPE) {
		analyzeFirstOrderUnit(fos->firstOrderUnit);
	}
}

void WhereConditionGraph::analyzeFirstOrderUnit(FirstOrderUnit* fou) {
	if (fou->type == FUNC_TYPE) {
		string funcname = fou->funcstat->funcName;
		if (!fou->funcstat->objList.empty()) {
			string first = fou->funcstat->objList[0];
			if (first.substr(0, 7) == "'-file ") {
				related_file = first.substr(7, first.size() - 8);
				type = 1;
			}
		}
	}
}

void FromConditionGraph::init(FromCondition* fc) {
	if (fc->type == FROM_OPERATOR_GSET && fc->operatorGSet->type == GSET_GSID_TYPE) {
		type = 0;
		gsid = *fc->operatorGSet->gsid;
	}
}

#include "GraphSchema.h"

GraphSchema::GraphSchema(string file) {
	gIO = new GraphIO(file, false, false);
	
	vector<int> params;
	gIO->mapping(this, 0, params);

	delete gIO;

	gIO = new GraphIO(file, true, false);
}

GraphSchema::GraphSchema(string file, string base_dir, unordered_map<string, GraphSchema*>& schemas, bool& succ) {
	gIO = new GraphIO(file, false, false);

	vector<int> params;
	gIO->mapping(this, 0, params);

	delete gIO;

	if (schemas.find(name) != schemas.end()) {
		succ = false;
		return;
	}
	else {
		succ = true;
	}

	gIO = new GraphIO(base_dir + "\\" + name + ".sch", true, false);
}

GraphSchema::GraphSchema(string file, string schemaname, unordered_map<string, vector<pair<string, string>>>& nodeAttrMap, unordered_map<string, vector<pair<string, string>>>& edgeAttrMap, unordered_map<string, vector<pair<string, string>>>& schemaNetwork) {
	gIO = new GraphIO(file, true, false);

	name = schemaname;
	nodenum = nodeAttrMap.size();
	edgelabelnum = edgeAttrMap.size();

	network = vector<unordered_map<int, vector<int>>>(nodenum + 1);
	nodenamemap["ANY"] = 0;

	int index = 0;
	for (auto& nl : nodeAttrMap) {
		nodelabels.push_back(nl.first);
		nodenamemap[nl.first] = index + 1;
		for (int j = 0; j < nl.second.size(); ++j) {
			nodelabeltoattr[index + 1].push_back(make_pair(nl.second[j].first, returnTypeCode(nl.second[j].second)));
		}

		index++;
	}
	
	index = 0;
	for (auto& el : edgeAttrMap) {
		edgelabels.push_back(el.first);
		edgenamemap[el.first] = index + 1;
		for (int j = 0; j < el.second.size(); ++j) {
			edgelabeltoattr[index + 1].push_back(make_pair(el.second[j].first, returnTypeCode(el.second[j].second)));
		}

		index++;
	}
	
	edgenum = 0;
	for (const auto& rel : schemaNetwork) {
		for (const auto& reledge : rel.second) {
			int srcint = nodenamemap[reledge.first];
			int dstint = nodenamemap[reledge.second];
			int relint = edgenamemap[rel.first];
			network[srcint][dstint].push_back(relint);
			edgenum++;
		}
	}
}

GraphSchema::~GraphSchema() {
	vector<int> params;
	gIO->unmapping(this, 0, params);

	if (gIO)
		delete gIO;
}
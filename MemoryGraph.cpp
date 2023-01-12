#include "MemoryGraph.h"

MemoryGraph::MemoryGraph() {
	inMemory = true;
	outMaxDegree = -1;
	inMaxDegree = -1;
	maxDegree = -1;
	edgenum = 0;
	hasNodeLabel = false;
};

MemoryGraph::MemoryGraph(vector<int> n, unordered_map<int, unordered_map<string, string>>* na
	, unordered_map<int, unordered_map<int, unordered_map<string, string>>>* ea
	, vector<unordered_map<int, vector<int>>>* oe, vector<unordered_map<int, vector<int>>>* ie, int labnum
	, vector<int>* nl) {
	nodes = vector<int>(n);
	sort(nodes.begin(), nodes.end());
	nodeAttributes = na;
	edgeAttributes = ea;
	outedges = oe;
	inedges = ie;
	labelnum = labnum;
	if (nl != NULL)
		hasNodeLabel = true;
	else
		hasNodeLabel = false;

	nodeNum = n.size();
	nodeLabels = *nl;

	if (nl != NULL) {
		nodeLabels = *nl;
		labelEdgesVec = new vector<vector<LabelVList*>>(nodeNum + 1, vector<LabelVList*>(labelnum, NULL));
	}

	outMaxDegree = -1;
	inMaxDegree = -1;
	maxDegree = -1;

	preprocess();
}

MemoryGraph::MemoryGraph(string file, string labelfile) {
	gLoader->readGraphFromFile(*this, file, labelfile);
}

MemoryGraph::MemoryGraph(MemoryGraph* mg) {
	communityNum = mg->communityNum;
	nodeNum = mg->nodeNum;
	labelnum = mg->labelnum;
	maxCommSize = mg->maxCommSize;
	hasNodeLabel = mg->hasNodeLabel;
	hasEdgeLabel = mg->hasEdgeLabel;
	nodes = mg->nodes;
	nodeInfo = mg->nodeInfo;
	nodeLabels = mg->nodeLabels;
	commNetworkSet = mg->commNetworkSet;
	netWorkSet = mg->netWorkSet;
	netWorkVec = mg->netWorkVec;

	degreePosOut = mg->degreePosOut;
	degreePosIn = mg->degreePosIn;
	commOutBoundary = mg->commOutBoundary;
	commInBoundary = mg->commInBoundary;
	twoHopLimitation = mg->twoHopLimitation;
	hasTwoHopComms = mg->hasTwoHopComms;
	len4Limitation = mg->len4Limitation;
	triangleLimitation = mg->triangleLimitation;
	len5Limitation = mg->len5Limitation;
	commTotalNumTag = mg->commTotalNumTag;
	commMaxNumTag = mg->commMaxNumTag;

	commOuts = mg->commOuts;
	commIns = mg->commIns;

	inMemory = mg->inMemory;
	outMaxDegree = mg->outMaxDegree;
	inMaxDegree = mg->inMaxDegree;
	maxDegree = mg->maxDegree;
	labelList = mg->labelList;

	nodeAttributes = new unordered_map<int, unordered_map<string, string>>(mg->nodeAttributes->begin(), mg->nodeAttributes->end());
	edgeAttributes = new unordered_map<int, unordered_map<int, unordered_map<string, string>>>(mg->edgeAttributes->begin(), mg->edgeAttributes->end());
	outedges = new vector<unordered_map<int, vector<int>>>(mg->outedges->begin(), mg->outedges->end());
	inedges = new vector<unordered_map<int, vector<int>>>(mg->inedges->begin(), mg->inedges->end());
	invec = new vector<vector<int>>(mg->invec->begin(), mg->invec->end());
	outvec = new vector<vector<int>>(mg->outvec->begin(), mg->outvec->end());
	outvecp = new vector<int>(mg->outvecp->begin(), mg->outvecp->end());
	labelEdgesVec = new vector<vector<LabelVList*>>(mg->labelEdgesVec->begin(), mg->labelEdgesVec->end());
	neighLabels = mg->neighLabels;

	degrees = new int[nodeNum + 1];
	largerbound = new int[nodeNum + 1];
	for (int i = 0; i <= nodeNum; ++i) {
		degrees[i] = mg->degrees[i];
		largerbound[i] = mg->largerbound[i];
	}
	avgdegree = mg->avgdegree;
	edgenum = mg->edgenum;
	idMapping = mg->idMapping;

	nodeIdAlloter = mg->nodeIdAlloter;
	communityIdAlloter = mg->communityIdAlloter;
	communityNodes = mg->communityNodes;
	nodeCommunitySet = mg->nodeCommunitySet;
	destIter = mg->destIter;
	typeIter = mg->typeIter;
	nodeEdges = mg->nodeEdges;
	initialNodes = mg->initialNodes;
	graphNodes = mg->graphNodes;
	edge_dest_head = mg->edge_dest_head;
	nodeblock = mg->nodeblock;
	nodeType = mg->nodeType;
	node_startEdge = mg->node_startEdge;
}

MemoryGraph::~MemoryGraph() {
	if (nodeIdAlloterType == 0) {
		if (nodeIdAlloter.i2iAlloter)
			delete nodeIdAlloter.i2iAlloter;
	}
	else {
		if (nodeIdAlloter.s2iAlloter)
			delete nodeIdAlloter.s2iAlloter;
	}
	
	if (communityIdAlloterType == 0) {
		if (communityIdAlloter.i2iAlloter)
			delete communityIdAlloter.i2iAlloter;
	}
	else {
		if (communityIdAlloter.s2iAlloter)
			delete communityIdAlloter.s2iAlloter;
	}
}

void MemoryGraph::setInfo(int nnum, int cnum, int nodetype, int commtype, string path, string ndval, string commdval) {
	nodeNum = nnum;
	communityNum = cnum;

	if (nodetype == 0) {
		int dval = atoi(ndval.c_str());
		nodeIdAlloter.i2iAlloter = new IdAlloter<int>(path, "node", dval, false);
	}
	else {
		nodeIdAlloter.s2iAlloter = new IdAlloter<string>(path, "node", ndval, false);
	}

	if (commtype == 0) {
		int cdval = atoi(commdval.c_str());
		communityIdAlloter.i2iAlloter = new IdAlloter<int>(path, "comm", cdval, false);
	}
	else {
		communityIdAlloter.s2iAlloter = new IdAlloter<string>(path, "comm", commdval, false);
	}
}

void MemoryGraph::initIdAlloter() {
	if (nodeIdAlloterType == 0) {
		nodeIdAlloter.i2iAlloter->idAlloter(nodes);
	}
	else {
		vector<string> nodestr;
		nodeIdAlloter.s2iAlloter->idAlloter(nodestr);
	}

	if (communityIdAlloterType == 0) {
		communityIdAlloter.i2iAlloter->idAlloter(communities);
	}
	else {
		vector<string> commstr;
		communityIdAlloter.s2iAlloter->idAlloter(commstr);
	}
}


void MemoryGraph::preprocess() {
	invec = new vector<vector<int>>(nodeNum + 1);
	outvec = new vector<vector<int>>(nodeNum + 1);

	edgenum = 0;
	for (int n1 = 1; n1 < inedges->size(); ++n1)
	{
		inMaxDegree = max(inMaxDegree, (int)(*inedges)[n1].size());
		for (const auto& n2 : (*inedges)[n1])
		{
			(*invec)[n1].push_back(n2.first);
		}
		sort((*invec)[n1].begin(), (*invec)[n1].end());
		edgenum += (*invec)[n1].size();
	}

	outvecp = new vector<int>[nodeNum + 1];
	//fill(outvecp->begin(), outvecp->end(), vector<int>());
	largerbound = new int[nodeNum + 1];
	fill(largerbound, largerbound + nodeNum + 1, -1);
	for (int n1 = 1; n1 < outedges->size(); ++n1)
	{
		int myout = (*outedges)[n1].size();
		int myin = (*inedges)[n1].size();
		outMaxDegree = max(outMaxDegree, myout);
		maxDegree = max(maxDegree, myout + myin);
		largerbound[n1] = outedges->size() - 1;

		for (const auto& n2 : (*outedges)[n1])
		{
			(*outvec)[n1].push_back(n2.first);
			if (hasNodeLabel)
			{
				int label = nodeLabels[n2.first];
				if ((*labelEdgesVec)[n1][label] != NULL)
				{
					(*labelEdgesVec)[n1][label]->vList.insert(n2.first);
				}
				else
				{
					LabelVList* l = new LabelVList();
					l->label = label;
					l->vList.insert(n2.first);
					(*labelEdgesVec)[n1][label] = l;
					neighLabels[n1].insert(label);
				}
			}
		}
		sort((*outvec)[n1].begin(), (*outvec)[n1].end());
		outvecp[n1] = vector<int>((*outvec)[n1].begin(), (*outvec)[n1].end());
		for (int i = 0; i < outvecp[n1].size(); ++i) {
			if (outvecp[n1][i] >= n1) {
				largerbound[n1] = i;
				break;
			}
		}
	}

	getdegrees();
}

void MemoryGraph::readCommunity(const string& pathFile)
{
	fstream inFile;
	inFile.open(pathFile, ios::in);
	if (inFile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}
	const int BUFFER_LENGTH = 100;
	char buffer[BUFFER_LENGTH] = { 0 };

	inFile >> nodeNum >> communityNum >> labelnum;
	communityNodes = vector<vector<int>>(communityNum + 1);
	nodeInfo = vector<vector<int>>(nodeNum + 1);
	inFile.get();

	int counter = 13;

	while (inFile.getline(buffer, BUFFER_LENGTH))
	{
		if (buffer[0] == '#')continue;
		int community = -1;
		int nodeId = -1;
		int label = 0;
		//sscanf(buffer, "%d	%d %d", &nodeId, &community, &label);
		sscanf(buffer, "%d	%d", &nodeId, &community);

		//if(!node_ids.empty() && node_ids[node_ids.size() - 1] == nodeId)
		//	continue;

		nodeInfo[nodeId] = vector<int>(2);
		nodes.push_back(nodeId);
		if (community == -1)
		{
			//graph.nodeCommunity[nodeId] = counter;
			//if (graph.nodeCommunitySet[nodeId].empty())
			{
				nodeInfo[nodeId][0] = counter;
				//nodeInfo[nodeId][1] = label;
				communityNodes[counter].push_back(nodeId);
			}
			counter++;
		}
		else
		{
			//graph.nodeCommunity[nodeId] = community;
			//if (graph.nodeCommunitySet[nodeId].empty())
			{
				nodeInfo[nodeId][0] = community;
				//nodeInfo[nodeId][1] = label;
				communityNodes[community].push_back(nodeId);
			}
		}
	}
	inFile.close();

	//nodeLabels = vector<int>(nodes.size() + 1);
	//for (const auto& n : nodes)
	//{
	//	nodeLabels[n] = nodeInfo[n][1];
	//}

	maxCommSize = 0;
	for (const auto& c : communityNodes) {
		if (c.size() >= maxCommSize)
			maxCommSize = c.size();
	}
}

void MemoryGraph::initAfterLoadNetwork() {
	outedges = &netWorkSet;
	inedges = &netWorkSet;
	// labelnum = labnum;

	if (hasNodeLabel)
	{
		labelEdgesVec = new vector<vector<LabelVList*>>(nodeNum + 1, vector<LabelVList*>(labelnum, NULL));
	}

	outMaxDegree = -1;
	inMaxDegree = -1;
	maxDegree = -1;

	preprocess();
}

/*
void MemoryGraph::loadFromFile(string file, string labelfile) {
	loadNetworkFromFile(file);

	for (int i = 0; i < netWorkSet.size(); ++i) {
		if (!netWorkSet[i].empty())
			nodes.push_back(i);
	}
	
	initAfterLoadNetwork(labelfile);
}

void MemoryGraph::loadNetworkFromFile(string file) {
	fstream inFile;
	inFile.open(file, ios::in);
	if (inFile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}
	const int BUFFER_LENGTH = 20;
	char buffer[BUFFER_LENGTH] = { 0 };

	int maxInterEdge = 0;
	int pre_node = -1;
	vector<pair<int, int>>temp;
	set<int>tempset;
	unordered_map<int, degmodel> nodeouts, nodeins;
	int liner = 0;

	while (inFile.getline(buffer, BUFFER_LENGTH))
	{
		if (buffer[0] == '#')continue;
		if (liner == 0) {
			sscanf(buffer, "%d %d", &nodeNum, &labelnum);
			liner++;
			initNetwork(nodeNum);
			continue;
		}
		int nodeId1 = -1;
		int nodeId2 = -1;
		int type = 0;
		if (labelnum > 0) {
			sscanf(buffer, "%d	%d", &nodeId1, &nodeId2);
		}
		else {
			sscanf(buffer, "%d	%d	%d", &nodeId1, &nodeId2, &type);
		}

		if (nodeId1 == nodeId2)
		{
			continue;
		}

		if (netWorkSet[nodeId1].find(nodeId2) != netWorkSet[nodeId1].end())
			continue;

		addEdge(nodeId1, nodeId2, type);
		//netWorkSet[nodeId1].insert(nodeId2);
		//inNetWorkSet[nodeId2].insert(nodeId1);
		//netWorkVec[nodeId1].push_back(nodeId2);
		//inNetWorkVec[nodeId2].push_back(nodeId1);

		//addEdge(nodeId2, nodeId1);
		//netWorkSet[nodeId2].insert(nodeId1);
		//inNetWorkSet[nodeId2].insert(nodeId1);
		//netWorkVec[nodeId2].push_back(nodeId1);
		//inNetWorkVec[nodeId2].push_back(nodeId1);
	}
	inFile.close();
}

void MemoryGraph::loadLabelFromFile(string file) {
	fstream inFile;
	inFile.open(file, ios::in);
	if (inFile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}
	const int BUFFER_LENGTH = 20;
	char buffer[BUFFER_LENGTH] = { 0 };

	int maxInterEdge = 0;
	int pre_node = -1;
	vector<pair<int, int>>temp;
	set<int>tempset;
	unordered_map<int, degmodel> nodeouts, nodeins;
	int liner = 0;

	int labelnodenum;

	while (inFile.getline(buffer, BUFFER_LENGTH))
	{
		if (buffer[0] == '#')continue;
		if (liner == 0) {
			sscanf(buffer, "%d %d", &labelnodenum, &labelnum);
			if (labelnodenum > nodeNum) {
				cout << "labelnodenum larger than nodenum" << endl;
				return;
			}
			liner++;
			nodeLabels.clear();
			nodeLabels = vector<int>(nodeNum + 1, 0);
			continue;
		}
		int nodeId = -1;
		int type = 0;
		sscanf(buffer, "%d	%d", &nodeId, &type);
		nodeLabels[nodeId] = type;
	}
	inFile.close();
}
*/

void MemoryGraph::getdegrees() {
	degrees = new int[nodeNum + 1];
	int degree_sum = 0;
	for (const auto& nid : nodes) {
		degrees[nid] = netWorkSet[nid].size();
		degree_sum += degrees[nid];
	}
	avgdegree = (double)degree_sum / nodeNum;
}

void MemoryGraph::initNetwork(int n) {
	netWorkSet = vector<unordered_map<int, vector<int>>>(n + 1);
	nodeEdges = vector<int>(n + 1, 0);
	destIter = vector<unordered_map<int, vector<int>>::iterator>(n + 1);
	typeIter = vector<vector<int>::iterator>(n + 1);
	edge_dest_head = vector<EdgePos>(n + 1);
	nodeblock = vector<unordered_set<int>>(n + 1);
	//netWorkVec = vector<vector<int>>(n + 1); 
}

void MemoryGraph::initCommunity(int m, int n) {
	communityNodes = vector<vector<int>>(m + 1);
	nodeInfo = vector<vector<int>>(n + 1);
	nodeCommunitySet = vector<unordered_set<int>>(n + 1);
}

void MemoryGraph::init(int n, int m) {
	communityNodes = vector<vector<int>>(m + 1);
	netWorkSet = vector<unordered_map<int, vector<int>>>(n + 1);
	//netWorkVec = vector<vector<int>>(n + 1); 
	destIter = vector<unordered_map<int, vector<int>>::iterator>(n + 1);
	typeIter = vector<vector<int>::iterator>(n + 1);
	nodeEdges = vector<int>(n + 1, 0);

	nodeCommunitySet = vector<unordered_set<int>>(n + 1);
	edge_dest_head = vector<EdgePos>(n + 1);
	nodeblock = vector<unordered_set<int>>(n + 1);

}

bool MemoryGraph::existNode(int node) {
	if (nodeIdAlloterType == 0) {
		return nodeIdAlloter.i2iAlloter->existId(node);
	}
	else {
		return nodeIdAlloter.s2iAlloter->existId(node);
	}
}

void MemoryGraph::insertNode(int node, vector<int>& comm_id, bool resize) {
	graphNodes.insert(node);

	if (!comm_id.empty())
	{
		if (resize)
		{
			int max_commid = -1;
			for (const auto& comm : comm_id)
				max_commid = max(max_commid, comm);

			reAllotNodeSpace(node);
			reAllotCommSpace(max_commid);
		}

		for (int i = 0; i < comm_id.size(); i++)
		{
			communityNodes[comm_id[i]].push_back(node);
			nodeCommunitySet[node].insert(comm_id[i]);
		}
	}
}

void MemoryGraph::removeNode(int node) {
	graphNodes.erase(node);

	if (nodeIdAlloterType == 0) {
		nodeIdAlloter.i2iAlloter->removenId(node);
	}
	else {
		nodeIdAlloter.s2iAlloter->removenId(node);
	}

	for (const auto& cid : nodeCommunitySet[node]) {
		for (int i = 0; i < communityNodes[cid].size(); ++i) {
			if (communityNodes[cid][i] == node) {
				communityNodes[cid][i] = communityNodes[cid][communityNodes[cid].size() - 1];
				communityNodes[cid].pop_back();
				break;
			}
		}
		//communityNodes[cid].erase(node);
	}
}

bool MemoryGraph::nodeHasCommunity(int node)
{
	if (communityIdAlloterType == 0) {
		return node <= communityIdAlloter.i2iAlloter->getMaxId() && !nodeCommunitySet[node].empty();
	}
	else {
		return node <= communityIdAlloter.s2iAlloter->getMaxId() && !nodeCommunitySet[node].empty();
	}
}

int MemoryGraph::getNodeFirstCommunity(int node)
{
	if (nodeHasCommunity(node))
		return *nodeCommunitySet[node].begin();
}

int MemoryGraph::getNodeNum()
{
	if (nodeIdAlloterType == 0) {
		return nodeIdAlloter.i2iAlloter->getIdNum();
	}
	else {
		return nodeIdAlloter.s2iAlloter->getIdNum();
	}
}

int MemoryGraph::getCommunityNum() {
	if (communityIdAlloterType == 0) {
		return communityIdAlloter.i2iAlloter->getIdNum();
	}
	else {
		return communityIdAlloter.s2iAlloter->getIdNum();
	}
}

int MemoryGraph::getMaxNodeId() {
	if (nodeIdAlloterType == 0) {
		return nodeIdAlloter.i2iAlloter->getMaxId();
	}
	else {
		return nodeIdAlloter.s2iAlloter->getMaxId();
	}
}

int MemoryGraph::getMaxCommunityId() {
	if (communityIdAlloterType == 0) {
		return communityIdAlloter.i2iAlloter->getMaxId();
	}
	else {
		return communityIdAlloter.s2iAlloter->getMaxId();
	}
}

void MemoryGraph::reAllotNodeSpace(int nid)
{
	if (nid >= nodeCommunitySet.size())
	{
		nodeCommunitySet.resize(nid + 1);
		edge_dest_head.resize(nid + 1);
		nodeblock.resize(nid + 1);
	}
}

void MemoryGraph::reAllotCommSpace(int cid)
{
	if (cid >= communityNodes.size())
		communityNodes.resize(cid + 1);
}
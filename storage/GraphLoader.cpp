#include "GraphLoader.h"

void GraphLoader::readCommunity(MemoryGraph& graph, const string& pathFile, string idpath)
{
	graph.communityNodes.clear();

	fstream inFile;
	inFile.open(pathFile, ios::in);
	if (inFile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}
	const int BUFFER_LENGTH = 100;
	char buffer[BUFFER_LENGTH] = { 0 };

	int counter = 13;

	string iddefault, commdefault;
	inFile >> graph.nodeNum >> graph.nodeIdAlloterType >> iddefault >> graph.communityNum >> graph.communityIdAlloterType >> commdefault >> graph.labelnum;
	inFile.get();
	// Get Node Num and Community Num
	graph.initCommunity(graph.communityNum, graph.nodeNum);

	graph.setInfo(graph.nodeNum, graph.communityNum, graph.nodeIdAlloterType, graph.communityIdAlloterType, idpath, iddefault, commdefault);

	while (inFile.getline(buffer, BUFFER_LENGTH))
	{
		if (buffer[0] == '#')continue;

		if (graph.nodeIdAlloterType == 0 && graph.communityIdAlloterType == 0) {
			int community = -1;
			int nodeId = -1;
			int label = 0;
			sscanf(buffer, "%d	%d", &nodeId, &community);
			//community -= 2;

			nodeId = graph.nodeIdAlloter.i2iAlloter->allotId(nodeId);
			community = graph.communityIdAlloter.i2iAlloter->allotId(community);

			graph.nodeInfo[nodeId] = vector<int>(2);

			if (graph.graphNodes.find(nodeId) == graph.graphNodes.end())
			{
				graph.initialNodes.push_back(nodeId);
				graph.graphNodes.insert(nodeId);
			}

			graph.nodeInfo[nodeId][0] = community;
			graph.nodeCommunitySet[nodeId].insert(community);
			graph.communityNodes[community].push_back(nodeId);
		}
		else if (graph.nodeIdAlloterType == 0 && graph.communityIdAlloterType == 1) {
			string community = "";
			int nodeId = -1;
			int label = 0;
			sscanf(buffer, "%d	%s", &nodeId, &community);
			//community -= 2;

			nodeId = graph.nodeIdAlloter.i2iAlloter->allotId(nodeId);
			int communityid = graph.communityIdAlloter.s2iAlloter->allotId(community);

			graph.nodeInfo[nodeId] = vector<int>(2);

			if (graph.graphNodes.find(nodeId) == graph.graphNodes.end())
			{
				graph.initialNodes.push_back(nodeId);
				graph.graphNodes.insert(nodeId);
			}

			graph.nodeInfo[nodeId][0] = communityid;
			graph.nodeCommunitySet[nodeId].insert(communityid);
			graph.communityNodes[communityid].push_back(nodeId);
		}
	}
	inFile.close();

	for (int i = 1; i <= graph.communityNum; ++i) {
		graph.communities.push_back(i);
	}

	sort(graph.initialNodes.begin(), graph.initialNodes.end());
	graph.nodes = graph.initialNodes;

	graph.maxCommSize = 0;
	for (const auto& c : graph.communityNodes) {
		if (c.size() >= graph.maxCommSize)
			graph.maxCommSize = c.size();
	}
}

void GraphLoader::readGraphFromFile(MemoryGraph& graph, string file, string labelfile) {
	readNetworkFromFile(graph, file);

	if (graph.nodes.empty()) {
		for (int i = 0; i < graph.netWorkSet.size(); ++i) {
			if (!graph.netWorkSet[i].empty()) {
				graph.nodes.push_back(i);
				graph.graphNodes.insert(i);
			}
		}

		sort(graph.nodes.begin(), graph.nodes.end());
		graph.initialNodes = graph.nodes;
	}

	initAfterReadNetwork(graph, labelfile);
}

void GraphLoader::initAfterReadNetwork(MemoryGraph& graph, string labelfile) {
	graph.nodeNum = graph.nodes.size();

	if (labelfile != "") {
		graph.hasNodeLabel = true;
		readLabelFromFile(graph, labelfile);
	}

	graph.initAfterLoadNetwork();
}

void GraphLoader::readNetworkFromFile(MemoryGraph& graph, string file) {
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
	int liner = 0;

	while (inFile.getline(buffer, BUFFER_LENGTH))
	{
		if (buffer[0] == '#')continue;
		if (liner == 0) {
			sscanf(buffer, "%d %d", &graph.nodeNum, &graph.labelnum);
			liner++;
			graph.initNetwork(graph.nodeNum);
			continue;
		}
		int nodeId1 = -1;
		int nodeId2 = -1;
		int type = 0;
		if (graph.labelnum > 0) {
			sscanf(buffer, "%d	%d	%d", &nodeId1, &nodeId2, &type);
		}
		else {
			sscanf(buffer, "%d	%d", &nodeId1, &nodeId2);
		}

		if (nodeId1 == nodeId2)
		{
			continue;
		}

		graph.netWorkSet[nodeId1][nodeId2].push_back(type);
		graph.nodeEdges[nodeId1]++;
	}
	inFile.close();

	cout << "finish read network" << endl;

	for (int i = 1; i < graph.netWorkSet.size(); ++i)
	{
		graph.destIter[i] = graph.netWorkSet[i].begin();

		if (graph.destIter[i] != graph.netWorkSet[i].end())
		{
			graph.typeIter[i] = graph.netWorkSet[i].begin()->second.begin();
		}
	}
}


void GraphLoader::readLabelFromFile(MemoryGraph& graph, string file) {
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
			sscanf(buffer, "%d %d", &labelnodenum, &graph.labelnum);
			if (labelnodenum > graph.nodeNum) {
				cout << "labelnodenum larger than nodenum" << endl;
				return;
			}
			liner++;
			graph.nodeLabels.clear();
			graph.nodeLabels = vector<int>(graph.nodeNum + 1, 0);
			continue;
		}
		int nodeId = -1;
		int type = 0;
		sscanf(buffer, "%d	%d", &nodeId, &type);
		graph.nodeLabels[nodeId] = type;
	}
	inFile.close();
}

void GraphLoader::loadCommunityNodes(MemoryGraph& graph, string& filepath)
{
	ifstream infile(filepath);
	if (infile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}

	string buffer = "";

	int n = graph.getMaxNodeId();
	int m = graph.getMaxCommunityId();
	
	graph.communityNodes = vector<vector<int>>(m + 1);
	graph.nodeCommunitySet = vector<unordered_set<int>>(n + 1);

	// vector<int> existIds = vector<int>(m + 1, 0);

	if (infile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}

	while (getline(infile, buffer))
	{
		istringstream iss;
		iss.str(buffer);

		int comm_id;
		iss >> comm_id;

		int node_id;

		while (iss >> node_id)
		{
			graph.communityNodes[comm_id].push_back(node_id);
			graph.nodeCommunitySet[node_id].insert(comm_id);
		}
	}
	infile.close();
}

void GraphLoader::writeCommunityNodes(MemoryGraph& graph, string& filepath)
{
	ofstream outfile(filepath);

	if (graph.communityIdAlloterType == 0) {
		int maxId = graph.communityIdAlloter.i2iAlloter->getMaxId();
		for (int comm = 1; comm <= maxId; ++comm)
		{
			if (!graph.communityIdAlloter.i2iAlloter->existId(comm)) {
				continue;
			}

			outfile << comm;

			for (const auto& node : graph.communityNodes[comm])
			{
				outfile << " " << node;
			}

			outfile << endl;
		}
	}
	else {
		int maxId = graph.communityIdAlloter.s2iAlloter->getMaxId();
		for (int comm = 1; comm <= maxId; ++comm)
		{
			if (!graph.communityIdAlloter.s2iAlloter->existId(comm)) {
				continue;
			}

			outfile << comm;

			for (const auto& node : graph.communityNodes[comm])
			{
				outfile << " " << node;
			}

			outfile << endl;
		}
	}

	outfile.close();
}

void GraphLoader::loadNodeBlocks(MemoryGraph& graph, string& filepath) {
	ifstream infile(filepath);
	if (infile.fail()) {
		cerr << "读取文件错误" << endl;
		return;
	}

	string buffer = "";

	int n = graph.getMaxNodeId();

	graph.nodeblock = vector<unordered_set<int>>(n + 1);

	// vector<int> existIds = vector<int>(m + 1, 0);

	if (infile.fail()) {
		cerr << "读取文件错误" << endl;
		return;
	}

	while (getline(infile, buffer)) {
		istringstream iss;
		iss.str(buffer);

		int nodeid;
		iss >> nodeid;

		int blockid;
		while (iss >> blockid) {
			graph.nodeblock[nodeid].insert(blockid);
		}
	}
	infile.close();
}

void GraphLoader::writeNodeBlocks(MemoryGraph& graph, string& filepath)
{
	ofstream outfile(filepath);

	for (int i = 1; i < graph.nodeblock.size(); ++i) {
		if (!graph.nodeblock[i].empty()) {
			outfile << i;
			for (const auto& blockid : graph.nodeblock[i]) {
				outfile << " " << blockid;
			}
			outfile << endl;
		}
	}

	outfile.close();
}

void GraphLoader::loadEdgeDestHead(MemoryGraph& graph, string& filepath)
{
	ifstream infile(filepath);
	if (infile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}

	string buffer = "";

	int n = graph.getMaxNodeId();

	graph.edge_dest_head = vector<EdgePos>(n + 1);

	// vector<int> existIds = vector<int>(m + 1, 0);

	if (infile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}

	int node_id;
	int block_pos;
	int list_index;
	int edge_index;

	while (getline(infile, buffer)) {
		istringstream iss;
		iss.str(buffer);

		iss >> node_id;

		while (iss >> block_pos >> list_index >> edge_index) {
			graph.edge_dest_head[node_id] = EdgePos(block_pos, list_index, edge_index);
		}
	}
	infile.close();
}

void GraphLoader::writeEdgeDestHead(MemoryGraph& graph, string& filepath)
{
	ofstream outfile(filepath);

	for (int i = 1; i < graph.edge_dest_head.size(); ++i) {
		if (graph.edge_dest_head[i].block_pos != -1) {
			outfile << i << " " << graph.edge_dest_head[i].block_pos << " " << graph.edge_dest_head[i].list_index << " " << graph.edge_dest_head[i].edge_index << endl;
		}
	}

	outfile.close();
}

void GraphLoader::loadNetworkReg(GraphManager& g, TempGraph& graph, string pathFile)
{
	fstream inFile;
	inFile.open(pathFile, ios::in);
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
	
	while (inFile.getline(buffer, BUFFER_LENGTH))
	{
		if (buffer[0] == '#')continue;
		int nodeId1 = -1;
		int nodeId2 = -1;
		int type = 0;
		if (g.mGraph->nodeIdAlloterType == 0) {
			sscanf(buffer, "%d	%d", &nodeId1, &nodeId2);

			if (nodeId1 == nodeId2) {
				continue;
			}

			nodeId1 = g.mGraph->nodeIdAlloter.i2iAlloter->allotId(nodeId1);
			graph.insertFirstNode(nodeId1, g.mGraph->nodeIdAlloter.i2iAlloter->newAlloted());

			nodeId2 = g.mGraph->nodeIdAlloter.i2iAlloter->allotId(nodeId2);
			graph.insertSecondNode(nodeId2, g.mGraph->nodeIdAlloter.i2iAlloter->newAlloted());
		}
		else {
			string node1str, node2str;
			sscanf(buffer, "%s	%s", &node1str, &node2str);

			if (node1str == node2str) {
				continue;
			}

			nodeId1 = g.mGraph->nodeIdAlloter.s2iAlloter->allotId(node1str);
			graph.insertFirstNode(nodeId1, g.mGraph->nodeIdAlloter.s2iAlloter->newAlloted());

			nodeId2 = g.mGraph->nodeIdAlloter.s2iAlloter->allotId(node2str);
			graph.insertSecondNode(nodeId2, g.mGraph->nodeIdAlloter.s2iAlloter->newAlloted());
		}

		graph.netWorkSet[nodeId1][nodeId2].push_back(type);
		graph.nodeEdges[nodeId1]++;
	}
	inFile.close();

	cout << "finish read network" << endl;
}
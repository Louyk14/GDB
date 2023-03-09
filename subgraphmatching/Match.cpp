#include "Match.h"

Match::Match(GraphManager* gmanager, MemoryGraph* p) {
	gm = gmanager;
	pattern = p;

	if (!gm->inMemory)
		gm->setInMemory();
	data = gm->mGraph;
	analyzeNetwork(data);

	constructCommunityGraph();

	share1NeighbourPairs = vector<vector<bool>>(data->communityNum + 1, vector<bool>(data->communityNum + 1, false));
	share2NeighbourPairs = vector<vector<vector<bool>>>(data->communityNum + 1, vector<vector<bool>>(data->communityNum + 1, vector<bool>(data->communityNum + 1, false)));

	for (int i = 1; i < data->netWorkSet.size(); ++i)
	{
		int n1 = i;
		set<int> rec;
		unordered_map<int, int> record_comm;
		// int comm1 = data->nodeInfo[n1][0];
		int comm1 = *data->nodeCommunitySet[n1].begin();
		for (const auto& n2 : data->netWorkSet[n1])
		{
			// int comm2 = data->nodeInfo[n2.first][0];
			int comm2 = *data->nodeCommunitySet[n2.first].begin();
			rec.insert(comm2);
			if (record_comm.find(comm2) == record_comm.end())
				record_comm[comm2] = 1;
			else
				record_comm[comm2]++;
			share1NeighbourPairs[comm1][comm2] = true;
		}
		vector<int> recv = vector<int>(rec.begin(), rec.end());
		for (int p = 0; p < recv.size(); ++p)
		{
			for (int q = 0; q < recv.size(); ++q)
			{
				if (recv[p] == recv[q] && record_comm[recv[p]] == 1)
					continue;
				share2NeighbourPairs[comm1][recv[p]][recv[q]] = true;
			}
		}
	}
	cout << "finish share" << endl;
	ansnum = 0;
	internum = 0;
	matchType = 1;

	usefulCS = 0;
	uselessCS = 0;
	uselessDouble = 0;
	uselessUntrivial = 0;
	uselessCut2 = 0;
}

Match::Match(string datafile, string communityfile, string patternfile)
{
	samecounter = 0;
	//data = new MemoryGraph();
	cout << "start community" << endl;
	data->readCommunity(communityfile);
	cout << "finish community" << endl;
	//system("pause");
	data->gLoader->readNetworkFromFile(*data, datafile);
	analyzeNetwork(data);
	//data->readNetwork(datafile);
	cout << "finish network" << endl;

	int m = data->edgenum;
	float Q=0,e,a;
	for(int c = 1; c < data->communityNodes.size(); ++c)// for each community
	{
		e=a=0;
		for(const auto& n : data->communityNodes[c])
		{
			a += data->netWorkSet[n].size();
			for(const auto& n2 : data->netWorkSet[n])
			{
				if(data->nodeInfo[n2.first][0] == c)
					e++;
			}
		}

		e /= m;
		a /= m;
		Q += (e - a*a);
	}
	cout << "Modularity: " << Q << endl;

	//system("pause");
	loadPattern(patternfile);
	//system("pause");
	logger.open("log.dat", ios::app);
	cout << "start share" << endl;
	share1NeighbourPairs = vector<vector<bool>>(data->communityNum + 1, vector<bool>(data->communityNum + 1, false));
	share2NeighbourPairs = vector<vector<vector<bool>>>(data->communityNum + 1, vector<vector<bool>>(data->communityNum + 1, vector<bool>(data->communityNum + 1, false)));

	for (int i = 1; i < data->netWorkSet.size(); ++i)
	{
		int n1 = i;
		set<int> rec;
		unordered_map<int, int> record_comm;
		int comm1 = data->nodeInfo[n1][0];
		for (const auto& n2 : data->netWorkSet[n1])
		{
			int comm2 = data->nodeInfo[n2.first][0];
			rec.insert(comm2);
			if (record_comm.find(comm2) == record_comm.end())
				record_comm[comm2] = 1;
			else
				record_comm[comm2]++;
			share1NeighbourPairs[comm1][comm2] = true;
		}
		vector<int> recv = vector<int>(rec.begin(), rec.end());
		for (int p = 0; p < recv.size(); ++p)
		{
			for (int q = 0; q < recv.size(); ++q)
			{
				if (recv[p] == recv[q] && record_comm[recv[p]] == 1)
					continue;
				share2NeighbourPairs[comm1][recv[p]][recv[q]] = true;
			}
		}
	}
	cout << "finish share" << endl;
	ansnum = 0;
	internum = 0;
	matchType = 1;

	usefulCS = 0;
	uselessCS = 0;
	uselessDouble = 0;
	uselessUntrivial = 0;
	uselessCut2 = 0;
}

Match::Match(MemoryGraph* datagraph, MemoryGraph* patterngraph, bool loadpattern, string patternfile, bool loadcommunity, string communityfile) {
	samecounter = 0;
	data = datagraph;

	//data = new MemoryGraph();
	if (loadcommunity) {
		cout << "start community" << endl;
		data->readCommunity(communityfile);
		cout << "finish community" << endl;
	}
	//system("pause");
	
	analyzeNetwork(data);

	int m = data->edgenum;
	float Q = 0, e, a;
	for (int c = 1; c < data->communityNodes.size(); ++c)// for each community
	{
		e = a = 0;
		for (const auto& n : data->communityNodes[c])
		{
			a += data->netWorkSet[n].size();
			for (const auto& n2 : data->netWorkSet[n])
			{
				if (data->nodeInfo[n2.first][0] == c)
					e++;
			}
		}

		e /= m;
		a /= m;
		Q += (e - a*a);
	}
	cout << "Modularity: " << Q << endl;

	//system("pause");
	if (loadpattern) {
		loadPattern(patternfile);
	}
	else {
		pattern = patterngraph;
	}

	//system("pause");
	logger.open("log.dat", ios::app);
	cout << "start share" << endl;

	constructCommunityGraph();

	share1NeighbourPairs = vector<vector<bool>>(data->communityNum + 1, vector<bool>(data->communityNum + 1, false));
	share2NeighbourPairs = vector<vector<vector<bool>>>(data->communityNum + 1, vector<vector<bool>>(data->communityNum + 1, vector<bool>(data->communityNum + 1, false)));

	for (int i = 1; i < data->netWorkSet.size(); ++i)
	{
		int n1 = i;
		set<int> rec;
		unordered_map<int, int> record_comm;
		int comm1 = data->nodeInfo[n1][0];
		for (const auto& n2 : data->netWorkSet[n1])
		{
			int comm2 = data->nodeInfo[n2.first][0];
			rec.insert(comm2);
			if (record_comm.find(comm2) == record_comm.end())
				record_comm[comm2] = 1;
			else
				record_comm[comm2]++;
			share1NeighbourPairs[comm1][comm2] = true;
		}
		vector<int> recv = vector<int>(rec.begin(), rec.end());
		for (int p = 0; p < recv.size(); ++p)
		{
			for (int q = 0; q < recv.size(); ++q)
			{
				if (recv[p] == recv[q] && record_comm[recv[p]] == 1)
					continue;
				share2NeighbourPairs[comm1][recv[p]][recv[q]] = true;
			}
		}
	}
	cout << "finish share" << endl;
	ansnum = 0;
	internum = 0;
	matchType = 1;

	usefulCS = 0;
	uselessCS = 0;
	uselessDouble = 0;
	uselessUntrivial = 0;
	uselessCut2 = 0;
}

void Match::loadPatternGraph(string filename, vector<int>& nodes
	, unordered_map<int, unordered_map<string, string>>& nodeAttributes
	, unordered_map<int, unordered_map<int, unordered_map<string, string>>>& edgeAttributes
	, vector<unordered_map<int, vector<int>>>& outedges
	, vector<unordered_map<int, vector<int>>>& inedges, vector<int>* nodeLabels)
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
		int actual = gm->gSchema->nodenamemap[nlabel];
		(*nodeLabels)[nodeid] = actual;
		if (attrnum != 0) {
			for (int j = 0; j < attrnum; ++j) {
				string attrname;
				string attrval;
				nodeAttributes[nodeid][attrname] = attrval;
			}
		}
	}

	if (type == 0) {
		for (int i = 0; i < edgenum; ++i) {
			int src, dst, eattrnum;
			string elabel;
			infile >> src >> dst >> elabel >> eattrnum;
			int actual = gm->gSchema->edgenamemap[elabel];
			outedges[src][dst].push_back(actual);
			outedges[dst][src].push_back(actual);

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
			int actual = gm->gSchema->edgenamemap[elabel];
			outedges[src][dst].push_back(actual);

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

void Match::analyzeNetwork(MemoryGraph* g) {
	cout << g->nodeNum << " " << g->communityNum << " " << g->labelnum << endl;
	
	g->commNetworkSet = vector<vector<vector<unordered_set<int>>>>(g->nodeNum + 1, vector<vector<unordered_set<int>>>(g->communityNum + 1, vector<unordered_set<int>>(g->labelnum)));
	g->commOutBoundary = vector<vector<vector<vector<int>>>>(g->communityNum + 1, vector<vector<vector<int>>>(g->communityNum + 1, vector<vector<int>>(g->labelnum)));
	g->commInBoundary = vector<vector<vector<vector<int>>>>(g->communityNum + 1, vector<vector<vector<int>>>(g->communityNum + 1, vector<vector<int>>(g->labelnum)));
	g->degreePosOut = vector<vector<vector<vector<DegreePos>>>>(g->communityNum + 1, vector<vector<vector<DegreePos>>>(g->communityNum + 1, vector<vector<DegreePos>>(g->labelnum)));
	g->degreePosIn = vector<vector<vector<vector<DegreePos>>>>(g->communityNum + 1, vector<vector<vector<DegreePos>>>(g->communityNum + 1, vector<vector<DegreePos>>(g->labelnum)));
	//twoHopLimitation = vector<vector<unordered_map<int, unordered_map<int, int>>>>(nodeNum + 1, vector<unordered_map<int, unordered_map<int, int>>>(communityNum + 1));

	//twoHopLimitation = vector<vector<unordered_map<int, unordered_map<int, int>>>>(nodeNum + 1, vector<unordered_map<int, unordered_map<int, int>>>(communityNum + 1));
	//twoHopLimitation = vector<vector<vector<unordered_map<int, int>*>>>(nodeNum + 1, vector<vector<unordered_map<int, int>*>>(communityNum + 1, vector<unordered_map<int, int>*>(communityNum + 1, NULL)));
	//hasTwoHopComms = vector<vector<vector<bool>>>(nodeNum + 1, vector<vector<bool>>(communityNum + 1, vector<bool>(communityNum + 1, false)));
	//hasTwoHopLabels = vector<vector<vector<vector<int>>>>(nodeNum + 1, vector<vector<vector<int>>>(communityNum + 1, vector<vector<int>>(communityNum + 1)));

	//len4Limitation = vector<vector<vector<vector<bool>>>>(communityNum + 1, vector<vector<vector<bool>>>(communityNum + 1, vector<vector<bool>>(communityNum + 1, vector<bool>(communityNum + 1, false))));
	//triangleLimitation = len4Limitation;

	g->triangleLimitation = vector<vector<vector<bool>>>(g->communityNum + 1, vector<vector<bool>>(g->communityNum + 1, vector<bool>(g->communityNum + 1, false)));

	g->commTotalNumTag = vector<vector<int>>(g->communityNum + 1, vector<int>(g->communityNum + 1, 0));
	g->commMaxNumTag = vector<vector<int>>(g->communityNum + 1, vector<int>(g->communityNum + 1, 0));
	/*commTotalNumTag = new int*[communityNum + 1];
	commMaxNumTag = new int*[communityNum + 1];
	for (int i = 0; i < communityNum + 1; ++i) {
	commTotalNumTag[i] = new int[communityNum + 1];
	commMaxNumTag[i] = new int[communityNum + 1];
	memset(commTotalNumTag[i], 0, (communityNum + 1) * sizeof(int));
	memset(commMaxNumTag[i], 0, (communityNum + 1) * sizeof(int));
	}*/

	cout << "finish alloc" << endl;

	for (const auto& nodeId1 : g->nodes) {
		for (const auto& nodeId2 : g->netWorkSet[nodeId1]) {
			// int c2 = g->nodeInfo[nodeId2.first][0];
			int c2 = *g->nodeCommunitySet[nodeId2.first].begin();
			g->commNetworkSet[nodeId1][c2][g->nodeLabels[nodeId2.first]].insert(nodeId2.first);
			// int c1 = g->nodeInfo[nodeId1][0];
			int c1 = *g->nodeCommunitySet[nodeId1].begin();
			g->commTotalNumTag[c1][c2]++;

			if (g->commOuts[c1][c2].find(nodeId1) != g->commOuts[c1][c2].end())
			{
				g->commOuts[c1][c2][nodeId1].degree++;
			}
			else
			{
				degmodel d;
				d.degree = 1;
				d.node_id = nodeId1;
				g->commOuts[c1][c2][nodeId1] = d;
			}

			if (g->commIns[c2][c1].find(nodeId2.first) != g->commIns[c2][c1].end())
			{
				g->commIns[c2][c1][nodeId2.first].degree++;
			}
			else
			{
				degmodel d;
				d.degree = 1;
				d.node_id = nodeId2.first;
				g->commIns[c2][c1][nodeId2.first] = d;
			}
		}
	}

	for (const auto& n : g->nodes)
	{
		int outdeg = g->netWorkSet[n].size();
		int indeg = g->netWorkSet[n].size();
		g->outMaxDegree = max(g->outMaxDegree, outdeg);
		g->inMaxDegree = max(g->inMaxDegree, indeg);
		g->maxDegree = max(g->maxDegree, outdeg + indeg);
	}

	cout << "finish read network" << endl;

	for (const auto& comm1 : g->commOuts)
	{
		for (const auto& comm2 : comm1.second)
		{
			vector<degmodel> temp;
			for (const auto& d : comm2.second)
			{
				temp.push_back(d.second);
			}

			sort(temp.begin(), temp.end(), mydegcomp);

			g->commMaxNumTag[comm1.first][comm2.first] = temp[temp.size() - 1].degree;

			for (const auto& t : temp)
			{
				g->commOutBoundary[comm1.first][comm2.first][g->nodeLabels[t.node_id]].push_back(t.node_id);
			}
		}
	}
	//commInBoundary.clear();
	for (const auto& comm1 : g->commIns)
	{
		for (const auto& comm2 : comm1.second)
		{
			vector<degmodel> temp;
			for (const auto& d : comm2.second)
			{
				temp.push_back(d.second);
			}

			sort(temp.begin(), temp.end(), mydegcomp);

			for (const auto& t : temp)
			{
				g->commInBoundary[comm1.first][comm2.first][g->nodeLabels[t.node_id]].push_back(t.node_id);
			}
		}
	}
	for (int comm1 = 1; comm1 < g->commOutBoundary.size(); ++comm1)
	{
		for (int comm2 = 1; comm2 < g->commOutBoundary[comm1].size(); ++comm2)
		{
			for (int label = 0; label < g->labelnum; ++label)
			{
				int last = 0;
				for (int i = 0; i < g->commOutBoundary[comm1][comm2][label].size(); i++)
				{
					int index = g->commOutBoundary[comm1][comm2][label][i];
					if (g->commOuts[comm1][comm2][index].degree != last)
					{
						last = g->commOuts[comm1][comm2][index].degree;
						DegreePos dp;
						dp.degree = last;
						dp.pos = i;
						g->degreePosOut[comm1][comm2][label].push_back(dp);
					}
				}
			}
		}
	}
	for (int comm1 = 1; comm1 < g->commInBoundary.size(); ++comm1)
	{
		for (int comm2 = 1; comm2 < g->commInBoundary[comm1].size(); ++comm2)
		{
			for (int label = 0; label < g->labelnum; ++label)
			{
				int last = 0;
				for (int i = 0; i < g->commInBoundary[comm1][comm2][label].size(); i++)
				{
					int index = g->commInBoundary[comm1][comm2][label][i];
					if (g->commIns[comm1][comm2][index].degree != last)
					{
						last = g->commIns[comm1][comm2][index].degree;
						DegreePos dp;
						dp.degree = last;
						dp.pos = i;
						g->degreePosIn[comm1][comm2][label].push_back(dp);
					}
				}
			}
		}
	}

	g->commOuts.clear();
	g->commIns.clear();
	//return;
	for (const auto& n : g->nodes)
	{
		// int comm_n = g->nodeInfo[n][0];
		int comm_n = *g->nodeCommunitySet[n].begin();
		for (const auto& neigh1 : g->netWorkSet[n])
		{
			// int comm_id = g->nodeInfo[neigh1.first][0];
			int comm_id = *g->nodeCommunitySet[neigh1.first].begin();
			for (const auto& neigh2 : g->netWorkSet[neigh1.first])
			{
				// int comm_id2 = g->nodeInfo[neigh2.first][0];
				int comm_id2 = *g->nodeCommunitySet[neigh2.first].begin();
				if (g->netWorkSet[n].find(neigh2.first) != g->netWorkSet[n].end())
				{
					g->triangleLimitation[comm_n][comm_id][comm_id2] = true;
				}
			}
		}
	}
}

void Match::constructCommunityGraph() {
	vector<int> nodes;
	//unordered_map<int, unordered_map<string, string>>* nodeAttributes = new unordered_map<int, unordered_map<string, string>>();
	//unordered_map<int, unordered_map<int, unordered_map<string, string>>>* edgeAttributes = new unordered_map<int, unordered_map<int, unordered_map<string, string>>>();

	unordered_map<int, unordered_map<string, unordered_set<string>>> commna;
	unordered_map<int, unordered_map<int, unordered_map<string, unordered_set<string>>>> commea;
	vector<int>* nodeLabels = new vector<int>();

	commoe = vector<unordered_map<int, vector<int>>>(data->communityNum + 1);
	commie = vector<unordered_map<int, vector<int>>>(data->communityNum + 1);

	for (int c = 1; c <= data->communityNum; ++c)
	{
		commIds.push_back(c);
	}
	communityGraphsVec = vector<MemoryGraph*>(commIds.size() + 1, NULL);

	data->maxCommSize = 0;
	for (int i = 0; i < commIds.size(); i++)
	{
		//unordered_map<int, unordered_set<int>> interouts, interins;

		if (data->communityNodes[commIds[i]].size() > 1)
		{			
			commoe[commIds[i]][commIds[i]].push_back(0);
		}

		data->maxCommSize = max(data->maxCommSize, (int)data->communityNodes[commIds[i]].size());

		vector<int> cnodes(1, -1);
		unordered_set<int> cnodeset;
		unordered_map<int, int> idToNew;
		int index = 0;
		vector<int> newnodes;
		for (const auto& n : data->communityNodes[commIds[i]])
		{
			cnodes.push_back(n);
		}
		sort(cnodes.begin(), cnodes.end());
		for (const auto& n : cnodes)
		{
			idToNew[n] = index++;
		}
		vector<unordered_map<int, vector<int>>>* edges = new vector<unordered_map<int, vector<int>>>(index);
		vector<int> cnodeLabels(index, 0);
		index = 1;
		for (const auto& n : data->communityNodes[commIds[i]])
		{
			newnodes.push_back(index++);
			cnodeLabels[idToNew[n]] = data->nodeLabels[n];
			//cnodes.push_back(n);
			//commna[c.first]["TYPE"].insert(to_string(storage.GetNodeType(to_string(n).c_str())));

			for (const auto& neigh : data->netWorkSet[n])
			{
				// if (data->nodeInfo[neigh.first][0] == commIds[i])
				if (*data->nodeCommunitySet[neigh.first].begin() == commIds[i])
				{
					int newNeigh = idToNew[neigh.first];
					int newN = idToNew[n];
					(*edges)[newNeigh][newN].push_back(0);
					(*edges)[newN][newNeigh].push_back(0);
				}

				//int c1 = data->nodeInfo[n][0];
				//int c2 = data->nodeInfo[neigh.first][0];

				int c1 = *data->nodeCommunitySet[n].begin();
				int c2 = *data->nodeCommunitySet[neigh.first].begin();

				commoe[c1][c2].push_back(0);
				commie[c2][c1].push_back(1);
			}
		}

		//sort(cnodes.begin(), cnodes.end());
		MemoryGraph* t = new MemoryGraph(newnodes, NULL, NULL, edges, edges, data->labelnum, &cnodeLabels);
		//t->nodeset = new unordered_set<int>(newnodes.begin(), newnodes.end());
		t->idMapping = cnodes;
		//t->getedgemap();

		communityGraphs[commIds[i]] = t;
		communityGraphsVec[commIds[i]] = t;
	}
}

void Match::loadPattern(string filename)
{
	vector<int> nodes;
	unordered_map<int, unordered_map<string, string>>* nodeAttributes = new unordered_map<int, unordered_map<string, string>>();
	unordered_map<int, unordered_map<int, unordered_map<string, string>>>* edgeAttributes = new unordered_map<int, unordered_map<int, unordered_map<string, string>>>();
	vector<unordered_map<int, vector<int>>>* outedges = new vector<unordered_map<int, vector<int>>>();
	vector<unordered_map<int, vector<int>>>* inedges = new vector<unordered_map<int, vector<int>>>();

	unordered_map<int, unordered_map<string, unordered_set<string>>> commna;
	unordered_map<int, unordered_map<int, unordered_map<string, unordered_set<string>>>> commea;
	vector<int>* nodeLabels = new vector<int>();

	loadPatternGraph(filename, nodes, *nodeAttributes, *edgeAttributes, *outedges, *inedges, nodeLabels);

	pattern = new MemoryGraph(nodes, nodeAttributes, edgeAttributes, outedges, inedges, data->labelnum, nodeLabels);
}

void Match::initCompleteMatchNodes()
{
	unordered_map<int, vector<int>> initvec;
	for (const auto& n : pattern->nodes)
	{
		initvec[n].push_back(n);
		completeMatchPatternNodes[initvec[n]].insert(initvec[n]);
	}

	for (int i = 0; i < pattern->nodes.size(); i++) {
		int pid = pattern->nodes[i];

		for (int j = i + 1; j < pattern->nodes.size(); j++) {
			int pid2 = pattern->nodes[j];
			if (completeMatchPatternNodes[initvec[pid]] == completeMatchPatternNodes[initvec[pid2]])
				continue;

			if (matchType == 0)
			{
				if ((*pattern->outedges)[pid].size() != (*pattern->outedges)[pid2].size()
					|| (*pattern->inedges)[pid].size() != (*pattern->inedges)[pid2].size()
					|| pattern->nodeLabels[pid] != pattern->nodeLabels[pid2])				{
					continue;
				}
			}
			else if (matchType == 1)
			{
				if ((*pattern->outedges)[pid].size() != (*pattern->outedges)[pid2].size()
					|| pattern->nodeLabels[pid] != pattern->nodeLabels[pid2])
				{
					continue;
				}
			}

			bool ok = true;

			for (const auto& n : (*pattern->outedges)[pid])
			{
				if (n.first != pid2 && (*pattern->outedges)[pid2].find(n.first) == (*pattern->outedges)[pid2].end())
				{
					ok = false;
					break;
				}
			}

			if (!ok)
			{
				continue;
			}

			if (pattern->nodeAttributes[pid].size() != pattern->nodeAttributes[pid2].size()) {
				continue;
			}

			for (const auto& attrpair : pattern->nodeAttributes[pid]) {
				if (pattern->nodeAttributes[pid2].find(attrpair.first) != pattern->nodeAttributes[pid2].end()
					|| attrpair.second != pattern->nodeAttributes[pid2][attrpair.first]) {
					ok = false;
					break;
				}
			}

			if (!ok) {
				continue;
			}

			if (matchType == 0)
			{
				for (const auto& n : (*pattern->inedges)[pid])
				{
					if (n.first != pid2 && (*pattern->inedges)[pid2].find(n.first) == (*pattern->inedges)[pid2].end())
					{
						ok = false;
						break;
					}
				}

				if (!ok)
				{
					continue;
				}
			}

			completeMatchPatternNodes[initvec[pid]].insert(initvec[pid2]);
			//completeMatchPatternNodes[initvec[pid2]].insert(initvec[pid]);
			//delete completeMatchPatternNodes[initvec[pid2]];
			completeMatchPatternNodes[initvec[pid2]].insert(initvec[pid]);
			equals[pid].insert(pid2);
			equals[pid2].insert(pid);
		}
	}

	int classNumber = 0;
	for (const auto& n : pattern->nodes) {
		if (patternEqualClass.find(n) != patternEqualClass.end())
		{
			continue;
		}
		classNumber++;
		int node_id = n;
		for (const auto& c : completeMatchPatternNodes[initvec[node_id]])
		{
			for (const auto& cn : c)
			{
				patternEqualClass[cn] = classNumber;
			}
		}
	}

	string ans = "";
	unordered_map<int, int> mapper;
	unordered_map<int, unordered_map<int, bool>> symm;
	for (const auto& n : pattern->nodes)
	{
		for (const auto& m : pattern->nodes)
		{
			if (completeMatchPatternNodes[initvec[n]].find(initvec[m]) == completeMatchPatternNodes[initvec[n]].end()
				&& pattern->nodeLabels[n] == pattern->nodeLabels[m])
			{
				int count = 0;
				vector<vector<int>*> boundary(pattern->nodeNum + 1, NULL);
				boundary[n] = &initvec[m];
				boundary[m] = &initvec[n];
				
				//自同构接口 interface #1
				VF3StateSelf s(pattern, pattern, data->labelnum);
				s.nodeArea = &boundary;
				if (s.match())
				{
					symmetryNodes[initvec[n]].insert(initvec[m]);
				}
			}
		}
	}

}

void Match::handleExchange(unordered_map<string, vector<vector<int>>>& isomorphicList
	, map<vector<int>, string>& isomap)
{
	vector<int> current;
	for (const auto& n : pattern->nodes)
	{
		current.push_back(n);
	}
	unordered_set<int> record;
	vector<int> temp;
	getAllMatchNodes(current, 0, temp, record, false);

	for (const auto& v : completeMatchPatternNodes[current])
	{
		//vector v
		bool canmatch = true;
		for (int i = 0; i < pattern->nodes.size(); ++i)
		{
			int n1 = pattern->nodes[i];
			for (const auto& n2 : (*pattern->outedges)[n1])
			{
				if ((*pattern->outedges)[v[n1 - 1]].find(v[n2.first - 1]) == (*pattern->outedges)[v[n1 - 1]].end())
				{
					canmatch = false;
					break;
				}
			}
			if (!canmatch)
				break;
		}
		if (canmatch)
		{
			displace.insert(v);
		}
	}

	schemes = vector<vector<int>>(displace.size(), vector<int>(pattern->nodes.size() + 1));
	int index = 0;
	for (const auto& d : displace)
	{
		for (int i = 0; i < d.size(); ++i)
		{
			schemes[index][d[i]] = i + 1;
		}
		index++;
	}

	current.clear();
	completeMatchPatternNodes.clear();
	retrivalPatterns(current, 0, false);

	/*map<vector<int>, set<vector<int>>>::iterator mit = completeMatchPatternNodes.begin();
	while (mit != completeMatchPatternNodes.end())
	{
		set<vector<int>>::iterator sit = mit->second.begin();
		while (sit != mit->second.end())
		{
			vector<int> nv(*sit);
			//sort(nv.begin(), nv.end());
			if (completeMatchRecord[mit->first].find(nv) != completeMatchRecord[mit->first].end())
			{
				//(completeMatchPatternNodes[mit->first]).erase(sit++);
				//continue;
			}
			completeMatchRecord[mit->first].insert(nv);
			sort(nv.begin(), nv.end());
			if (isomap[nv] != isomap[mit->first])
			//{
		//		(completeMatchPatternNodes[mit->first]).erase(sit++);
			//}
			//else
			//{
		//		sit++;
		//	}
		//}
		//handled.insert(mit->second);
	//	mit++;
//	}*/

	map<vector<int>, set<vector<int>>>::iterator mit = completeMatchPatternNodes.begin();
	while (mit != completeMatchPatternNodes.end())
	{
		set<vector<int>>::iterator sit = mit->second.begin();
		set<int> mitset = set<int>(mit->first.begin(), mit->first.end());
		while (sit != mit->second.end())
		{
			set<int> nv(sit->begin(), sit->end());
			completeSet[mitset].insert(nv);
			sit++;
		}
		//handled.insert(mit->second);
		mit++;
	}
}


void Match::retrivalPatterns(vector<int>& current, int pos, bool added)
{
	if (added)
	{
		if (current.size() >= 1)
		{
			vector<int> t(current.size());
			for (int i = 0; i < schemes.size(); ++i)
			{
				for (int j = 0; j < current.size(); ++j)
				{
					t[j] = schemes[i][current[j]];
				}
				sort(t.begin(), t.end());
				completeMatchPatternNodes[current].insert(t);
			}
		}
	}

	if (pos >= pattern->nodes.size())
	{
		return;
	}

	retrivalPatterns(current, pos + 1, false);

	current.push_back(pattern->nodes[pos]);
	retrivalPatterns(current, pos + 1, true);
	current.pop_back();
}

void Match::getAllMatchNodes(vector<int>& currents, int pos, vector<int>& t, unordered_set<int>& record, bool hasSymm)
{
	if (pos >= currents.size())
	{
		if (completeMatchPatternNodes.find(currents) != completeMatchPatternNodes.end()
			&& completeMatchPatternNodes[currents].find(t) != completeMatchPatternNodes[currents].end())
		{
			return;
		}
		if (hasSymm)
		{
			unordered_map<int, int> mapper;
			for (int i = 0; i < currents.size(); i++)
			{
				mapper[currents[i]] = t[i];
			}

			unordered_set<int> nodes, currentNodes, tNodes;
			bool isAll = false;
			bool isSameNeighs = true;

			for (const auto& c : currents)
			{
				//nodes.insert(c);
				currentNodes.insert(c);
			}
			for (const auto& c : t)
			{
				//nodes.insert(c);
				tNodes.insert(c);
			}

			for (int i = 0; i < currents.size(); i++)
			{
				unordered_set<int> currentOutNeighs, currentOutNeighs2, currentInNeighs, currentInNeighs2, tOutNeighs, tOutNeighs2, tInNeighs, tInNeighs2;

				//currentOutNeighs.insert(mapper[currents[i]]);
				for (const auto& out : (*pattern->outedges)[currents[i]])
				{
					if (out.first == currents[i] || out.first == t[i])
					{
						continue;
					}
					if (mapper.find(out.first) != mapper.end())
					{
						currentOutNeighs.insert(mapper[out.first]);
					}
					else
					{
						currentOutNeighs.insert(out.first);
					}
					currentOutNeighs2.insert(out.first);
				}

				/*if (mapper.find(t[i]) != mapper.end())
				{
				tOutNeighs.insert(mapper[t[i]]);
				}
				else*/
				{
					//tOutNeighs.insert(t[i]);
				}
				for (const auto& out : (*pattern->outedges)[t[i]])
				{
					if (out.first == currents[i] || out.first == t[i])
					{
						continue;
					}
					if (mapper.find(out.first) != mapper.end())
					{
						tOutNeighs2.insert(mapper[out.first]);
					}
					else
					{
						tOutNeighs2.insert(out.first);
					}
					tOutNeighs.insert(out.first);
				}
				if (currentOutNeighs != tOutNeighs && currentOutNeighs2 != tOutNeighs2 && currentOutNeighs2 != tOutNeighs)
				{
					isSameNeighs = false;
					break;
				}

				//currentInNeighs.insert(mapper[currents[i]]);
				for (const auto& in : (*pattern->inedges)[currents[i]])
				{
					if (in.first == currents[i] || in.first == t[i])
					{
						continue;
					}
					if (mapper.find(in.first) != mapper.end())
					{
						currentInNeighs.insert(mapper[in.first]);
					}
					else
					{
						currentInNeighs.insert(in.first);
					}
					currentInNeighs2.insert(in.first);
				}

				/*if (mapper.find(t[i]) != mapper.end())
				{
				tInNeighs.insert(mapper[t[i]]);
				}
				else*/
				{
					//tInNeighs.insert(t[i]);
				}
				for (const auto& in : (*pattern->inedges)[t[i]])
				{
					if (in.first == currents[i] || in.first == t[i])
					{
						continue;
					}
					if (mapper.find(in.first) != mapper.end())
					{
						tInNeighs2.insert(mapper[in.first]);
					}
					else
					{
						tInNeighs2.insert(in.first);
					}
					tInNeighs.insert(in.first);
				}

				if (currentInNeighs != tInNeighs && currentInNeighs2 != tInNeighs2 && currentInNeighs2 != tInNeighs)
				{
					isSameNeighs = false;
					break;
				}
			}

			if (isSameNeighs)
			{
				if (currentNodes == tNodes)
				{
					//if (is_sorted(t.begin(), t.end()))
					{
						//if (completeMatchPatternNodes.find(currents) == completeMatchPatternNodes.end())
						//{
						//completeMatchPatternNodes[currents] = new set<vector<int>>();
						//}
						completeMatchPatternNodes[currents].insert(t);
						completeMatchPatternNodes[t].insert(currents);// = completeMatchPatternNodes[currents];
					}
				}
				else
				{
					//if (completeMatchPatternNodes.find(currents) == completeMatchPatternNodes.end())
					//{
					//	completeMatchPatternNodes[currents] = new set<vector<int>>();
					//}
					completeMatchPatternNodes[currents].insert(t);
					if (is_sorted(t.begin(), t.end()))
					{
						completeMatchPatternNodes[t].insert(currents);// = completeMatchPatternNodes[currents];
					}
					//completeMatchPatternNodes[currents]->insert(t);
				}
			}
			/*if (nodes.size() == patternGraph->nodes.size())
			{
			isAll = true;
			}
			if (isAll || isSameNeighs)
			{
			if (currentNodes == tNodes)
			{
			if (is_sorted(t.begin(), t.end()))
			{
			completeMatchPatternNodes[currents].insert(t);
			}
			}
			else
			{
			completeMatchPatternNodes[currents].insert(t);
			}
			}*/
		}
		else
		{
			unordered_map<int, vector<int>> equalClassVector;
			for (int i = 0; i < t.size(); i++)
			{
				equalClassVector[patternEqualClass[t[i]]].push_back(t[i]);
			}
			/*for (const auto& e : equalClassVector)
			{
				if (!is_sorted(e.second.begin(), e.second.end()))
				{
					return;
				}
			}*/

			//if (completeMatchPatternNodes.find(currents) == completeMatchPatternNodes.end())
			//{
			//	completeMatchPatternNodes[currents] = new set<vector<int>>();
			//}
			completeMatchPatternNodes[currents].insert(t);
			if (is_sorted(t.begin(), t.end()))
			{
				completeMatchPatternNodes[t].insert(currents);// = completeMatchPatternNodes[currents];
			}
			//completeMatchPatternNodes[currents]->insert(t);
		}

		return;
	}

	vector<int> temp(1, currents[pos]);

	for (const auto& ns : completeMatchPatternNodes[temp])
	{
		for (const auto& n : ns)
		{
			if (record.find(n) != record.end())
			{
				continue;
			}
			t.push_back(n);
			record.insert(n);
			getAllMatchNodes(currents, pos + 1, t, record, hasSymm);
			t.pop_back();
			record.erase(n);
		}
	}

	for (const auto& ns : symmetryNodes[temp])
	{
		for (const auto& n : ns)
		{
			if (record.find(n) != record.end())
			{
				continue;
			}
			t.push_back(n);
			record.insert(n);
			getAllMatchNodes(currents, pos + 1, t, record, true);
			t.pop_back();
			record.erase(n);
		}
	}
}

void Match::initOrderTree()
{
	for (auto& c : completeMatchPatternNodes)
	{
		if (c.second.begin()->size() > 1)
		{
			orderTree.insert(set<int>(c.second.begin()->begin(), c.second.begin()->end()));
		}
		else
		{
			orderTree1D.insert((*c.second.begin())[0]);
		}

		int minlocal = *c.first.begin();
		set<vector<int>>::iterator record = c.second.end();
		set<vector<int>>::iterator cit = c.second.begin();
		while(cit != c.second.end())
		{
			if ((*cit)[0] == minlocal)
			{
				if (record == c.second.end())
					record = cit;
				else
				{
					for (int i = 0; i < (*cit).size(); ++i)
					{
						if ((*record)[i] >(*cit)[i])
						{
							record = cit;
						}
					}
				}
			}

			cit++;
		}

		localMinTree.insert(set<int>(record->begin(), record->end()));
	}
}

int Match::GoMatch_Turbo()
{
	clock_t start, end;
	start = clock();

	TurboMatch tm;
	tm.q = pattern;
	tm.g = new MemoryGraph(data->nodes, NULL, NULL, &(data->netWorkSet), &(data->netWorkSet), data->labelnum, &data->nodeLabels);
	tm.data = this->data;
	tm.gm = this;
	tm.storeType = -1;
	tm.communityGraphs = &communityGraphsVec;
	tm.init();
	
	bool candups = false;
	ansnum = tm.TurboISO(tm.q, tm.g, candups, 0);

	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

	//ans.clear();

	//cout << "super match over" << endl;

	/*int sumc = 0;
	int index = 0;
	cout << "start" << endl;
	for (const auto& n : tans)
	{
	cout << index++ << " " << n.size() << endl;
	sumc += n.size();
	for (const auto& m : n)
	{
	ans.push_back(m);
	}
	}
	//cout << "blocktime: " << storage.blocktime << endl;*/
	cout << "sumc: " << ansnum << endl;
	//cout << usefulCS << " " << uselessCS << " " << uselessCut2 << " " << uselessUntrivial << endl;

	logger << ansnum << " " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	logger.close();
	return ansnum;
}

int Match::GoMatch_Turbo_comm()
{
	clock_t start, end;
	start = clock();

	completeMatchPatternNodes.clear();
	initCompleteMatchNodes();

	unordered_map<string, vector<vector<int>>> isomorphicList;
	map<vector<int>, string> isomap;
	handleExchange(isomorphicList, isomap);
	//handleMatchPattern(isomorphicList, isomap);
	//initOrderTree();
	
	//cout << "init over" << endl;
	vector<vector<vector<int>>> tans(1, vector<vector<int>>());

	int count[16] = { 0 };
	int pc = 0;

	vector<vector<int>> equalq(pattern->nodeNum + 1, vector<int>(pattern->nodeNum + 1, 0));
	NECTree q_prime;
	TurboMatch tempm;
	vector<vector<int>> NECV;
	vector<int> qnodes = pattern->nodes;
	tempm.FindNEC(&NECV, &qnodes, pattern);
	//#pragma omp parallel for schedule(dynamic) if(ISPARALLEL)
	for (int i = 0; i < NECV.size(); i++)
	{
		//unordered_set<int>* s = new unordered_set<int>(NECV[i].begin(), NECV[i].end());
		for (const auto& n : NECV[i])
		{
			for(const auto& n2 : NECV[i])
				equalq[n][n2] = 1;
		}
	}

	int s = 0;
	//for (int i = 0; i < 16; ++i)
	//	s += count[i];
	//cout << "sum: " << s <<  " " << tans[0].size() << " " << tans[1].size() << " " << tans[2].size() << " " << tans[3].size() << endl;
	//cout << s << endl;
	ansnum = 0;
	//return 0;
	vector<map<int, vector<int>>> supermatch;

	int c = 0;
	MemoryGraph commGraph(commIds, NULL, NULL, &commoe, &commie, data->labelnum, &data->nodeLabels);
	//可重复的子图匹配 interface #3
	TurboMatch tm;
	tm.q = pattern;
	tm.g = &commGraph;
	tm.data = this->data;
	tm.gm = this;
	tm.storeType = 2;
	tm.superans = &supermatch;
	tm.tans = &tans;
	tm.isomap = &isomap;
	tm.communityGraphs = &communityGraphsVec;
	tm.originalgraph = data; // new TempMatchGraph(data->nodes, NULL, NULL, &(data->netWorkSet), &(data->netWorkSet), data->labelnum, &data->nodeLabels);
	tm.equalq = &equalq;
	bool candups = true;
	tm.init(true);
	vector<NECTree> qs(pattern->nodeNum + 1);
	for (int i = 1; i < qs.size(); ++i)
	{
		NECTree temp;
		tm.RewriteToNECTree(pattern, i, &temp);
		qs[i] = temp;
	}
	tm.q_primes = &qs;
	tm.TurboISOSuper(tm.q, tm.g, candups);

	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

	//ans.clear();

	//cout << "super match over" << endl;

	/*int sumc = 0;
	int index = 0;
	cout << "start" << endl;
	for (const auto& n : tans)
	{
	cout << index++ << " " << n.size() << endl;
	sumc += n.size();
	for (const auto& m : n)
	{
	ans.push_back(m);
	}
	}
	//cout << "blocktime: " << storage.blocktime << endl;*/
	cout << "sumc: " << s + ansnum << endl;
	cout << usefulCS << " " << uselessCS << " " << uselessCut2 << " " << uselessUntrivial << " " << uselessDouble << " " << samecounter << endl;

	logger << ansnum << " " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	logger.close();
	return ansnum + s;
}

int Match::GoMatch_DAF_comm()
{
	MemoryGraph* originalgraph = data;//new MemoryGraph(data->nodes, NULL, NULL, &(data->netWorkSet), &(data->netWorkSet), data->labelnum, &data->nodeLabels);
	//originalgraph->getedgemap();
	MemoryGraph commGraph(commIds, NULL, NULL, &commoe, &commie, data->labelnum, &data->nodeLabels);
	//commGraph.getedgemap();

	//pattern->getedgemap();
	completeMatchPatternNodes.clear();
	initCompleteMatchNodes();

	unordered_map<string, vector<vector<int>>> isomorphicList;
	map<vector<int>, string> isomap;
	handleExchange(isomorphicList, isomap);
	//handleMatchPattern(isomorphicList, isomap);
	//initOrderTree();
	
	//cout << "init over" << endl;
	vector<vector<vector<int>>> tans(1, vector<vector<int>>());

	int count[16] = { 0 };
	int pc = 0;

	vector<vector<int>> equalq(pattern->nodeNum + 1, vector<int>(pattern->nodeNum + 1, 0));
	NECTree q_prime;
	TurboMatch tempm;
	vector<vector<int>> NECV;
	vector<int> qnodes = pattern->nodes;
	tempm.FindNECSelf(&NECV, &qnodes, pattern);
	//#pragma omp parallel for schedule(dynamic) if(ISPARALLEL)
	for (int i = 0; i < NECV.size(); i++)
	{
		//unordered_set<int>* s = new unordered_set<int>(NECV[i].begin(), NECV[i].end());
		for (const auto& n : NECV[i])
		{
			for(const auto& n2 : NECV[i]) {
				equalq[n][n2] = 1;
			}
		}
	}
	cout << pattern->nodeNum + 1 << endl;
	int s = 0;
	//for (int i = 0; i < 16; ++i)
	//	s += count[i];
	//cout << "sum: " << s <<  " " << tans[0].size() << " " << tans[1].size() << " " << tans[2].size() << " " << tans[3].size() << endl;
	cout << s << endl;
	ansnum = 0;
	//return 0;
	vector<map<int, vector<int>>> supermatch;
	hittimes = 0;
	int c = 0;

	DAF daf(&commGraph, pattern, data);
	daf.gm = this;
	daf.equalq = &equalq;
	daf.communityGraphs = &communityGraphsVec;
	daf.originalgraph = originalgraph;//new TempGraph(data->node_ids, NULL, NULL, &(data->netWorkSet), &(data->netWorkSet), data->labelnum, &data->nodeLabels);
	//daf.originalgraph->getedgemap();
	daf.init();

	cout << "Start" << endl;

	clock_t start, end;
	start = clock();

	daf.startMatch_comm();

	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

	cout << "sumc: " << ansnum << endl;
	//cout << usefulCS << " " << uselessCS << " " << uselessCut2 << " " << uselessUntrivial << endl;

	logger << ansnum << " " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	logger.close();
	cout << daf.itercount << " " << "C" << " " << hittimes << endl;
	return ansnum;
}

int Match::GoMatch_DAF()
{
	//MemoryGraph* data_graph = new MemoryGraph(data->nodes, NULL, NULL, &(data->netWorkSet), &(data->netWorkSet), data->labelnum, &data->nodeLabels);
	//data_graph->getedgemap();

	DAF daf(data, pattern, data);
	daf.gm = this;
	daf.candmap = new int*[pattern->nodeNum + 1];
	for (int i = 1; i < pattern->nodeNum + 1; ++i) {
		daf.candmap[i] = new int[data->nodeNum + 1];
		fill(daf.candmap[i], daf.candmap[i] + data->nodeNum + 1, -1);
	}
	daf.pivot_pos = new int[pattern->nodeNum + 1];
	fill(daf.pivot_pos, daf.pivot_pos + pattern->nodeNum + 1, 0);

	clock_t start, end;
	start = clock();

	daf.startMatch();

	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

	cout << "sumc: " << ansnum << endl;
	//cout << usefulCS << " " << uselessCS << " " << uselessCut2 << " " << uselessUntrivial << endl;

	logger << ansnum << " " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	logger.close();
	return ansnum;
}

bool Match::getAllInPatternCompleteMatch(map<int, vector<int>>& supermatch, map<int, int>& supermatchmap, string& mystr, map<int, vector<int>>::iterator& sit, vector<map<int, int>>& allmaps, map<int, int>& currentMap, unordered_set<int>& usednodes)
{
	if (sit == supermatch.end())
	{
		bool issmallest = true;
		string thisstr = "";
		map<int, int> newmatch;
		for (const auto& a : currentMap)
		{
			newmatch[a.second] = a.first;
		}
		for (const auto& a : newmatch)
		{
			string str = to_string(supermatchmap[a.second]);
			thisstr += ('A' + str.size());
			thisstr += str + " ";
		}
		if (thisstr < mystr)
		{
			return false;
		}
		else
		{
			allmaps.push_back(currentMap);
			//allmaps.insert(currentMap);
			return true;
		}
	}

	int comm_id = sit->first;
	map<int, vector<int>>::iterator nextit = ++sit;
	sit--;

	for (const auto& v : completeMatchPatternNodes[sit->second])
	{
		bool check = true;
		for (int i = 0; i < v.size(); i++)
		{
			if (usednodes.find(v[i]) != usednodes.end())
			{
				check = false;
				break;
			}

			currentMap[sit->second[i]] = v[i];
		}
		if (!check)
		{
			continue;
		}

		usednodes.insert(v.begin(), v.end());

		if (!getAllInPatternCompleteMatch(supermatch, supermatchmap, mystr, nextit, allmaps, currentMap, usednodes))
		{
			return false;
		}

		for (int i = 0; i < v.size(); i++)
		{
			currentMap[sit->second[i]] = -1;
			usednodes.erase(v[i]);
		}
	}

	return true;
}

bool Match::getCompleteMatch(int* supermatchmap, vector<int>& allmaps, unordered_set<string>& record)
{
	for(int i = 0; i < schemes.size(); ++i)
	{
		bool smaller = false;
		string thisstr = "";
		for (int j = 1; j < schemes[i].size(); ++j)
		{
			int snode = schemes[i][j];
			if (!smaller)
			{
				if (supermatchmap[snode] < supermatchmap[j])
					return false;
				else if (supermatchmap[snode] > supermatchmap[j])
				{
					smaller = true;
				}
			}
			//string str = to_string(supermatchmap[schemes[i][j]]);
			thisstr += to_string(supermatchmap[snode]);
			thisstr += " ";
		}
		/*if (thisstr < mystr)
		{
			//cout << thisstr << " " << mystr << endl;
			//system("pause");
			return false;
		}
		else
		{
			if (record.find(thisstr) == record.end())
			{
				allmaps.push_back(i);
				record.insert(thisstr);
			}
			//allmaps.insert(currentMap);
		}*/
		if (record.find(thisstr) == record.end())
		{
			allmaps.push_back(i);
			record.insert(thisstr);
		}
	}

	return true;
}

bool Match::match_sub(VF2StateSub* s, int* pcount, string& ans, unordered_map<int, int>& mapper, int nextn1, bool iswrite)
{
	if (s->IsGoal())
	{
		++*pcount;
		int n = s->CoreLen();
		s->GetCoreSet(ans, mapper, iswrite);
		return true;
	}

	if (s->IsDead())
	{
		return false;
	}

	int n1 = -1, n2 = -1;
	while (s->NextPair(&n1, &n2, n1, n2))
	{
		if (s->IsFeasiblePair(n1, n2))
		{
			VF2StateSub* s1 = s->Clone();
			s1->AddPair(n1, n2);
			if (match_sub(s1, pcount, ans, mapper, nextn1 + 1, iswrite))
			{
				s1->BackTrack();
				delete s1;
				return true;
			}
			else
			{
				s1->BackTrack();
				delete s1;
			}
		}
	}

	return false;
}

bool Match::vf3_match(VF3State &s, int *pn)
{
	if (s.IsGoal())
	{
		++*pn;
		//int n = s.CoreLen();
		//s.GetCoreSet(c2);
		return false;
	}

	if (s.IsDead())
		return false;

	int n1 = -1, n2 = -1;
	
	while (s.NextPair(&n1, &n2, n1, n2))
	{
		if (s.IsFeasiblePair(n1, n2))
		{
			VF3State s1(s);
			s1.AddPair(n1, n2);
			if (vf3_match(s1, pn))
			{
				return true;
			}
		}
	}
	return false;
}

int Match::GoMatch_vf3()
{
	clock_t start, end;
	start = clock();

	VF3NodeSorter sorter(data);
	vector<int> sorted = sorter.SortNodes(pattern);

	int pnum = pattern->nodes.size();
	int gnum = data->nodes.size();
	
	VF3State s0(pattern, data, this, data->labelnum, sorted.data());
	int n = 0;

	vf3_match(s0, &n);

	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	cout << n << endl;

	logger << "VF3: " << ansnum << " " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	logger.close();

	return 0;
}

int Match::GoMatch_vf3_comm()
{
	clock_t start, end;
	start = clock();

	completeMatchPatternNodes.clear();
	initCompleteMatchNodes();

	unordered_map<string, vector<vector<int>>> isomorphicList;
	map<vector<int>, string> isomap;
	handleExchange(isomorphicList, isomap);
	//handleMatchPattern(isomorphicList, isomap);
	//initOrderTree();

	//cout << "init over" << endl;
	vector<vector<vector<int>>> tans(1, vector<vector<int>>());

	int count[16] = { 0 };
	int pc = 0;

	vector<vector<int>> equalq(pattern->nodeNum + 1, vector<int>(pattern->nodeNum + 1, 0));
	NECTree q_prime;
	TurboMatch tempm;
	vector<vector<int>> NECV;
	vector<int> qnodes = pattern->nodes;
	tempm.FindNEC(&NECV, &qnodes, pattern);
	//#pragma omp parallel for schedule(dynamic) if(ISPARALLEL)
	for (int i = 0; i < NECV.size(); i++)
	{
		//unordered_set<int>* s = new unordered_set<int>(NECV[i].begin(), NECV[i].end());
		for (const auto& n : NECV[i])
		{
			for(const auto& n2 : NECV[i])
				equalq[n][n2] = 1;
		}
	}

	int s = 0;
	for (int i = 0; i < 16; ++i)
		s += count[i];
	//cout << "sum: " << s <<  " " << tans[0].size() << " " << tans[1].size() << " " << tans[2].size() << " " << tans[3].size() << endl;
	cout << s << endl;
	ansnum = 0;
	//return 0;
	vector<map<int, vector<int>>> supermatch;

	int c = 0;
	MemoryGraph commGraph(commIds, NULL, NULL, &commoe, &commie, data->labelnum, &data->nodeLabels);
	//可重复的子图匹配 interface #3

	vector<vector<int>> commNodeLabels(commIds.size() + 1, vector<int>(data->labelnum + 1, 0));
	for (int c = 1; c < data->communityNodes.size(); ++c)
	{
		for (const auto& n : data->communityNodes[c])
		{
			commNodeLabels[c][data->nodeLabels[n]] = 1;
		}
	}
	
	this->new_core = new int[pattern->nodeNum + 1];

	VF3StateSuper state(pattern, &commGraph, this, data->labelnum);
	state.data = this->data;
	state.communityGraphs = &communityGraphsVec;
	state.originalgraph = data;// new TempMatchGraph(data->nodes, NULL, NULL, &(data->netWorkSet), &(data->netWorkSet), data->labelnum, &data->nodeLabels);
	state.equalq = &equalq;
	state.commNodeLabels = &commNodeLabels;
	state.recin = new VF3StateIn(pattern, NULL, this, data->labelnum);
	state.recbound = new VF3StateBound(pattern, state.originalgraph, this, data->labelnum);
	state.recbound->communityGraphs = state.communityGraphs;
	state.recbound->data = data;
	state.match();

	end = clock();
	cout << "Time: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

	cout << "sumc: " << s + ansnum << endl;
	cout << usefulCS << " " << uselessCS << " " << uselessCut2 << " " << uselessUntrivial << endl;

	logger << "VF3: " << ansnum << " " << (double)(end - start) / CLOCKS_PER_SEC << endl;
	logger.close();
	return ansnum + s;
}


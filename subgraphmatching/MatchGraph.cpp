#include "MatchGraph.h"

void MatchGraph::readCommunity(const string& pathFile)
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
	communityNodes = vector<vector<int>>(communityNum + 1, vector<int>());
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
		node_ids.push_back(nodeId);
		if (community == -1)
		{
			//graph.nodeCommunity[nodeId] = counter;
			//if (graph.nodeCommunitySet[nodeId].empty())
			{
				nodeInfo[nodeId][0] = counter;
				nodeInfo[nodeId][1] = label;
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
				nodeInfo[nodeId][1] = label;
				communityNodes[community].push_back(nodeId);
			}
		}
	}
	inFile.close();

	nodeLabels = vector<int>(node_ids.size() + 1);
	for (const auto& n : node_ids)
	{
		nodeLabels[n] = nodeInfo[n][1];
	}

	maxCommSize = 0;
	for (const auto& c : communityNodes) {
		if (c.size() >= maxCommSize)
			maxCommSize = c.size();
	}
}

void MatchGraph::readNetwork(const string& pathFile)
{
	//cout << "start alloc" << endl;
	cout << nodeNum << " " << communityNum << " " << labelnum << endl;
	netWorkSet = vector<unordered_set<int>>(nodeNum + 1);
	//inNetWorkSet = vector<unordered_set<int>>(nodeNum + 1);
	netWorkVec = vector<vector<int>>(nodeNum + 1);
	//inNetWorkVec = vector<vector<int>>(nodeNum + 1);
	commNetworkSet = vector<vector<vector<unordered_set<int>>>>(nodeNum + 1, vector<vector<unordered_set<int>>>(communityNum + 1, vector<unordered_set<int>>(labelnum)));
	commOutBoundary = vector<vector<vector<vector<int>>>>(communityNum + 1, vector<vector<vector<int>>>(communityNum + 1, vector<vector<int>>(labelnum)));
	commInBoundary = vector<vector<vector<vector<int>>>>(communityNum + 1, vector<vector<vector<int>>>(communityNum + 1, vector<vector<int>>(labelnum)));
	degreePosOut = vector<vector<vector<vector<DegreePos>>>>(communityNum + 1, vector<vector<vector<DegreePos>>>(communityNum + 1, vector<vector<DegreePos>>(labelnum)));
	degreePosIn = vector<vector<vector<vector<DegreePos>>>>(communityNum + 1, vector<vector<vector<DegreePos>>>(communityNum + 1, vector<vector<DegreePos>>(labelnum)));
	//twoHopLimitation = vector<vector<unordered_map<int, unordered_map<int, int>>>>(nodeNum + 1, vector<unordered_map<int, unordered_map<int, int>>>(communityNum + 1));

	//twoHopLimitation = vector<vector<unordered_map<int, unordered_map<int, int>>>>(nodeNum + 1, vector<unordered_map<int, unordered_map<int, int>>>(communityNum + 1));
	//twoHopLimitation = vector<vector<vector<unordered_map<int, int>*>>>(nodeNum + 1, vector<vector<unordered_map<int, int>*>>(communityNum + 1, vector<unordered_map<int, int>*>(communityNum + 1, NULL)));
	//hasTwoHopComms = vector<vector<vector<bool>>>(nodeNum + 1, vector<vector<bool>>(communityNum + 1, vector<bool>(communityNum + 1, false)));
	//hasTwoHopLabels = vector<vector<vector<vector<int>>>>(nodeNum + 1, vector<vector<vector<int>>>(communityNum + 1, vector<vector<int>>(communityNum + 1)));

	//len4Limitation = vector<vector<vector<vector<bool>>>>(communityNum + 1, vector<vector<vector<bool>>>(communityNum + 1, vector<vector<bool>>(communityNum + 1, vector<bool>(communityNum + 1, false))));
	//triangleLimitation = len4Limitation;

	triangleLimitation = vector<vector<vector<bool>>>(communityNum + 1, vector<vector<bool>>(communityNum + 1, vector<bool>(communityNum + 1, false)));
	
	commTotalNumTag = vector<vector<int>>(communityNum + 1, vector<int>(communityNum + 1, 0));
	commMaxNumTag = vector<vector<int>>(communityNum + 1, vector<int>(communityNum + 1, 0));
	/*commTotalNumTag = new int*[communityNum + 1];
	commMaxNumTag = new int*[communityNum + 1];
	for (int i = 0; i < communityNum + 1; ++i) {
		commTotalNumTag[i] = new int[communityNum + 1];
		commMaxNumTag[i] = new int[communityNum + 1];
		memset(commTotalNumTag[i], 0, (communityNum + 1) * sizeof(int));
		memset(commMaxNumTag[i], 0, (communityNum + 1) * sizeof(int));
	}*/

	cout << "finish alloc" << endl;
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
	set<int>tempset;
	unordered_map<int, degmodel> nodeouts, nodeins;

	while (inFile.getline(buffer, BUFFER_LENGTH))
	{
		if (buffer[0] == '#')continue;
		int nodeId1 = -1;
		int nodeId2 = -1;
		int type = 0;
		sscanf(buffer, "%d	%d", &nodeId1, &nodeId2);

		if (nodeId1 == nodeId2)
		{
			continue;
		}

		if (netWorkSet[nodeId1].find(nodeId2) != netWorkSet[nodeId1].end())
			continue;

		edgeNum += 2;

		netWorkSet[nodeId1].insert(nodeId2);
		//inNetWorkSet[nodeId2].insert(nodeId1);
		netWorkVec[nodeId1].push_back(nodeId2);
		//inNetWorkVec[nodeId2].push_back(nodeId1);
		int c2 = nodeInfo[nodeId2][0];
		commNetworkSet[nodeId1][c2][nodeLabels[nodeId2]].insert(nodeId2);
		int c1 = nodeInfo[nodeId1][0];
		commTotalNumTag[c1][c2]++;

		if (commOuts[c1][c2].find(nodeId1) != commOuts[c1][c2].end())
		{
			commOuts[c1][c2][nodeId1].degree++;
		}
		else
		{
			degmodel d;
			d.degree = 1;
			d.node_id = nodeId1;
			commOuts[c1][c2][nodeId1] = d;
		}

		if (commIns[c2][c1].find(nodeId2) != commIns[c2][c1].end())
		{
			commIns[c2][c1][nodeId2].degree++;
		}
		else
		{
			degmodel d;
			d.degree = 1;
			d.node_id = nodeId2;
			commIns[c2][c1][nodeId2] = d;
		}

		//if(netWorkSet[nodeId2].find(nodeId1) != netWorkSet[nodeId2].end())
		//continue;
		
		int t = nodeId1;
		nodeId1 = nodeId2;
		nodeId2 = t;

		netWorkSet[nodeId1].insert(nodeId2);
		//inNetWorkSet[nodeId2].insert(nodeId1);
		netWorkVec[nodeId1].push_back(nodeId2);
		//inNetWorkVec[nodeId2].push_back(nodeId1);
		c2 = nodeInfo[nodeId2][0];
		commNetworkSet[nodeId1][c2][nodeLabels[nodeId2]].insert(nodeId2);
		c1 = nodeInfo[nodeId1][0];

		if (commOuts[c1][c2].find(nodeId1) != commOuts[c1][c2].end())
		{
			commOuts[c1][c2][nodeId1].degree++;
		}
		else
		{
			degmodel d;
			d.degree = 1;
			d.node_id = nodeId1;
			commOuts[c1][c2][nodeId1] = d;
		}

		if (commIns[c2][c1].find(nodeId2) != commIns[c2][c1].end())
		{
			commIns[c2][c1][nodeId2].degree++;
		}
		else
		{
			degmodel d;
			d.degree = 1;
			d.node_id = nodeId2;
			commIns[c2][c1][nodeId2] = d;
		}
	}
	inFile.close();

	for (const auto& n : node_ids)
	{
		int outdeg = netWorkSet[n].size();
		int indeg = netWorkSet[n].size();
		outMaxDegree = max(outMaxDegree, outdeg);
		inMaxDegree = max(inMaxDegree, indeg);
		maxDegree = max(maxDegree, outdeg + indeg);
	}

	cout << "finish read network" << endl;

	for (const auto& comm1 : commOuts)
	{
		for (const auto& comm2 : comm1.second)
		{
			vector<degmodel> temp;
			for (const auto& d : comm2.second)
			{
				temp.push_back(d.second);
			}

			sort(temp.begin(), temp.end(), mydegcomp);

			commMaxNumTag[comm1.first][comm2.first] = temp[temp.size() - 1].degree;

			for (const auto& t : temp)
			{
				commOutBoundary[comm1.first][comm2.first][nodeLabels[t.node_id]].push_back(t.node_id);
			}
		}
	}
	//commInBoundary.clear();
	for (const auto& comm1 : commIns)
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
				commInBoundary[comm1.first][comm2.first][nodeLabels[t.node_id]].push_back(t.node_id);
			}
		}
	}
	for (int comm1 = 1; comm1 < commOutBoundary.size(); ++comm1)
	{
		for (int comm2 = 1; comm2 < commOutBoundary[comm1].size(); ++comm2)
		{
			for (int label = 0; label < labelnum; ++label)
			{
				int last = 0;
				for (int i = 0; i < commOutBoundary[comm1][comm2][label].size(); i++)
				{
					int index = commOutBoundary[comm1][comm2][label][i];
					if (commOuts[comm1][comm2][index].degree != last)
					{
						last = commOuts[comm1][comm2][index].degree;
						DegreePos dp;
						dp.degree = last;
						dp.pos = i;
						degreePosOut[comm1][comm2][label].push_back(dp);
					}
				}
			}
		}
	}
	for (int comm1 = 1; comm1 < commInBoundary.size(); ++comm1)
	{
		for (int comm2 = 1; comm2 < commInBoundary[comm1].size(); ++comm2)
		{
			for (int label = 0; label < labelnum; ++label)
			{
				int last = 0;
				for (int i = 0; i < commInBoundary[comm1][comm2][label].size(); i++)
				{
					int index = commInBoundary[comm1][comm2][label][i];
					if (commIns[comm1][comm2][index].degree != last)
					{
						last = commIns[comm1][comm2][index].degree;
						DegreePos dp;
						dp.degree = last;
						dp.pos = i;
						degreePosIn[comm1][comm2][label].push_back(dp);
					}
				}
			}
		}
	}

	commOuts.clear();
	commIns.clear();
	//return;
	for (const auto& n : node_ids)
	{
		int comm_n = nodeInfo[n][0];
		for (const auto& neigh1 : netWorkSet[n])
		{
			int comm_id = nodeInfo[neigh1][0];
			for (const auto& neigh2 : netWorkSet[neigh1])
			{
				int comm_id2 = nodeInfo[neigh2][0];
				if(netWorkSet[n].find(neigh2) != netWorkSet[n].end())
				{
					triangleLimitation[comm_n][comm_id][comm_id2] = true;
				}
			}
		}
	}

	return;
	for (const auto& n : node_ids)
	{
		int comm_n = nodeInfo[n][0];
		for (const auto& neigh1 : netWorkSet[n])
		{
			int comm_id = nodeInfo[neigh1][0];
			unordered_map<int, unordered_map<int, int>> outds;
			for (const auto& neigh2 : netWorkSet[neigh1])
			{
				int comm_id2 = nodeInfo[neigh2][0];
				for (const auto& n2 : netWorkSet[n])
				{
					if (n2 == neigh1)
						continue;
					int c2 = nodeInfo[n2][0];
					if (n != neigh2 && n2 != neigh1)
					{
						len4Limitation[c2][comm_n][comm_id][comm_id2] = true;
						if (n2 == neigh2)
						{
							//triangleLimitation[c2][comm_n][comm_id][comm_id2] = true;
						}
					}
					/*for (const auto& n3 : netWorkSet[n2])
					{
						if (n3 == n)
							continue;
						int c3 = nodeInfo[n3][0];
						len5Limitation[c3][c2][comm_n][comm_id][comm_id2] = true;
					}*/
				}			
				outds[comm_id2][nodeLabels[neigh2]]++;
			}
			for (const auto& o : outds)
			{
				/*if(!hasTwoHopComms[n][comm_id][o.first])
					hasTwoHopComms[n][comm_id][o.first] = true;
				for (const auto& l : o.second)
				{
					if (twoHopLimitation[n][comm_id][o.first][l.first] == 0)
					{
						twoHopLimitation[n][comm_id][o.first][l.first] = l.second;
					}
					else
					{
						twoHopLimitation[n][comm_id][o.first][l.first] = max(twoHopLimitation[n][comm_id][o.first][l.first], l.second);
					}
				}*/
				if (twoHopLimitation[n][comm_id][o.first] == NULL)
				{
					twoHopLimitation[n][comm_id][o.first] = new unordered_map<int, int>(o.second);
				}
				else
				{
					for (const auto& l : o.second)
					{
						if (twoHopLimitation[n][comm_id][o.first]->find(l.first) == twoHopLimitation[n][comm_id][o.first]->end())
						{
							(*twoHopLimitation[n][comm_id][o.first])[l.first] = l.second;
						}
						else
						{
							(*twoHopLimitation[n][comm_id][o.first])[l.first] = max((*twoHopLimitation[n][comm_id][o.first])[l.first], l.second);
						}
					}
				}
			}
		}
	}
}


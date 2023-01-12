#include "TempGraph.h"

TempGraph::TempGraph(GraphStat& gs, GraphManager* gm) {
	int maxInterEdge = 0;
	int pre_node = -1;
	vector<pair<int, int>>temp;

	for (const auto& edge : gs.eidmap) {
		string src = edge.second->start;
		string dst = edge.second->end;
		string label = edge.second->label;

		int nodeId1, nodeId2;

		if (gm->mGraph->nodeIdAlloterType == 0) {
			if (src == dst) {
				continue;
			}

			nodeId1 = atoi(src.substr(1, src.size() - 1).c_str());
			nodeId2 = atoi(dst.substr(1, dst.size() - 1).c_str());

			nodeId1 = gm->mGraph->nodeIdAlloter.i2iAlloter->allotId(nodeId1);
			insertFirstNode(nodeId1, gm->mGraph->nodeIdAlloter.i2iAlloter->newAlloted());

			nodeId2 = gm->mGraph->nodeIdAlloter.i2iAlloter->allotId(nodeId2);
			insertSecondNode(nodeId2, gm->mGraph->nodeIdAlloter.i2iAlloter->newAlloted());
		}
		else {
			if (src == dst) {
				continue;
			}

			nodeId1 = gm->mGraph->nodeIdAlloter.s2iAlloter->allotId(src);
			insertFirstNode(nodeId1, gm->mGraph->nodeIdAlloter.s2iAlloter->newAlloted());

			nodeId2 = gm->mGraph->nodeIdAlloter.s2iAlloter->allotId(dst);
			insertSecondNode(nodeId2, gm->mGraph->nodeIdAlloter.s2iAlloter->newAlloted());
		}

		netWorkSet[nodeId1][nodeId2].push_back(atoi(label.c_str()));
		nodeEdges[nodeId1]++;
	}

	for (const auto& e : netWorkSet) {
		if (e.second.empty())
			continue;
		int i = e.first;
		destIter[i] = netWorkSet[i].begin();

		if (destIter[i] != netWorkSet[i].end())
		{
			typeIter[i] = netWorkSet[i].begin()->second.begin();
		}
	}

	cout << "finish read network" << endl;
}

void TempGraph::insertFirstNode(int node, bool newAlloted)
{
	if (newAlloted)
	{
		unstored.insert(node);;
	}
	else
	{
		if (unstored.find(node) == unstored.end())
		{
			storedStarts.insert(node);
			stored.insert(node);
		}
	}
}

void TempGraph::insertSecondNode(int node, bool newAlloted)
{
	if (newAlloted)
	{
		unstored.insert(node);
	}
	else
	{
		if (unstored.find(node) == unstored.end())
		{
			stored.insert(node);
		}
	}
}
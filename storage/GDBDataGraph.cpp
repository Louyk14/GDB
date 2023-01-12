#include "GDBDataGraph.h"

GDBDataGraph::GDBDataGraph()
{
	
}

GDBDataGraph::~GDBDataGraph()
{

}

void GDBDataGraph::init(int n, int m)
{	
	communityNodes = vector<unordered_set<int>>(m + 1);
	netWork = vector<unordered_map<int, vector<int>>>(n + 1);
	destIter = vector<unordered_map<int, vector<int>>::iterator>(n + 1);
	typeIter = vector<vector<int>::iterator>(n + 1);
	nodeEdges = vector<int>(n + 1, 0);
	
	nodeCommunitySet = vector<unordered_set<int>>(n + 1);
	edge_dest_head = vector<EdgePos>(n + 1);
	nodeblock = vector<unordered_set<int>>(n + 1);
}

// ÅÐ¶ÏIdÊÇ·ñ´æÔÚ(newId)
bool GDBDataGraph::existNode(int node)
{
	return nodeIdAlloter.existId(node);
}

void GDBDataGraph::insertNode(int node, vector<int>& comm_id, bool resize)
{
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
			communityNodes[comm_id[i]].insert(node);
			nodeCommunitySet[node].insert(comm_id[i]);
		}
	}
}

void GDBDataGraph::removeNode(int node)
{
	graphNodes.erase(node);
	nodeIdAlloter.removeId(node);

	for (const auto& cid : nodeCommunitySet[node])
	{
		communityNodes[cid].erase(node);
	}
}

bool GDBDataGraph::nodeHasCommunity(int node)
{
	return node <= nodeIdAlloter.getMaxId() && !nodeCommunitySet[node].empty();
}

int GDBDataGraph::getNodeFirstCommunity(int node)
{
	if (nodeHasCommunity(node))
		return *nodeCommunitySet[node].begin();
}

int GDBDataGraph::nodeNum()
{
	return nodeIdAlloter.getIdNum();
}

int GDBDataGraph::communityNum()
{
	return communityIdAlloter.getIdNum();
}

void GDBDataGraph::reAllotNodeSpace(int nid)
{
	if (nid >= nodeCommunitySet.size())
	{
		nodeCommunitySet.resize(nid + 1);
		edge_dest_head.resize(nid + 1);
		nodeblock.resize(nid + 1);
	}
}

void GDBDataGraph::reAllotCommSpace(int cid)
{
	if (cid >= communityNodes.size())
		communityNodes.resize(cid + 1);
}
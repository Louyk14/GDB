#include "vf2_state.h"

VF2State::VF2State(MemoryGraph* data, int nodenum, vector<int>& n, unordered_map<int, unordered_map<string, string>>& na
	, unordered_map<int, unordered_map<int, unordered_map<string, string>>>& ea
	, unordered_map<int, unordered_set<int>>& oe
	, unordered_map<int, unordered_set<int>>& ie)
{
	nodes = &n;
	nodeAttributes = &na;
	edgeAttributes = &ea;
	outedges = &oe;
	inedges = &ie;

	order = NULL;

	n1 = (*nodes).size();
	n2 = nodenum;

	core_len = orig_core_len = 0;
	t1both_len = t1in_len = t1out_len = 0;
	t2both_len = t2in_len = t2out_len = 0;

	added_node1 = -1;

	core_1 = new unordered_map<int, int>();
	core_2 = new unordered_map<int, int>();
	in_1 = new unordered_map<int, int>();
	in_2 = new unordered_map<int, int>();
	out_1 = new unordered_map<int, int>();
	out_2 = new unordered_map<int, int>();
	share_count = new int;

	int i;
	for (i = 0; i < n1; i++)
	{
		(*core_1)[(*nodes)[i]] = -1;
		(*in_1)[(*nodes)[i]] = 0;
		(*out_1)[(*nodes)[i]] = 0;
	}
	for (const auto& n : data->nodes)
	{
		(*core_2)[n] = -1;
		(*in_2)[n] = 0;
		(*out_2)[n] = 0;
	}
	/*for (i = 0; i <= n1; i++)
	{
	core_1[i] = -1;
	in_1[i] = 0;
	out_1[i] = 0;
	}
	for (i = 0; i <= n2; i++)
	{
	core_2[i] = -1;
	in_2[i] = 0;
	out_2[i] = 0;
	}*/

	*share_count = 1;
}

VF2State::VF2State(const VF2State &state)
{
	nodes = state.nodes;
	nodeAttributes = state.nodeAttributes;
	edgeAttributes = state.edgeAttributes;
	inedges = state.inedges;
	outedges = state.outedges;
	n1 = state.n1;
	n2 = state.n2;

	order = state.order;

	core_len = orig_core_len = state.core_len;
	t1in_len = state.t1in_len;
	t1out_len = state.t1out_len;
	t1both_len = state.t1both_len;
	t2in_len = state.t2in_len;
	t2out_len = state.t2out_len;
	t2both_len = state.t2both_len;

	added_node1 = -1;

	core_1 = state.core_1;
	core_2 = state.core_2;
	in_1 = state.in_1;
	in_2 = state.in_2;
	out_1 = state.out_1;
	out_2 = state.out_2;
	share_count = state.share_count;

	++ *share_count;
}

VF2State::~VF2State()
{
	if (-- *share_count == 0)
	{
		delete core_1;
		delete core_2;
		delete in_1;
		delete out_1;
		delete in_2;
		delete out_2;
		delete share_count;

		delete[] order;
	}
}

bool VF2State::CompareNodeAttribute(MemoryGraph* data, int n1, int n2)
{
	return true;
	string n2_str = to_string(n2);
	int n1type = atoi((*nodeAttributes)[n1]["TYPE"].c_str());
	int n2type = data->nodeInfo[n2][1];

	if (n1type != n2type)
	{
		return false;
	}

	map<string, map<string, string>> answer;
	//storage.attr.getNodeAllAttributesBatch(storage.db, vector<string>(1, n2_str), vector<string>(1, storage.nodetype2tablename[n2type]), answer);

	for (const auto& a : (*nodeAttributes)[n1])
	{
		if (a.first == "TYPE")
		{
			continue;
		}

		if (answer[n2_str].find(a.first) == answer[n2_str].end())
		{
			return false;
		}
		else
		{
			if (a.second != answer[n2_str][a.first])
			{
				return false;
			}
		}
	}

	return true;
}

bool VF2State::CompareEdgeAttribute(MemoryGraph* data, int src1, int dst1, int src2, int dst2)
{
	return true;
	int type1 = atoi((*edgeAttributes)[src1][dst1]["TYPE"].c_str());
	unordered_set<int> type2;// = storage.GetEdgeType(src2, dst2);

	if (type2.find(type1) == type2.end())
	{
		return false;
	}

	string estr = "\'" + to_string(src2) + "_" + to_string(dst2) + "\'";

	map<string, map<string, string>> answer;
	//storage.attr.getEdgeAttributes(storage.db, storage.edgetype2tablename[type1], vector<string>(1, estr), vector<string>(), answer);

	for (const auto& e : (*edgeAttributes)[src1][dst1])
	{
		if (e.first == "TYPE")
		{
			continue;
		}

		if (answer[estr].find(e.first) == answer[estr].end())
		{
			return false;
		}
		else
		{
			if (e.second != answer[estr][e.first])
			{
				return false;
			}
		}
	}

	return true;
}

bool VF2State::NextPair(MemoryGraph* data, int *pn1, int *pn2, int prev_n1, int prev_n2)
{
	if (prev_n1 == -1)
		prev_n1 = 0;

	if (prev_n2 == -1)
		prev_n2 = 0;
	else
		prev_n2++;

	if (t1both_len > core_len && t2both_len > core_len)
	{
		while (prev_n1 < n1 &&
			((*core_1)[(*nodes)[prev_n1]] != -1 || (*out_1)[(*nodes)[prev_n1]] == 0 || (*in_1)[(*nodes)[prev_n1]] == 0))
		{
			prev_n1++;
			prev_n2 = 0;
		}
	}
	else if (t1out_len > core_len && t2out_len > core_len)
	{
		while (prev_n1 < n1 &&
			((*core_1)[(*nodes)[prev_n1]] != -1 || (*out_1)[(*nodes)[prev_n1]] == 0))
		{
			prev_n1++;
			prev_n2 = 0;
		}
	}
	else if (t1in_len > core_len && t2in_len > core_len)
	{
		while (prev_n1 < n1 &&
			((*core_1)[(*nodes)[prev_n1]] != -1 || (*in_1)[(*nodes)[prev_n1]] == 0))
		{
			prev_n1++;
			prev_n2 = 0;
		}
	}
	else if (prev_n1 == 0 && order != NULL)
	{
		int i = 0;
		while (i < n1 && (*core_1)[(*nodes)[prev_n1 = order[i]]] != -1)
			i++;
		if (i == n1)
			prev_n1 = n1;
	}
	else
	{
		while (prev_n1 < n1 && (*core_1)[(*nodes)[prev_n1]] != -1)
		{
			prev_n1++;
			prev_n2 = 0;
		}
	}


	if (t1both_len > core_len && t2both_len > core_len)
	{
		while (prev_n2 < n2 &&
			((*core_2)[data->nodes[prev_n2]] != -1 || (*out_2)[data->nodes[prev_n2]] == 0
				|| (*in_2)[data->nodes[prev_n2]] == 0))
		{
			prev_n2++;
		}
	}
	else if (t1out_len > core_len && t2out_len > core_len)
	{
		while (prev_n2 < n2 &&
			((*core_2)[data->nodes[prev_n2]] != -1 || (*out_2)[data->nodes[prev_n2]] == 0))
		{
			prev_n2++;
		}
	}
	else if (t1in_len > core_len && t2in_len > core_len)
	{
		while (prev_n2 < n2 &&
			((*core_2)[data->nodes[prev_n2]] != -1 || (*in_2)[data->nodes[prev_n2]] == 0))
		{
			prev_n2++;
		}
	}
	else
	{
		while (prev_n2 < n2 && (*core_2)[data->nodes[prev_n2]] != -1)
		{
			prev_n2++;
		}
	}


	if (prev_n1 < n1 && prev_n2 < n2)
	{
		*pn1 = prev_n1;
		*pn2 = prev_n2;
		return true;
	}

	return false;
}

/*
bool VF2State::NextPair(int *pn1, int *pn2, int prev_n1, int prev_n2)
{
if (prev_n1 == -1)
prev_n1 = 1;

if (prev_n2 == -1)
prev_n2 = 1;
else
prev_n2++;

if (t1both_len > core_len && t2both_len > core_len)
{
while (prev_n1 <= n1 &&
(core_1[prev_n1] != -1 || out_1[prev_n1] == 0 || in_1[prev_n1] == 0))
{
prev_n1++;
prev_n2 = 1;
}
}
else if (t1out_len > core_len && t2out_len > core_len)
{
while (prev_n1 <= n1 &&
(core_1[prev_n1] != -1 || out_1[prev_n1] == 0))
{
prev_n1++;
prev_n2 = 1;
}
}
else if (t1in_len > core_len && t2in_len > core_len)
{
while (prev_n1 <= n1 &&
(core_1[prev_n1] != -1 || in_1[prev_n1] == 0))
{
prev_n1++;
prev_n2 = 1;
}
}
else if (prev_n1 == 1 && order != NULL)
{
int i = 0;
while (i <= n1 && core_1[prev_n1 = order[i]] != -1)
i++;
if (i == n1)
prev_n1 = n1;
}
else
{
while (prev_n1 <= n1 && core_1[prev_n1] != -1)
{
prev_n1++;
prev_n2 = 1;
}
}


if (t1both_len > core_len && t2both_len > core_len)
{
while (prev_n2 <= n2 &&
(core_2[prev_n2] != -1 || out_2[prev_n2] == 0
|| in_2[prev_n2] == 0))
{
prev_n2++;
}
}
else if (t1out_len > core_len && t2out_len > core_len)
{
while (prev_n2 <= n2 &&
(core_2[prev_n2] != -1 || out_2[prev_n2] == 0))
{
prev_n2++;
}
}
else if (t1in_len > core_len && t2in_len > core_len)
{
while (prev_n2 <= n2 &&
(core_2[prev_n2] != -1 || in_2[prev_n2] == 0))
{
prev_n2++;
}
}
else
{
while (prev_n2 <= n2 && core_2[prev_n2] != -1)
{
prev_n2++;
}
}


if (prev_n1 <= n1 && prev_n2 <= n2)
{
*pn1 = prev_n1;
*pn2 = prev_n2;
return true;
}

return false;
}
*/

bool VF2State::IsFeasiblePair(MemoryGraph* data, int node1, int node2)
{
	assert(node1 < n1);
	assert(node2 < n2);

	node1 = (*nodes)[node1];
	node2 = data->nodes[node2];

	assert((*core_1)[node1] == -1);
	assert((*core_2)[node2] == -1);

	if (!CompareNodeAttribute(data, node1, node2))
		return false;

	int i, other1, other2;
	void *attr1;
	int termout1 = 0, termout2 = 0, termin1 = 0, termin2 = 0, new1 = 0, new2 = 0;

	// Check the 'out' edges of node1
	for (const auto& oe : (*outedges)[node1])
	{
		other1 = oe;
		//other1 = g1->GetOutEdge(node1, i, &attr1);
		if ((*core_1)[other1] != -1)
		{
			other2 = (*core_1)[other1];
			if (!data->hasEdge(node2, other2) ||
				!CompareEdgeAttribute(data, node1, other1, node2, other2))
				return false;
		}
		else
		{
			if ((*in_1)[other1])
				termin1++;
			if ((*out_1)[other1])
				termout1++;
			if (!(*in_1)[other1] && !(*out_1)[other1])
				new1++;
		}
	}

	// Check the 'in' edges of node1
	for (const auto& ie : (*inedges)[node1])
	{
		other1 = ie;
		if ((*in_1).find(other1) == (*in_1).end())
		{
			continue;
		}
		//other1 = g1->GetInEdge(node1, i, &attr1);
		if ((*core_1)[other1] != -1)
		{
			other2 = (*core_1)[other1];
			if (!data->hasEdge(other2, node2) ||
				!CompareEdgeAttribute(data, other1, node1, other2, node2))
				return false;
		}
		else
		{
			if ((*in_1)[other1])
				termin1++;
			if ((*out_1)[other1])
				termout1++;
			if (!(*in_1)[other1] && !(*out_1)[other1])
				new1++;
		}
	}

	int rid;
	for (const auto& outnode : data->netWorkSet[node2])
	{
		other2 = outnode.first;
		if ((*core_2).find(other2) == (*core_2).end())
		{
			continue;
		}
		//other2 = g2->GetOutEdge(node2, i);
		if ((*core_2)[other2] != -1)
		{
			//other1 = core_2[other2];
			//if (!HasEdge(node1, other1))
			//	return false;
		}
		else
		{
			if ((*in_2)[other2])
				termin2++;
			if ((*out_2)[other2])
				termout2++;
			if (!(*in_2)[other2] && !(*out_2)[other2])
				new2++;
		}
	}



	// Check the 'in' edges of node2
	for (const auto& innode : data->netWorkSet[node2])
	{
		other2 = innode.first;
		if ((*core_2).find(other2) == (*core_2).end())
		{
			continue;
		}
		//other2 = g2->GetInEdge(node2, i);
		if ((*core_2)[other2] != -1)
		{
			//other1 = core_2[other2];
			//if (!HasEdge(other1, node1))
			//	return false;
		}
		else
		{
			if ((*in_2)[other2])
				termin2++;
			if ((*out_2)[other2])
				termout2++;
			if (!(*in_2)[other2] && !(*out_2)[other2])
				new2++;
		}
	}

	// Check the 'out' edges of node2
	/*set<int> outNeighs;
	storage.tools->getOneHopNeighbours(storage, node2, outNeighs);

	for (const auto& outnode : outNeighs)
	{
	other2 = outnode;
	//other2 = g2->GetOutEdge(node2, i);
	if (core_2[other2] != -1)
	{
	//other1 = core_2[other2];
	//if (!HasEdge(node1, other1))
	//	return false;
	}
	else
	{
	if (in_2[other2])
	termin2++;
	if (out_2[other2])
	termout2++;
	if (!in_2[other2] && !out_2[other2])
	new2++;
	}
	}

	// Check the 'in' edges of node2
	unordered_set<int> neighbours;
	storage.GetNodeInNeighbours(node2, neighbours);

	for (const auto& innode : neighbours)
	{
	other2 = innode;
	//other2 = g2->GetInEdge(node2, i);
	if (core_2[other2] != -1)
	{
	//other1 = core_2[other2];
	//if (!HasEdge(other1, node1))
	//	return false;
	}
	else
	{
	if (in_2[other2])
	termin2++;
	if (out_2[other2])
	termout2++;
	if (!in_2[other2] && !out_2[other2])
	new2++;
	}
	}*/

	return termin1 <= termin2 && termout1 <= termout2
		&& (termin1 + termout1 + new1) <= (termin2 + termout2 + new2);
}

void VF2State::AddPair(MemoryGraph* data, int node1, int node2)
{
	assert(node1 < n1);
	assert(node2 < n2);
	assert(core_len < n1);
	assert(core_len < n2);

	node1 = (*nodes)[node1];
	node2 = data->nodes[node2];

	core_len++;
	added_node1 = node1;

	if (!(*in_1)[node1])
	{
		(*in_1)[node1] = core_len;
		t1in_len++;
		if ((*out_1)[node1])
		{
			t1both_len++;
		}
	}
	if (!(*out_1)[node1])
	{
		(*out_1)[node1] = core_len;
		t1out_len++;
		if ((*in_1)[node1])
		{
			t1both_len++;
		}
	}

	if (!(*in_2)[node2])
	{
		(*in_2)[node2] = core_len;
		t2in_len++;
		if ((*out_2)[node2])
		{
			t2both_len++;
		}
	}
	if (!(*out_2)[node2])
	{
		(*out_2)[node2] = core_len;
		t2out_len++;
		if ((*in_2)[node2])
		{
			t2both_len++;
		}
	}

	(*core_1)[node1] = node2;
	(*core_2)[node2] = node1;

	for (const auto& ie : (*inedges)[node1])
	{
		int other = ie;
		if ((*in_1).find(other) != (*in_1).end()
			&& !(*in_1)[other])
		{
			(*in_1)[other] = core_len;
			t1in_len++;
			if ((*out_1)[other])
			{
				t1both_len++;
			}
		}
	}

	for (const auto& oe : (*outedges)[node1])
	{
		int other = oe;
		if ((*out_1).find(other) != (*out_1).end()
			&& !(*out_1)[other])
		{
			(*out_1)[other] = core_len;
			t1out_len++;
			if ((*in_1)[other])
			{
				t1both_len++;
			}
		}
	}

	int rid;
	for (const auto& innode : data->netWorkSet[node2])
	{
		int other = innode.first;
		if ((*in_2).find(other) == (*in_2).end())
		{
			continue;
		}

		if (!(*in_2)[other])
		{
			(*in_2)[other] = core_len;
			t2in_len++;
			if ((*out_2)[other])
			{
				t2both_len++;
			}
		}
	}

	for (const auto& outnode : data->netWorkSet[node2])
	{
		int other = outnode.first;
		if ((*out_2).find(other) == (*out_2).end())
		{
			continue;
		}

		if (!(*out_2)[other])
		{
			(*out_2)[other] = core_len;
			t2out_len++;
			if ((*in_2)[other])
			{
				t2both_len++;
			}
		}
	}

	/*unordered_set<int> neighbours;
	storage.GetNodeInNeighbours(node2, neighbours);

	for (const auto& innode : neighbours)
	{
	int other = innode;
	if (!in_2[other])
	{
	in_2[other] = core_len;
	t2in_len++;
	if (out_2[other])
	{
	t2both_len++;
	}
	}
	}

	set<int> outNeighs;
	storage.tools->getOneHopNeighbours(storage, node2, outNeighs);

	for (const auto& outnode : outNeighs)
	{
	int other = outnode;
	if (!out_2[other])
	{
	out_2[other] = core_len;
	t2out_len++;
	if (in_2[other])
	{
	t2both_len++;
	}
	}
	}*/
}

void VF2State::GetCoreSet(vector<vector<int>>& ans)
{
	vector<int> temp((*nodes).size(), -1);

	for (int i = 0; i < n1; i++)
	{
		temp[(*nodes)[i] - 1] = (*core_1)[(*nodes)[i]];
	}

	//ans.push_back(temp);
}

void VF2State::GetCoreSet(vector<unordered_map<int, int>>& ans)
{
	unordered_map<int, int> temp;

	int i, j;
	for (i = 0; i < n1; i++)
	{
		if ((*core_1)[(*nodes)[i]] != -1)
		{
			temp[(*nodes)[i]] = (*core_1)[(*nodes)[i]];
		}
	}

	//ans.push_back(temp);
}

VF2State* VF2State::Clone()
{
	return new VF2State(*this);
}

void VF2State::BackTrack(MemoryGraph* data)
{
	assert(core_len - orig_core_len <= 1);
	assert(added_node1 != -1);

	if (orig_core_len < core_len)
	{
		int i, node2;

		if ((*in_1)[added_node1] == core_len)
		{
			(*in_1)[added_node1] = 0;
		}

		for (const auto& ie : (*inedges)[added_node1])
		{
			if ((*in_1).find(ie) == (*in_1).end())
			{
				continue;
			}
			if ((*in_1)[ie] == core_len)
			{
				(*in_1)[ie] = 0;
			}
		}

		if ((*out_1)[added_node1] == core_len)
		{
			(*out_1)[added_node1] = 0;
		}

		for (const auto& oe : (*outedges)[added_node1])
		{
			if ((*in_1).find(oe) == (*in_1).end())
			{
				continue;
			}
			if ((*out_1)[oe] == core_len)
			{
				(*out_1)[oe] = 0;
			}
		}

		node2 = (*core_1)[added_node1];

		if ((*in_2)[node2] == core_len)
		{
			(*in_2)[node2] = 0;
		}

		int rid;
		for (const auto& innode : data->netWorkSet[node2])
		{
			if ((*in_2).find(innode.first) == (*in_2).end())
			{
				continue;
			}

			if ((*in_2)[innode.first] == core_len)
			{
				(*in_2)[innode.first] = 0;
			}
		}

		if ((*out_2)[node2] == core_len)
		{
			(*out_2)[node2] = 0;
		}

		for (const auto& outnode : data->netWorkSet[node2])
		{
			if ((*out_2).find(outnode.first) == (*out_2).end())
			{
				continue;
			}

			if ((*out_2)[outnode.first] == core_len)
			{
				(*out_2)[outnode.first] = 0;
			}
		}

		/*unordered_set<int> neighbours;
		storage.GetNodeInNeighbours(node2, neighbours);

		for (const auto& innode : neighbours)
		{
		if (in_2[innode] == core_len)
		{
		in_2[innode] = 0;
		}
		}

		if (out_2[node2] == core_len)
		{
		out_2[node2] = 0;
		}

		set<int> outNeighs;
		storage.tools->getOneHopNeighbours(storage, node2, outNeighs);

		for (const auto& outnode : outNeighs)
		{
		if (out_2[outnode] == core_len)
		{
		out_2[outnode] = 0;
		}
		}*/

		(*core_1)[added_node1] = -1;
		(*core_2)[node2] = -1;

		core_len = orig_core_len;
		added_node1 = -1;
	}
}

bool VF2State::HasEdge(int src, int dst)
{
	return ((*outedges)[src].find(dst) != (*outedges)[src].end());
}
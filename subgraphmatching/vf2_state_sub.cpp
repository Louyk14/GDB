#include "vf2_state_sub.h"

VF2StateSub::VF2StateSub(MemoryGraph* ag1, MemoryGraph* ag2, bool deg, unordered_map<int, vector<int>>* boundary)
{
	g1 = ag1;
	g2 = ag2;

	order = NULL;

	n1 = g1->nodes.size();
	n2 = g2->nodes.size();

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
	degree = deg;

	int i;
	for (i = 0; i < n1; i++)
	{
		(*core_1)[g1->nodes[i]] = -1;
		(*in_1)[g1->nodes[i]] = 0;
		(*out_1)[g1->nodes[i]] = 0;
	}
	for (i = 0; i < n2; i++)
	{
		(*core_2)[g2->nodes[i]] = -1;
		(*in_2)[g2->nodes[i]] = 0;
		(*out_2)[g2->nodes[i]] = 0;
	}

	if (degree)
	{
		nodeArea = boundary;
	}

	*share_count = 1;
}

VF2StateSub::VF2StateSub(const VF2StateSub &state)
{
	g1 = state.g1;
	g2 = state.g2;
	n1 = state.n1;
	n2 = state.n2;
	degree = state.degree;
	nodeArea = state.nodeArea;

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

VF2StateSub::~VF2StateSub()
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

//只比较属性是否存在
bool VF2StateSub::CompareNodeAttribute(int n1, int n2)
{
	return true;
	string n1type = g1->nodeAttributes[n1]["TYPE"];
	string n2type = g2->nodeAttributes[n2]["TYPE"];

	if (n1type != n2type)
	{
		return false;
	}

	/*for (const auto& a : g1->nodeAttributes[n1])
	{
	if (a.first == "TYPE")
	{
	continue;
	}

	if (g2->nodeAttributes[n2].find(a.first) == g2->nodeAttributes[n2].end())
	{
	return false;
	}
	else
	{
	if (g2->nodeAttributes[n2][a.first].find(a.second) == g2->nodeAttributes[n2][a.first].end())
	{
	return false;
	}
	}
	}*/

	return true;
}

//只比较属性是否存在
bool VF2StateSub::CompareEdgeAttribute(int src1, int dst1, int src2, int dst2)
{
	return true;
	string type1 = g1->edgeAttributes[src1][dst1]["TYPE"];
	string type2 = g2->edgeAttributes[src2][dst2]["TYPE"];

	if (type1 != type2)
	{
		return false;
	}

	/*for (const auto& e : g1->edgeAttributes[src1][dst1])
	{
	if (e.first == "TYPE")
	{
	continue;
	}

	if (g2->edgeAttributes[src2][dst2].find(e.first) == g2->edgeAttributes[src2][dst2].end())
	{
	return false;
	}
	else
	{
	if (g2->edgeAttributes[src2][dst2][e.first].find(e.second) == g2->edgeAttributes[src2][dst2][e.first].end())
	{
	return false;
	}
	}
	}*/

	return true;
}

bool VF2StateSub::NextPair(int *pn1, int *pn2, int prev_n1, int prev_n2)
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
			((*core_1)[g1->nodes[prev_n1]] != -1 || (*out_1)[g1->nodes[prev_n1]] == 0 || (*in_1)[g1->nodes[prev_n1]] == 0))
		{
			prev_n1++;
			prev_n2 = 0;
		}
	}
	else if (t1out_len > core_len && t2out_len > core_len)
	{
		while (prev_n1 < n1 &&
			((*core_1)[g1->nodes[prev_n1]] != -1 || (*out_1)[g1->nodes[prev_n1]] == 0))
		{
			prev_n1++;
			prev_n2 = 0;
		}
	}
	else if (t1in_len > core_len && t2in_len > core_len)
	{
		while (prev_n1 < n1 &&
			((*core_1)[g1->nodes[prev_n1]] != -1 || (*in_1)[g1->nodes[prev_n1]] == 0))
		{
			prev_n1++;
			prev_n2 = 0;
		}
	}
	else if (prev_n1 == 0 && order != NULL)
	{
		int i = 0;
		while (i < n1 && (*core_1)[g1->nodes[prev_n1 = order[i]]] != -1)
			i++;
		if (i == n1)
			prev_n1 = n1;
	}
	else
	{
		while (prev_n1 < n1 && (*core_1)[g1->nodes[prev_n1]] != -1)
		{
			prev_n1++;
			prev_n2 = 0;
		}
	}

	if (prev_n1 >= n1)
	{
		return false;
	}

	if (!degree || (*nodeArea).find(g1->nodes[prev_n1]) == (*nodeArea).end())
	{
		if (t1both_len > core_len && t2both_len > core_len)
		{
			while (prev_n2 < n2 &&
				((*core_2)[g2->nodes[prev_n2]] != -1 || (*out_2)[g2->nodes[prev_n2]] == 0
					|| (*in_2)[g2->nodes[prev_n2]] == 0))
			{
				prev_n2++;
			}
		}
		else if (t1out_len > core_len && t2out_len > core_len)
		{
			while (prev_n2 < n2 &&
				((*core_2)[g2->nodes[prev_n2]] != -1 || (*out_2)[g2->nodes[prev_n2]] == 0))
			{
				prev_n2++;
			}
		}
		else if (t1in_len > core_len && t2in_len > core_len)
		{
			while (prev_n2 < n2 &&
				((*core_2)[g2->nodes[prev_n2]] != -1 || (*in_2)[g2->nodes[prev_n2]] == 0))
			{
				prev_n2++;
			}
		}
		else
		{
			while (prev_n2 < n2 && (*core_2)[g2->nodes[prev_n2]] != -1)
			{
				prev_n2++;
			}
		}
	}
	else
	{
		if (t1both_len > core_len && t2both_len > core_len)
		{
			while (prev_n2 < (*nodeArea)[g1->nodes[prev_n1]].size() &&
				((*core_2)[(*nodeArea)[g1->nodes[prev_n1]][prev_n2]] != -1 || (*out_2)[(*nodeArea)[g1->nodes[prev_n1]][prev_n2]] == 0
					|| (*in_2)[(*nodeArea)[g1->nodes[prev_n1]][prev_n2]] == 0))
			{
				prev_n2++;
			}
		}
		else if (t1out_len > core_len && t2out_len > core_len)
		{
			while (prev_n2 < (*nodeArea)[g1->nodes[prev_n1]].size() &&
				((*core_2)[(*nodeArea)[g1->nodes[prev_n1]][prev_n2]] != -1 || (*out_2)[(*nodeArea)[g1->nodes[prev_n1]][prev_n2]] == 0))
			{
				prev_n2++;
			}
		}
		else if (t1in_len > core_len && t2in_len > core_len)
		{
			while (prev_n2 < (*nodeArea)[g1->nodes[prev_n1]].size() &&
				((*core_2)[(*nodeArea)[g1->nodes[prev_n1]][prev_n2]] != -1 || (*in_2)[(*nodeArea)[g1->nodes[prev_n1]][prev_n2]] == 0))
			{
				prev_n2++;
			}
		}
		else
		{
			while (prev_n2 < (*nodeArea)[g1->nodes[prev_n1]].size() && (*core_2)[(*nodeArea)[g1->nodes[prev_n1]][prev_n2]] != -1)
			{
				prev_n2++;
			}
		}
	}

	if (!degree || (*nodeArea).find(g1->nodes[prev_n1]) == (*nodeArea).end())
	{
		if (prev_n1 < n1 && prev_n2 < n2)
		{
			*pn1 = prev_n1;
			*pn2 = prev_n2;
			return true;
		}
	}
	else
	{
		if (prev_n1 < n1 && prev_n2 < (*nodeArea)[g1->nodes[prev_n1]].size())
		{
			*pn1 = prev_n1;
			*pn2 = prev_n2;
			return true;
		}
	}

	return false;
}

bool VF2StateSub::IsFeasiblePair(int node1, int node2)
{
	if (!degree || (*nodeArea).find(g1->nodes[node1]) == (*nodeArea).end())
	{
		assert(node1 < n1);
		assert(node2 < n2);

		node1 = g1->nodes[node1];
		node2 = g2->nodes[node2];
	}
	else
	{
		assert(node1 < n1);
		node1 = g1->nodes[node1];

		assert(node2 < (*nodeArea)[node1].size());
		node2 = (*nodeArea)[node1][node2];
	}

	assert((*core_1)[node1] == -1);
	assert((*core_2)[node2] == -1);

	if (!CompareNodeAttribute(node1, node2))
		return false;

	int i, other1, other2;
	void *attr1;
	int termout1 = 0, termout2 = 0, termin1 = 0, termin2 = 0, new1 = 0, new2 = 0;

	// Check the 'out' edges of node1
	for (const auto& oe : (*g1->outedges)[node1])
	{
		other1 = oe.first;
		if ((*out_1).find(other1) == (*out_1).end())
		{
			continue;
		}
		//other1 = g1->GetOutEdge(node1, i, &attr1);
		if ((*core_1)[other1] != -1)
		{
			other2 = (*core_1)[other1];
			if (!g2->HasEdge(node2, other2) ||
				!CompareEdgeAttribute(node1, other1, node2, other2))
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
	for (const auto& ie : (*g1->inedges)[node1])
	{
		other1 = ie.first;
		if ((*out_1).find(other1) == (*out_1).end())
		{
			continue;
		}
		//other1 = g1->GetInEdge(node1, i, &attr1);
		if ((*core_1)[other1] != -1)
		{
			other2 = (*core_1)[other1];
			if (!g2->HasEdge(other2, node2) ||
				!CompareEdgeAttribute(other1, node1, other2, node2))
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


	// Check the 'out' edges of node2

	for (const auto& oe : (*g2->outedges)[node2])
	{
		other2 = oe.first;
		if ((*out_2).find(other2) == (*out_2).end())
		{
			continue;
		}
		//other2 = g2->GetOutEdge(node2, i);
		if ((*core_2)[other2] != -1)
		{
			other1 = (*core_2)[other2];
			if (!g1->HasEdge(node1, other1))
				return false;
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

	for (const auto& ie : (*g2->inedges)[node2])
	{
		other2 = ie.first;
		if ((*out_2).find(other2) == (*out_2).end())
		{
			continue;
		}
		//other2 = g2->GetInEdge(node2, i);
		if ((*core_2)[other2] != -1)
		{
			other1 = (*core_2)[other2];
			if (!g1->HasEdge(other1, node1))
				return false;
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

	return termin1 <= termin2 && termout1 <= termout2 && new1 <= new2;
}

void VF2StateSub::AddPair(int node1, int node2)
{
	if (!degree || (*nodeArea).find(g1->nodes[node1]) == (*nodeArea).end())
	{
		assert(node1 < n1);
		assert(node2 < n2);
		assert(core_len < n1);
		assert(core_len < n2);

		node1 = g1->nodes[node1];
		node2 = g2->nodes[node2];
	}
	else
	{
		assert(node1 < n1);
		node1 = g1->nodes[node1];

		assert(node2 < (*nodeArea)[node1].size());
		node2 = (*nodeArea)[node1][node2];

		assert(core_len < n1);
		assert(core_len < n2);
	}

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

	for (const auto& ie : (*g1->inedges)[node1])
	{
		int other = ie.first;
		if ((*out_1).find(other) == (*out_1).end())
		{
			continue;
		}
		if (!(*in_1)[other])
		{
			(*in_1)[other] = core_len;
			t1in_len++;
			if ((*out_1)[other])
			{
				t1both_len++;
			}
		}
	}

	for (const auto& oe : (*g1->outedges)[node1])
	{
		int other = oe.first;
		if ((*out_1).find(other) == (*out_1).end())
		{
			continue;
		}
		if (!(*out_1)[other])
		{
			(*out_1)[other] = core_len;
			t1out_len++;
			if ((*in_1)[other])
			{
				t1both_len++;
			}
		}
	}

	for (const auto& ie : (*g2->inedges)[node2])
	{
		int other = ie.first;
		if ((*out_2).find(other) == (*out_2).end())
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

	for (const auto& oe : (*g2->outedges)[node2])
	{
		int other = oe.first;
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
}

void VF2StateSub::GetCoreSet(string& ans, unordered_map<int, int>& mapper, bool iswrite)
{
	if (!iswrite)
		return;

	vector<string> r;

	int i, j;
	for (i = 0; i < n1; i++)
	{
		if ((*core_1)[g1->nodes[i]] != -1)
		{
			mapper[g1->nodes[i]] = (*core_1)[g1->nodes[i]];
			r.push_back(to_string((*core_1)[g1->nodes[i]]));
		}
	}

	sort(r.begin(), r.end());
	for (int i = 0; i < r.size(); i++)
	{
		ans += r[i];
		ans += "_";
	}
}

VF2StateSub* VF2StateSub::Clone()
{
	return new VF2StateSub(*this);
}

void VF2StateSub::BackTrack()
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

		for (const auto& ie : (*g1->inedges)[added_node1])
		{
			if ((*out_1).find(ie.first) == (*out_1).end())
			{
				continue;
			}
			if ((*in_1)[ie.first] == core_len)
			{
				(*in_1)[ie.first] = 0;
			}
		}

		if ((*out_1)[added_node1] == core_len)
		{
			(*out_1)[added_node1] = 0;
		}

		for (const auto& oe : (*g1->outedges)[added_node1])
		{
			if ((*out_1).find(oe.first) == (*out_1).end())
			{
				continue;
			}
			if ((*out_1)[oe.first] == core_len)
			{
				(*out_1)[oe.first] = 0;
			}
		}

		node2 = (*core_1)[added_node1];

		if ((*in_2)[node2] == core_len)
		{
			(*in_2)[node2] = 0;
		}

		for (const auto& ie : (*g2->inedges)[node2])
		{
			if ((*out_2).find(ie.first) == (*out_2).end())
			{
				continue;
			}
			if ((*in_2)[ie.first] == core_len)
			{
				(*in_2)[ie.first] = 0;
			}
		}

		if ((*out_2)[node2] == core_len)
		{
			(*out_2)[node2] = 0;
		}

		for (const auto& oe : (*g2->outedges)[node2])
		{
			if ((*out_2).find(oe.first) == (*out_2).end())
			{
				continue;
			}
			if ((*out_2)[oe.first] == core_len)
			{
				(*out_2)[oe.first] = 0;
			}
		}

		(*core_1)[added_node1] = -1;
		(*core_2)[node2] = -1;

		core_len = orig_core_len;
		added_node1 = -1;
	}
}
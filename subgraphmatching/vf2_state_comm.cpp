#include "vf2_state_comm.h"

VF2StateComm::VF2StateComm(MemoryGraph* data, MemoryGraph* ag1, MemoryGraph* ag2, int pid, bool islazy
	, bool deg, int cid, map<int, int>* dp, unordered_map<int, vector<int>>* boundary, unordered_set<int>* blist
	, bool act, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oo
	, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oi
	, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* io
	, bool af, vector<int>* autonodes, vector<int>* all)
{
	g1 = ag1;
	g2 = ag2;

	order = NULL;
	lazy = islazy;
	processId = pid;
	degree = deg;
	comm_id = cid;
	distributionplan = dp;
	active = act;
	oomessage = oo;
	oimessage = oi;
	iomessage = io;
	autofill = af;
	autofillnodes = autonodes;
	allnodes = all;

	n1 = g1->nodes.size();
	n2 = g2->nodes.size();

	core_len = orig_core_len = 0;
	t1both_len = t1in_len = t1out_len = 0;
	t2both_len = t2in_len = t2out_len = 0;

	added_node1 = -1;

	share_count = new int;

	core_1 = new unordered_map<int, int>();
	core_2 = new unordered_map<int, int>();
	in_1 = new unordered_map<int, int>();
	in_2 = new unordered_map<int, int>();
	out_1 = new unordered_map<int, int>();
	out_2 = new unordered_map<int, int>();

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

	*share_count = 1;

	if (degree)
	{
		nodeArea = boundary;
	}

	banlist = blist;
}

VF2StateComm::VF2StateComm(const VF2StateComm &state)
{
	g1 = state.g1;
	g2 = state.g2;
	n1 = state.n1;
	n2 = state.n2;
	lazy = state.lazy;
	processId = state.processId;
	degree = state.degree;
	comm_id = state.comm_id;
	distributionplan = state.distributionplan;
	nodeArea = state.nodeArea;
	banlist = state.banlist;
	active = state.active;
	oomessage = state.oomessage;
	oimessage = state.oimessage;
	iomessage = state.iomessage;
	autofill = state.autofill;
	autofillnodes = state.autofillnodes;
	allnodes = state.allnodes;

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

VF2StateComm::~VF2StateComm()
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

bool VF2StateComm::CompareNodeAttribute(MemoryGraph* data, int n1, int n2)
{
	return true;
	string n2_str = to_string(n2);
	int n1type = atoi((*g1->nodeAttributes)[n1]["TYPE"].c_str());
	int n2type = data->nodeInfo[n2][1];

	if (n1type != n2type)
	{
		return false;
	}

	map<string, map<string, string>> answer;
	//storage.attr.getNodeAllAttributesBatch(storage.db, vector<string>(1, n2_str), vector<string>(1, storage.nodetype2tablename[n2type]), answer);

	for (const auto& a : (*g1->nodeAttributes)[n1])
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

bool VF2StateComm::CompareEdgeAttribute(MemoryGraph* data, int src1, int dst1, int src2, int dst2)
{
	return true;
	int type1 = atoi((*g1->edgeAttributes)[src1][dst1]["TYPE"].c_str());
	unordered_set<int> type2;// = storage.GetEdgeType(src2, dst2);

	if (type2.find(type1) == type2.end())
	{
		return false;
	}

	string estr = "\'" + to_string(src2) + "_" + to_string(dst2) + "\'";

	map<string, map<string, string>> answer;
	//storage.attr.getEdgeAttributes(storage.db, storage.edgetype2tablename[type1], vector<string>(1, estr), vector<string>(), answer);

	for (const auto& e : (*g1->edgeAttributes)[src1][dst1])
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

bool VF2StateComm::NextPair(MemoryGraph* data, int *pn1, int *pn2, int prev_n1, int prev_n2)
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

bool VF2StateComm::IsFeasiblePair(MemoryGraph* data, int node1, int node2)
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

	if (!CompareNodeAttribute(data, node1, node2))
		return false;

	int i, other1, other2;
	void *attr1;
	int termout1 = 0, termout2 = 0, termin1 = 0, termin2 = 0, new1 = 0, new2 = 0;

	int rid;

	if (banlist != NULL
		&& (*banlist).find(node2) != (*banlist).end())
	{
		return false;
	}

	if (active)
	{
		unordered_map<int, vector<int>>* outedges1;
		unordered_map<int, vector<int>>* inedges1;

		unordered_map<int, vector<int>>* outedges2 = &data->netWorkSet[node2];
		unordered_map<int, vector<int>>* inedges2 = &data->netWorkSet[node2];
		
		//storage.getCommEdges(0, node2, processId, rid, inedges2, outedges2);

		for (int i = 0; i < g1->nodes.size(); i++)
		{
			if ((*core_1)[g1->nodes[i]] != -1)
			{
				int id = (*core_1)[g1->nodes[i]];
				inedges1 = &data->netWorkSet[id];
				outedges1 = &data->netWorkSet[id];
				//storage.getCommEdges(0, (*core_1)[(*g1->nodes)[i]], processId, rid, inedges1, outedges1);
				
				/*if ((*connects).find((*g1->nodes)[i]) != (*connects).end()
				&& (*connects)[(*g1->nodes)[i]].find(node1) != (*connects)[(*g1->nodes)[i]].end())
				{
				unordered_set<int> r;
				unordered_map<int, int> rec;
				for (const auto& o1 : *outedges1)
				{
				if (r.find(o1) == r.end())
				{
				if (storage.testgraph->nodeCommunity[o1] != storage.testgraph->nodeCommunity[node2])
				{
				rec[storage.testgraph->nodeCommunity[o1]]++;
				r.insert(o1);
				}
				}
				}
				for (const auto& o1 : *inedges1)
				{
				if (r.find(o1) == r.end())
				{
				if (storage.testgraph->nodeCommunity[o1] != storage.testgraph->nodeCommunity[node2])
				{
				rec[storage.testgraph->nodeCommunity[o1]]++;
				r.insert(o1);
				}
				}
				}
				for (const auto& o1 : *outedges2)
				{
				if (r.find(o1) == r.end())
				{
				if (storage.testgraph->nodeCommunity[o1] != storage.testgraph->nodeCommunity[node2])
				{
				rec[storage.testgraph->nodeCommunity[o1]]++;
				r.insert(o1);
				}
				}
				}
				for (const auto& o1 : *inedges2)
				{
				if (r.find(o1) == r.end())
				{
				if (storage.testgraph->nodeCommunity[o1] != storage.testgraph->nodeCommunity[node2])
				{
				rec[storage.testgraph->nodeCommunity[o1]]++;
				r.insert(o1);
				}
				}
				}

				for (const auto& m : (*connects)[(*g1->nodes)[i]][node1])
				{
				if (m.second > rec[m.first])
				{
				return false;
				}
				}
				}*/

				if ((*oomessage).find(g1->nodes[i]) != (*oomessage).end()
					&& (*oomessage)[g1->nodes[i]].find(node1) != (*oomessage)[g1->nodes[i]].end())
				{
					int cid = (*distributionplan)[node1];
					unordered_map<int, int> record;
					for (const auto& o1 : *outedges1)
					{
						if ((*inedges2).find(o1.first) != (*inedges2).end())
						{
							if (data->inMemory)
							{
								int c = data->nodeInfo[o1.first][0];
								//for (const auto& c : testgraph->nodeCommunitySet[o1])
								//{
									if (c != cid)
									{
										record[c]++;
									}
								//}
								/*if (storage.testgraph->nodeCommunity[o1] != comm_id)
								{
								record[storage.testgraph->nodeCommunity[o1]]++;
								}*/
							}
							else
							{
								//int o1comm = storage.GetNodeCommunity(to_string(o1).c_str());
								//if (o1comm != cid)
								//{
								//	record[o1comm]++;
								//}
							}
						}
					}

					for (const auto& m : (*oomessage)[g1->nodes[i]][node1])
					{
						if (m.second > record[m.first])
						{
							return false;
						}
					}
				}

				if ((*oomessage).find(node1) != (*oomessage).end()
					&& (*oomessage)[node1].find(g1->nodes[i]) != (*oomessage)[node1].end())
				{
					int cid = (*distributionplan)[node1];
					unordered_map<int, int> record;
					for (const auto& o2 : *outedges2)
					{
						if ((*inedges1).find(o2.first) != (*inedges1).end())
						{
							if (data->inMemory)
							{
								int c = data->nodeInfo[o2.first][0];
								//for (const auto& c : storage.testgraph->nodeCommunitySet[o2])
								{
									if (c != cid)
									{
										record[c]++;
									}
								}
								/*if (storage.testgraph->nodeCommunity[o2] != storage.testgraph->nodeCommunity[node2])
								{
								record[storage.testgraph->nodeCommunity[o2]]++;
								}*/
							}
							else
							{
								//int o2comm = storage.GetNodeCommunity(to_string(o2).c_str());
								//if (o2comm != cid)
								//{
								//	record[o2comm]++;
								//}
							}
						}
					}

					for (const auto& m : (*oomessage)[node1][g1->nodes[i]])
					{
						if (m.second > record[m.first])
						{
							return false;
						}
					}
				}

				if ((*oimessage).find(g1->nodes[i]) != (*oimessage).end()
					&& (*oimessage)[g1->nodes[i]].find(node1) != (*oimessage)[g1->nodes[i]].end())
				{
					int cid = (*distributionplan)[node1];
					unordered_map<int, int> record;
					for (const auto& o1 : *outedges1)
					{
						if ((*outedges2).find(o1.first) != (*outedges2).end())
						{
							if (data->inMemory)
							{
								int c = data->nodeInfo[o1.first][0];
								//for (const auto& c : storage.testgraph->nodeCommunitySet[o1])
								{
									if (c != cid)
									{
										record[c]++;
									}
								}
								/*
								if (storage.testgraph->nodeCommunity[o1] != storage.testgraph->nodeCommunity[node2])
								{
								record[storage.testgraph->nodeCommunity[o1]]++;
								}*/
							}
							else
							{
								//int o1comm = storage.GetNodeCommunity(to_string(o1).c_str());
								//if (o1comm != cid)
								//{
								//	record[o1comm]++;
								//}
							}
						}
					}

					for (const auto& m : (*oimessage)[g1->nodes[i]][node1])
					{
						if (m.second > record[m.first])
						{
							return false;
						}
					}
				}

				if ((*iomessage).find(g1->nodes[i]) != (*iomessage).end()
					&& (*iomessage)[g1->nodes[i]].find(node1) != (*iomessage)[g1->nodes[i]].end())
				{
					int cid = (*distributionplan)[node1];
					unordered_map<int, int> record;
					for (const auto& o1 : *inedges1)
					{
						if ((*inedges2).find(o1.first) != (*inedges2).end())
						{
							if (data->inMemory)
							{
								int c = data->nodeInfo[o1.first][0];
								//for (const auto& c : storage.testgraph->nodeCommunitySet[o1])
								{
									if (c != cid)
									{
										record[c]++;
									}
								}
								/*
								if (storage.testgraph->nodeCommunity[o1] != storage.testgraph->nodeCommunity[node2])
								{
								record[storage.testgraph->nodeCommunity[o1]]++;
								}*/
							}
							else
							{
								//int o1comm = storage.GetNodeCommunity(to_string(o1).c_str());
								//if (o1comm != cid)
								//{
								//	record[o1comm]++;
								//}
							}
						}
					}

					for (const auto& m : (*iomessage)[g1->nodes[i]][node1])
					{
						if (m.second > record[m.first])
						{
							return false;
						}
					}
				}
			}
		}

		// Check the 'out' edges of node1
		for (const auto& oe : (*g1->outedges)[node1])
		{
			other1 = oe.first;
			if ((*in_1).find(other1) == (*in_1).end())
			{
				continue;
			}
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
		for (const auto& ie : (*g1->inedges)[node1])
		{
			other1 = ie.first;
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

		for (const auto& outnode : *outedges2)
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
				//return false;
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
		for (const auto& innode : *inedges2)
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
				//return false;
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

		return termin1 <= termin2 && termout1 <= termout2
			&& (termin1 + termout1 + new1) <= (termin2 + termout2 + new2);
	}
	else
	{
		// Check the 'out' edges of node1
		for (const auto& oe : (*g1->outedges)[node1])
		{
			other1 = oe.first;
			if ((*in_1).find(other1) == (*in_1).end())
			{
				continue;
			}
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
		for (const auto& ie : (*g1->inedges)[node1])
		{
			other1 = ie.first;
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

		unordered_map<int, vector<int>>* outedges = &data->netWorkSet[node2];
		unordered_map<int, vector<int>>* inedges = &data->netWorkSet[node2];
		//storage.getCommEdges(0, node2, processId, rid, inedges, outedges);

		for (const auto& outnode : *outedges)
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
				//return false;
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
		for (const auto& innode : *inedges)
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
				//return false;
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

		return termin1 <= termin2 && termout1 <= termout2
			&& (termin1 + termout1 + new1) <= (termin2 + termout2 + new2);
	}
}

void VF2StateComm::AddPair(MemoryGraph* data, int node1, int node2)
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

	for (const auto& oe : (*g1->outedges)[node1])
	{
		int other = oe.first;
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
	unordered_map<int, vector<int>>* outedges = &data->netWorkSet[node2];
	unordered_map<int, vector<int>>* inedges = &data->netWorkSet[node2];
	//storage.getCommEdges(0, node2, processId, rid, inedges, outedges);

	for (const auto& innode : *inedges)
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

	for (const auto& outnode : *outedges)
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
}

void VF2StateComm::GetCoreSet(vector<string>& ans)
{
	string s = "";

	for (int i = 0; i < n1; i++)
	{
		s += to_string((*core_1)[g1->nodes[i]]) + " ";
	}

	ans.push_back(s);
}

void VF2StateComm::GetCoreSet(vector<int>& ans)
{
	for (int i = 0; i < n1; i++)
	{
		ans.push_back((*core_1)[g1->nodes[i]]);
	}
}

void VF2StateComm::GetCoreSet(MemoryGraph* data, vector<int>& ans)
{
	AutoFillFreeNodes(data, ans, 0);
}

void VF2StateComm::GetCoreSet(vector<vector<int>>& ans, bool storeAns)
{
	vector<int> temp;

	for (int i = 0; i < n1; i++)
	{
		temp.push_back((*core_1)[g1->nodes[i]]);
	}

	if (storeAns)
	{
		//ans.push_back(temp);
	}
}

void VF2StateComm::GetCoreSet(vector<unordered_map<int, int>>& ans)
{
	unordered_map<int, int> temp;

	int i, j;
	for (i = 0; i < n1; i++)
	{
		if ((*core_1)[g1->nodes[i]] != -1)
		{
			temp[g1->nodes[i]] = (*core_1)[g1->nodes[i]];
		}
	}

	ans.push_back(temp);
}

void VF2StateComm::GetCoreSet(set<map<int, int>>& ans)
{
	map<int, int> temp;

	int i, j;
	for (i = 0; i < n1; i++)
	{
		if ((*core_1)[g1->nodes[i]] != -1)
		{
			temp[g1->nodes[i]] = (*core_1)[g1->nodes[i]];
		}
	}

	ans.insert(temp);
}

VF2StateComm* VF2StateComm::Clone()
{
	return new VF2StateComm(*this);
}

void VF2StateComm::BackTrack(MemoryGraph* data)
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
			if ((*in_1).find(ie.first) == (*in_1).end())
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
			if ((*in_1).find(oe.first) == (*in_1).end())
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

		int rid;
		unordered_map<int, vector<int>>* outedges = &data->netWorkSet[node2];
		unordered_map<int, vector<int>>* inedges = &data->netWorkSet[node2];
		//storage.getCommEdges(0, node2, processId, rid, inedges, outedges);

		for (const auto& innode : *inedges)
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

		for (const auto& outnode : *outedges)
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
		if (in_2.find(innode) == in_2.end())
		{
		continue;
		}

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
		if (out_2.find(outnode) == out_2.end())
		{
		continue;
		}

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

void VF2StateComm::AutoFillFreeNodes(MemoryGraph* data, vector<int>& ans, int level)
{
	if (level == (*autofillnodes).size())
	{
		for (int i = 0; i < (*allnodes).size(); i++)
		{
			ans.push_back((*core_1)[(*allnodes)[i]]);
		}

		return;
	}

	int node_id = (*autofillnodes)[level];
	vector<int> area;
	bool can = true;

	for (const auto n : *core_1)
	{
		if (n.second == -1)
		{
			continue;
		}

		int rid;
		unordered_map<int, vector<int>>* inedges = NULL;
		unordered_map<int, vector<int>>* outedges = NULL;

		if (g1->HasEdge(node_id, n.first))
		{
			//storage.getCommEdges(0, n.second, processId, rid, inedges, outedges);
			outedges = &data->netWorkSet[n.second];
			inedges = &data->netWorkSet[n.second];

			if (area.empty())
			{
				for (const auto& node : *inedges)
				{
					if (data->inMemory)
					{
						if (data->nodeInfo[node.first][0] == comm_id
							&& (*core_2)[node.first] == -1)
						{
							area.push_back(node.first);
						}
					}
					else
					{
						//int o1comm = storage.GetNodeCommunity(to_string(node).c_str());
						//if (o1comm == comm_id && (*core_2)[node] == -1)
						//{
						//	area.push_back(node);
						//}
					}
				}
			}
			else
			{
				vector<int> newarea;
				for (int i = 0; i < area.size(); i++)
				{
					if ((*inedges).find(area[i]) != (*inedges).end()
						&& (*core_2)[area[i]] == -1)
					{
						newarea.push_back(area[i]);
					}
				}
				area = newarea;
			}

			if (area.empty())
			{
				can = false;
				break;
			}
		}
		if (g1->HasEdge(n.first, node_id))
		{
			if (outedges == NULL)
			{
				//storage.getCommEdges(0, n.second, processId, rid, inedges, outedges);
				outedges = &data->netWorkSet[n.second];
				inedges = &data->netWorkSet[n.second];
			}

			if (area.empty())
			{
				for (const auto& node : *outedges)
				{
					if (data->inMemory)
					{
						if (data->nodeInfo[node.first][0] == comm_id
						&& (*core_2)[node.first] == -1)
						{
							area.push_back(node.first);
						}
					}
					else
					{
						//int o1comm = storage.GetNodeCommunity(to_string(node).c_str());
						//if (o1comm == comm_id && (*core_2)[node] == -1)
						//{
						//	area.push_back(node);
						//}
					}
				}
			}
			else
			{
				vector<int> newarea;
				for (int i = 0; i < area.size(); i++)
				{
					if ((*outedges).find(area[i]) != (*outedges).end()
						&& (*core_2)[area[i]] == -1)
					{
						newarea.push_back(area[i]);
					}
				}
				area = newarea;
			}

			if (area.empty())
			{
				can = false;
				break;
			}
		}
	}

	if (!can)
	{
		return;
	}

	if (area.empty())
	{
		for (const auto& n : data->communityNodes[comm_id])
		{
			if ((*core_2)[n] != -1)
			{
				continue;
			}
			(*core_1)[node_id] = n;
			(*core_2)[n] = node_id;
			AutoFillFreeNodes(data, ans, level + 1);
			(*core_2)[n] = -1;
		}
	}
	else
	{
		for (int i = 0; i < area.size(); i++)
		{
			(*core_1)[node_id] = area[i];
			(*core_2)[area[i]] = node_id;
			AutoFillFreeNodes(data, ans, level + 1);
			(*core_2)[area[i]] = -1;
		}
	}

	(*core_1)[node_id] = -1;
}
#include "LPAT.h"

LPAT::LPAT(int itertime)
{
	iter_time = itertime;
}

LPAT::~LPAT()
{
	for (int i = 0; i < nodes.size(); i++)
		delete nodes[i];
}

void LPAT::Update(unordered_map<int, unordered_map<int, vector<int>>>&network, unordered_map<int, int>& nodeCommunity)
{
	int n = network.size();
	vector<int> ids;
	ids.clear();

	set<int> record;

	unordered_map<int, unordered_map<int, vector<int>>>::iterator it = network.begin();
	int count = 0;
	while (it != network.end())
	{
		record.insert(it->first);
		Node* node = new Node();
		node->id = it->first;

		if (nodeCommunity.find(it->first) != nodeCommunity.end())
		{
			node->cid = nodeCommunity[it->first];
		}
		else
			node->cid = it->first;

		ids.push_back(node->id);
		nodes[node->id] = node;

		for (const auto& n2 : it->second)
		{
			if (record.find(n2.first) == record.end())
			{
				record.insert(n2.first);

				Node* node = new Node();
				node->id = n2.first;

				if (nodeCommunity.find(n2.first) != nodeCommunity.end())
				{
					node->cid = nodeCommunity[n2.first];
				}
				else
					node->cid = it->first;

				ids.push_back(node->id);
				nodes[node->id] = node;
			}
		}

		it++;
	}

	int* sequence = new int[n];
	for (int i = 0; i < n; i++)
		sequence[i] = i;
	Node* node;
	for (int i = 0; i < iter_time; i++)
	{
		cout << "iteration time :" << i + 1 << endl;
		Shuffle(sequence, n);

		for (int j = 0; j < n; j++)
		{
			node = nodes[ids[sequence[j]]];
			if (nodeCommunity.find(node->id) == nodeCommunity.end())
				node->cid = UpdateNaive(node->id, network, nodeCommunity);
		}
	}
	//communityNode.clear();
	for (int i = 0; i < nodes.size(); i++)
		nodeCommunity[nodes[ids[i]]->id] = nodes[ids[i]]->cid;
		//communityNode[nodes[ids[i]]->cid].insert(nodes[ids[i]]->id);

	delete[] sequence;
}

void LPAT::Proceed(unordered_map<int, vector<int>>&network)
{
	int n = network.size();
	vector<int> ids;
	ids.clear();

	unordered_map<int, vector<int>>::iterator it = network.begin();
	int count = 0;
	while (it != network.end())
	{
		Node* node = new Node();
		node->id = it->first;
		node->cid = it->first;
		nodes[node->id] = node;
		ids.push_back(node->id);
		it++;
	}

	int* sequence = new int[n];
	for (int i = 0; i < n; i++)
		sequence[i] = i;
	Node* node;
	for (int i = 0; i < iter_time; i++)
	{
		cout << "iteration time :" << i + 1 << endl;
		Shuffle(sequence, n);

		for (int j = 0; j < n; j++)
		{
			node = nodes[ids[sequence[j]]];
			node->cid = UpdateNaive(node->id, network);
		}
	}
	//comunityNode.clear();
	//for (int i = 0; i < nodes.size(); i++)
	//	comunityNode[nodes[ids[i]]->cid].insert(nodes[ids[i]]->id);

}

void LPAT::Shuffle(int* seq, int n)
{
	list<int>ll;
	for (int i = 0; i < n; i++)
		ll.push_back(i);

	list<int>::iterator pos;
	for (int i = 0; i < n; i++)
	{
		int t = rand() % ll.size();
		pos = ll.begin();
		for (int j = 0; j < t; j++)
			pos++;

		seq[i] = *pos;
		ll.remove(seq[i]);
	}
}

int LPAT::UpdateNaive(int id, unordered_map<int, vector<int>>&network)
{
	unordered_map<int, float>count;
	for (int i = 0; i < network[id].size(); i++)
	{
		int endNode = network[id][i];
		count[nodes[endNode]->cid]++;
	}
	return GetFrequentLabel(count);
}

int LPAT::UpdateNaive(int id, unordered_map<int, unordered_map<int, vector<int>>>&network, unordered_map<int, int>& nodeCommunity)
{
	unordered_map<int, float>count;
	for(const auto& endNode : network[id])
	{
		int cid = nodes[endNode.first]->cid;
		count[cid]++;
	}
	return GetFrequentLabel(count);
}

static bool cmp_value_float(const pair<int, float>& i, const pair<int, float>& j)
{
	return i.second > j.second;
}

int LPAT::GetFrequentLabel(unordered_map<int, float>&count)
{
	vector<pair<int, float> >vec;

	unordered_map <int, float>::iterator iter;

	for (iter = count.begin(); iter != count.end(); iter++)
	{
		pair<int, float> p = *iter;
		vec.push_back(p);
	}

	sort(vec.begin(), vec.end(), cmp_value_float);
	vector<int> candidates;

	float max_f = vec[0].second;

	for (int i = 0; i < vec.size(); i++)
	{
		pair<int, float> p = vec[i];

		if (p.second != max_f)
			break;
		candidates.push_back(p.first);
	}

	int pos = 0;
	if (!candidates.empty())
		pos = rand() % candidates.size();

	return candidates[pos];

}

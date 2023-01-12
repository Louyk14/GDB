#include "probability_strategy.h"

void NodeProbabilityStrategy::evaluateProbabilities(MemoryGraph* source) {
	int i;
	int node_count;
	int attr;

	map<int, int> labelsmap;

	if (!source)
		return;

	out_deg_size = source->outMaxDegree + 1;
	in_deg_size = source->inMaxDegree + 1;
	degree_size = source->maxDegree + 1;
	node_count = source->nodes.size();


	//std::cout<<"\n" <<out_deg_size<<" - " << in_deg_size << " - " << degree_size ;
	vector<int> out_deg_counter(out_deg_size, 0);
	vector<int> in_deg_counter(in_deg_size, 0);
	vector<int> total_deg_counter(degree_size, 0);

	out_deg = new double[out_deg_size];
	in_deg = new double[in_deg_size];
	degree = new double[degree_size];

	for (i = 0; i < node_count; i++) {
		//Reading attributes
		int id = i + 1;
		int out_deg = source->netWorkSet[id].size();// OutEdgeCount(i);
		int in_deg = source->netWorkSet[id].size();// InEdgeCount(i);
		int total_deg = in_deg + out_deg;
		attr = source->nodeInfo[id][1];

		//td::cout << "\nNode " << i << ": " << out_deg << " - " << in_deg << " - " << total_deg;

		out_deg_counter[out_deg]++;
		in_deg_counter[in_deg]++;
		total_deg_counter[total_deg]++;

		if (labelsmap.count(attr)) {
			labelsmap[attr]++;
		}
		else {
			labelsmap[attr] = 1;
		}
	}

	//std::cout << "\nOut Deg";
	for (i = 0; i < out_deg_size; i++) {
		out_deg[i] = ((double)out_deg_counter[i]) / node_count;
		//std::cout << "\n" << i << ": " << out_deg_counter[i];
	}

	//std::cout << "\nIn Deg";
	for (i = 0; i < in_deg_size; i++) {
		in_deg[i] = ((double)in_deg_counter[i]) / node_count;
		//std::cout << "\n" << i << ": " << in_deg_counter[i];
	}

	//std::cout << "\nTot Deg";
	for (i = 0; i < degree_size; i++) {
		degree[i] = ((double)total_deg_counter[i]) / node_count;
		//std::cout << "\n" << i << ": " << total_deg_counter[i];
	}

	//for (typename std::map<int, int>::iterator iter = labelsmap.begin(); iter != labelsmap.end(); ++iter)
	for (std::map<int, int>::iterator iter = labelsmap.begin(); iter != labelsmap.end(); ++iter)
	{
		int n = iter->first;
		labels[n] = ((double)labelsmap[n]) / node_count;
	}
}

/*
void NodeProbabilityStrategy::evaluateProbabilities(MemoryGraph* source) {
	int i;
	int node_count;
	int attr;

	map<int, int> labelsmap;

	if (!source)
		return;

	out_deg_size = source->outMaxDegree + 1;
	in_deg_size = source->inMaxDegree + 1;
	degree_size = source->maxDegree + 1;
	node_count = source->nodenum;


	//std::cout<<"\n" <<out_deg_size<<" - " << in_deg_size << " - " << degree_size ;
	vector<int> out_deg_counter(out_deg_size, 0);
	vector<int> in_deg_counter(in_deg_size, 0);
	vector<int> total_deg_counter(degree_size, 0);

	out_deg = new double[out_deg_size];
	in_deg = new double[in_deg_size];
	degree = new double[degree_size];

	for (i = 0; i < node_count; i++) {
		//Reading attributes
		int id = i + 1;
		int out_deg = (*source->outedges)[id].size();// OutEdgeCount(i);
		int in_deg = (*source->inedges)[id].size();// InEdgeCount(i);
		int total_deg = in_deg + out_deg;
		attr = source->nodeLabels[id];

		//td::cout << "\nNode " << i << ": " << out_deg << " - " << in_deg << " - " << total_deg;

		out_deg_counter[out_deg]++;
		in_deg_counter[in_deg]++;
		total_deg_counter[total_deg]++;

		if (labelsmap.count(attr)) {
			labelsmap[attr]++;
		}
		else {
			labelsmap[attr] = 1;
		}
	}

	//std::cout << "\nOut Deg";
	for (i = 0; i < out_deg_size; i++) {
		out_deg[i] = ((double)out_deg_counter[i]) / node_count;
		//std::cout << "\n" << i << ": " << out_deg_counter[i];
	}

	//std::cout << "\nIn Deg";
	for (i = 0; i < in_deg_size; i++) {
		in_deg[i] = ((double)in_deg_counter[i]) / node_count;
		//std::cout << "\n" << i << ": " << in_deg_counter[i];
	}

	//std::cout << "\nTot Deg";
	for (i = 0; i < degree_size; i++) {
		degree[i] = ((double)total_deg_counter[i]) / node_count;
		//std::cout << "\n" << i << ": " << total_deg_counter[i];
	}

	//for (typename std::map<int, int>::iterator iter = labelsmap.begin(); iter != labelsmap.end(); ++iter)
	for (std::map<int, int>::iterator iter = labelsmap.begin(); iter != labelsmap.end(); ++iter)
	{
		int n = iter->first;
		labels[n] = ((double)labelsmap[n]) / node_count;
	}
}
*/

double SubIsoNodeProbability::getProbability(MemoryGraph* g, int id) {
	double node_p;
	int node_out_deg, node_in_deg, node_deg;
	int node_attr;
	node_out_deg = (*g->outedges)[id].size();
	node_in_deg = (*g->inedges)[id].size();
	node_deg = node_out_deg + node_in_deg;
	node_attr = g->nodeLabels[id];

	//Sum of probability
	double out_deg_p_sum, in_deg_p_sum, tot_deg_p_sum;
	out_deg_p_sum = in_deg_p_sum = tot_deg_p_sum = 0;

	for (int i = this->out_deg_size - 1; i >= node_out_deg; i--) {
		out_deg_p_sum += this->out_deg[i];
	}

	for (int i = this->in_deg_size - 1; i >= node_in_deg; i--) {
		in_deg_p_sum += this->in_deg[i];
	}

	for (int i = this->degree_size - 1; i >= node_deg; i--) {
		tot_deg_p_sum += this->degree[i];
	}

	node_p = out_deg_p_sum*in_deg_p_sum*/*tot_deg_p_sum**/this->labels[node_attr];

	return node_p;
}
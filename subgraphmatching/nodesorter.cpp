#include "nodesorter.h"

VF3NodeSorter::VF3NodeSorter(MemoryGraph* target)
{
	probability = new SubIsoNodeProbability(target);
}

/*
VF3NodeSorter::VF3NodeSorter(MemoryGraph* target)
{
	probability = new SubIsoNodeProbability(target);
}
*/

VF3NodeSorter::~VF3NodeSorter()
{
	delete probability;
}

vector<int> VF3NodeSorter::SortNodes(MemoryGraph* pattern)
{
	int nodeCount;
	int i;
	nodeCount = pattern->nodeNum;
	vector<int> nodes_order; //Output vector with sorted nodes

							 //We use two structures the fist used to quickly edit the deg_m of a node by its index
							 //The second to perform a priority queue by means a max heap
	snode_t* nodes = new snode_t[nodeCount + 1];
	//mypriority prio; //Heap of references
	vector<snode_t*> node_star;
	vector<snode_t*> candidates; //Node candidate for the addition
	vector<snode_t*>::iterator candidate_it;
	vector<snode_t*>::iterator max_node;
	//Initializing the node vector for sorting

	for (i = 1; i <= nodeCount; i++)
	{

		nodes[i].id = i;
		nodes[i].deg_m = 0; //Dynamically updated
		nodes[i].deg = (*pattern->outedges)[i].size() + (*pattern->inedges)[i].size();
		nodes[i].deg_neigh = 0;
		nodes[i].probability = probability->getProbability(pattern, i);
		nodes[i].used = false;			//The node has been sorted
		nodes[i].in_candidate = false;	//The node has to be ignored as candidate
		nodes[i].vis_count = 0;
		nodes[i].neig_count = 0;
		nodes[i].unv_count = 0;
		node_star.push_back(&nodes[i]);
	}

	int n = 1;
	candidate_it = min_element(node_star.begin(), node_star.end(), CompareNodeStarProbability());
	int top = (*candidate_it)->id;
	AddNodeToSortedSet(pattern, top, n, nodes, candidates, nodes_order);

	//Getting the first node of the heap
	for (; n < nodeCount; n++) {
		candidate_it = min_element(candidates.begin(), candidates.end(), CompareNodeStar());

		//Searching for remaining user
		if ((*candidate_it)->used)
		{
			candidate_it = find_if(node_star.begin(), node_star.end(), FindUnused());
			AddNodeToSortedSet(pattern, (*candidate_it)->id, n, nodes, candidates, nodes_order);
		}
		else if (candidate_it != candidates.end())
		{
			AddNodeToSortedSet(pattern, (*candidate_it)->id, n, nodes, candidates, nodes_order);
		}
	}

	delete[] nodes;
	return nodes_order;

}

void VF3NodeSorter::AddNodeToSortedSet(MemoryGraph* pattern,
	int node, int level, snode_t* nodes, vector<snode_t*> &candidates, vector<int> &nodes_order)
{
	int i, neigh;
	int in1_count, out1_count;


	nodes_order.push_back(node);
	nodes[node].used = true;
	nodes[node].in_candidate = true;
	nodes[node].deg_m = 0;		//Cleaning Deg Count for inserted nodes

								//Updating Terminal set size count And degree
	in1_count = (*pattern->inedges)[node].size();
	out1_count = (*pattern->outedges)[node].size();

	//Updating Inner Nodes not yet inserted
	//for (i = 0; i < in1_count; i++)
	for (const auto& neigh : (*pattern->inedges)[node])
	{
		//Getting Neighborhood
		//neigh = pattern->GetInEdge(node, i);
		if (!nodes[neigh.first].used)
			nodes[neigh.first].deg_m++;
		if (!nodes[neigh.first].in_candidate) {
			nodes[neigh.first].in_candidate = true;
			candidates.push_back(&nodes[neigh.first]);
		}

	}

	//Updating Outer Nodes not yet insered
	//for (i = 0; i < out1_count; i++)
	for (const auto& neigh : (*pattern->outedges)[node])
	{
		//Getting Neighborhood
		//neigh = pattern->GetOutEdge(node, i);
		if (!nodes[neigh.first].used)
			nodes[neigh.first].deg_m++;
		if (!nodes[neigh.first].in_candidate) {
			nodes[neigh.first].in_candidate = true;
			candidates.push_back(&nodes[neigh.first]);
		}
	}

}
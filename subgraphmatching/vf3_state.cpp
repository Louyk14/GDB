#include "vf3_state.h"

void VF3State::print_terminal(int c) {
	std::cout << "\nClass: " << c << " Core_len: " << core_len_c[c];
	std::cout << " t1both_len: " << t1both_len_c[core_len][c] << " t2both_len " << t2both_len_c[c];
	std::cout << " t1out_len: " << t1out_len_c[core_len][c] << " t2out_len " << t2out_len_c[c];
	std::cout << " t1in_len: " << t1in_len_c[core_len][c] << " t2in_len " << t2in_len_c[c];

}

/*----------------------------------------------------------
* VF3State::VF3State(g1, g2)
* Constructor. Makes an empty state.
---------------------------------------------------------*/

VF3State::VF3State(MemoryGraph *ag1, MemoryGraph *ag2, Match* m, int nclass, int* order)
{
	//assert(class_1 != NULL && class_2 != NULL);

	//VF3State::instance_count = 1;
	g1 = ag1;
	g2 = ag2;
	n1 = g1->nodeNum;
	n2 = g2->nodes.size();
	gm = m;

	this->order = order;
	//this->class_1 = class_1;
	//this->class_2 = class_2;
	this->classes_count = nclass;

	core_len = orig_core_len = 0;
	t2both_len = t2in_len = t2out_len = 0;

	//Creazione degli insiemi
	t1both_len = new int[n1 + 1];
	t1in_len = new int[n1 + 1];
	t1out_len = new int[n1 + 1];

	termin1 = (int*)calloc(n1, sizeof(int));
	termout1 = (int*)calloc(n1, sizeof(int));
	new1 = (int*)calloc(n1, sizeof(int));

	t1both_len_c = (int**)malloc((n1 + 1) * sizeof(int*));
	t1in_len_c = (int**)malloc((n1 + 1) * sizeof(int*));
	t1out_len_c = (int**)malloc((n1 + 1) * sizeof(int*));


	termin1_c = (int**)malloc(n1 * sizeof(int*));
	termout1_c = (int**)malloc(n1 * sizeof(int*));
	new1_c = (int**)malloc(n1 * sizeof(int*));

	core_len_c = (int*)calloc(classes_count, sizeof(int));
	t2both_len_c = (int*)calloc(classes_count, sizeof(int));
	t2in_len_c = (int*)calloc(classes_count, sizeof(int));
	t2out_len_c = (int*)calloc(classes_count, sizeof(int));
	termout2_c = new int[classes_count];
	termin2_c = new int[classes_count];
	new2_c = new int[classes_count];

	added_node1 = -1;

	core_1 = new int[n1 + 1];
	core_2 = new int[n2 + 1];
	in_2 = new int[n2 + 1];
	out_2 = new int[n2 + 1];
	dir = new node_dir_t[n1 + 1];
	predecessors = new int[n1 + 1];
	share_count = new long;

	int i;
	for (i = 0; i <= n1; i++)
	{
		if (i<n1) {
			termin1_c[i] = (int*)calloc(classes_count, sizeof(int));
			termout1_c[i] = (int*)calloc(classes_count, sizeof(int));
			new1_c[i] = (int*)calloc(classes_count, sizeof(int));
		}
		core_1[i] = -1;
		t1both_len_c[i] = (int*)calloc(classes_count, sizeof(int));
		t1in_len_c[i] = (int*)calloc(classes_count, sizeof(int));
		t1out_len_c[i] = (int*)calloc(classes_count, sizeof(int));
	}

	for (i = 1; i <= n2; i++)
	{
		core_2[i] = -1;
		in_2[i] = 0;
		out_2[i] = 0;
	}

	ComputeFirstGraphTraversing();
	*share_count = 1;
}


/*----------------------------------------------------------
* VF3State::VF3State(state)
* Copy constructor.
---------------------------------------------------------*/
VF3State::VF3State(const VF3State &state)
{
	g1 = state.g1;
	g2 = state.g2;
	n1 = state.n1;
	n2 = state.n2;
	gm = state.gm;

	order = state.order;
	//class_1 = state.class_1;
	//class_2 = state.class_2;
	classes_count = state.classes_count;
	//VF3State::instance_count++;

	core_len = orig_core_len = state.core_len;

	t1in_len = state.t1in_len;
	t1out_len = state.t1out_len;
	t1both_len = state.t1both_len;

	t2in_len = state.t2in_len;
	t2out_len = state.t2out_len;
	t2both_len = state.t2both_len;

	core_len_c = state.core_len_c;
	t1both_len_c = state.t1both_len_c;
	t2both_len_c = state.t2both_len_c;
	t1in_len_c = state.t1in_len_c;
	t2in_len_c = state.t2in_len_c;
	t1out_len_c = state.t1out_len_c;
	t2out_len_c = state.t2out_len_c;

	termout1_c = state.termout1_c;
	termout2_c = state.termout2_c;
	termin1_c = state.termin1_c;
	termin2_c = state.termin2_c;
	new1_c = state.new1_c;
	new2_c = state.new2_c;

	termin1 = state.termin1;
	termout1 = state.termout1;
	new1 = state.new1;

	added_node1 = -1;

	core_1 = state.core_1;
	core_2 = state.core_2;
	in_2 = state.in_2;
	out_2 = state.out_2;
	dir = state.dir;
	predecessors = state.predecessors;
	share_count = state.share_count;

	++ *share_count;

}


/*---------------------------------------------------------------
* VF3State::~VF3State()
* Destructor.
--------------------------------------------------------------*/
VF3State::~VF3State()
{

	if (-- *share_count > 0)
		BackTrack();

	if (*share_count == 0)
	{
		delete[] core_1;
		delete[] core_2;
		delete[] in_2;
		delete[] out_2;
		delete[] dir;
		delete[] predecessors;
		delete[] t1both_len;
		delete[] t1in_len;
		delete[] t1out_len;
		delete[] termin1;
		delete[] termout1;
		delete[] new1;

		for (int i = 0; i <= n1; i++) {
			delete[] t1both_len_c[i];
			delete[] t1in_len_c[i];
			delete[] t1out_len_c[i];
			if (i< n1) {
				delete[] termin1_c[i];
				delete[] termout1_c[i];
				delete[] new1_c[i];
			}
		}

		delete[] t1both_len_c;
		delete[] t1in_len_c;
		delete[] t1out_len_c;
		delete[] termin1_c;
		delete[] termout1_c;
		delete[] new1_c;
		delete[] t2both_len_c;
		delete[] t2in_len_c;
		delete[] t2out_len_c;
		delete[] core_len_c;
		delete[] termin2_c;
		delete[] termout2_c;
		delete[] new2_c;

		delete share_count;
	}
}

void VF3State::UpdateTerminalSetSize(int node, int level, bool* in_1, bool* out_1, bool* inserted) {
	int i, neigh, c_neigh;
	int in1_count, out1_count;

	//Updating Terminal set size count And degree
	in1_count = (*g1->inedges)[node].size();
	out1_count = (*g1->outedges)[node].size();

	//Updating Inner Nodes not yet inserted
	//for (i = 0; i < in1_count; i++)
	//{
	for (const auto& neigh : (*g1->inedges)[node])
	{
		//Getting Neighborhood
		//neigh = g1->GetInEdge(node, i);
		c_neigh = g1->nodeLabels[neigh.first];

		if (!inserted[neigh.first])
		{
			if (in_1[neigh.first]) {
				termin1[level]++;
				termin1_c[level][c_neigh]++;
			}
			if (out_1[neigh.first]) {
				termout1[level]++;
				termout1_c[level][c_neigh]++;
			}
			if (!in_1[neigh.first] && !out_1[neigh.first]) {
				new1[level]++;
				new1_c[level][c_neigh]++;
			}
		}
	}

	//Updating Outer Nodes not yet insered
	//for (i = 0; i < out1_count; i++)
	for (const auto& neigh : (*g1->outedges)[node])
	{
		//Getting Neighborhood
		//neigh = g1->GetOutEdge(node, i);
		c_neigh = g1->nodeLabels[neigh.first];
		if (!inserted[neigh.first])
		{
			if (in_1[neigh.first]) {
				termin1[level]++;
				termin1_c[level][c_neigh]++;
			}
			if (out_1[neigh.first]) {
				termout1[level]++;
				termout1_c[level][c_neigh]++;
			}
			if (!in_1[neigh.first] && !out_1[neigh.first]) {
				new1[level]++;
				new1_c[level][c_neigh]++;
			}
		}
	}
}


//Provare ad avere in1 ed ou1 predeterminati, senza doverlo calcolare ad ogni iterazione
//La loro dimensione ad ogni livello dell'albero di ricerca e' predeterminato
//In questo modo mi basta conoscere solo l'ordine di scelta e la dimensione di in1 ed out1
void VF3State::ComputeFirstGraphTraversing() {
	//The algorithm start with the node with the maximum degree
	int depth, i;
	int node;	//Current Node
	int node_c; //Class of the current node
	bool* inserted = new bool[n1 + 1];
	bool *in, *out; //Internal Terminal Set used for updating the size of
	in = new bool[n1 + 1];
	out = new bool[n1 + 1];

	//Init vectors and variables
	node = 0;
	node_c = 0;

	t1in_len[0] = 0;
	t1out_len[0] = 0;
	t1both_len[0] = 0;

	for (i = 1; i <= n1; i++)
	{
		in[i] = false;
		out[i] = false;
		dir[i] = NODE_DIR_NONE;
		inserted[i] = false;
		predecessors[i] = -1;
	}

	/* Following the imposed node order */
	for (depth = 0; depth < n1; depth++)
	{
		node = order[depth];
		node_c = g1->nodeLabels[node];
		inserted[node] = true;

		UpdateTerminalSetSize(node, depth, in, out, inserted);

		//Updating counters for next step
		t1in_len[depth + 1] = t1in_len[depth];
		t1out_len[depth + 1] = t1out_len[depth];
		t1both_len[depth + 1] = t1both_len[depth];
		for (int j = 0; j < classes_count; j++)
		{
			t1in_len_c[depth + 1][j] = t1in_len_c[depth][j];
			t1out_len_c[depth + 1][j] = t1out_len_c[depth][j];
			t1both_len_c[depth + 1][j] = t1both_len_c[depth][j];
		}
		//Inserting the node
		//Terminal set sizes depends on the depth
		// < depth non sono nell'insieme
		// >= depth sono nell'insieme
		if (!in[node])
		{
			in[node] = true;
			t1in_len[depth + 1]++;
			t1in_len_c[depth + 1][node_c]++;
			if (out[node]) {
				t1both_len[depth + 1]++;
				t1both_len_c[depth + 1][node_c]++;
			}
		}

		if (!out[node])
		{
			out[node] = true;
			t1out_len[depth + 1]++;
			t1out_len_c[depth + 1][node_c]++;
			if (in[node]) {
				t1both_len[depth + 1]++;
				t1both_len_c[depth + 1][node_c]++;
			}
		}

		//Updating terminal sets
		int i, other, other_c;
		other_c = -1;
		//int insize = g1->inNetWorkSet[node].size();

		for (const auto& other : (*g1->inedges)[node])
			//for (i = 0; i<insize; i++)
		{
			//other = g1->GetInEdge(node, i);
			if (!in[other.first])
			{
				other_c = g1->nodeLabels[other.first];
				in[other.first] = true;
				t1in_len[depth + 1]++;
				t1in_len_c[depth + 1][other_c]++;
				if (!inserted[other.first])
				{
					//dir[other] = NODE_DIR_IN;
					if (predecessors[other.first] == -1)
					{
						dir[other.first] = NODE_DIR_IN;
						predecessors[other.first] = node;
					}
				}
				if (out[other.first]) {
					t1both_len[depth + 1]++;
					t1both_len_c[depth + 1][other_c]++;
					//if(!inserted[other])
					//dir[other] = NODE_DIR_BOTH;
				}
			}
		}

		for (const auto& other : (*g1->outedges)[node])
			//for (i = 0; i<g1->OutEdgeCount(node); i++)
		{
			//other = g1->GetOutEdge(node, i);
			if (!out[other.first])
			{
				other_c = g1->nodeLabels[other.first];
				out[other.first] = true;
				t1out_len[depth + 1]++;
				t1out_len_c[depth + 1][other_c]++;
				if (!inserted[other.first])
				{
					//dir[other] = NODE_DIR_OUT;
					if (predecessors[other.first] == -1)
					{
						predecessors[other.first] = node;
						dir[other.first] = NODE_DIR_OUT;
					}
				}
				if (in[other.first]) {
					t1both_len[depth + 1]++;
					t1both_len_c[depth + 1][other_c]++;
					//if(!inserted[other])
					//dir[other] = NODE_DIR_BOTH;
				}
			}
		}

	}

	delete[] in;
	delete[] out;
	delete[] inserted;
}

bool VF3State::NextPair(int *pn1, int *pn2, int prev_n1, int prev_n2)
{
	int curr_n1;
	int pred_pair; //Node mapped with the predecessor
	int pred_set_size = 0;
	int c = 0;

	//core_len indica la profondondita' della ricerca
	curr_n1 = order[core_len];
	c = g1->nodeLabels[curr_n1];

	if (predecessors[curr_n1] != -1)
	{
		if (prev_n2 == -1)
			last_candidate_index = 0;
		else {
			last_candidate_index++; //Next Element
		}

		pred_pair = core_1[predecessors[curr_n1]];
		switch (dir[curr_n1])
		{
		case NODE_DIR_IN:
			pred_set_size = g2->netWorkSet[pred_pair].size();// g2->InEdgeCount(pred_pair);

			while (last_candidate_index < pred_set_size)
			{
				prev_n2 = g2->netWorkVec[pred_pair][last_candidate_index];
				if (core_2[prev_n2] != -1 || g2->nodeInfo[prev_n2][1] != c)
					last_candidate_index++;
				else
					break;
			}

			break;

		case NODE_DIR_OUT:
			pred_set_size = g2->netWorkSet[pred_pair].size();

			while (last_candidate_index < pred_set_size)
			{
				prev_n2 = g2->netWorkVec[pred_pair][last_candidate_index];
				if (core_2[prev_n2] != -1 || g2->nodeInfo[prev_n2][1] != c)
					last_candidate_index++;
				else
					break;
			}

			break;
		}

		if (last_candidate_index >= pred_set_size)
			return false;

	}
	else
	{
		//for nodes without any parent, prev_n2 is the indexing, else, prev_n2 is 
		//Recupero il nodo dell'esterno
		if (prev_n2 == -1)
			last_candidate_index = 0;
		else {
			last_candidate_index++; //Next Element
		}
		//else
		//	prev_n2++;

		while (last_candidate_index < n2)
		{
			prev_n2 = g2->nodes[last_candidate_index];
			if (core_2[prev_n2] == -1 && g2->nodeInfo[prev_n2][1] == c)
				break;
			++last_candidate_index;
		}

		if (last_candidate_index >= n2)
			return false;
	}
	//std::cout<<curr_n1 << " " << prev_n2 << " \n";

	if (prev_n2 <= n2) {
		*pn1 = curr_n1;
		*pn2 = prev_n2;
		//std::cout<<"\nNP END: " <<curr_n1<<" " << prev_n2 << "\n" ;
		return true;
	}

	return false;
}


/*---------------------------------------------------------------
* bool VF3State::IsFeasiblePair(node1, node2)
* Returns true if (node1, node2) can be added to the state
* NOTE:
*   The attribute compatibility check (methods CompatibleNode
*   and CompatibleEdge of ARGraph) is always performed
*   applying the method to g1, and passing the attribute of
*   g1 as first argument, and the attribute of g2 as second
*   argument. This may be important if the compatibility
*   criterion is not symmetric.
--------------------------------------------------------------*/
bool VF3State::IsFeasiblePair(int node1, int node2)
{
	//std::cout << "\nIF: " << node1 << " " << node2;
	//print_core(core_1, core_2, core_len);
	assert(node1 <= n1);
	assert(node2 <= n2);
	assert(core_1[node1] == -1);
	assert(core_2[node2] == -1);

	//if (!nf(g1->GetNodeAttr(node1), g2->GetNodeAttr(node2)))
	//	return false;
	int n1outsize = (*g1->outedges)[node1].size();
	int n1insize = (*g1->inedges)[node1].size();
	//if (n1insize > g2->inNetWorkSet[node2].size()
	//	|| n1outsize > g2->netWorkSet[node2].size())
	//	return false;
	if (n1insize > g2->netWorkSet[node2].size()
		|| n1outsize > g2->netWorkSet[node2].size())
		return false;

	int i, other1, other2, c_other;
	//Edge1 eattr1;
	//Edge2 eattr2;
	int termout2 = 0, termin2 = 0, new2 = 0;
	memset(termin2_c, 0, classes_count * sizeof(int));
	memset(termout2_c, 0, classes_count * sizeof(int));
	memset(new2_c, 0, classes_count * sizeof(int));

	// Check the 'out' edges of node1
	//for (i = 0; i< n1insize; i++)
	//{
	for (const auto& other1 : (*g1->outedges)[node1])
	{
		//other1 = g1->GetOutEdge(node1, i, eattr1);
		c_other = g1->nodeLabels[other1.first];
		if (core_1[other1.first] != -1)
		{
			other2 = core_1[other1.first];
			if (!g2->hasEdge(node2, other2))//, eattr2) ||
											//!ef(eattr1, eattr2))
				return false;
		}
	}

	// Check the 'in' edges of node1
	//for (i = 0; i<g1->InEdgeCount(node1); i++)
	for (const auto& other1 : (*g1->inedges)[node1])
	{
		//other1 = g1->GetInEdge(node1, i, eattr1);
		c_other = g1->nodeLabels[other1.first];
		if (core_1[other1.first] != -1)
		{
			other2 = core_1[other1.first];
			if (!g2->hasEdge(other2, node2))//, eattr2) ||
											//!ef(eattr1, eattr2))
				return false;
		}
	}


	// Check the 'out' edges of node2
	//for (i = 0; i<g2->OutEdgeCount(node2); i++)
	for (const auto& other2 : g2->netWorkSet[node2])
	{
		//other2 = g2->GetOutEdge(node2, i);
		c_other = g2->nodeInfo[other2.first][1];
		if (core_2[other2.first] != -1)
		{
			//other1 = core_2[other2];
			//if (!g1->HasEdge(node1, other1))
			//	return false;
		}
		else
		{
			if (in_2[other2.first]) {
				termin2++;
				termin2_c[c_other]++;
			}
			if (out_2[other2.first]) {
				termout2++;
				termout2_c[c_other]++;
			}
			if (!in_2[other2.first] && !out_2[other2.first]) {
				new2++;
				new2_c[c_other]++;
			}
		}
	}

	// Check the 'in' edges of node2
	//for (i = 0; i<g2->InEdgeCount(node2); i++)
	//for (const auto& other2 : g2->inNetWorkSet[node2])
	for (const auto& other2 : g2->netWorkSet[node2])
	{
		//other2 = g2->GetInEdge(node2, i);
		c_other = g2->nodeInfo[other2.first][1];
		if (core_2[other2.first] != -1)
		{
			//other1 = core_2[other2];
			//if (!g1->HasEdge(other1, node1))
			//	return false;
		}
		else
		{
			if (in_2[other2.first]) {
				termin2++;
				termin2_c[c_other]++;
			}
			if (out_2[other2.first]) {
				termout2++;
				termout2_c[c_other]++;
			}
			if (!in_2[other2.first] && !out_2[other2.first]) {
				new2++;
				new2_c[c_other]++;
			}
		}
	}

	//Look-ahead check
	if (termin1[core_len] <= termin2 && termout1[core_len] <= termout2) {
		for (i = 0; i < classes_count; i++) {
			if (termin1_c[core_len][i] > termin2_c[i] ||
				termout1_c[core_len][i] > termout2_c[i]) {
				return false;
			}
		}
	}
	else return false;

	if (new1[core_len] + termin1[core_len] + termout1[core_len]
		<= new2 + termin2 + termout2)
	{
		for (i = 0; i < classes_count; i++) {
			if (new1_c[core_len][i] + termin1_c[core_len][i] + termout1_c[core_len][i]
		> new2_c[i] + termin2_c[i] + termout2_c[i])
				return false;
		}
	}
	else return false;

	//std::cout << "\nIs Feasible: " << node1 << " " << node2;
	return true;

}



/*--------------------------------------------------------------
* void VF3State::AddPair(node1, node2)
* Adds a pair to the Core set of the state.
* Precondition: the pair must be feasible
-------------------------------------------------------------*/
void VF3State::AddPair(int node1, int node2)
{

	/*std::cout<<"\nAP:";
	print_core(core_1,core_2,n1);
	std::cout<<" <- "<< node1 <<":"<< node2;*/

	assert(node1 <= n1);
	assert(node2 <= n2);
	assert(core_len<n1);
	assert(core_len<n2);
	assert(g1->nodeLabels[node1] == g2->nodeInfo[node2][1]);

	//Updating the core lenght
	core_len++;
	added_node1 = node1;
	int node_c = g1->nodeLabels[node1];
	core_len_c[node_c]++;

	//Checking if node2 is not in T2_in
	if (!in_2[node2])
	{
		in_2[node2] = core_len;
		//in2_set[node_c].push_back(node2);
		t2in_len++;
		t2in_len_c[node_c]++;
		if (out_2[node2]) {
			t2both_len++;
			t2both_len_c[node_c]++;
		}
	}

	//Checking if node2 is not in T2_in
	if (!out_2[node2])
	{
		out_2[node2] = core_len;
		//out2_set[node_c].push_back(node2);
		t2out_len++;
		t2out_len_c[node_c]++;
		if (in_2[node2]) {
			t2both_len++;
			t2both_len_c[node_c]++;
		}
	}

	//Inserting nodes into the core set
	core_1[node1] = node2;
	core_2[node2] = node1;

	//Evaluation of the neighborhood
	int i, other, other_c;
	other_c = -1;

	//for (i = 0; i<g2->InEdgeCount(node2); i++)
	//{
	//for (const auto& other : g2->inNetWorkSet[node2])
	for (const auto& other : g2->netWorkSet[node2])
	{
		//other = g2->GetInEdge(node2, i);
		if (!in_2[other.first])
		{
			other_c = g2->nodeInfo[other.first][1];
			in_2[other.first] = core_len;
			//in2_set[other_c].push_back(other);
			t2in_len++;
			t2in_len_c[other_c]++;
			if (out_2[other.first]) {
				t2both_len++;
				t2both_len_c[other_c]++;
			}
		}
	}

	//for (i = 0; i<g2->OutEdgeCount(node2); i++)
	for (const auto& other : g2->netWorkSet[node2])
	{
		//other = g2->GetOutEdge(node2, i);
		if (!out_2[other.first])
		{
			other_c = g2->nodeInfo[other.first][1];
			out_2[other.first] = core_len;
			//out2_set[other_c].push_back(other);
			t2out_len++;
			t2out_len_c[other_c]++;
			if (in_2[other.first]) {
				t2both_len++;
				t2both_len_c[other_c]++;
			}
		}
	}

}



/*--------------------------------------------------------------
* void VF3State::GetCoreSet(c1, c2)
* Reads the core set of the state into the arrays c1 and c2.
* The i-th pair of the mapping is (c1[i], c2[i])
--------------------------------------------------------------*/
void VF3State::GetCoreSet(int c2[])
{
	int i, j;
	for (i = 1, j = 1; i <= n1; i++)
		if (core_1[i] != -1)
		{
			//c1[j] = i;
			gm->logger << i << " " << core_1[i] << endl;
			//c2[j] = core_1[i];
			j++;
		}
	gm->logger << endl;
}

/*----------------------------------------------------------------
* Undoes the changes to the shared vectors made by the
* current state. Assumes that at most one AddPair has been
* performed.
----------------------------------------------------------------*/
void VF3State::BackTrack()
{

	/*std::cout<<"\nBT:";
	print_core(core_1,core_2,n1);
	std::cout<<" -> "<< added_node1 <<":"<< core_1[added_node1];*/

	assert(core_len - orig_core_len <= 1);
	assert(added_node1 != -1);

	int other_c = 0;
	int node_c = g1->nodeLabels[added_node1];

	if (orig_core_len < core_len)
	{
		int i, node2;
		node2 = core_1[added_node1];

		if (in_2[node2] == core_len) {
			in_2[node2] = 0;
			//in2_set[node_c].erase(node2);
			t2in_len_c[node_c]--;
			if (out_2[node2])
				t2both_len_c[node_c]--;
		}

		if (out_2[node2] == core_len) {
			out_2[node2] = 0;
			//out2_set[node_c].erase(node2);
			t2out_len_c[node_c]--;
			if (in_2[node2])
				t2both_len_c[node_c]--;

		}

		//Backtraking neightborhood
		//for (i = 0; i<g2->InEdgeCount(node2); i++)
		//for (const auto& other : g2->inNetWorkSet[node2])
		for (const auto& other : g2->netWorkSet[node2])
		{
			//int other = g2->GetInEdge(node2, i);
			other_c = g2->nodeInfo[other.first][1];
			if (in_2[other.first] == core_len) {
				in_2[other.first] = 0;
				//in2_set[other_c].erase(other);
				t2in_len_c[other_c] --;
				if (out_2[other.first])
					t2both_len_c[other_c]--;
			}
		}

		//for (i = 0; i<g2->OutEdgeCount(node2); i++)
		for (const auto& other : g2->netWorkSet[node2])
		{
			//int other = g2->GetOutEdge(node2, i);
			other_c = g2->nodeInfo[other.first][1];
			if (out_2[other.first] == core_len) {
				out_2[other.first] = 0;
				//out2_set[other_c].erase(other);
				t2out_len_c[other_c] --;
				if (in_2[other.first])
					t2both_len_c[other_c]--;
			}
		}

		core_1[added_node1] = -1;
		core_2[node2] = -1;

		core_len = orig_core_len;
		core_len_c[node_c]--;
		added_node1 = -1;
	}
}

bool VF3State::IsDead() {
	if (n1 > n2) {
		return true;
	}

	if (t1both_len[core_len] > t2both_len ||
		t1out_len[core_len] > t2out_len ||
		t1in_len[core_len] > t2in_len) {
		return true;
	}

	for (int c = 0; c < classes_count; c++) {
		if (t1both_len_c[core_len][c] > t2both_len_c[c] ||
			t1out_len_c[core_len][c] > t2out_len_c[c] ||
			t1in_len_c[core_len][c] > t2in_len_c[c]) {
			return true;
		}
	}

	return false;
}

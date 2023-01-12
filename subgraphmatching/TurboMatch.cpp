#include "TurboMatch.h"

TurboMatch::TurboMatch()
{
	core = 0;
	nodeArea = NULL;
	oomessage = NULL;
	oimessage = NULL;
	iomessage = NULL;
	comm_id = -1;
	vans = vector<vector<int>*>(4);
	rectm = NULL;
	boundtm = NULL;
	news = 0;
	ncMap = NULL;
	level = NULL;
}

void TurboMatch::init(bool tough)
{
	//outds = vector<vector<unordered_map<int, int>>>(q->nodenum + 1, vector<unordered_map<int, int>>(q->nodenum + 1));
	//outcomm = vector<vector<int>>(q->nodenum + 1, vector<int>());

	ranks = new int*[q->nodeNum];
	for (int pn = 0; pn < q->nodeNum; ++pn)
	{
		ranks[pn] = new int[q->nodeNum];
	}

	int K = min(3, q->nodeNum);
	newM = new int[q->nodeNum + 1];
	u = new int[K];
	candN = new int[K];
	flag = new bool[q->nodeNum + 1];
	CPer = vector<LabelVList*>(data->labelnum, NULL);
	M = new int[q->nodeNum + 1];
	for (int j = 0; j < q->nodeNum; j++)
	{
		M[q->nodes[j]] = -1;
	}
	F = new bool[data->nodeNum + 1];
	memset(F, false, sizeof(bool) * (data->nodeNum + 1));
	if (tough)
	{
		n2cNum = vector<vector<int>>(q->nodeNum + 1, vector<int>(g->nodeNum + 1, 0));
		boundary = vector<vector<int>*>(q->nodeNum + 1, NULL);
		toadd = vector<vector<int>>(q->nodeNum + 1);
		existaddpos = vector<vector<pair<int, int>>>(q->nodeNum + 1);
		penv = vector<vector<int>>(q->nodeNum + 1);
		penv_en = vector<vector<vector<int>>>(q->nodeNum + 1);
	}
}

TurboMatch::TurboMatch(int comm, vector<vector<int>*>* boundary, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oo
	, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* oi, unordered_map<int, unordered_map<int, unordered_map<int, int>>>* io
	, MemoryGraph* gr, MemoryGraph* query, MemoryGraph* graph)
{
	core = 0;
	comm_id = comm;
	nodeArea = boundary;
	oomessage = oo;
	oimessage = oi;
	iomessage = io;
	data = gr;
	q = query;
	g = graph;
	vans = vector<vector<int>*>(4);
	rectm = NULL;
	boundtm = NULL;
	news = 0;
	ncMap = NULL;
	level = NULL;
}

TurboMatch::TurboMatch(string& f)
{
	core = 0;
	filename = f;
	nodeArea = NULL;
	oomessage = NULL;
	oimessage = NULL;
	iomessage = NULL;
	comm_id = -1;
	vans = vector<vector<int>*>(4);
	rectm = NULL;
	boundtm = NULL;
	news = 0;
	ncMap = NULL;
	level = NULL;
}

void TurboMatch::SetFile(string& f)
{
	filename = f;
}

int cmp(const void *a, const void *b)
{
	if (((TurboNeighbor *)b)->NeighborN != ((TurboNeighbor *)a)->NeighborN)
	{
		return ((TurboNeighbor *)b)->NeighborN - ((TurboNeighbor *)a)->NeighborN;
	}
	else return ((TurboNeighbor *)a)->uc_prime - ((TurboNeighbor *)b)->uc_prime;
}

int cmpE(const void *a, const void *b)
{
	if (fabs(((TurboElem *)a)->value - ((TurboElem *)b)->value) > 1e-6)
	{
		if (((TurboElem *)a)->value - ((TurboElem *)b)->value > 1e-6)
		{
			return 1;
		}
		else return -1;
	}
	else return ((TurboElem *)a)->v - ((TurboElem *)b)->v;
}

static bool cmpD(const DegreePos& a, const DegreePos& b)
{
	return a.degree < b.degree;
}

struct commStruct {
	int id;
	int num;
};

bool cmpC(const commStruct& a, const commStruct& b)
{
	return a.num < b.num;
}

int TurboMatch::TurboISO(MemoryGraph* q, MemoryGraph* g, bool& candup, int comm_id) //生成NEC树时未考虑结点的邻居是否完全相同，只处理了是否完全图
{
	//NECTree q_prime;
	q_prime.vList.clear();
	q_prime.isLinked.clear();
	q_prime.child.clear();
	q_prime.NEC.clear();
	q_prime.parent.clear();
	q_prime.vertexNum = 0;

	Vid U_s = ChooseStartQVertex(q, g);
	RewriteToNECTree(q, U_s, &q_prime);	// q_prime: NECTree

	int numVertex = g->nodeNum;
	assert(numVertex != 0);
	//int counts[16] = {0};
	//unordered_map<int, int> countresult;
	this->comm_id = comm_id;
	firstpattern = U_s;
	int csum = 0;

	int qNumVertex = q->nodes.size();
	//unordered_map<int, int> M;

	NECTree* cur_q = &q_prime;// &(*q_primes)[U_s];//
	TurboElem *order = new TurboElem[cur_q->vertexNum];
	unordered_set<Vid> VM;
	vector<Vid> qV;
	vector<Vid> gV;

	if (true)//storeType != 1)
	{
		//		omp_set_num_threads(16);
		//#pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < numVertex; ++i)
		{
			int count = 0;
			int id = 0;
			//int id = omp_get_thread_num();
			//if (q->vList[U_s] == g->vList[i])
			//{
			int gvertex = g->nodes[i];
			if (q->nodeLabels[U_s] != g->nodeLabels[gvertex])
				continue;
			if ((*g->outedges)[gvertex].size() < (*q->outedges)[U_s].size())
				continue;

			if (storeType == 1)
			{
				cout << "here!" << endl;
				int mapped = g->idMapping[gvertex];
				//if (gm->equalInData.find(mapped) == gm->equalInData.end())
				if (gm->equalBool[mapped] == 0)
					continue;
				memberNum = gm->equalBool[mapped];
			}

			firstmatch = gvertex;
			/*if (storeType == 0)
			{
			bool conti = false;
			for (const auto& n : data->graphEqualNodes[gvertex])
			{
			if (countresult.find(n) != countresult.end())
			{
			//cout << "continue!" << endl;
			countresult[gvertex] = countresult[n];
			conti = true;
			break;
			}
			}
			if (conti)
			continue;
			}*/
			//CRTree CR;
			CR.init(cur_q->vertexNum);
			VM.clear();
			VM.insert(gvertex);
			//unordered_map<int, bool> visited;
			//bool *visited = new bool[numVertex + 1];
			//memset(visited, false, sizeof(bool) * (numVertex + 1));

			bool explore = ExploreCR(0, &VM, &CR, -1, cur_q, g, q, F, candup);

			//if (visited != NULL)
			//	delete[]visited;

			if (explore)
			{
				DetermineMatchingOrder(cur_q, &CR, order, 0, 1, q);
				qsort(order, cur_q->vertexNum, sizeof(TurboElem), cmpE);


				assert(qNumVertex != 0);

				qV.clear();
				qV.push_back(U_s);
				gV.clear();
				gV.push_back(gvertex);
				UpdateState(M, F, &qV, &gV);

				if (qNumVertex != 1)
				{
					SubgraphSearch(cur_q, order, 1, M, F, &CR, csum, candup);
				}
				else
				{
					csum += 1;
				}

				RestoreState(M, F, &qV, &gV);
				//if (storeType == 3 && count > 0)
				{
					//continue;//break;
				}
				//csum += count;
			}
		}
	}

	if (order != NULL)
		delete[]order;
	//if (M != NULL)
	//	delete[]M;
	//if (F != NULL)
	//	delete[]F;

	return csum;//ount;
}

int TurboMatch::TurboISODense(MemoryGraph* q, MemoryGraph* g, bool& candup, int comm_id) //生成NEC树时未考虑结点的邻居是否完全相同，只处理了是否完全图
{
	for (const auto& n : q->nodes)
	{
		ncMap[n] = -1;
	}
	//NECTree q_prime;
	q_prime.vList.clear();
	q_prime.isLinked.clear();
	q_prime.child.clear();
	q_prime.NEC.clear();
	q_prime.parent.clear();
	q_prime.vertexNum = 0;

	Vid U_s = ChooseStartQVertex(q, g);
	BuildNECTree(q, U_s, &q_prime);	// q_prime: NECTree
	int numVertex = g->nodes.size();
	assert(numVertex != 0);
	int count = 0;
	firstpattern = U_s;
	
	TurboElem *order = new TurboElem[q_prime.vertexNum];
	unordered_set<Vid> VM;
	vector<Vid> qV;
	vector<Vid> gV;

	{
		int qNumVertex = q->nodes.size();
		assert(qNumVertex != 0);
		int* M = NULL;

		for (int i = 0; i < numVertex; i++)
		{
			int gvertex = g->nodes[i];
			CR.init(q_prime.vertexNum);
			VM.clear();
			VM.insert(gvertex);
			bool explore = ExploreCR(0, &VM, &CR, -1, &q_prime, g, q, F, candup);

			if (explore)
			{
				DetermineMatchingOrder(&q_prime, &CR, order, 0, 1, q);
				qsort(order, q_prime.vertexNum, sizeof(TurboElem), cmpE);

				qV.clear();
				qV.push_back(U_s);
				gV.clear();
				gV.push_back(gvertex);
				UpdateStateDense(M, F, &qV, &gV);

				if (qNumVertex != 1)
				{
					ncMap[U_s] = gvertex;
					SubgraphSearchDense(q, &q_prime, g, order, 1, M, &CR, count, candup);
				}

				RestoreStateDense(M, F, &qV, &gV);
			}
		}

		if (order != NULL)
			delete[]order;
		if (M != NULL)
			delete[]M;
	}

	return count;//ount;
}

int TurboMatch::TurboISOBound(MemoryGraph* q, MemoryGraph* g, bool& candup) //生成NEC树时未考虑结点的邻居是否完全相同，只处理了是否完全图
{
	for (const auto& n : q->nodes)
	{
		ncMap[n] = -1;
	}

	//NECTree q_prime;
	q_prime.vList.clear();
	q_prime.isLinked.clear();
	q_prime.child.clear();
	q_prime.NEC.clear();
	q_prime.parent.clear();
	q_prime.vertexNum = 0;

	Vid U_s = ChooseStartQVertex(q, g);
	RewriteToNECTree(q, U_s, &q_prime);	// q_prime: NECTree
	int numVertex = g->nodes.size();
	assert(numVertex != 0);
	int count = 0;
	firstpattern = U_s;

	int qNumVertex = q->nodes.size();
	assert(qNumVertex != 0);
	//unordered_map<int, int> M;
	TurboElem *order = new TurboElem[q_prime.vertexNum];
	unordered_set<Vid> VM;
	vector<Vid> qV;
	vector<Vid> gV;

	//if (nodeArea != NULL)
	{
		if (nodeArea != NULL && (*nodeArea)[U_s] != NULL)
		{
			int nsize = (*nodeArea)[U_s]->size();
			for (int i = 0; i < nsize; i++)
			{
				//if (q->vList[U_s] == g->vList[i])
				//{
				int gvertex = (*(*nodeArea)[U_s])[i];
				//CRTree CR;
				CR.init(q_prime.vertexNum);
				VM.clear();
				VM.insert(gvertex);
				//unordered_map<int, bool> visited;
				//bool *visited = new bool[numVertex + 1];
				//memset(visited, false, sizeof(bool) * (numVertex + 1));
				bool explore = ExploreCR(0, &VM, &CR, -1, &q_prime, g, q, F, candup);
				//if (visited != NULL)
				//	delete[]visited;

				if (explore)
				{
					DetermineMatchingOrder(&q_prime, &CR, order, 0, 1, q);
					//sort(order, order + q_prime.vertexNum, cmpE);
					qsort(order, q_prime.vertexNum, sizeof(TurboElem), cmpE);

					qV.clear();
					qV.push_back(U_s);
					gV.clear();
					gV.push_back(gvertex);
					UpdateStateDense(M, F, &qV, &gV);

					if (qNumVertex != 1)
					{
						ncMap[U_s] = gvertex;
						SubgraphSearchBound(&q_prime, order, 1, M, F, &CR, count, candup);
					}
					else
					{
						ncMap[U_s] = gvertex;
						GenPerm(M, &q_prime, 0, q, g, count, candup);
					}

					RestoreStateDense(M, F, &qV, &gV);
				}
			}

			if (order != NULL)
				delete[]order;
			//if (M != NULL)
			//	delete[]M;
			//if (F != NULL)
			//	delete[]F;

			return count;
		}
		else
		{
			vector<int>* nodes = &data->communityNodes[distributeplan[U_s]];//(*(*communityGraphs)[distributeplan[U_s]]).nodes;
																			//int nsize = nodes->size();
			for (const auto& gvertex : *nodes)
			{
				//if (q->vList[U_s] == g->vList[i])
				//{
				//int gvertex = (*nodes)[i];
				//CRTree CR;
				CR.init(q_prime.vertexNum);
				VM.clear();
				VM.insert(gvertex);
				//unordered_map<int, bool> visited;
				//bool *visited = new bool[numVertex + 1];
				//memset(visited, false, sizeof(bool) * (numVertex + 1));
				bool explore = ExploreCR(0, &VM, &CR, -1, &q_prime, g, q, F, candup);
				//if (visited != NULL)
				//	delete[]visited;

				if (explore)
				{
					DetermineMatchingOrder(&q_prime, &CR, order, 0, 1, q);
					//sort(order, order + q_prime.vertexNum, cmpE);
					qsort(order, q_prime.vertexNum, sizeof(TurboElem), cmpE);

					qV.clear();
					qV.push_back(U_s);
					gV.clear();
					gV.push_back(gvertex);
					UpdateStateDense(M, F, &qV, &gV);

					if (qNumVertex != 1)
					{
						ncMap[U_s] = gvertex;
						SubgraphSearchBound(&q_prime, order, 1, M, F, &CR, count, candup);
					}
					else
					{
						ncMap[U_s] = gvertex;
						GenPerm(M, &q_prime, 0, q, g, count, candup);
					}

					RestoreStateDense(M, F, &qV, &gV);
				}
			}

			if (order != NULL)
				delete[]order;
			//if (M != NULL)
			//	delete[]M;
			//if (F != NULL)
			//	delete[]F;

			return count;
		}
	}

	return count;
}

int TurboMatch::TurboISOSuper(MemoryGraph* q, MemoryGraph* g, bool& candup) //生成NEC树时未考虑结点的邻居是否完全相同，只处理了是否完全图
{
	ncMap = new int[q->nodes.size() + 1];
	for (const auto& n : q->nodes)
	{
		ncMap[n] = -1;
	}
	//NECTree q_prime;
	q_prime.vList.clear();
	q_prime.isLinked.clear();
	q_prime.child.clear();
	q_prime.NEC.clear();
	q_prime.parent.clear();
	q_prime.vertexNum = 0;

	Vid U_s = ChooseStartQVertex(q, g);
	BuildNECTree(q, U_s, &q_prime);	// q_prime: NECTree
	int numVertex = g->nodes.size();
	assert(numVertex != 0);
	int count = 0;
	firstpattern = U_s;
	initIETree();
	TurboElem *order = new TurboElem[q_prime.vertexNum];
	unordered_set<Vid> VM;
	vector<Vid> qV;
	vector<Vid> gV;

	//if (candup)
	{
		int qNumVertex = q->nodes.size();
		assert(qNumVertex != 0);
		int* M = NULL;
		//		omp_set_num_threads(16);
		//#pragma omp parallel for schedule(dynamic)
		for (int i = 0; i < numVertex; i++)
		{
			//if (q->vList[U_s] == g->vList[i])
			//{
			int gvertex = g->nodes[i];
			//CRTree CR;
			CR.init(q_prime.vertexNum);
			VM.clear();
			VM.insert(gvertex);
			//unordered_map<int, bool> visited;
			//bool *visited = new bool[numVertex + 1];
			//memset(visited, false, sizeof(bool) * (numVertex + 1));
			bool explore = ExploreCR(0, &VM, &CR, -1, &q_prime, g, q, F, candup);
			//if (visited != NULL)
			//	delete[]visited;

			if (explore)
			{
				DetermineMatchingOrder(&q_prime, &CR, order, 0, 1, q);
				qsort(order, q_prime.vertexNum, sizeof(TurboElem), cmpE);

				// = new int[qNumVertex];
				/*for (int j = 0; j < (*q->nodes).size(); j++)
				{
				M[(*q->nodes)[j]] = -1;
				}*/
				//unordered_map<int, bool> F;// = new bool[numVertex];
				//memset(F, false, sizeof(bool) * numVertex);

				qV.clear();
				qV.push_back(U_s);
				gV.clear();
				gV.push_back(gvertex);
				//UpdateState(M, &qV, &gV);

				if (qNumVertex != 1)
				{
					//currentMap[gvertex].insert(U_s);
					ncMap[U_s] = gvertex;
					SubgraphSearchSuper(q, &q_prime, g, order, 1, M, &CR, count, candup);
					//currentMap.erase(gvertex);
				}


				//RestoreState(M, &qV, &gV);

				//if (F != NULL)
				//	delete[]F;
			}
		}

		if (order != NULL)
			delete[]order;
		if (M != NULL)
			delete[]M;
	}

	delete[] ncMap;
	return count;
}

int TurboMatch::contain(int e, vector<LabelVList> *tmp)
{
	int Size = tmp->size();
	for (int i = 0; i < Size; i++)
	{
		if ((*tmp)[i].label == e)
			return i;
	}
	return -1;
}

int TurboMatch::contain(int e, vector<LabelVList*> *tmp)
{
	int Size = tmp->size();
	for (int i = 0; i < Size; i++)
	{
		if ((*tmp)[i]->label == e)
			return i;
	}
	return -1;
}

template<class T>
int TurboMatch::contain(T e, vector<T> *tmp)
{
	int Size = tmp->size();
	for (int i = 0; i < Size; i++)
	{
		if ((*tmp)[i] == e)
		{
			return i;
		}
	}
	return -1;
}

int TurboMatch::ChooseStartQVertex(MemoryGraph* q, MemoryGraph* g)
{
	int K = min(3, q->nodeNum);
	memset(candN, 0, K * sizeof(int));

	priority_queue<TurboElem, vector<TurboElem>, TurboComQ> pq;
	for (int i = 0; i < (int)q->nodes.size(); i++)
	{
		int vnode = q->nodes[i];
		TurboElem tmp;
		tmp.v = vnode;
		tmp.value = 0.0;
		/*
		* Rank(u) = freq(g, L(u)) / deg(u)
		*       where freq(g, l) is the number of data vertices in
		* g that have label l, and deg(u) means the degree of u.
		*/
		//int Size = q->edgeList[i].size();
		//for (int j = 0; j < Size; j++)
		//	tmp.value += q->edgeList[i][j].vList.size();
		tmp.value += (*q->outedges)[vnode].size();
		//tmp.value += (*q->inedges)[vnode].size();
		if (nodeArea != NULL)
		{
			if ((*nodeArea)[vnode] != NULL)
			{
				tmp.value = (*nodeArea)[vnode]->size() / tmp.value;
			}
			else
			{
				tmp.value = data->communityNodes[distributeplan[vnode]].size() / tmp.value;
			}
		}
		else
		{
			tmp.value = g->nodes.size() / tmp.value;
		}
		//tmp.value = g->labelList[q->vList[i]].size() / tmp.value;
		pq.push(tmp);
		if (pq.size() > K)
			pq.pop();
	}
	// acquire top-three query vertices
	int It = K;
	while (It--)
	{
		TurboElem tmp = pq.top();
		pq.pop();
		u[It] = tmp.v;
	}

	for (int i = 0; i < K; i++)
	{
		int label = q->nodeLabels[u[i]];
		//Label label = q->vList[u[i]];
		//int graphSize = g->labelList[label].size();
		int graphSize = g->nodes.size();
		int outdegreeU = (*q->outedges)[u[i]].size();
		if (nodeArea != NULL)
		{
			if ((*nodeArea)[u[i]] != NULL)
			{
				for (int j = 0; j < (*nodeArea)[u[i]]->size(); j++)
				{
					// First Check if deq(u) <= deg(v)
					Vid v = (*(*nodeArea)[u[i]])[j];
					int outdegreeV = (*g->outedges)[v].size();
					//int indegreeU = (*q->inedges)[u[i]].size();
					//int indegreeV = (*g->inedges)[v].size();

					if (outdegreeU > outdegreeV)
						//|| indegreeU > indegreeV)
						continue;

					//next exploit the neighborhood label frequency filter
					// (NLF filter), which checks if |adj(u, l)| <= |adj(v, l)|
					// for every distinct label l of the adjacent vertices of u.
					//int querySize = (*q->labelEdgesVec)[u[i]].size();
					bool Flag = true;
					for (const auto& label1 : q->neighLabels[u[i]])	//对u的邻居的每个label
					{
						//Label label1 = (*q->labelEdgesVec)[u[i]][k].label;
						int curN = (*q->labelEdgesVec)[u[i]][label1]->vList.size();
						if ((*g->labelEdgesVec)[v][label1] == NULL || curN > (*g->labelEdgesVec)[v][label1]->vList.size())
						{
							Flag = false;
							break;
						}
					}
					if (Flag)
						candN[i] ++;

					//candN[i] ++;
				}
			}
			else
			{
				vector<int>* nodes = &data->communityNodes[distributeplan[u[i]]];
				for (const auto& v : *nodes)
				{
					// First Check if deq(u) <= deg(v)
					//Vid v = (*nodes)[j];
					int outdegreeV = (*g->outedges)[v].size();
					//int indegreeU = (*q->inedges)[u[i]].size();
					//int indegreeV = (*g->inedges)[v].size();

					if (outdegreeU > outdegreeV)
						//|| indegreeU > indegreeV)
						continue;

					//next exploit the neighborhood label frequency filter
					// (NLF filter), which checks if |adj(u, l)| <= |adj(v, l)|
					// for every distinct label l of the adjacent vertices of u.

					//int querySize = (*q->labelEdgesVec)[u[i]].size();
					bool Flag = true;
					for (const auto& label1 : q->neighLabels[u[i]])	//对u的邻居的每个label
					{
						//Label label1 = (*q->labelEdgesVec)[u[i]][k].label;
						int curN = (*q->labelEdgesVec)[u[i]][label1]->vList.size();
						if ((*g->labelEdgesVec)[v][label1] == NULL || curN > (*g->labelEdgesVec)[v][label1]->vList.size())
						{
							Flag = false;
							break;
						}
					}
					if (Flag)
						candN[i] ++;

					//candN[i] ++;
				}
			}
		}
		else
		{
			for (int j = 0; j < graphSize; j++)
			{
				// First Check if deq(u) <= deg(v)
				Vid v = g->nodes[j];
				int outdegreeV = (*g->outedges)[v].size();
				//int indegreeU = (*q->inedges)[u[i]].size();
				//int indegreeV = (*g->inedges)[v].size();

				if (outdegreeU > outdegreeV)
					//|| indegreeU > indegreeV)
					continue;

				//next exploit the neighborhood label frequency filter
				// (NLF filter), which checks if |adj(u, l)| <= |adj(v, l)|
				// for every distinct label l of the adjacent vertices of u.

				bool Flag = true;
				for (const auto& label1 : q->neighLabels[u[i]])	//对u的邻居的每个label
				{
					//Label label1 = (*q->labelEdgesVec)[u[i]][k].label;
					int curN = (*q->labelEdgesVec)[u[i]][label1]->vList.size();
					if ((*g->labelEdgesVec)[v][label1] == NULL || (storeType != 2 && curN > (*g->labelEdgesVec)[v][label1]->vList.size()))
					{
						Flag = false;
						break;
					}
				}
				if (Flag)
					candN[i] ++;

				//candN[i] ++;
			}
		}
	}

	//assert(g->getVertexNum() != 0);
	int Min = g->nodes.size() + 1;
	int curU = -1;
	for (int i = 0; i < K; i++)
	{
		if (candN[i] < Min)
		{
			Min = candN[i];
			curU = i;
		}
	}
	assert(curU != -1);
	int res = u[curU];

	//if (u != NULL)
	//	delete[] u;
	//if (candN != NULL)
	//	delete[] candN;

	return res;
}

void TurboMatch::FindNEC(vector<vector<Vid>> *NECV, vector<Vid> *vertexList, MemoryGraph *q)
{
	sort(vertexList->begin(), vertexList->end());
	int Size = vertexList->size();
	if (Size == 1)
	{
		(*NECV).push_back(*vertexList);
	}
	else
	{
		int *p = new int[Size];
		p[0] = 0;
		for (int i = 1; i < Size; i++)
		{
			int flag = i;
			for (int j = 0; j < i; j++)
			{
				if ((*q->outedges)[(*vertexList)[i]] == (*q->outedges)[(*vertexList)[j]])
					//&& (*q->inedges)[(*vertexList)[i]] == (*q->inedges)[(*vertexList)[j]])
				{
					if (nodeArea != NULL)
					{
						if (((*nodeArea)[(*vertexList)[i]] == NULL && (*nodeArea)[(*vertexList)[j]] == NULL
							&& distributeplan[(*vertexList)[i]] == distributeplan[(*vertexList)[j]])
							|| ((*nodeArea)[(*vertexList)[i]] == ((*nodeArea)[(*vertexList)[j]])))
						{
							flag = j;
							break;
						}
					}
					else
					{
						flag = j;
						break;
					}
				}
			}
			p[i] = p[flag];
			p[flag] = i;
		}
		for (int i = 0; i < Size; i++)
		{
			if (p[i] > i)
			{
				vector<Vid> vlist;
				vlist.push_back((*vertexList)[i]);
				int Pos = p[i];
				while (Pos != i)
				{
					vlist.push_back((*vertexList)[Pos]);
					Pos = p[Pos];
				}
				(*NECV).push_back(vlist);
			}
		}
		for (int i = 0, j = 0; i < Size; i++)
		{
			if (p[i] != i)
			{
				vector <Vid>::iterator Iter = vertexList->begin() + j;
				(*vertexList).erase(Iter);
			}
			else
			{
				j++;
			}
		}
		if (p != NULL)
			delete[]p;
		Size = vertexList->size();
		if (Size == 1)
		{
			(*NECV).push_back(*vertexList);
		}
		else if (Size == 0)
		{
			//bug fixed
		}
		else
		{
			int label = q->nodeLabels[(*vertexList)[0]];
			for (int i = 0; i < vertexList->size(); )
			{
				vector<Vid> a;
				vector<int> b;
				int Vi = (*vertexList)[i];
				a.push_back(Vi);
				b.push_back(i);

				if ((*q->labelEdgesVec)[Vi][label] == NULL)
					//if ((*q->outedges)[Vi].empty())// || (*q->inedges)[Vi].empty())
				{
					(*NECV).push_back(a);
					vector <Vid>::iterator Iter = vertexList->begin() + i;
					(*vertexList).erase(Iter);
				}
				else
				{
					for (int j = i + 1; j < vertexList->size(); j++)
					{
						Vid Vj = (*vertexList)[j];

						if ((*q->labelEdgesVec)[Vj][label] == NULL)
							continue;
						if (nodeArea != NULL)
						{
							if (!(((*nodeArea)[(*vertexList)[i]] == NULL && (*nodeArea)[(*vertexList)[j]] == NULL
								&& distributeplan[(*vertexList)[i]] == distributeplan[(*vertexList)[j]])
								|| ((*nodeArea)[(*vertexList)[i]] == ((*nodeArea)[(*vertexList)[j]]))))
							{
								continue;
							}
						}

						int sizea = a.size();
						bool fmm = true;
						for (int mm = 0; mm < sizea; mm++)
						{
							if ((*q->outedges)[a[mm]].size() != (*q->outedges)[Vj].size() ||
								(*q->outedges)[Vj].find(a[mm]) == (*q->outedges)[Vj].end())
								//int posmm = contain(a[mm], &(q->edgeList[Vj][pos3].vList));
								//if (posmm == -1)
							{
								fmm = false;
								break;
							}
							//unordered_set<int> us;
							for (const auto& n : (*q->outedges)[Vj])
							{
								if (n.first == a[mm])
									continue;
								if ((*q->outedges)[a[mm]].find(n.first) == (*q->outedges)[a[mm]].end())
								{
									fmm = false;
									break;
								}
							}
							if (!fmm)
								break;
						}
						if (fmm)
						{
							a.push_back(Vj);
							b.push_back(j);
						}
					}
					(*NECV).push_back(a);
					int sizea = a.size();
					for (int nn = sizea - 1; nn >= 0; nn--)
					{
						vector <Vid>::iterator Iter = vertexList->begin() + b[nn];
						(*vertexList).erase(Iter);
					}
				}
			}
		}
	}
}

void TurboMatch::RewriteToNECTree(MemoryGraph *q, int U_s, NECTree *q_prime)
{
	int numVertex = q->nodeNum;// getVertexNum();
	assert(numVertex != 0);

	memset(flag, false, sizeof(bool) * (numVertex + 1));// = new bool[numVertex];
														//memset(flag, false, sizeof(bool) * numVertex);
														// Line 1: create a root NEC vertex Us'
	q_prime->vertexNum++;
	q_prime->vList.push_back(q->nodeLabels[U_s]);
	vector<Vid> root;
	root.push_back(U_s);
	// Line 2: u's.NEC = [U_s]
	q_prime->NEC.push_back(root);
	q_prime->isLinked.push_back(false);
	q_prime->parent.push_back(-1);
	TurboChild child;
	q_prime->child.push_back(child);
	// Line 3: mark U_s as visited
	flag[U_s] = true;

	/*
	* Todo: Algo 2, Line 4
	*/
	int currentS = -1;
	int currentE = -1;
	int nextS = 0;
	int nextE = 0;
	int childS = 0;
	int childE = 0;
	int index = 0;
	while (nextE >= nextS)
	{
		currentS = nextS;
		currentE = nextE;
		nextS = currentE + 1;
		nextE = currentE;
		childS = currentE + 1;
		childE = currentE;
		for (int i = currentS; i <= currentE; i++)
		{
			bool ever = false;
			int necSize = q_prime->NEC[i].size();
			index++;
			for (int j = 0; j < necSize; j++)
			{
				Vid v = q_prime->NEC[i][j];
				//int outedgeSize = (*q->labelEdgesVec)[v].size();
				for (const auto& k : q->neighLabels[v])
				{
					// 遍历以v为节点的不同标签节点
					LabelVList *tmp = (*q->labelEdgesVec)[v][k];
					// 获取每个标签的各邻近节点
					//int Size = tmp->vList.size();
					//bool find = false;
					unordered_set<int>::iterator ll = tmp->vList.begin();
					while (ll != tmp->vList.end())
					{
						if (!flag[*ll])
						{
							break;
						}
						ll++;
					}
					if (ll == tmp->vList.end())
						continue;

					ever = true;
					if (CPer[tmp->label] == NULL)
					{
						LabelVList* l = new LabelVList();
						l->label = tmp->label;
						l->vList.insert(*ll);
						flag[*ll] = true;
						ll++;
						while (ll != tmp->vList.end())
						{
							int llt = *ll;
							if (!flag[llt])
							{
								flag[llt] = true;
								l->vList.insert(llt);
							}
							ll++;
						}
						CPer[tmp->label] = l;
					}
					else
					{
						int llt = *ll;
						int tlabel = tmp->label;
						if (CPer[tlabel]->vList.find(llt) == CPer[tlabel]->vList.end())
						{
							flag[llt] = true;
							CPer[tlabel]->vList.insert(llt);
						}
						ll++;
						while (ll != tmp->vList.end())
						{
							llt = *ll;
							if (!flag[llt])
							{
								if (CPer[tlabel]->vList.find(llt) == CPer[tlabel]->vList.end())
								{
									flag[llt] = true;
									CPer[tlabel]->vList.insert(llt);
								}
							}
						}
					}
				}
			}
			if (ever)
			{
				int Csize = CPer.size();
				for (int j = 0; j < Csize; j++)
				{
					if (CPer[j] == NULL)
						continue;
					int last = q_prime->NEC.size();
					//vector<vector<Vid>> NECV;
					vector<int> temp(CPer[j]->vList.begin(), CPer[j]->vList.end());
					FindNEC(&q_prime->NEC, &temp, q);
					int necvSize = q_prime->NEC.size() - last;// NECV.size();
					nextE += necvSize;
					childE += necvSize;
					q_prime->vertexNum += necvSize;
					if (q_prime->child[i].s == -1)
					{
						q_prime->child[i].s = childS;
					}
					q_prime->child[i].e = childE;
					for (int k = 0; k < necvSize; k++)
					{
						int lk = last + k;
						q_prime->vList.push_back(CPer[j]->label);
						if (q_prime->NEC[lk].size() >= 2 && q->HasEdge(q_prime->NEC[lk][0], q_prime->NEC[lk][1]))
							q_prime->isLinked.push_back(true);
						else
							q_prime->isLinked.push_back(false);

						//q_prime->NEC.push_back(NECV[k]);
						q_prime->parent.push_back(i);
						q_prime->child.push_back(child);
					}
				}
				childS = childE + 1;
				for (int t = 0; t < CPer.size(); ++t)
				{
					if (CPer[t] != NULL)
					{
						delete CPer[t];
						CPer[t] = NULL;
					}
				}
			}
		}
	}
	//if (flag != NULL)
	//	delete[] flag;
}

void TurboMatch::BuildNECTree(MemoryGraph *q, int U_s, NECTree *q_prime)
{
	int numVertex = q->nodes.size();// getVertexNum();
	level = new int[numVertex + 1];
	assert(numVertex != 0);
	bool *flag = new bool[numVertex + 1];
	memset(flag, false, sizeof(bool) * (numVertex + 1));// = new bool[numVertex];
														//memset(flag, false, sizeof(bool) * numVertex);

														// Line 1: create a root NEC vertex Us'
	q_prime->vertexNum++;
	q_prime->vList.push_back(q->nodeLabels[U_s]);
	vector<Vid> root;
	root.push_back(U_s);
	// Line 2: u's.NEC = [U_s]
	q_prime->NEC.push_back(root);
	q_prime->isLinked.push_back(false);
	q_prime->parent.push_back(-1);
	TurboChild child;
	q_prime->child.push_back(child);
	// Line 3: mark U_s as visited
	flag[U_s] = true;

	/*
	* Todo: Algo 2, Line 4
	*/
	int currentS = -1;
	int currentE = -1;
	int nextS = 0;
	int nextE = 0;
	int childS = 0;
	int childE = 0;
	int index = 0;
	while (nextE >= nextS)
	{
		currentS = nextS;
		currentE = nextE;
		nextS = currentE + 1;
		nextE = currentE;
		childS = currentE + 1;
		childE = currentE;
		for (int i = currentS; i <= currentE; i++)
		{
			bool ever = false;
			vector<LabelVList*> C(data->labelnum, NULL);
			int necSize = q_prime->NEC[i].size();
			index++;
			for (int j = 0; j < necSize; j++)
			{
				Vid v = q_prime->NEC[i][j];
				level[v] = index;
				//int outedgeSize = (*q->labelEdgesVec)[v].size();
				for (const auto& k : q->neighLabels[v])
				{
					// 遍历以v为节点的不同标签节点
					LabelVList *tmp = (*q->labelEdgesVec)[v][k];
					// 获取每个标签的各邻近节点
					//int Size = tmp->vList.size();
					//bool find = false;
					unordered_set<int>::iterator ll = tmp->vList.begin();
					while (ll != tmp->vList.end())
					{
						if (!flag[*ll])
						{
							break;
						}
						ll++;
					}
					if (ll == tmp->vList.end())
						continue;

					ever = true;
					if (C[tmp->label] == NULL)
					{
						LabelVList* l = new LabelVList();
						l->label = tmp->label;
						l->vList.insert(*ll);
						flag[*ll] = true;
						ll++;
						while (ll != tmp->vList.end())
						{
							int llt = *ll;
							if (!flag[llt])
							{
								flag[llt] = true;
								l->vList.insert(llt);
							}
							ll++;
						}
						C[tmp->label] = l;
					}
					else
					{
						int llt = *ll;
						int tlabel = tmp->label;
						if (C[tlabel]->vList.find(llt) == C[tlabel]->vList.end())
						{
							flag[llt] = true;
							C[tlabel]->vList.insert(llt);
						}
						ll++;
						while (ll != tmp->vList.end())
						{
							llt = *ll;
							if (!flag[llt])
							{
								if (C[tlabel]->vList.find(llt) == C[tlabel]->vList.end())
								{
									flag[llt] = true;
									C[tlabel]->vList.insert(llt);
								}
							}
						}
					}
				}
			}
			if (ever)
			{
				int Csize = C.size();
				for (int j = 0; j < Csize; j++)
				{
					if (C[j] == NULL)
						continue;
					int last = q_prime->NEC.size();
					//vector<vector<Vid>> NECV;
					vector<int> temp(C[j]->vList.begin(), C[j]->vList.end());
					FindNEC(&q_prime->NEC, &temp, q);
					int necvSize = q_prime->NEC.size() - last;// NECV.size();
					nextE += necvSize;
					childE += necvSize;
					q_prime->vertexNum += necvSize;
					if (q_prime->child[i].s == -1)
					{
						q_prime->child[i].s = childS;
					}
					q_prime->child[i].e = childE;
					for (int k = 0; k < necvSize; k++)
					{
						int lk = last + k;
						q_prime->vList.push_back(C[j]->label);
						if (q_prime->NEC[lk].size() >= 2 && q->HasEdge(q_prime->NEC[lk][0], q_prime->NEC[lk][1]))
							q_prime->isLinked.push_back(true);
						else
							q_prime->isLinked.push_back(false);
						//q_prime->NEC.push_back(NECV[k]);
						q_prime->parent.push_back(i);
						q_prime->child.push_back(child);
					}
				}
				childS = childE + 1;
				for (auto& p : C)
				{
					if (p != NULL)
						delete p;
				}
			}
		}
	}
	if (flag != NULL)
		delete[] flag;
}

void TurboMatch::ClearCR(Vid uc_Dprime, Vid v_prime, CRTree *CR)
{
	int pos = contain(v_prime, &(CR->parent[uc_Dprime]));
	vector <Vid>::iterator Iter1 = CR->parent[uc_Dprime].begin() + pos;
	CR->parent[uc_Dprime].erase(Iter1);
	vector <vector <Vid> >::iterator Iter2 = CR->CR[uc_Dprime].begin() + pos;
	CR->CR[uc_Dprime].erase(Iter2);
	/*int pos = contain(v_prime, &(CR->parent[uc_Dprime]));
	vector <Vid>::iterator Iter1 = CR->parent[uc_Dprime].begin() + pos;
	CR->parent[uc_Dprime].erase(Iter1);
	vector <vector <Vid> >::iterator Iter2 = CR->CR[uc_Dprime].begin() + pos;
	CR->CR[uc_Dprime].erase(Iter2);*/
	//CR->CR[uc_Dprime].erase(v_prime);
}

bool TurboMatch::ExploreCR(int u_prime, unordered_set <Vid> *VM, CRTree *CR, Vid v, NECTree *q_prime, MemoryGraph *g, MemoryGraph *q, bool* visited, bool& candup)
{
	int vertex = q_prime->NEC[u_prime][0];
	if (nodeArea != NULL)
	{
		if ((*nodeArea)[vertex] != NULL)
		{
			for (auto& vi : (*(*nodeArea)[vertex]))
			{
				if ((*VM).find(vi) == (*VM).end())
				{
					continue;
				}
				if (!candup && visited[vi])
					continue;
				int u_primeNEC1 = q_prime->NEC[u_prime][0];
				int v_prime = vi;

				if ((*q->outedges)[u_primeNEC1].size() > (*g->outedges)[v_prime].size())
				{
					continue;
				}

				unordered_set<int>* qs = &q->neighLabels[u_primeNEC1];
				int Size1 = qs->size();
				int Size2 = g->neighLabels[v_prime].size();
				if (Size1 > Size2)
					continue;

				bool f = true;
				for (const auto& label : *qs)
				{
					//int label = (*q->labelEdgesVec)[u_primeNEC1][j].label;

					if ((*g->labelEdgesVec)[v_prime][label] == NULL)
					{
						f = false;
						break;
					}
					if ((*q->labelEdgesVec)[u_primeNEC1][label]->vList.size() >(*g->labelEdgesVec)[v_prime][label]->vList.size())
					{
						f = false;
						break;
					}
				}
				if (!f)
					continue;

				visited[vi] = true;
				bool matched = true;

				int S = q_prime->child[u_prime].s;
				if (S != -1)
				{
					int E = q_prime->child[u_prime].e;
					int Len = E - S + 1;

					TurboNeighbor *neighbor = new TurboNeighbor[Len];
					for (int j = S; j <= E; j++)
					{
						int label = q_prime->vList[j];
						int pos = label;// contain(label, &(*g->labelEdgesVec)[v_prime]);
						neighbor[j - S].uc_prime = j;
						neighbor[j - S].pos = pos;
						//neighbor[j - S].NeighborN = g->edgeList[v_prime][pos].vList.size();
						neighbor[j - S].NeighborN = data->commNetworkSet[v_prime][distributeplan[q_prime->NEC[j][0]]][label].size();
					}
					qsort(neighbor, Len, sizeof(TurboNeighbor), cmp);

					for (int j = 0; j < Len; j++)
					{
						int label = q_prime->vList[j + S];
						//if (!ExploreCR(neighbor[j].uc_prime, &((*g->outedges)[v_prime]), CR, v_prime, q_prime, g, q, visited, candup))			
						if (!ExploreCR(neighbor[j].uc_prime, &data->commNetworkSet[v_prime][distributeplan[q_prime->NEC[neighbor[j].uc_prime][0]]][label]
							, CR, v_prime, q_prime, g, q, visited, candup))
						{
							for (int k = 0; k < j; k++)
							{
								ClearCR(neighbor[k].uc_prime, v_prime, CR);
							}
							matched = false;
							break;
						}
					}

					delete[]neighbor;
				}
				visited[vi] = false;
				if (!matched)
					continue;

				int pos = contain(v, &(CR->parent[u_prime]));
				if (pos == -1)
				{
					CR->parent[u_prime].push_back(v);
					vector <Vid> tempV;
					tempV.push_back(v_prime);
					CR->CR[u_prime].push_back(tempV);
				}
				else CR->CR[u_prime][pos].push_back(v_prime);
			}
			int pos = contain(v, &(CR->parent[u_prime]));
			if (pos == -1)
			{
				return false;
			}
			set<int> temp(CR->CR[u_prime][pos].begin(), CR->CR[u_prime][pos].end());
			CR->CR[u_prime][pos] = vector<int>(temp.begin(), temp.end());
			if (CR->CR[u_prime][pos].size() < q_prime->NEC[u_prime].size())
			{
				ClearCR(u_prime, v, CR);
				return false;
			}
			// sort(CR->CR[u_prime][pos].begin(), CR->CR[u_prime][pos].end());
			return true;
		}
		else
		{
			for (auto& vi : *VM)
			{
				if (data->nodeInfo[vi][0] != distributeplan[vertex])
				{
					continue;
				}
				if (!candup && visited[vi])
					continue;
				int u_primeNEC1 = q_prime->NEC[u_prime][0];
				int v_prime = vi;

				if ((*q->outedges)[u_primeNEC1].size() > (*g->outedges)[v_prime].size())
				{
					continue;
				}

				unordered_set<int>* qs = &q->neighLabels[u_primeNEC1];
				int Size1 = qs->size();
				int Size2 = g->neighLabels[v_prime].size();
				if (Size1 > Size2)
					continue;

				bool f = true;
				for (const auto& label : *qs)
				{
					//int label = (*q->labelEdgesVec)[u_primeNEC1][j].label;

					if ((*g->labelEdgesVec)[v_prime][label] == NULL)
					{
						f = false;
						break;
					}
					if ((*q->labelEdgesVec)[u_primeNEC1][label]->vList.size() >(*g->labelEdgesVec)[v_prime][label]->vList.size())
					{
						f = false;
						break;
					}
				}
				if (!f)
					continue;

				visited[vi] = true;
				bool matched = true;

				int S = q_prime->child[u_prime].s;
				if (S != -1)
				{
					int E = q_prime->child[u_prime].e;
					int Len = E - S + 1;

					TurboNeighbor *neighbor = new TurboNeighbor[Len];
					for (int j = S; j <= E; j++)
					{
						int label = q_prime->vList[j];
						int pos = label;// contain(label, &(*g->labelEdgesVec)[v_prime]);
						neighbor[j - S].uc_prime = j;
						neighbor[j - S].pos = pos;
						//neighbor[j - S].NeighborN = g->edgeList[v_prime][pos].vList.size();
						neighbor[j - S].NeighborN = data->commNetworkSet[v_prime][distributeplan[q_prime->NEC[j][0]]][label].size();
					}
					qsort(neighbor, Len, sizeof(TurboNeighbor), cmp);

					for (int j = 0; j < Len; j++)
					{
						int label = q_prime->vList[j + S];
						/*if (CR->CR[neighbor[j].uc_prime].find(vi) != CR->CR[neighbor[j].uc_prime].end())
						{
						continue;
						}*/
						//if (!ExploreCR(neighbor[j].uc_prime, &((*g->outedges)[v_prime]), CR, v_prime, q_prime, g, q, visited, candup))	
						if (!ExploreCR(neighbor[j].uc_prime, &data->commNetworkSet[v_prime][distributeplan[q_prime->NEC[neighbor[j].uc_prime][0]]][label]
							, CR, v_prime, q_prime, g, q, visited, candup))
						{
							for (int k = 0; k < j; k++)
							{
								ClearCR(neighbor[k].uc_prime, v_prime, CR);
							}
							matched = false;
							break;
						}
					}

					delete[]neighbor;
				}
				visited[vi] = false;
				if (!matched)
					continue;

				int pos = contain(v, &(CR->parent[u_prime]));
				if (pos == -1)
				{
					CR->parent[u_prime].push_back(v);
					vector <Vid> tempV;
					tempV.push_back(v_prime);
					CR->CR[u_prime].push_back(tempV);
				}
				else CR->CR[u_prime][pos].push_back(v_prime);
			}
			int pos = contain(v, &(CR->parent[u_prime]));
			if (pos == -1)
			{
				return false;
			}
			set<int> temp(CR->CR[u_prime][pos].begin(), CR->CR[u_prime][pos].end()); //多条路径到上一个节点的57，使得重复push v_prime
			CR->CR[u_prime][pos] = vector<int>(temp.begin(), temp.end());
			if (CR->CR[u_prime][pos].size() < q_prime->NEC[u_prime].size())
			{
				ClearCR(u_prime, v, CR);
				return false;
			}
			//sort(CR->CR[u_prime][pos].begin(), CR->CR[u_prime][pos].end());
			return true;
		}
	}
	else
	{
		int VMSize = VM->size();
		//for (int i = 0; i < VMSize; i++)
		for (auto& vi : (*VM))
		{
			if (!candup && visited[vi])
				continue;
			int u_primeNEC1 = q_prime->NEC[u_prime][0];
			int v_prime = vi;

			unordered_set<int>* qs = &q->neighLabels[u_primeNEC1];
			int Size1 = qs->size();
			int Size2 = g->neighLabels[v_prime].size();
			if (Size1 > Size2)
				continue;

			if (storeType != 2)
			{
				if ((*q->outedges)[u_primeNEC1].size() > (*g->outedges)[v_prime].size())
				{
					continue;
				}

				bool f = true;
				for (const auto& label : *qs)
				{
					//int label = (*q->labelEdgesVec)[u_primeNEC1][j].label;
					if ((*g->labelEdgesVec)[v_prime][label] == NULL)
					{
						f = false;
						break;
					}
					if ((*q->labelEdgesVec)[u_primeNEC1][label]->vList.size() > (*g->labelEdgesVec)[v_prime][label]->vList.size())
					{
						f = false;
						break;
					}
				}
				if (!f)
					continue;
			}

			visited[vi] = true;
			bool matched = true;
			//unordered_set<int>* vedge = &(*g->outedges)[v_prime];
			//int vsize = vedge->size();

			int S = q_prime->child[u_prime].s;
			if (S != -1)
			{
				int E = q_prime->child[u_prime].e;
				int Len = E - S + 1;

				TurboNeighbor *neighbor = new TurboNeighbor[Len];
				for (int j = S; j <= E; j++)
				{
					int label = q_prime->vList[j];
					int pos = label;// contain(label, &(*g->labelEdgesVec)[v_prime]);
					neighbor[j - S].uc_prime = j;
					neighbor[j - S].pos = pos;
					neighbor[j - S].NeighborN = (*g->labelEdgesVec)[v_prime][pos]->vList.size();
					//neighbor[j - S].NeighborN = vsize;
				}
				qsort(neighbor, Len, sizeof(TurboNeighbor), cmp);

				for (int j = 0; j < Len; j++)
				{
					if (!ExploreCR(neighbor[j].uc_prime, &(*g->labelEdgesVec)[v_prime][neighbor[j].pos]->vList, CR, v_prime, q_prime, g, q, visited, candup))
					{
						for (int k = 0; k < j; k++)
						{
							ClearCR(neighbor[k].uc_prime, v_prime, CR);
						}
						matched = false;
						break;
					}
				}

				delete[]neighbor;
			}
			visited[vi] = false;
			if (!matched)
				continue;

			int pos = contain(v, &(CR->parent[u_prime]));
			if (pos == -1)
			{
				CR->parent[u_prime].push_back(v);
				vector <Vid> tempV;
				tempV.push_back(v_prime);
				CR->CR[u_prime].push_back(tempV);
			}
			else CR->CR[u_prime][pos].push_back(v_prime);
		}
		int pos = contain(v, &(CR->parent[u_prime]));
		if (pos == -1)
		{
			return false;
		}
		set<int> temp(CR->CR[u_prime][pos].begin(), CR->CR[u_prime][pos].end());
		CR->CR[u_prime][pos] = vector<int>(temp.begin(), temp.end());
		if (storeType != 2 && CR->CR[u_prime][pos].size() < q_prime->NEC[u_prime].size())
		{
			ClearCR(u_prime, v, CR);
			return false;
		}
		//sort(CR->CR[u_prime][pos].begin(), CR->CR[u_prime][pos].end());
		return true;
	}
}

bool TurboMatch::ExploreCR(int u_prime, vector<Vid> *VM, CRTree *CR, Vid v, NECTree *q_prime, MemoryGraph *g, MemoryGraph *q, bool* visited, bool& candup)
{
	int vertex = q_prime->NEC[u_prime][0];

	{
		int VMSize = VM->size();
		//for (int i = 0; i < VMSize; i++)
		for (auto& vi : (*VM))
		{
			if (!candup && visited[vi])
				continue;
			int u_primeNEC1 = q_prime->NEC[u_prime][0];
			int v_prime = vi;

			unordered_set<int>* qs = &q->neighLabels[u_primeNEC1];
			int Size1 = qs->size();
			int Size2 = g->neighLabels[v_prime].size();
			if (Size1 > Size2)
				continue;

			if (storeType != 2)
			{
				if ((*q->outedges)[u_primeNEC1].size() > (*g->outedges)[v_prime].size())
				{
					continue;
				}

				bool f = true;
				for (const auto& label : *qs)
				{
					//int label = (*q->labelEdgesVec)[u_primeNEC1][j].label;
					int();
					if ((*g->labelEdgesVec)[v_prime][label] == NULL)
					{
						f = false;
						break;
					}
					if ((*q->labelEdgesVec)[u_primeNEC1][label]->vList.size() >(*g->labelEdgesVec)[v_prime][label]->vList.size())
					{
						f = false;
						break;
					}
				}
				if (!f)
					continue;
			}

			visited[vi] = true;
			bool matched = true;
			//unordered_set<int>* vedge = &(*g->outedges)[v_prime];
			//int vsize = vedge->size();

			int S = q_prime->child[u_prime].s;
			if (S != -1)
			{
				int E = q_prime->child[u_prime].e;
				int Len = E - S + 1;

				TurboNeighbor *neighbor = new TurboNeighbor[Len];
				for (int j = S; j <= E; j++)
				{
					int label = q_prime->vList[j];
					int pos = label;// contain(label, &(*g->labelEdgesVec)[v_prime]);
					neighbor[j - S].uc_prime = j;
					neighbor[j - S].pos = pos;
					neighbor[j - S].NeighborN = (*g->labelEdgesVec)[v_prime][pos]->vList.size();
					//neighbor[j - S].NeighborN = vsize;
				}
				qsort(neighbor, Len, sizeof(TurboNeighbor), cmp);

				for (int j = 0; j < Len; j++)
				{
					if (!ExploreCR(neighbor[j].uc_prime, &(*g->labelEdgesVec)[v_prime][neighbor[j].pos]->vList, CR, v_prime, q_prime, g, q, visited, candup))
					{
						for (int k = 0; k < j; k++)
						{
							ClearCR(neighbor[k].uc_prime, v_prime, CR);
						}
						matched = false;
						break;
					}
				}

				delete[]neighbor;
			}
			visited[vi] = false;
			if (!matched)
				continue;

			int pos = contain(v, &(CR->parent[u_prime]));
			if (pos == -1)
			{
				CR->parent[u_prime].push_back(v);
				vector <Vid> tempV;
				tempV.push_back(v_prime);
				CR->CR[u_prime].push_back(tempV);
			}
			else CR->CR[u_prime][pos].push_back(v_prime);
		}
		int pos = contain(v, &(CR->parent[u_prime]));
		if (pos == -1)
		{
			return false;
		}
		set<int> temp(CR->CR[u_prime][pos].begin(), CR->CR[u_prime][pos].end());
		CR->CR[u_prime][pos] = vector<int>(temp.begin(), temp.end());
		if (storeType != 2 && CR->CR[u_prime][pos].size() < q_prime->NEC[u_prime].size())
		{
			ClearCR(u_prime, v, CR);
			return false;
		}
		//sort(CR->CR[u_prime][pos].begin(), CR->CR[u_prime][pos].end());
		return true;
	}
}

double TurboMatch::C(int n, int m)
{
	if (n < m)
		return 0.0;
	else if (n == m)
		return 1.0;
	else
	{
		double res = 1.0;
		for (int i = 0; i < m; i++)
		{
			res *= (double)(n - i) / (m - i);
		}
		return res;
	}
}

double TurboMatch::DetermineMatchingOrder(NECTree *q_prime, CRTree *CRTree, TurboElem *order, Vid v, int product, MemoryGraph *q)
{
	int ENum = 0;
	int nSize = q_prime->NEC[v].size();
	for (int ii = 0; ii < nSize; ii++)
	{
		int vv = q_prime->NEC[v][ii];
		ENum += (*q->outedges)[vv].size();
		//int graS = q->edgeList[vv].size();
		//for (int i = 0; i < graS; i++)
		//	ENum += q->edgeList[vv][i].vList.size();
	}

	if (nSize > 1)
	{
		/*int Label = q_prime->vList[v];
		vector <LabelVList> *p = &(*q->labelEdgesVec)[q_prime->NEC[v][0]];
		int pos = contain(Label, p);
		if (pos != -1)
		{
		if (contain(q_prime->NEC[v][1], &((*p)[pos].vList)) != -1)
		{
		ENum -= nSize * (nSize - 1) / 2;
		}
		}*/

		if ((*q->outedges)[q_prime->NEC[v][0]].find(q_prime->NEC[v][1]) != (*q->outedges)[q_prime->NEC[v][0]].end())
		{
			ENum -= nSize * (nSize - 1) / 2;
		}
	}

	int S = q_prime->child[v].s;
	if (S != -1)
	{
		int E = q_prime->child[v].e;
		int Product;
		if (v == 0)
		{
			int eNum = 0;
			for (int jj = S; jj <= E; jj++)
			{
				eNum += nSize * q_prime->NEC[jj].size();
			}
			Product = product * (ENum - eNum + 1);
		}
		else
		{
			int eNum = nSize * q_prime->NEC[q_prime->parent[v]].size();
			for (int jj = S; jj <= E; jj++)
			{
				eNum += nSize * q_prime->NEC[jj].size();
			}
			Product = product * (ENum - eNum + 1);
		}
		double Min = DBL_MAX;
		for (int i = S; i <= E; i++)
		{
			double tempD = DetermineMatchingOrder(q_prime, CRTree, order, i, Product, q);
			if (Min - tempD > 1e-6)
				Min = tempD;
		}
		order[v].v = v;
		order[v].value = Min;
		return order[v].value;
	}
	else
	{
		if (q_prime->parent[v] == -1)
		{
			order[v].v = v;
			order[v].value = 0;
			return order[v].value;
		}
		int eNum = nSize * q_prime->NEC[q_prime->parent[v]].size();
		int Product = product * (ENum - eNum + 1);
		int Size = q_prime->NEC[v].size();
		if (Size == 1)
		{
			int Num = 0;
			int Size2 = CRTree->CR[v].size();
			for (int i = 0; i < Size2; i++)
			{
				Num += CRTree->CR[v][i].size();
			}
			order[v].v = v;
			order[v].value = (double)Num / Product;
		}
		else
		{
			double Num = 0.0;
			int Size2 = CRTree->CR[v].size();
			for (int i = 0; i < Size2; i++)
			{
				Num += C(CRTree->CR[v][i].size(), Size);
			}
			order[v].v = v;
			order[v].value = Num / Product;
		}
		return order[v].value;
	}
}

void TurboMatch::UpdateState(int* M, bool* F, vector <Vid> *qV, vector <Vid> *gV)
{
	int Size = qV->size();
	for (int i = 0; i < Size; i++)
	{
		int g = (*gV)[i];
		F[g] = true;
		M[(*qV)[i]] = g;
	}
}

void TurboMatch::UpdateStateDense(int* M, bool* F, vector <Vid> *qV, vector <Vid> *gV)
{
	int Size = qV->size();
	for (int i = 0; i < Size; i++)
	{
		int g = (*gV)[i];
		F[g] = true;
	}
}

void TurboMatch::UpdateState(int* M, vector <Vid> *qV, vector <Vid> *gV)
{
	int Size = qV->size();
	for (int i = 0; i < Size; i++)
	{
		int g = (*gV)[i];
		M[(*qV)[i]] = g;
	}
}

void TurboMatch::NextComb(vector <Vid> *C, int Size, vector <int> *rank, vector <Vid> *value, int& dc, NECTree *q_prime, bool super)
{
	if (true)
	{
		if ((*rank)[0] == -1)
		{
			(*rank)[0] = 0;
			int cz = (*C)[0];
			(*value).push_back(cz);
			for (int i = 1; i < Size; i++)
			{
				(*rank).push_back(0);
				(*value).push_back(cz);
			}
			return;
		}

		int pos = Size - 1;
		(*rank)[pos]++;
		if ((*rank)[pos] >= C->size())
		{
			for (pos = pos - 1; pos >= 0; pos--)
			{
				(*rank)[pos]++;
				if ((*rank)[pos] < C->size())// && (*C).size() - (*rank)[pos] >= Size - pos)
				{
					int rp = (*rank)[pos];
					int rsize = (*rank).size();
					(*value)[pos] = (*C)[rp];
					for (int j = pos + 1; j < rsize; j++)
					{
						(*rank)[j] = rp;
						(*value)[j] = (*C)[rp];
					}
					break;
				}
			}
			if (pos == -1)
			{
				(*rank)[0] = -1;
				return;
			}
		}
		else
		{
			(*value)[pos] = (*C)[(*rank)[pos]];
		}
	}
}

void TurboMatch::NextComb(vector <Vid> *C, int Size, vector <int> *rank, vector <Vid> *value, int& dc, NECTree *q_prime, int& midvalpos, int& midval, int& bigpos, bool super)
{
	if (true)
	{
		if ((*rank)[0] == -1)
		{
			(*rank).clear();
			//(*value).push_back((*C)[0]);
			for (int i = 0; i < midvalpos; i++)
			{
				(*rank).push_back(0);
				(*value).push_back((*C)[0]);
			}
			for (int i = midvalpos; i < Size; i++)
			{
				(*rank).push_back(bigpos);
				(*value).push_back((*C)[bigpos]);
			}
			return;
		}

		int pos = Size - 1;
		(*rank)[pos]++;
		if ((*rank)[pos] >= (*C).size() || (pos < midvalpos && (*C)[(*rank)[pos]] > midval))
		{
			for (pos = pos - 1; pos >= 0; pos--)
			{
				(*rank)[pos]++;
				if ((*rank)[pos] < (*C).size())
				{
					if (pos < midvalpos && (*C)[(*rank)[pos]] > midval)
					{
						continue;
					}
					else
					{
						if (pos < midvalpos)
						{
							(*value)[pos] = (*C)[(*rank)[pos]];
							for (int j = pos + 1; j < midvalpos; j++)
							{
								(*rank)[j] = (*rank)[pos];
								(*value)[j] = (*C)[(*rank)[j]];
							}
							for (int j = midvalpos; j < Size; j++)
							{
								(*rank)[j] = bigpos;
								(*value)[j] = (*C)[bigpos];
							}
							break;
						}
						else
						{
							(*value)[pos] = (*C)[(*rank)[pos]];
							for (int j = pos + 1; j < Size; j++)
							{
								(*rank)[j] = (*rank)[pos];
								(*value)[j] = (*C)[(*rank)[j]];
							}
							break;
						}
					}
				}
			}
			if (pos == -1)
			{
				(*rank)[0] = -1;
				return;
			}
		}
		else
		{
			(*value)[pos] = (*C)[(*rank)[pos]];
		}
	}
}

void TurboMatch::NextComb(vector <Vid> *C, int Size, vector <int> *rank, vector <Vid> *value, int& dc, int& u_prime, NECTree *q_prime)
{
	if ((*rank)[0] == -1)
	{
		(*rank)[0] = 0;
		(*value).push_back((*C)[0]);
		for (int i = 1; i < Size; i++)
		{
			(*rank).push_back(i);
			(*value).push_back((*C)[i]);
		}
		return;
	}

	int pos = Size - 1;
	(*rank)[pos]++;
	if ((*rank)[pos] >= (*C).size())
	{
		for (pos = pos - 1; pos >= 0; pos--)
		{
			(*rank)[pos]++;
			if ((*rank)[pos] < (*C).size() && (*C).size() - (*rank)[pos] >= Size - pos)
			{
				(*value)[pos] = (*C)[(*rank)[pos]];
				for (int j = pos + 1; j < (*rank).size(); j++)
				{
					(*rank)[j] = (*rank)[j - 1] + 1;
					(*value)[j] = (*C)[(*rank)[j]];
				}
				break;
			}
		}
		if (pos == -1)
		{
			(*rank)[0] = -1;
			return;
		}
	}
	else
	{
		(*value)[pos] = (*C)[(*rank)[pos]];
	}
}

int TurboMatch::GetFirst(vector <Vid>& C, int Size, vector <int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos)
{
	if (pos < 0)
	{
		return -1;
	}

	int old_rank = rank[pos];
	int old_val = value[pos];
	int cur = q_prime->NEC[dc][pos];

	if (old_val != -1)
	{
		for (const auto& neigh : (*q->outedges)[cur])
		{
			int commNeigh = ncMap[neigh.first];
			if (commNeigh != -1)
			{
				n2cNum[cur][commNeigh] = 0;
				n2cNum[neigh.first][old_val]--;
			}
		}

		//currentMap[old_val].erase(q_prime->NEC[dc][pos]);
		ncMap[cur] = -1;
		for (const auto& neigh : toadd[cur])
		{
			penv[neigh].pop_back();
			penv_en[neigh].pop_back();
		}
		for (const auto& neigh_pair : existaddpos[cur])
		{
			penv_en[neigh_pair.first][neigh_pair.second].pop_back();
		}
		toadd[cur].clear();
		existaddpos[cur].clear();
		penv[cur].clear();
		penv_en[cur].clear();
	}

	while (true)
	{
		bool find = false;

		while (true)
		{
			rank[pos]++;
			if (rank[pos] < C.size())
			{
				int val = C[rank[pos]];
				bool takeover = true;
				ncMap[cur] = val;
				
				for (const auto& v : gm->IETreeS[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] < ncMap[cur])))
					{
						takeover = false;
						break;
					}
				}
				if (!takeover)
				{
					ncMap[cur] = -1;
					find = false;
					break;
				}
				int maxlevel = -1;
				for (const auto& v : gm->IETreeL[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] > ncMap[cur])))
					{
						takeover = false;
						maxlevel = max(maxlevel, ncMap[v]);
						//break;
					}
				}
				if (!takeover)
				{
					rank[pos] = lower_bound(C.begin() + rank[pos], C.end(), maxlevel) - C.begin() - 1;
					ncMap[cur] = -1;
					continue;
				}

				//recn2c = n2cNum;
				for (const auto& neigh : (*q->outedges)[cur])
				{
					int commNeigh = ncMap[neigh.first];
					if (commNeigh != -1)
					{
						n2cNum[cur][commNeigh]++;
						n2cNum[neigh.first][val]++;
						if (n2cNum[cur][commNeigh] > data->commMaxNumTag[val][commNeigh]
							|| n2cNum[neigh.first][val] > data->commMaxNumTag[commNeigh][val])
						{
							for (const auto& n : (*q->outedges)[cur])
							{
								int commN = ncMap[n.first];
								if (commN != -1)
								{
									n2cNum[cur][commN]--;
									n2cNum[n.first][val]--;
								}

								if (n == neigh)
									break;
							}
							takeover = false;
							break;
						}
					}
				}
				if (!takeover)
				{
					//n2cNum = recn2c;
					ncMap[cur] = -1;
					continue;
				}

				//vector<int> mys;
				unordered_set<int> myrecord;
				for (int i = 0; i < (*q->outvec)[cur].size(); ++i)
				{
					int neigh = (*q->outvec)[cur][i];
					if (ncMap[neigh] != -1)
					{
						int nval = ncMap[neigh];

						if (!gm->share1NeighbourPairs[val][nval])
						{
							takeover = false;
							break;
						}

						bool added = true;
						for (int j = 0; j < penv[neigh].size(); ++j)
						{
							int c2 = penv[neigh][j];
							if (val == c2)
							{
								added = false;
								addpos = j;
							}
							//else
							{
								if (!gm->share2NeighbourPairs[nval][val][c2])
								{
									takeover = false;
									break;
								}
							}

							for (int k = 0; k < penv[cur].size(); ++k)
							{
								//if (penv[cur][k] == nval)
								//	continue;
								bool catchv = false;
								for (const auto& p1 : penv_en[cur][k])
								{
									for (const auto& p2 : penv_en[neigh][j])
									{
										if (p1 == p2)
										{
											catchv = true;
											break;
										}
									}
									if (catchv)
										break;
								}
								//if ((catchv && !data->triangleLimitation[penv[cur][k]][val][nval][c2]) || (!catchv && !data->len4Limitation[penv[cur][k]][val][nval][c2]))
								if (catchv && !data->triangleLimitation[penv[cur][k]][val][nval])
								{
									takeover = false;
									break;
								}
							}
							if (!takeover)
								break;
						}
						if (!takeover)
							break;

						if (myrecord.find(nval) == myrecord.end())
						{
							penv[cur].push_back(nval);
							penv_en[cur].push_back(vector<int>(1, neigh));
							myrecord.insert(nval);
						}
						else
						{
							for (int index = penv_en[cur].size() - 1; index >= 0; --index)
							{
								if (penv[cur][index] == nval)
								{
									penv_en[cur][index].push_back(neigh);
									break;
								}
							}
						}
						//mys.push_back(nval);

						for (int p = 0; p < penv[neigh].size(); ++p)
						{
							for (int p_en = 0; p_en < penv_en[neigh][p].size(); ++p_en)
							{
								int nn = penv_en[neigh][p][p_en];
								int comm_nn = ncMap[nn];
								//if (nn != cur)
								{
									for (int q = 0; q < penv[nn].size(); ++q)
									{
										int env = penv[nn][q];
										//if ((penv_en[nn][q].size() > 1 || penv_en[nn][q][0] != neigh) && !data->len4Limitation[val][nval][comm_nn][env])
										//{
										//	takeover = false;
										//	break;
										//}
									}
									if (!takeover)
										break;
								}
							}
							if (!takeover)
								break;
						}
						if (!takeover)
							break;

						if (added)
						{
							toadd[cur].push_back(neigh);
						}
						else
						{
							existaddpos[cur].push_back(make_pair(neigh, addpos));
						}
					}
				}
				if (!takeover)
				{
					penv[cur].clear();
					penv_en[cur].clear();
					toadd[cur].clear();
					existaddpos[cur].clear();
					ncMap[cur] = -1;
					//n2cNum = recn2c;
					for (const auto& n : (*q->outedges)[cur])
					{
						int commN = ncMap[n.first];
						if (commN != -1)
						{
							n2cNum[cur][commN]--;
							n2cNum[n.first][val]--;
						}
					}
					continue;
				}

				/*if (!penv[cur].empty())
				{
				for (int i = 0; i < penv[cur].size(); ++i)
				{
				for (int j = i + 1; j < penv[cur].size(); ++j)
				{
				//if (!gm->share2NeighbourPairs[val][penv[cur][i]][penv[cur][j]])
				//{
				//	takeover = false;
				//	break;
				//}
				}
				if (!takeover)
				break;
				}
				}
				if (!takeover)
				{
				penv[cur].clear();
				penv_en[cur].clear();
				toadd[cur].clear();
				existaddpos[cur].clear();
				ncMap[cur] = -1;
				continue;
				}*/

				for (const auto& neigh : toadd[cur])
				{
					penv[neigh].push_back(val);
					penv_en[neigh].push_back(vector<int>(1, cur));
				}
				for (const auto& neigh_pair : existaddpos[cur])
				{
					penv_en[neigh_pair.first][neigh_pair.second].push_back(cur);
				}
				find = true;
				break;
			}
			else
			{
				find = false;
				break;
			}
		}

		if (!find)
		{
			//pos--;
			int k = GetComb(C, Size, rank, value, dc, q_prime, pos - 1);
			if (k < 0)
			{
				ncMap[cur] = -1;
				return -1;
			}
			//pos++;
			rank[pos] = rank[pos - 1] - 1;
		}
		else
		{
			break;
		}
	}

	value[pos] = C[rank[pos]];
	if (pos + 1 < rank.size())
	{
		rank[pos + 1] = rank[pos] - 1;
		value[pos + 1] = -1;
		return GetFirst(C, Size, rank, value, dc, q_prime, pos + 1);
	}
	else
		return 0;
}

int TurboMatch::GetComb(vector <Vid>& C, int Size, vector <int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos)
{
	if (pos < 0)
	{
		return -1;
	}

	int old_rank = rank[pos];
	int old_val = value[pos];
	int cur = q_prime->NEC[dc][pos];
	ncMap[cur] = -1;

	for (const auto& neigh : (*q->outedges)[cur])
	{
		int commNeigh = ncMap[neigh.first];
		if (commNeigh != -1)
		{
			n2cNum[cur][commNeigh] = 0;
			n2cNum[neigh.first][old_val]--;
		}
	}

	for (const auto& neigh : toadd[cur])
	{
		penv[neigh].pop_back();
		penv_en[neigh].pop_back();
	}
	for (const auto& neigh_pair : existaddpos[cur])
	{
		penv_en[neigh_pair.first][neigh_pair.second].pop_back();
	}
	toadd[cur].clear();
	existaddpos[cur].clear();
	penv[cur].clear();
	penv_en[cur].clear();

	while (true)
	{
		bool find = false;

		while (true)
		{
			rank[pos]++;
			if (rank[pos] < C.size())
			{
				int val = C[rank[pos]];
				bool takeover = true;
				ncMap[cur] = val;
				
				for (const auto& v : gm->IETreeS[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] < ncMap[cur])))
					{
						takeover = false;
						break;
					}
				}
				if (!takeover)
				{
					ncMap[cur] = -1;
					find = false;
					break;
				}
				int maxlevel = -1;
				for (const auto& v : gm->IETreeL[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] > ncMap[cur])))
					{
						takeover = false;
						maxlevel = max(maxlevel, ncMap[v]);
						//break;
					}
				}
				if (!takeover)
				{
					rank[pos] = lower_bound(C.begin() + rank[pos], C.end(), maxlevel) - C.begin() - 1;
					ncMap[cur] = -1;
					continue;
				}

				//recn2c = n2cNum;
				for (const auto& neigh : (*q->outedges)[cur])
				{
					int commNeigh = ncMap[neigh.first];
					if (commNeigh != -1)
					{
						n2cNum[cur][commNeigh]++;
						n2cNum[neigh.first][val]++;
						if (n2cNum[cur][commNeigh] > data->commMaxNumTag[val][commNeigh]
							|| n2cNum[neigh.first][val] > data->commMaxNumTag[commNeigh][val])
						{
							for (const auto& n : (*q->outedges)[cur])
							{
								int commN = ncMap[n.first];
								if (commN != -1)
								{
									n2cNum[cur][commN]--;
									n2cNum[n.first][val]--;
								}

								if (n == neigh)
									break;
							}
							takeover = false;
							break;
						}
					}
				}
				if (!takeover)
				{
					//n2cNum = recn2c;
					ncMap[cur] = -1;
					continue;
				}

				//vector<int> mys;
				unordered_set<int> myrecord;
				for (int i = 0; i < (*q->outvec)[cur].size(); ++i)
				{
					int neigh = (*q->outvec)[cur][i];
					if (ncMap[neigh] != -1)
					{
						int nval = ncMap[neigh];

						if (!gm->share1NeighbourPairs[val][nval])
						{
							takeover = false;
							break;
						}

						bool added = true;
						for (int j = 0; j < penv[neigh].size(); ++j)
						{
							int c2 = penv[neigh][j];
							if (val == c2)
							{
								added = false;
								addpos = j;
							}
							//else
							{
								if (!gm->share2NeighbourPairs[nval][val][c2])
								{
									takeover = false;
									break;
								}
							}

							for (int k = 0; k < penv[cur].size(); ++k)
							{
								//if (penv[cur][k] == nval)
								//	continue;
								bool catchv = false;
								for (const auto& p1 : penv_en[cur][k])
								{
									for (const auto& p2 : penv_en[neigh][j])
									{
										if (p1 == p2)
										{
											catchv = true;
											break;
										}
									}
									if (catchv)
										break;
								}
								//if ((catchv && !data->triangleLimitation[penv[cur][k]][val][nval][c2]) || (!catchv && !data->len4Limitation[penv[cur][k]][val][nval][c2]))
								if (catchv && !data->triangleLimitation[penv[cur][k]][val][nval])
								{
									takeover = false;
									break;
								}
							}
							if (!takeover)
								break;
						}
						if (!takeover)
							break;

						if (myrecord.find(nval) == myrecord.end())
						{
							penv[cur].push_back(nval);
							penv_en[cur].push_back(vector<int>(1, neigh));
							myrecord.insert(nval);
						}
						else
						{
							for (int index = penv_en[cur].size() - 1; index >= 0; --index)
							{
								if (penv[cur][index] == nval)
								{
									penv_en[cur][index].push_back(neigh);
									break;
								}
							}
						}
						//mys.push_back(nval);

						for (int p = 0; p < penv[neigh].size(); ++p)
						{
							for (int p_en = 0; p_en < penv_en[neigh][p].size(); ++p_en)
							{
								int nn = penv_en[neigh][p][p_en];
								int comm_nn = ncMap[nn];
								//if (nn != cur)
								{
									for (int q = 0; q < penv[nn].size(); ++q)
									{
										int env = penv[nn][q];
										//if ((penv_en[nn][q].size() > 1 || penv_en[nn][q][0] != neigh) && !data->len4Limitation[val][nval][comm_nn][env])
										//{
										//	takeover = false;
										//	break;
										//}
									}
									if (!takeover)
										break;
								}
							}
							if (!takeover)
								break;
						}
						if (!takeover)
							break;

						if (added)
						{
							toadd[cur].push_back(neigh);
						}
						else
						{
							existaddpos[cur].push_back(make_pair(neigh, addpos));
						}
					}
				}
				if (!takeover)
				{
					penv[cur].clear();
					penv_en[cur].clear();
					toadd[cur].clear();
					existaddpos[cur].clear();
					//n2cNum = recn2c;
					for (const auto& n : (*q->outedges)[cur])
					{
						int commN = ncMap[n.first];
						if (commN != -1)
						{
							n2cNum[cur][commN]--;
							n2cNum[n.first][val]--;
						}
					}
					ncMap[cur] = -1;
					continue;
				}

				/*if (!penv[cur].empty())
				{
				for (int i = 0; i < penv[cur].size(); ++i)
				{
				for (int j = i + 1; j < penv[cur].size(); ++j)
				{
				//if (!gm->share2NeighbourPairs[val][penv[cur][i]][penv[cur][j]])
				//{
				//	takeover = false;
				//	break;
				//}
				}
				if (!takeover)
				break;
				}
				}
				if (!takeover)
				{
				penv[cur].clear();
				penv_en[cur].clear();
				toadd[cur].clear();
				existaddpos[cur].clear();
				ncMap[cur] = -1;
				continue;
				}*/

				for (const auto& neigh : toadd[cur])
				{
					penv[neigh].push_back(val);
					penv_en[neigh].push_back(vector<int>(1, cur));
				}
				for (const auto& neigh_pair : existaddpos[cur])
				{
					penv_en[neigh_pair.first][neigh_pair.second].push_back(cur);
				}
				find = true;
				break;
			}
			else
			{
				find = false;
				break;
			}
		}

		if (!find)
		{
			//pos--;
			int k = GetComb(C, Size, rank, value, dc, q_prime, pos - 1);
			if (k < 0)
			{
				ncMap[cur] = -1;
				return -1;
			}
			//pos++;
			rank[pos] = rank[pos - 1] - 1;
		}
		else
		{
			break;
		}
	}

	value[pos] = C[rank[pos]];
	return 0;
}

int TurboMatch::GetFirstDense(vector <Vid>& C, int Size, vector <int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos)
{
	if (pos < 0)
	{
		return -1;
	}

	int old_rank = rank[pos];
	int old_val = value[pos];
	int cur = q_prime->NEC[dc][pos];

	if (old_val != -1)
	{
		ncMap[cur] = -1;
	}

	while (true)
	{
		bool find = false;

		while (true)
		{
			rank[pos]++;
			if (rank[pos] < C.size() && C.size() - rank[pos] >= Size - pos)
			{
				int val = C[rank[pos]];
				bool takeover = true;
				ncMap[cur] = val;
				for (const auto& v : gm->IETreeS[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] < ncMap[cur])))
					{
						takeover = false;
						break;
					}
				}
				if (!takeover)
				{
					ncMap[cur] = -1;
					find = false;
					break;
				}
				int maxlevel = -1;
				for (const auto& v : gm->IETreeL[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] > ncMap[cur])))
					{
						takeover = false;
						maxlevel = max(maxlevel, ncMap[v]);
						//break;
					}
				}
				if (!takeover)
				{
					rank[pos] = upper_bound(C.begin() + rank[pos], C.end(), maxlevel) - C.begin() - 1;
					ncMap[cur] = -1;
					continue;
				}

				find = true;
				break;
			}
			else
			{
				find = false;
				break;
			}
		}

		if (!find)
		{
			//pos--;
			int k = GetCombDense(C, Size, rank, value, dc, q_prime, pos - 1);
			if (k < 0)
			{
				ncMap[cur] = -1;
				return -1;
			}
			//pos++;
			rank[pos] = rank[pos - 1];
		}
		else
		{
			break;
		}
	}

	value[pos] = C[rank[pos]];
	if (pos + 1 < rank.size())
	{
		rank[pos + 1] = rank[pos];
		value[pos + 1] = -1;
		return GetFirstDense(C, Size, rank, value, dc, q_prime, pos + 1);
	}
	else
		return 0;
}

int TurboMatch::GetCombDense(vector <Vid>& C, int Size, vector <int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos)
{
	if (pos < 0)
	{
		return -1;
	}

	int old_rank = rank[pos];
	int old_val = value[pos];
	int cur = q_prime->NEC[dc][pos];
	ncMap[cur] = -1;

	while (true)
	{
		bool find = false;

		while (true)
		{
			rank[pos]++;
			if (rank[pos] < C.size() && C.size() - rank[pos] >= Size - pos)
			{
				int val = C[rank[pos]];
				bool takeover = true;
				ncMap[cur] = val;
				for (const auto& v : gm->IETreeS[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] < ncMap[cur])))
					{
						takeover = false;
						break;
					}
				}
				if (!takeover)
				{
					ncMap[cur] = -1;
					find = false;
					break;
				}
				int maxlevel = -1;
				for (const auto& v : gm->IETreeL[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] > ncMap[cur])))
					{
						takeover = false;
						maxlevel = max(maxlevel, ncMap[v]);
						//break;
					}
				}
				if (!takeover)
				{
					rank[pos] = upper_bound(C.begin() + rank[pos], C.end(), maxlevel) - C.begin() - 1;
					ncMap[cur] = -1;
					continue;
				}

				find = true;
				break;
			}
			else
			{
				find = false;
				break;
			}
		}

		if (!find)
		{
			//pos--;
			int k = GetCombDense(C, Size, rank, value, dc, q_prime, pos - 1);
			if (k < 0)
			{
				ncMap[cur] = -1;
				return -1;
			}
			//pos++;
			rank[pos] = rank[pos - 1];
		}
		else
		{
			break;
		}
	}

	value[pos] = C[rank[pos]];
	return 0;
}

int TurboMatch::GetFirstBound(vector <Vid>& C, int Size, vector <int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos)
{
	if (pos < 0)
	{
		return -1;
	}

	int old_rank = rank[pos];
	int old_val = value[pos];
	int cur = q_prime->NEC[dc][pos];

	if (old_val != -1)
	{
		ncMap[cur] = -1;
	}

	while (true)
	{
		bool find = false;

		while (true)
		{
			rank[pos]++;
			if (rank[pos] < C.size() && C.size() - rank[pos] >= Size - pos)
			{
				int val = C[rank[pos]];
				bool takeover = true;
				ncMap[cur] = val;

				for (const auto& v : pIETreeS[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] < ncMap[cur])))
					{
						takeover = false;
						break;
					}
				}

				if (!takeover)
				{
					ncMap[cur] = -1;
					find = false;
					break;
				}
				int maxlevel = -1;
				for (const auto& v : pIETreeL[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] > ncMap[cur])))
					{
						takeover = false;
						maxlevel = max(maxlevel, ncMap[v]);
						//break;
					}
				}
				if (!takeover)
				{
					rank[pos] = upper_bound(C.begin() + rank[pos], C.end(), maxlevel) - C.begin() - 1;
					ncMap[cur] = -1;
					continue;
				}

				find = true;
				break;
			}
			else
			{
				find = false;
				break;
			}
		}

		if (!find)
		{
			//pos--;
			int k = GetCombBound(C, Size, rank, value, dc, q_prime, pos - 1);
			if (k < 0)
			{
				ncMap[cur] = -1;
				return -1;
			}
			//pos++;
			rank[pos] = rank[pos - 1];
		}
		else
		{
			break;
		}
	}

	value[pos] = C[rank[pos]];
	if (pos + 1 < rank.size())
	{
		rank[pos + 1] = rank[pos];
		value[pos + 1] = -1;
		return GetFirstBound(C, Size, rank, value, dc, q_prime, pos + 1);
	}
	else
		return 0;
}

int TurboMatch::GetCombBound(vector <Vid>& C, int Size, vector <int>& rank, vector <Vid>& value, int& dc, NECTree *q_prime, int pos)
{
	if (pos < 0)
	{
		return -1;
	}

	int old_rank = rank[pos];
	int old_val = value[pos];
	int cur = q_prime->NEC[dc][pos];
	ncMap[cur] = -1;

	while (true)
	{
		bool find = false;

		while (true)
		{
			rank[pos]++;
			if (rank[pos] < C.size() && C.size() - rank[pos] >= Size - pos)
			{
				int val = C[rank[pos]];
				bool takeover = true;
				ncMap[cur] = val;
				
				for (const auto& v : pIETreeS[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] < ncMap[cur])))
					{
						takeover = false;
						break;
					}
				}
				if (!takeover)
				{
					ncMap[cur] = -1;
					find = false;
					break;
				}
				int maxlevel = -1;
				for (const auto& v : pIETreeL[cur])
				{
					if (ncMap[v] != -1 && ((ncMap[v] > ncMap[cur])))
					{
						takeover = false;
						maxlevel = max(maxlevel, ncMap[v]);
						//break;
					}
				}
				if (!takeover)
				{
					rank[pos] = upper_bound(C.begin() + rank[pos], C.end(), maxlevel) - C.begin() - 1;
					ncMap[cur] = -1;
					continue;
				}

				find = true;
				break;
			}
			else
			{
				find = false;
				break;
			}
		}

		if (!find)
		{
			//pos--;
			int k = GetCombBound(C, Size, rank, value, dc, q_prime, pos - 1);
			if (k < 0)
			{
				ncMap[cur] = -1;
				return -1;
			}
			//pos++;
			rank[pos] = rank[pos - 1];
		}
		else
		{
			break;
		}
	}

	value[pos] = C[rank[pos]];
	return 0;
}

bool TurboMatch::IsJoinableSuper(MemoryGraph *q, MemoryGraph *g, int* M, int qV, int gV)
{
	unordered_map<int, vector<int>>* og = &(*g->outedges)[gV];
	for (const auto& u : (*q->outedges)[qV])
	{
		int v = M[u.first];
		if (v != -1 && level[qV] != level[u.first] && og->find(v) == og->end())
		{
			return false;
		}
	}

	return true;
	/*int Size = q->edgeList[qV].size();
	for (int i = 0; i < Size; i++)
	{
	int label = q->edgeList[qV][i].label;
	int Size2 = q->edgeList[qV][i].vList.size();
	for (int j = 0; j < Size2; j++)
	{
	int u = q->edgeList[qV][i].vList[j];
	Vid v = M[u];
	if (v != -1)
	{
	int pos = contain(label, &(g->edgeList[gV]));
	if (pos == -1)
	return false;
	if (contain(v, &(g->edgeList[gV][pos].vList)) == -1)
	return false;
	}
	}
	}
	return true;*/
}

bool TurboMatch::IsJoinable(int* M, int qV, int gV)
{
	//unordered_set<int>* og = &(*g->outedges)[gV];
	for (const auto& u : (*q->outedges)[qV])
	{
		if (M[u.first] != -1 && !g->HasEdge(gV, M[u.first]))
		{
			return false;
		}
	}

	return true;
	/*int Size = q->edgeList[qV].size();
	for (int i = 0; i < Size; i++)
	{
	int label = q->edgeList[qV][i].label;
	int Size2 = q->edgeList[qV][i].vList.size();
	for (int j = 0; j < Size2; j++)
	{
	int u = q->edgeList[qV][i].vList[j];
	Vid v = M[u];
	if (v != -1)
	{
	int pos = contain(label, &(g->edgeList[gV]));
	if (pos == -1)
	return false;
	if (contain(v, &(g->edgeList[gV][pos].vList)) == -1)
	return false;
	}
	}
	}
	return true;*/
}

void TurboMatch::output(int* M, int qVNum, int& count)
{
	/*for(int i = 0; i < qVNum; ++i)
	{
	fprintf(fpR, "(%d, %d) ", i, M[i]);
	}
	fprintf(fpR, "\n");*/
	/*#pragma omp critical
	{
	count++;
	}*/
	//for (int i = 0; i < qVNum; ++i)
	//cout << "get answer" << endl;
	if (storeType == -1)
	{
		//cout << "get ans" << endl;
		/*vector<int> t;
		for (int i = 0; i < (*q->nodes).size(); i++)
		{
		t.push_back(M[(*q->nodes)[i]]);
		}
		vvans->push_back(t);*/
		/*for (int i = 0; i < (*q->nodes).size(); ++i)
		{
			gm->logger << i + 1 << " " << M[(*q->nodes)[i]] << endl;
		}
		gm->logger << endl;*/

		count++;
	}
	else if (storeType == 0)
	{
		/*if (newallmaps->size() > 1)
		{
		int p = 0;
		//vector<map<int, int>>::iterator sit = newallmaps->begin();
		//while (sit != newallmaps->end())
		for (const auto& nsit : *newallmaps)
		{
		//map<int, int> m = *sit;
		for (const auto& t : M)
		{
		p = t.second;
		}
		//tans[id].push_back(newmap);
		//sit++;
		}
		}*/
		/*vector<int> t;
		for (int i = 0; i < (*q->nodes).size(); i++)
		{
			//t.push_back(M[(*q->nodes)[i]]);
			gm->logger << i + 1 << " " << M[(*q->nodes)[i]] << endl;
		}
		gm->logger << endl;
		//vvans->push_back(t);
		/*for (const auto& n : M)
		{
		vans[omp_get_thread_num()]->push_back(n.second);
		}*/
		
		/*for (int j = 0; j < pschemes.size(); ++j)
		{
			vector<int> t;
			for (int i = 1; i <= (*q->nodes).size(); ++i)
			{
				t.push_back(ncMap[(*pschemes[j])[i]]);
				//gm->logger << i << " " <<  ncMap[(*pschemes[j])[i]] << endl;
			}
			//gm->logger << endl;
			vvans->push_back(t);
		}*/
		
		count += pschemes.size();
		//count++;
	}
	else if (storeType == 5)
	{
		count++;
	}
	else if (storeType == 1)
	{
		//count += gm->equalInData[comm_id][firstmatch].size();
		//vector<unordered_set<int>>* s = &gm->equalDiff[comm_id][firstmatch];

		//count++;
		count += gm->schemes.size();
		/*int p = 0;
		for (int j = 0; j < gm->schemes.size(); ++j)
		{
			for (int i = 1; i <= (*q->nodes).size(); ++i)
			{
				p++;
				gm->logger << i << " " << g->idMapping[ncMap[gm->schemes[j][i]]] << endl;
			}
			gm->logger << endl;
		}
		//count += memberNum;
		/*int mapped = g->idMapping[firstmatch];
		for (const auto& n : gm->equalInData[mapped])
		{
		if (n == mapped)
		{
		count++;
		continue;
		}
		bool flag = true;
		for (const auto& neigh : (*q->outedges)[firstpattern])
		{
		int mappedneigh = g->idMapping[M[neigh]];
		if (!data->hasEdge(n, mappedneigh))
		{
		flag = false;
		break;
		}
		}
		if (flag)
		count++;
		}*/
		/*for (int j = 0; j < gm->equalInData[g->idMapping[firstmatch]].size(); ++j)
		{
		for (int i = 1; i <= (*q->nodes).size(); ++i)
		{
		if (i == firstpattern)
		{
		gm->logger << i << " " << gm->equalInData[g->idMapping[firstmatch]][j] << endl;
		}
		else if (g->idMapping[M[i]] == gm->equalInData[g->idMapping[firstmatch]][j])
		{
		gm->logger << i << " " << g->idMapping[firstmatch] << endl;
		}
		else
		{
		gm->logger << i << " " << g->idMapping[M[i]] << endl;
		}
		}
		gm->logger << endl;
		}

		/*vector<int> t;
		for (int i = 0; i < (*q->nodes).size(); i++)
		{
		t.push_back(M[(*q->nodes)[i]]);
		}
		vvans->push_back(t);*/

		/*for (const auto& m : M)
		{
		gm->logger << m.first << " " << m.second << endl;
		}
		gm->logger << endl;
		count++;*/
	}
	else if (storeType == 2)
	{
		//int tnum = omp_get_thread_num();
		//unordered_map<int, vector<int>> t;
		//for (const auto& m : M)
		supert.clear();
		supermapper.clear();
		superc2cMap.clear();
		int index = 0;

		for (int i = 1; i <= q->nodes.size(); ++i)
		{
			//if (m.second != -1)
			if (M[i] != -1)
			{
				if (superc2cMap.find(M[i]) == superc2cMap.end())
				{
					int j = index;
					superc2cMap[M[i]] = index++;
					supermapper.push_back(M[i]);
					supert.push_back(vector<int>(1, i));
					newM[i] = j;
				}
				else
				{
					int j = superc2cMap[M[i]];
					supert[j].push_back(i);
					newM[i] = j;
				}
			}
		}

		//for (const auto& n : M)
		//{
		//	t[n.second].push_back(n.first);
		//}
		//(*superans).push_back(t);

		//if ((*superans).size() >= 5000000)
		{
			//cout << M[1] << " " << M[2] << " " << M[3] << " " << M[4] << endl;
			//system("pause");
			//if (M[1] == 1 && M[2] == 1 && M[3] == 2 && M[4] == 13)
			//	int b = 0;
			//	system("pause");
			//if(M[1] == 8 && M[2] == 1 && M[3] == 1 && M[4] == 1 && M[5] == 1)
			rematch_Turbo(supert, supermapper, newM, M, *communityGraphs, *q);
			//(*superans).clear();
		}
	}
	else if (storeType == 3)
	{
		vector<string> r;

		int i, j;
		for (i = 0; i < q->nodes.size(); i++)
		{
			if (M[q->nodes[i]] != -1)
			{
				(*subans)[q->nodes[i]] = M[q->nodes[i]];
				r.push_back(to_string(M[q->nodes[i]]));
			}
		}

		sort(r.begin(), r.end());
		for (int i = 0; i < r.size(); i++)
		{
			(*featurestr) += r[i];
			(*featurestr) += "_";
		}

		count = 1;
	}
}

bool TurboMatch::NextPerm(int* M, vector <Vid> *qV, vector<Vid> *mV, int *rank, bool& candup)
{//here
	if (candup)
	{
		//cout << "candup " << qV->size() << endl;
		int Size = qV->size();
		if ((*mV)[0] == -1)
		{
			for (int i = 0; i < Size; i++)
			{
				(*mV)[i] = M[(*qV)[i]];
			}
			return false;
		}
		if (Size == 1)
			return true;
		int ii = -1;
		for (int i = Size - 2; i >= 0; i--)
		{
			if ((*mV)[i] < (*mV)[i + 1])
			{
				ii = i;
				break;
			}
		}
		//cout << "ii " << ii << endl;
		if (ii == -1)
			return true;

		int iii = -1;
		for (int i = Size - 1; i > ii; i--)
		{
			//cout << M[(*qV)[rank[i]]] << " " << M[(*qV)[rank[ii]]] << endl;
			if ((*mV)[i] > (*mV)[ii])
			{
				iii = i;
				break;
			}
		}
		if (iii == -1)
		{
			return true;
		}

		int temp = (*mV)[ii];
		(*mV)[ii] = (*mV)[iii];
		(*mV)[iii] = temp;

		temp = M[(*qV)[ii]];
		M[(*qV)[ii]] = M[(*qV)[iii]];
		M[(*qV)[iii]] = temp;

		int E = (ii + Size - 1) / 2;
		for (int i = ii + 1; i <= E; i++)
		{
			int j = ii + Size - i;

			temp = (*mV)[i];
			(*mV)[i] = (*mV)[j];
			(*mV)[j] = temp;

			temp = M[(*qV)[i]];
			M[(*qV)[i]] = M[(*qV)[j]];
			M[(*qV)[j]] = temp;
		}

		return false;
	}
	else
	{
		int Size = qV->size();
		if (rank[0] == -1)
		{
			for (int i = 0; i < Size; i++)
				rank[i] = i;
			return false;
		}
		else
		{
			if (Size == 1)
				return true;
			int ii = -1;
			for (int i = Size - 2; i >= 0; i--)
			{
				if (rank[i] < rank[i + 1])
				{
					ii = i;
					break;
				}
			}
			if (ii == -1)
				return true;

			int iii = -1;
			for (int i = Size - 1; i > ii; i--)
			{
				//cout << M[(*qV)[rank[i]]] << " " << M[(*qV)[rank[ii]]] << endl;
				if (rank[i] > rank[ii])
				{
					iii = i;
					break;
				}
			}
			if (iii == -1)
			{
				return true;
			}

			int temp = rank[ii];
			rank[ii] = rank[iii];
			rank[iii] = temp;

			temp = M[(*qV)[rank[ii]]];
			M[(*qV)[rank[ii]]] = M[(*qV)[rank[iii]]];
			M[(*qV)[rank[iii]]] = temp;

			int E = (ii + Size - 1) / 2;
			//int j = Size - 1;
			for (int i = ii + 1; i <= E; i++)
			{
				int j = ii + Size - i;

				temp = rank[i];
				rank[i] = rank[j];
				rank[j] = temp;

				temp = M[(*qV)[rank[i]]];
				M[(*qV)[rank[i]]] = M[(*qV)[rank[j]]];
				M[(*qV)[rank[j]]] = temp;
				//j--;
			}

			return false;
		}
	}
}

void TurboMatch::GenPerm(int* M, NECTree *q_prime, int i, MemoryGraph* q, MemoryGraph* g, int& count, bool& candup)
{
	int qVNum = q->nodes.size();// getVertexNum();
								   //cut3 off
	if (i == q_prime->vertexNum || storeType == 2 || storeType == 1 || storeType == 0)
	{
		//if (M[1] == 17 && M[2] == 17 && M[3] == 17 && M[4] == 18)
		output(M, qVNum, count);
		return;
	}
	int Size = q_prime->NEC[i].size();
	if (Size == 1)
	{
		GenPerm(M, q_prime, i + 1, q, g, count, candup);
	}
	else
	{
		//int *rank = new int[Size];
		ranks[i][0] = -1;
		
		vector<int> mV(Size, -1);

		while (!NextPerm(M, &(q_prime->NEC[i]), &mV, ranks[i], candup))
		{
			GenPerm(M, q_prime, i + 1, q, g, count, candup);
			if (storeType == 3)
			{
				count = 1;
				break;
			}
		}

		//delete[] rank;
	}
}

void TurboMatch::RestoreState(int* M, bool* F, vector <Vid> *qV, vector <Vid> *gV)
{
	int Size = qV->size();
	for (int i = 0; i < Size; i++)
	{
		F[(*gV)[i]] = false;
		M[(*qV)[i]] = -1;
	}
}

void TurboMatch::RestoreState(int* M, vector <Vid> *qV, vector <Vid> *gV)
{
	int Size = qV->size();
	for (int i = 0; i < Size; i++)
	{
		M[(*qV)[i]] = -1;
	}
}

void TurboMatch::RestoreStateDense(int* M, bool* F, vector <Vid> *qV, vector <Vid> *gV)
{
	int Size = qV->size();
	for (int i = 0; i < Size; i++)
	{
		F[(*gV)[i]] = false;
	}
}

void TurboMatch::SubgraphSearch(NECTree *q_prime, TurboElem *order, int dc,
	int* M, bool* F, CRTree *CR, int& count, bool& candup)
{
	bool samelevel = false;

	int u_prime = order[dc].v;
	int firstcur = q_prime->NEC[u_prime][0];
	int p_u_prime = q_prime->parent[u_prime];
	int curfirst = firstcur;

	vector<Vid> C;
	int Size = q_prime->NEC[p_u_prime].size();
	for (int i = 0; i < Size; i++)
	{
		Vid v = M[q_prime->NEC[p_u_prime][i]];
		int pos = contain(v, &(CR->parent[u_prime]));
		vector <Vid> *t = &(CR->CR[u_prime][pos]);//&(CR->CR[u_prime][pos]);
		if (i == 0)
		{
			C = *t;
		}
		else
		{
			vector<int>::iterator it = set_intersection(C.begin(), C.end(), t->begin(), t->end(), C.begin());
			C.resize(it - C.begin());
			if (C.empty())
				return;
		}
	}

	//if (C.size() == 0)
	//{
	//	return;
	//}
	//NOTICE: this judgement is needed, otherwise bug may exist in some cases
	//if (C.empty())
	//{
	//	return;
	//}

	Size = q_prime->NEC[u_prime].size();
	if (C.size() < Size)
	{
		return;
	}

	//sort(C.begin(), C.end());

	//int *Srank = new int[Size];
	vector <int> Srank(1, -1);
	vector <Vid> value;						//C'

	while (true)
	{
		//if (!candup)
		{
			NextComb(&C, Size, &Srank, &value, u_prime, u_prime, q_prime);
		}
		/*else
		{
		if (!samelevel)
		{
		NextComb(&C, Size, &Srank, &value, dc, q_prime);
		}
		else
		{
		NextComb(&C, Size, &Srank, &value, dc, q_prime, midvalpos, M[firstpattern], bigpos);
		}
		}*/

		if (Srank[0] == -1)
		{
			break;
		}

		bool Continue = false;

		for (int i = 0; i < Size; i++)
		{
			if (F[value[i]])
			{
				Continue = true;
				break;
			}
		}
		if (Continue)
			continue;

		if (storeType == 1)
		{
			if (q_prime->isLinked[u_prime])
			{
				//if (contain(q_prime->NEC[u_prime][1], &((*p)[pos].vList)) != -1)
				{
					for (int i = 0; i < Size; i++)
					{
						//unordered_set<int>* vi = &(*g->outedges)[value[i]];
						//if (vi->empty())
						//{
						//	Continue = true;
						//	break;
						//}
						for (int j = i + 1; j < Size; j++)
						{
							if (!g->HasEdge(value[i], value[j]))
							{
								Continue = true;
								break;
							}
							/*if (contain(value[j], &((*p)[pos].vList)) == -1)
							{
							Continue = true;
							break;
							}*/
						}
						if (Continue)
							break;
					}
				}
			}
		}
		else
		{
			if (Size > 1 && (*q->outedges)[firstcur].find(q_prime->NEC[u_prime][1]) != (*q->outedges)[firstcur].end())
			{
				//if (contain(q_prime->NEC[u_prime][1], &((*p)[pos].vList)) != -1)
				{
					for (int i = 0; i < Size; i++)
					{
						unordered_map<int, vector<int>>* vi = &(*g->outedges)[value[i]];
						//if (vi->empty())
						//{
						//	Continue = true;
						//	break;
						//}
						for (int j = i + 1; j < Size; j++)
						{
							if (vi->find(value[j]) == vi->end())
							{
								Continue = true;
								break;
							}
							/*if (contain(value[j], &((*p)[pos].vList)) == -1)
							{
							Continue = true;
							break;
							}*/
						}
						if (Continue)
							break;
					}
				}
			}
		}

		if (Continue)
			continue;

		//if (storeType == 0)
		{
			bool matched = true;

			for (int i = 0; i < Size; i++)
			{
				if (!IsJoinable(M, q_prime->NEC[u_prime][i], value[i]))
				{
					matched = false;
					break;
				}
			}

			if (!matched)
				continue;
		}

		UpdateState(M, F, &q_prime->NEC[u_prime], &value);

		/*int savenum = 0;
		if (storeType == 1 && isLeader)
		{
		savenum = memberNum;
		for (int i = 0; i < value.size(); i++)
		{
		if (leaderSC->find(value[i]) != leaderSC->end())
		memberNum++;
		}
		}*/

		if (q_prime->vertexNum == dc + 1)
		{
			//cut3 off
			//unordered_map<int, int> tempM = M;

			/*if (!isLeader)
			{
			bool check = false;
			for (const auto& m : M)
			{
			if (m.second == gm->equalTeam[firstmatch])
			{
			check = true;
			break;
			}
			}
			if (check)
			{
			GenPerm(M, q_prime, 0, q, g, count, candup);
			}
			}
			else*/
			{
				GenPerm(M, q_prime, 0, q, g, count, candup);
			}
		}
		else SubgraphSearch(q_prime, order, dc + 1, M, F, CR, count, candup);

		//memberNum = savenum;
		RestoreState(M, F, &q_prime->NEC[u_prime], &value);

		//if (storeType == 3 && count > 0)
		{
			//return;
		}
	}
}

void TurboMatch::SubgraphSearchDense(MemoryGraph *q, NECTree *q_prime, MemoryGraph *g, TurboElem *order, int dc
	, int* M, CRTree *CR, int& count, bool& candup)
{
	bool samelevel = false;
	int u_prime = order[dc].v;
	//samelevel = gm->equals[q_prime->NEC[u_prime][0]].find(q_prime->NEC[0][0]) != gm->equals[q_prime->NEC[u_prime][0]].end();
	int p_u_prime = q_prime->parent[u_prime];
	vector<int>* qN = &q_prime->NEC[u_prime];
	int curfirst = q_prime->NEC[u_prime][0];

	vector<Vid> C;
	int Size = q_prime->NEC[p_u_prime].size();
	for (int i = 0; i < Size; i++)
	{
		Vid v = ncMap[q_prime->NEC[p_u_prime][i]];
		int pos = contain(v, &(CR->parent[u_prime]));
		vector <Vid> *t = &(CR->CR[u_prime][pos]);//&(CR->CR[u_prime][pos]);
		if (i == 0)
		{
			if (oomessage == NULL)
			{
				C = *t;
			}
		}
		else
		{
			vector<int>::iterator it = set_intersection(C.begin(), C.end(), t->begin(), t->end(), C.begin());
			C.resize(it - C.begin());
			if (C.empty())
				return;
		}
	}

	if (C.size() == 0)
	{
		return;
	}

	Size = qN->size();

	//int *Srank = new int[Size];
	vector<int> Srank(Size, -1);
	//Srank.push_back(-1);
	vector <Vid> value(Size, -1);						//C'

	int midvalpos, bigpos;

	if (samelevel)
	{
		midvalpos = lower_bound(q_prime->NEC[u_prime].begin(), q_prime->NEC[u_prime].end(), firstpattern) - q_prime->NEC[u_prime].begin();
		bigpos = lower_bound(C.begin(), C.end(), ncMap[firstpattern]) - C.begin();

		if (Size > midvalpos && C.size() <= bigpos)
			return;
	}

	while (true)
	{
		int r = 1;
		if (Srank[0] == -1)
		{
			r = GetFirstDense(C, Size, Srank, value, u_prime, q_prime, 0);
		}
		else
		{
			r = GetCombDense(C, Size, Srank, value, u_prime, q_prime, Size - 1);
		}

		if (Srank[0] == -1 || r < 0)
		{
			break;
		}

		bool Continue = false;

		for (int i = 0; i < Size; i++)
		{
			if (F[value[i]])
			{
				Continue = true;
				break;
			}
		}
		if (Continue)
			continue;

		if (q_prime->isLinked[u_prime])
		{
			for (int i = 0; i < Size; i++)
			{
				for (int j = i + 1; j < Size; j++)
				{
					if (!g->HasEdge(value[i], value[j]))
					{
						Continue = true;
						break;
					}
					/*if (contain(value[j], &((*p)[pos].vList)) == -1)
					{
					Continue = true;
					break;
					}*/
				}
				if (Continue)
					break;
			}
		}

		if (Continue)
			continue;

		//if (storeType == 0)
		{
			bool matched = true;

			for (int i = 0; i < Size; i++)
			{
				if (!IsJoinable(ncMap, q_prime->NEC[u_prime][i], value[i]))
				{
					matched = false;
					break;
				}
			}

			if (!matched)
				continue;
		}

		UpdateStateDense(M, F, &q_prime->NEC[u_prime], &value);

		if (q_prime->vertexNum == dc + 1)
		{
			int* tempM = new int[q->nodeNum + 1];
			for(int s = 1; s <= q->nodeNum; ++s)
				tempM[s] = ncMap[s];
			GenPerm(tempM, q_prime, 0, q, g, count, candup);
			delete[] tempM;
		}
		else SubgraphSearchDense(q, q_prime, g, order, dc + 1, M, CR, count, candup);

		RestoreStateDense(M, F, &q_prime->NEC[u_prime], &value);
	}

}

void TurboMatch::SubgraphSearchSuper(MemoryGraph *q, NECTree *q_prime, MemoryGraph *g, TurboElem *order, int dc
	, int* M, CRTree *CR, int& count, bool& candup)
{
	bool samelevel = false;
	int u_prime = order[dc].v;
	//if (storeType == 2)
	//{
	//	//cut3 off
	//	samelevel = gm->equals[q_prime->NEC[u_prime][0]].find(q_prime->NEC[0][0]) != gm->equals[q_prime->NEC[u_prime][0]].end();
	//}
	int p_u_prime = q_prime->parent[u_prime];
	vector<int>* qN = &q_prime->NEC[u_prime];
	int curfirst = q_prime->NEC[u_prime][0];

	vector<Vid> C;
	int Size = q_prime->NEC[p_u_prime].size();
	for (int i = 0; i < Size; i++)
	{
		Vid v = ncMap[q_prime->NEC[p_u_prime][i]];
		int pos = contain(v, &(CR->parent[u_prime]));
		vector <Vid> *t = &(CR->CR[u_prime][pos]);//&(CR->CR[u_prime][pos]);
		if (i == 0)
		{
			if (oomessage == NULL)
			{
				/*for (int i = 0; i < t->size(); ++i)
				{
				int ct = (*t)[i];
				bool can = true;
				for (int j = 0; j < dc; ++j)
				{
				int cdc = order[j].v;
				for (int k = 0; k < q_prime->NEC[cdc].size(); ++k)
				{
				int node = q_prime->NEC[cdc][k];
				if (q->HasEdge(node, curfirst) && !gm->share1NeighbourPairs[ct][ncMap[node]])
				{
				can = false;
				break;
				}
				}
				if (!can)
				break;
				}
				if (can)
				C.push_back(ct);
				}*/
				C = *t;
			}
		}
		else
		{
			vector<int>::iterator it = set_intersection(C.begin(), C.end(), t->begin(), t->end(), C.begin());
			C.resize(it - C.begin());
			if (C.empty())
				return;
		}
	}

	if (C.size() == 0)
	{
		return;
	}

	//sort(C.begin(), C.end());
	//NOTICE: this judgement is needed, otherwise bug may exist in some cases
	//if (C.empty())
	//{
	//	return;
	//}

	Size = qN->size();

	//int *Srank = new int[Size];
	vector<int> Srank(Size, -1);
	//Srank.push_back(-1);
	vector <Vid> value(Size, -1);						//C'

	int midvalpos, bigpos;
	if (storeType == 2)
	{
		if (samelevel)
		{
			midvalpos = lower_bound(q_prime->NEC[u_prime].begin(), q_prime->NEC[u_prime].end(), firstpattern) - q_prime->NEC[u_prime].begin();
			bigpos = lower_bound(C.begin(), C.end(), ncMap[firstpattern]) - C.begin();

			if (Size > midvalpos && C.size() <= bigpos)
				return;
		}
	}

	while (true)
	{
		int r = 1;
		if (Srank[0] == -1)
		{
			r = GetFirst(C, Size, Srank, value, u_prime, q_prime, 0);
			/*if (!samelevel)
			{
			NextComb(&C, Size, &Srank, &value, dc, q_prime, true);
			doors.push_back(C[0]);
			}
			else
			{
			NextComb(&C, Size, &Srank, &value, dc, q_prime, midvalpos, M[q_prime->NEC[0][0]], bigpos, true);
			doors.push_back(C[bigpos]);
			}*/
		}
		else
		{
			r = GetComb(C, Size, Srank, value, u_prime, q_prime, Size - 1);
		}

		if (Srank[0] == -1 || r < 0)
		{
			break;
		}

		bool Continue = false;

		/*
		if (q_prime->isLinked[u_prime])
		{
		//int Label = q_prime->vList[u_prime];
		//vector <LabelVList> *p = &(q->edgeList[q_prime->NEC[u_prime][0]]);
		//int pos = contain(Label, p);
		//if (pos != -1)
		//if ((*q->outedges)[(*qN)[0]].find((*qN)[1]) != (*q->outedges)[(*qN)[0]].end())
		{
		//if (contain(q_prime->NEC[u_prime][1], &((*p)[pos].vList)) != -1)
		{
		for (int i = 0; i < Size; i++)
		{
		unordered_set<int>* vi = &(*g->outedges)[value[i]];
		//if (vi->empty())
		//{
		//	Continue = true;
		//	break;
		//}
		for (int j = i + 1; j < Size; j++)
		{
		if (vi->find(value[j]) == vi->end())
		{
		Continue = true;
		break;
		}
		//if (contain(value[j], &((*p)[pos].vList)) == -1)
		//{
		//Continue = true;
		//break;
		//}
		}
		if (Continue)
		break;
		}
		if (Continue)
		continue;
		}
		}
		}

		bool matched = true;

		for (int i = 0; i < Size; i++)
		{
		if (!IsJoinableSuper(q, g, ncMap, (*qN)[i], value[i]))
		{
		matched = false;
		break;
		}
		}

		if (!matched)
		continue;
		*/
		//UpdateState(M, qN, &value);

		if (q_prime->vertexNum == dc + 1)
		{
			//cut3 off
			//unordered_map<int, int> tempM = M;
			int* tempM = new int[q->nodeNum + 1];
			for(int s = 1; s <= q->nodeNum; ++s)
				tempM[s] = ncMap[s];
			GenPerm(tempM, q_prime, 0, q, g, count, candup);
			delete[] tempM;
		}
		else SubgraphSearchSuper(q, q_prime, g, order, dc + 1, M, CR, count, candup);

		//RestoreState(M, qN, &value);

		//if (storeType == 3 && count > 0)
		{
			//return;
		}
	}

}

void TurboMatch::SubgraphSearchBound(NECTree *q_prime, TurboElem *order, int dc,
	int* M, bool* F, CRTree *CR, int& count, bool& candup)
{
	bool samelevel = false;

	int u_prime = order[dc].v;
	int firstcur = q_prime->NEC[u_prime][0];
	int p_u_prime = q_prime->parent[u_prime];
	vector<int>* qN = &q_prime->NEC[u_prime];
	int curfirst = firstcur;

	vector<Vid> C;
	vector<int>* qpN = &q_prime->NEC[p_u_prime];
	int Size = q_prime->NEC[p_u_prime].size();
	for (int i = 0; i < Size; i++)
	{
		Vid v = ncMap[(*qpN)[i]];
		int pos = contain(v, &(CR->parent[u_prime]));
		vector <Vid> *t = &(CR->CR[u_prime][pos]);//&(CR->CR[u_prime][pos]);
		if (i == 0)
		{
			//if (oomessage == NULL)
			{
				C = *t;
			}
		}
		else
		{
			vector<int>::iterator it = set_intersection(C.begin(), C.end(), t->begin(), t->end(), C.begin());
			C.resize(it - C.begin());
			if (C.empty())
				return;
		}
	}

	//if (C.size() == 0)
	//{
	//	return;
	//}
	//NOTICE: this judgement is needed, otherwise bug may exist in some cases
	//if (C.empty())
	//{
	//	return;
	//}

	Size = qN->size();
	if (C.size() < Size)
	{
		return;
	}

	//sort(C.begin(), C.end());

	//int *Srank = new int[Size];
	vector<int> Srank(Size, -1);
	//Srank.push_back(-1);
	vector <Vid> value(Size, -1);						//C'

	while (true)
	{
		int r = 1;
		if (Srank[0] == -1)
		{
			r = GetFirstBound(C, Size, Srank, value, u_prime, q_prime, 0);
		}
		else
		{
			r = GetCombBound(C, Size, Srank, value, u_prime, q_prime, Size - 1);
		}

		if (Srank[0] == -1 || r < 0)
		{
			break;
		}

		bool Continue = false;

		for (int i = 0; i < Size; i++)
		{
			if (F[value[i]])
			{
				Continue = true;
				break;
			}
		}
		if (Continue)
			continue;

		if (q_prime->isLinked[u_prime])
		{
			//int Label = q_prime->vList[u_prime];
			//vector <LabelVList> *p = &(q->edgeList[q_prime->NEC[u_prime][0]]);
			//int pos = contain(Label, p);
			//if (pos != -1)

			//if (Size > 1 && (*q->outedges)[firstcur].find((*qN)[1]) != (*q->outedges)[firstcur].end())
			{
				//if (contain(q_prime->NEC[u_prime][1], &((*p)[pos].vList)) != -1)
				{
					for (int i = 0; i < Size; i++)
					{
						//unordered_set<int>* vi = &(*g->outedges)[value[i]];
						//if (vi->empty())
						//{
						//	Continue = true;
						//	break;
						//}
						for (int j = i + 1; j < Size; j++)
						{
							if (!g->HasEdge(value[i], value[j]))
							{
								Continue = true;
								break;
							}
							/*if (contain(value[j], &((*p)[pos].vList)) == -1)
							{
							Continue = true;
							break;
							}*/
						}
						if (Continue)
							break;
					}
				}
			}
		}

		if (Continue)
			continue;

		bool matched = true;

		for (int i = 0; i < Size; i++)
		{
			if (!IsJoinable(ncMap, (*qN)[i], value[i]))
			{
				matched = false;
				break;
			}
		}

		if (!matched)
			continue;

		UpdateStateDense(M, F, qN, &value);

		/*int savenum = 0;
		if (storeType == 1 && isLeader)
		{
		savenum = memberNum;
		for (int i = 0; i < value.size(); i++)
		{
		if (leaderSC->find(value[i]) != leaderSC->end())
		memberNum++;
		}
		}*/

		if (q_prime->vertexNum == dc + 1)
		{
			//cut3 off
			//unordered_map<int, int> tempM = M;

			/*if (!isLeader)
			{
			bool check = false;
			for (const auto& m : M)
			{
			if (m.second == gm->equalTeam[firstmatch])
			{
			check = true;
			break;
			}
			}
			if (check)
			{
			GenPerm(M, q_prime, 0, q, g, count, candup);
			}
			}
			else*/
			{
				/*vector<int> rec(5);
				for (int r = 1; r < 5; ++r)
					rec[r] = ncMap[r];*/
				//int savecount = count;
				int* tempM = new int[q->nodeNum + 1];
				for(int s = 1; s <= q->nodeNum; ++s)
					tempM[s] = ncMap[s];
				GenPerm(tempM, q_prime, 0, q, g, count, candup);
				delete[] tempM;
				//cout << ncMap[1] << " " << ncMap[2] << " " << ncMap[3] << " " << ncMap[4] << " " << count - savecount << endl;
				/*for (int r = 1; r < 5; ++r)
					ncMap[r] = rec[r];*/
			}
		}
		else SubgraphSearchBound(q_prime, order, dc + 1, M, F, CR, count, candup);

		//memberNum = savenum;
		RestoreStateDense(M, F, qN, &value);

		//if (storeType == 3 && count > 0)
		{
			//return;
		}
	}
}

void TurboMatch::rematch_Turbo(vector<vector<int>>& supermatch, vector<int>& c2cmapper, int* supermatchmap, int* supermatchmapori
	, vector<MemoryGraph*>& communityGraphs, MemoryGraph& patternGraph)
{
	//int hittime turboisosuper= 0;
	//int totaltime = 0;
	//bool isCheck = false;
	//int supercount = 0;
	//cout << "supermatch: " << supermatch.size() << endl;

	/*map<int, vector<int>> m;
	m[1].push_back(1);
	m[12].push_back(2);
	m[12].push_back(3);
	m[12].push_back(4);
	//m[21].push_back(3);
	//supermatch = m;

	/*if (find(supermatch.begin(), supermatch.end(), m) != supermatch.end())
	{
	cout << "find it !!!!!" << endl;
	}
	else
	{
	cout << "not find" << endl;
	}*/

	//set<map<int, vector<int>>> supermatchrecord;
	//double testtime = 0;
	//int usedmatch = 0;
	//int usefulmatch = 0;

	//supercount++;
	//map<int, vector<int>> s;
	//cout << i++ << endl;
	//s.clear();
	//s[11].push_back(1);
	//s[9].push_back(2);
	//s[12].push_back(3);
	//s[11].push_back(4);
	//s[5].push_back(5);
	//supermatch = s;
	//for (auto& s : supermatch)
	//for (int i = 0; i < supermatch.size(); i++)
	//{
	//supermatch = m;
	bool cut1 = false;
	bool cut2 = true;//true;
	bool cut3 = true;//true;
	//cout << "info" << endl;
	bool isgo = true;

	/*for (int i = 0; i < supermatch.size(); ++i)
	{
	if (supermatch[i].size() > data->communityNodes[c2cmapper[i]].size())
	{
	isgo = false;
	break;
	}

	//sort(n.second.begin(), n.second.end());
	}*/

	//if (!isgo)
	//{
	//	return; //continue;
	//}

	if (supermatch.size() == 1)
	{
		//if (c2cmapper[0] != 13)
		//	return;
		//return;
		//cout << supermatch.begin()->first << endl;
		if (rectm == NULL)
		{
			rectm = new TurboMatch();
			rectm->data = data;
			rectm->gm = this->gm;
			rectm->storeType = 1;
			rectm->q = &patternGraph;
			rectm->init();
			rectm->q_primes = this->q_primes;
			rectm->ranks = new int*[patternGraph.nodeNum];
			for (int pn = 0; pn < patternGraph.nodeNum; ++pn)
			{
				rectm->ranks[pn] = new int[patternGraph.nodeNum];
			}
			rectm->ncMap = new int[q->nodes.size() + 1];
		}
		int cid = c2cmapper[0];
		rectm->g = communityGraphs[cid];
		//cout << cid << " " << rectm->g->nodenum << endl;
		bool candup = false;

		//rectm->vvans = &tans[0];
		//rectm->comm_id = cid;
		int count = rectm->TurboISODense(rectm->q, rectm->g, candup, cid);
		//cout << "count: " << count << endl;
		//gm->internum++;
		//#pragma omp critical
		{
			gm->ansnum += count;
		}
		return;//continue;
	}
	

	//int id = omp_get_thread_num();
	//vector<map<int, int>> newallmaps;
	bool smallestPattern = false;

	//supermatch = s;

	bool canMatch = true;

	bool canfind = true;

	pointers.clear();
	//gm->uselessUntrivial++;
	if (cut2)
	{
		for (int i = 1; i < patternGraph.nodeNum + 1; ++i)
		{
			boundary[i] = NULL;
		}

		//for (int i = 0; i < q->nodenum + 1; ++i)
		//{
		//outcomm[i].clear();
		//	for (int j = 0; j < supermatch.size(); ++j)
		//	{
		//		outds[i][j].clear();
		//	}
		//}

		for (int comm = 0; comm < supermatch.size(); ++comm)
		{
			int actualcomm = c2cmapper[comm];
			for (int i = 0; i < supermatch[comm].size(); ++i)
			{
				int n = supermatch[comm][i];
				bool rep = false;
				for (int p = 0; p < i; p++)
				{
					int vertex = supermatch[comm][p];
					if ((*equalq)[vertex][n])
					{
						rep = true;
						if (boundary[vertex] != NULL)
						{
							boundary[n] = boundary[vertex];
							//outds[n] = outds[vertex];
						}
						break;
					}
				}
				if (rep)
				{
					continue;
				}

				vector<int>* narea = NULL;// = *((*communityGraphs[comm.first]).nodes);
										  //sort(narea.begin(), narea.end());
				int index = 0;
				for (int c = 0; c < supermatch.size(); ++c)
				{
					if (c != comm)
					{
						int actualc = c2cmapper[c];
						/*outds.clear();
						index++;
						bool hasout = false;
						bool hasin = false;
						//unordered_map<int, int>* outpc = &(outds[n][c.first]);
						for (int t = 0; t < supermatch[c].size(); t++)
						{
						int node2 = supermatch[c][t];
						if ((*q->outedges)[n].find(node2) != (*q->outedges)[n].end())
						{
						hasout = true;
						//if (outds[n][c].empty())
						//	outcomm[n].push_back(c);
						int label2 = q->nodeLabels[node2];
						outds[label2]++;
						//(*outp)[c.first][(*q->nodeLabels)[node2]]++;
						}
						}*/

						//if (hasout)
						if (n2cNum[n][actualc] != 0)
						{
							//for (const auto& l : outds)
							{
								int label = 0;// l.first;
								p.degree = n2cNum[n][actualc];//l.second;
								p.pos = -1;

								vector<DegreePos>* dpSaver = &data->degreePosOut[actualcomm][actualc][label];
								if (dpSaver->empty())
								{
									canfind = false;
									break;
								}

								vector<DegreePos>::iterator sit = lower_bound(dpSaver->begin(), dpSaver->end(), p, cmpD);
								if (sit == dpSaver->end())
								{
									canfind = false;
									break;
								}
								else
								{
									vector<int>* cobSaver = &data->commOutBoundary[actualcomm][actualc][label];
									if (narea == NULL)
									{
										narea = new vector<int>(cobSaver->begin() + sit->pos, cobSaver->end());
										sort(narea->begin(), narea->end());
										pointers.push_back(narea);
									}
									else
									{
										//vector<int> t;
										vector<int> tempvector(cobSaver->begin() + sit->pos, cobSaver->end());
										sort(tempvector.begin(), tempvector.end());
										vector<int>::iterator it = set_intersection(narea->begin(), narea->end(), tempvector.begin(), tempvector.end(), narea->begin());
										narea->resize(it - narea->begin());
										if (narea->empty())
										{
											//if (index <= 2)
											canfind = false;
											break;
										}
										//*narea = t;
									}
								}
							}
						}
					}
					if (!canfind)
					{
						break;
					}
				}
				//outds.clear();
				if (!canfind)
				{
					break;
				}
				if (narea != NULL && !(narea->empty()))
				{
					boundary[n] = narea;
					//takeEffet.push_back(n);
					//narea.clear();
				}
			}
			if (!canfind)
			{
				break;
			}
		}

		if (!canfind)
		{
			for (auto& p : pointers)
			{
				delete p;
			}
			return;// continue;
		}

		//gm->uselessDouble++;
		/*
		for (int k = 0; k < takeEffet.size(); ++k)
		{
		int j = takeEffet[k];
		vector<int>* b = boundary[j];
		for (int i = 0; i < b->size(); ++i)
		{
		int n = (*b)[i];
		bool fit = true;
		for (const auto& pn : (*patternGraph.outedges)[j])
		{
		int comm_id = supermatchmapori[pn];
		vector<unordered_map<int, int>*>* twoHop = &data->twoHopLimitation[n][comm_id];
		for (const auto& c : outcomm[pn])
		{
		int actualc = c2cmapper[c];
		if ((*twoHop)[actualc] == NULL)
		{
		fit = false;
		break;
		}

		unordered_map<int, int>* t = (*twoHop)[actualc];
		for (const auto& l : outds[pn][c])
		{
		if (t->find(l.first) == t->end() || (*t)[l.first] < l.second)
		{
		fit = false;
		break;
		}
		}
		if (!fit)
		break;
		}
		if (!fit)
		break;
		}
		if (!fit)
		{
		b->erase(b->begin() + i);
		if (b->empty())
		{
		//system("pause");
		canfind = false;
		break;
		}
		--i;
		}
		}
		if (!canfind)
		break;
		}
		if (!canfind)
		{
		for (auto& p : pointers)
		{
		delete p;
		}
		return;
		}*/
		//gm->uselessDouble++;
		/*for (int n = 0; n < supermatch.size(); ++n)
		{
		unordered_set<int> cands;
		int ncount = 0;
		int nsize = supermatch[n].size();
		for (const auto& m : supermatch[n])
		{
		if (boundary[m] == NULL)
		break;
		ncount++;
		cands.insert(boundary[m]->begin(), boundary[m]->end());
		if (cands.size() < ncount)
		{
		canfind = false;
		break;
		}
		else if (cands.size() >= nsize)
		{
		break;
		}
		}
		if (!canfind)
		break;
		}

		if (!canfind)
		{
		for (auto& p : pointers)
		{
		delete p;
		}
		return;// continue;
		}*/

		/*dprec.clear();
		for (int n = 1; n <= patternGraph.nodenum; ++n)
		{
		if (boundary[n] != NULL)
		{
		DegreePos p;
		p.degree = boundary[n]->size();
		p.pos = n;
		dprec.push_back(p);
		}
		}

		sort(dprec.begin(), dprec.end(), cmpD);

		for (const auto& pn : dprec)
		{
		int n = pn.pos;
		bool can1 = false;
		int Size = boundary[n]->size() - 1;
		for (int i = Size; i >= 0; --i)
		{
		bool canmatch = true;
		int node = (*boundary[n])[i];
		for (const auto& neigh : (*patternGraph.outedges)[n])
		{
		if (boundary[neigh] == NULL)
		continue;

		bool can = false;
		for (const auto& n2 : *boundary[neigh])
		{
		if (originalgraph->HasEdge(node, n2))
		{
		can = true;
		break;
		}
		}
		if (!can)
		{
		canmatch = false;
		break;
		}
		}
		if (canmatch)
		{
		can1 = true;
		break;
		}
		else
		{
		boundary[n]->pop_back();
		}
		}
		if (!can1)
		{
		for (auto& p : pointers)
		{
		delete p;
		}
		return;
		}
		}*/
	}
	else
	{
		for (int i = 1; i < patternGraph.nodeNum + 1; ++i)
		{
			boundary[i] = &data->communityNodes[supermatchmapori[i]];
		}
	}

	//gm->uselessCut2++;

	vector<int> allmaps;
	if (cut3)
	{
		/*for (const auto& n : supermatchmap)
		{
		mystr += n.second;
		}*/

		//vector<map<int, int>> allmaps;
		unordered_set<string> record;

		if (!(gm->getCompleteMatch(supermatchmapori, allmaps, record)))//!(gm->getAllInPatternCompleteMatch(supermatch, supermatchmap, mystr, supermatch.begin(), newallmaps, cMap, usednodes)))
		{
			for (auto& p : pointers)
			{
				delete p;
			}
			//gm->uselessDouble++;
			//cout << "catch!" << endl;
			//for (auto& n : supermatchmap)
			//{
			//	gm->logger << n.first << " " << n.second << endl;
			//}
			//gm->logger << endl;
			return;// continue;
		}
	}
	//gm->usefulCS++;

	//unordered_map<int, unordered_map<int, unordered_map<int, int>>> oomessage;//, oimessage, iomessage;
	//storage->tools->getTwoHopPatternPairs(&patternGraph, supermatchmap, oomessage, oomessage, oomessage);//oimessage, iomessage);

	//TempGraph t(*q->nodes, &nodeAttributes, &edgeAttributes, *q->outedges, *q->outedges);
	bool candup = false;
	//if (supermatchmapori[1] == 5 && supermatchmapori[2] == 5 && supermatchmapori[3] == 5 && supermatchmapori[4] == 12)
	//	int ksp = 0;

	if (boundtm == NULL)
	{
		boundtm = new TurboMatch();
		boundtm->data = data;
		boundtm->gm = this->gm;
		boundtm->storeType = 0;
		boundtm->communityGraphs = this->communityGraphs;
		boundtm->q = &patternGraph;
		boundtm->g = originalgraph;
		boundtm->init();
		boundtm->ranks = new int*[patternGraph.nodeNum];
		for (int pn = 0; pn < patternGraph.nodeNum; ++pn)
		{
			boundtm->ranks[pn] = new int[patternGraph.nodeNum];
		}
		boundtm->ncMap = new int[q->nodes.size() + 1];
	}
	//TurboMatch tm(-1, &boundary, NULL, NULL, NULL, storage, &patternGraph, originalgraph);
	//tm.storeType = 0;
	//tm.communityGraphs = this->communityGraphs;

	if (cut2)
	{
		boundtm->nodeArea = &boundary;
		boundtm->initpIETree(supermatchmap);
	}
	else
	{
		//boundtm->nodeArea = NULL;
		boundtm->nodeArea = &boundary;
		boundtm->initpIETree(supermatchmap);
	}
	//vector<vector<int>> finds;
	//boundtm->vvans = &finds;
	boundtm->distributeplan = supermatchmapori;
	//boundtm->newallmaps = &newallmaps;
	
	//cout << supermatchmap[1] << " "<< supermatchmap[2] << " " <<supermatchmap[3] << " " << supermatchmap[4] <<endl;
	int count = boundtm->TurboISOBound(boundtm->q, boundtm->g, candup);
	//gm->internum++;
	//cout << count << endl;
	//if (count == 0)
	{
		//gm->uselessCS++;
		/*for (int n = 1; n <= patternGraph.nodenum; ++n)
		{
		gm->logger << n << " " << supermatchmapori[n] << endl;
		}
		gm->logger << endl;*/
	}
	//else
	{
		//gm->usefulCS++;
	}

	for (auto& p : pointers)
	{
		delete p;
	}

	if (cut3)
	{
		//#pragma omp critical
		{
			gm->ansnum += count * allmaps.size();
		}
		/*for (int f = 0; f < finds.size(); f++)
		{
			for (int i = 0; i < allmaps.size(); ++i)
			{
				vector<int> newmap(finds[f].size(), -1);
				for (int j = 1; j < gm->schemes[allmaps[i]].size(); ++j)
				{
					newmap[j - 1] = finds[f][gm->schemes[allmaps[i]][j] - 1];
				}
				for (int k = 0; k < newmap.size(); k++)
				{
					gm->logger << k + 1 << " " << newmap[k] << endl;
				}
				gm->logger << endl;
			}
		}
		/*vector<map<int, int>>::iterator sit = newallmaps.begin();
		while (sit != newallmaps.end())
		{
		map<int, int> m = *sit;
		vector<int> newmap(finds[f].size(), -1);
		for (int i = 0; i < finds[f].size(); i++)
		{
		if (finds[f][i] != -1)
		{
		newmap[m[i + 1] - 1] = finds[f][i];
		}
		}
		//int id = 0;
		//tans[id].push_back(newmap);
		for (int k = 0; k < newmap.size(); k++)
		{
		gm->logger << k + 1 << " " << newmap[k] << endl;
		}
		gm->logger << endl;

		sit++;
		}*/
		//}
	}
	else
	{
		//#pragma omp critical
		//{
		gm->ansnum += count;
		//}
		//for (int f = 0; f < finds.size(); f++)
		//{
		//tans[0].push_back(finds[f]);
		//}
	}

	//for (const auto& m : dels)
	//{
	//	delete maps[m];
	//}
	//maps.clear();
	//currentMap.clear();
	//commvec.clear();
	//}
}

void TurboMatch::initIETree()
{
	gm->IETreeL = vector<vector<int>>(q->nodeNum + 1);
	gm->IETreeS = vector<vector<int>>(q->nodeNum + 1);
	vector<unordered_set<int>> check(q->nodeNum + 1);
	int index = 0;
	for (int i = 0; i < gm->schemes.size(); ++i)
	{
		for (int j = 1; j <= q->nodeNum; ++j)
		{
			if (gm->schemes[i][j] != j)
			{
				if (check[j].find(gm->schemes[i][j]) == check[j].end())
				{
					gm->IETreeS[j].push_back(gm->schemes[i][j]);
					gm->IETreeL[gm->schemes[i][j]].push_back(j);
					check[j].insert(gm->schemes[i][j]);
					check[gm->schemes[i][j]].insert(j);
				}
				break;
			}
		}
	}
}

void TurboMatch::initpIETree(int* supermatchmap)
{
	if (pIETreeL.empty())
	{
		pIETreeL = vector<vector<int>>(q->nodeNum + 1);
		pIETreeS = vector<vector<int>>(q->nodeNum + 1);
	}
	else
	{
		for (int i = 1; i < pIETreeL.size(); ++i)
		{
			pIETreeL[i].clear();
			pIETreeS[i].clear();
		}
	}

	pschemes.clear();
	int index = 0;
	for (int i = 0; i < gm->schemes.size(); ++i)
	{
		bool flag = true;
		for (int j = 1; j <= q->nodeNum; ++j)
		{
			int s1 = gm->schemes[i][j];
			if (s1 != j && supermatchmap[s1] != supermatchmap[j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
			pschemes.push_back(&gm->schemes[i]);
	}

	for (int i = 0; i < pschemes.size(); ++i)
	{
		for (int j = 1; j <= q->nodeNum; ++j)
		{
			if ((*pschemes[i])[j] != j)
			{
				pIETreeS[j].push_back((*pschemes[i])[j]);
				pIETreeL[(*pschemes[i])[j]].push_back(j);
				break;
			}
		}
	}
}
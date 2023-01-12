#include "GraphManager.h"

GraphManager::GraphManager() {
	base_dir = "graphs\\";
}

GraphManager::GraphManager(string& dbn, int block_list, int list_edge, double ava, int cache_size,
	string leaf_file, string internal_file, int leaf_cache_size, int internal_cache_size, 
	string big_key_file, int big_key_cache_size, bool tree_empty, bool overwrite, bool firsttime)
{
	base_dir = "graphs\\";

	if (overwrite) {
		if (_access((base_dir + dbn).c_str(), 0) != 0) {
			system(("mkdir " + base_dir + dbn).c_str());
		}
	}

	block_listnum = block_list;
	list_edgenum = list_edge;
	ava_threshold = ava;

	srand((unsigned)time(NULL));
	db_name = dbn;
	db_path = dbn + "//_db.dat";
	node_index_path = db_name + "//_Node_index.db";
	big_node_index_path = db_name + "//_Big_node_index.db";
	spd_index_path = db_name + "//_Spd_index.db";
	shortest_path_dist_path = db_name + "//_Shortest_dist.db";
	c2n_index_path = db_name + "//_C2N_index.db";
	c2n_dist_path = db_name + "//_C2N_dist.db";

	relDB = new RDB(base_dir, dbn);
	relDB->connect_sqlite();

	gLoader = new GraphLoader();
	blockIdPool = new IDPoolDisk(base_dir + dbn + "//_blockIdPool.idx", overwrite, true);
	gUpdater = new GraphUpdater();

	list_size = sizeof(ListMeta) + list_edgenum * sizeof(GDBEdge);
	block_size = sizeof(BlockMeta) + block_listnum * list_size;

	begin_of_block = sizeof(int);

	vector<int> params;
	params.push_back(block_listnum);
	params.push_back(list_edgenum);
	cacheManager = new CacheManager(base_dir, db_name, cache_size, block_size, true, begin_of_block, sizeof(StorageMeta), false, params, overwrite);

	inMemory = false;
	doBetweenness = false;

	nodeBlockIndex = new BPlusTree<key_t_int, nodeBlockPos, value_t_int>(base_dir, leaf_file, internal_file, leaf_cache_size, internal_cache_size, db_name, big_key_cache_size, tree_empty, overwrite);
	cacheManager->getCache(cacheManager->getBlockMetaCache(), new_smeta, S_META_OFFSET);
	mGraph = new MemoryGraph();
	community_nodes_path = base_dir + dbn + "//_communityNodes.db";
	node_block_path = base_dir + dbn + "//_ nodeBlockMap.db";
	edh_path = base_dir + dbn + "//_edh.db";

	if (!firsttime) {
		graph_create_time = string(new_smeta->data->createtime);
		schemaid = string(new_smeta->data->schemaid);
		mGraph->setInfo(new_smeta->data->nodenum, new_smeta->data->commnum, new_smeta->data->idtype, new_smeta->data->commtype, base_dir + db_name + "\\", new_smeta->data->iddefault, new_smeta->data->commdefault);
		gLoader->loadCommunityNodes(*mGraph, community_nodes_path);
		gLoader->loadNodeBlocks(*mGraph, node_block_path);
		gLoader->loadEdgeDestHead(*mGraph, edh_path);
	}

	setOpened(false);
}

void GraphManager::copyFrom(GraphManager* gm, string newname) {
	// copyfile
	if (_access((base_dir + newname).c_str(), 0) != 0) {
		system(("mkdir " + base_dir + newname).c_str());
	}

	db_name = newname;

	copyFileFrom(gm->db_name);

	block_listnum = gm->block_listnum;
	list_edgenum = gm->list_edgenum;
	ava_threshold = gm->ava_threshold;

	db_path = db_name + "//_db.dat";
	node_index_path = db_name + "//_Node_index.db";
	big_node_index_path = db_name + "//_Big_node_index.db";
	spd_index_path = db_name + "//_Spd_index.db";
	shortest_path_dist_path = db_name + "//_Shortest_dist.db";
	c2n_index_path = db_name + "//_C2N_index.db";
	c2n_dist_path = db_name + "//_C2N_dist.db";

	relDB = new RDB(base_dir, db_name);
	relDB->connect_sqlite();

	gLoader = new GraphLoader();
	blockIdPool = new IDPoolDisk(gm->blockIdPool, base_dir + db_name + "//_blockIdPool.idx");
	gUpdater = new GraphUpdater();

	list_size = sizeof(ListMeta) + list_edgenum * sizeof(GDBEdge);
	block_size = sizeof(BlockMeta) + block_listnum * list_size;

	begin_of_block = sizeof(int);

	vector<int> params;
	params.push_back(block_listnum);
	params.push_back(list_edgenum);
	cacheManager = new CacheManager(gm->cacheManager, base_dir, newname);

	inMemory = gm->inMemory;
	doBetweenness = gm->doBetweenness;

	nodeBlockIndex = new BPlusTree<key_t_int, nodeBlockPos, value_t_int>(gm->nodeBlockIndex, base_dir, newname);

	cacheManager->getCache(cacheManager->getBlockMetaCache(), new_smeta, S_META_OFFSET);
	graph_create_time = gm->graph_create_time;
	schemaid = gm->schemaid;

	mGraph = new MemoryGraph(gm->mGraph);

	setOpened(false);
}

void GraphManager::copyFileFrom(string origraph) {
	string exec_inst_head = "copy " + base_dir + origraph;
	string exec_inst_second_head = base_dir + db_name;

	//system(("CD " + origraph).c_str());
	//system("DIR");
	//string s = exec_inst_head + "\\_db.dat" + " " + exec_inst_second_head + "\\_db.dat";
	//cout << s << endl;
	system((exec_inst_head + "\\_db.dat" + " " + exec_inst_second_head + "\\_db.dat").c_str());
	system((exec_inst_head + "\\_meta_db.dat" + " " + exec_inst_second_head + "\\_meta_db.dat").c_str());
	system((exec_inst_head + "\\_Node_index.db" + " " + exec_inst_second_head + "\\_Node_index.db").c_str());
	system((exec_inst_head + "\\_Big_node_index.db" + " " + exec_inst_second_head + "\\_Big_node_index.db").c_str());
	system((exec_inst_head + "\\_Spd_index.db" + " " + exec_inst_second_head + "\\_Spd_index.db").c_str());
	system((exec_inst_head + "\\_Shortest_dist.db" + " " + exec_inst_second_head + "\\_Shortest_dist.db").c_str());
	system((exec_inst_head + "\\_C2N_index.db" + " " + exec_inst_second_head + "\\_C2N_index.db").c_str());
	system((exec_inst_head + "\\_C2N_dist.db" + " " + exec_inst_second_head + "\\_C2N_dist.db").c_str());
	system((exec_inst_head + "\\_blockIdPool.idx " + exec_inst_second_head + "\\_blockIdPool.idx").c_str());
	system((exec_inst_head + "\\_pool_nodeBlockLeafIndex.idx " + exec_inst_second_head + "\\_pool_nodeBlockLeafIndex.idx").c_str());
	system((exec_inst_head + "\\_pool_nodeBlockInternalIndex.idx " + exec_inst_second_head + "\\_pool_nodeBlockInternalIndex.idx").c_str());
	system((exec_inst_head + "\\_pool_nodeBlockBigKeyIndex.idx " + exec_inst_second_head + "\\_pool_nodeBlockBigKeyIndex.idx").c_str());
	system((exec_inst_head + "\\_nodeBlockBigKey.idx " + exec_inst_second_head + "\\_nodeBlockBigKey.idx").c_str());
	system((exec_inst_head + "\\_meta_nodeBlockBigKey.idx " + exec_inst_second_head + "\\_meta_nodeBlockBigKey.idx").c_str());
	system((exec_inst_head + "\\_meta_nodeBlockInternalIndex.idx " + exec_inst_second_head + "\\_meta_nodeBlockInternalIndex.idx").c_str());
	system((exec_inst_head + "\\_nodeBlockInternalIndex.idx " + exec_inst_second_head + "\\_nodeBlockInternalIndex.idx").c_str());
	system((exec_inst_head + "\\_nodeBlockLeafIndex.idx " + exec_inst_second_head + "\\_nodeBlockLeafIndex.idx").c_str());
}

GraphManager::~GraphManager()
{
	gLoader->writeCommunityNodes(*mGraph, community_nodes_path);
	gLoader->writeNodeBlocks(*mGraph, node_block_path);
	gLoader->writeEdgeDestHead(*mGraph, edh_path);
	
	if (mGraph)
		delete mGraph;
	if (relDB) {
		relDB->disconnect_sqlite();
		delete relDB;
	}
	if (cacheManager)
		delete cacheManager;
	if (gLoader)
		delete gLoader;
	if (nodeBlockIndex)
		delete nodeBlockIndex;
	if (blockIdPool)
		delete blockIdPool;	
}

void GraphManager::init()
{
	//mGraph->nodeIdAlloter->set(mGraph->nodeNum);
	//mGraph->communityIdAlloter->set(mGraph->communityNum);

	// updateBigIndex = unordered_map<int, int>(n + 1, -1);
	// mGraph->init(mGraph->nodeNum, mGraph->communityNum);

	gRegion = vector<GDBRegion>(mGraph->communityNum + 1);
}

void GraphManager::storeAttributes(unordered_map<int, int>& nodetypes)
{
	relDB->initNodeTable(db_name + "\\nodeAttributes.dat", nodetypes);
	relDB->initEdgeTable(db_name + "\\edgeAttributes.dat");
}

void GraphManager::setOpened(bool op)
{
	opened = op;
}

bool GraphManager::isOpen()
{
	return opened;
}

double GraphManager::store(int limit)
{
	//tempGraph = new GDBDataGraph();
	//Graph gra;

	int n, m;

	gLoader->readCommunity(*mGraph, db_name + "\\community.dat", base_dir + db_name + "\\");
	gLoader->readGraphFromFile(*mGraph, db_name + "\\network.dat");
		
	storeAttributes(mGraph->nodeType);

	init();
	initialNew();

	double time_consumed = 0;

	cout << "Start to Write File" << endl;

	storeGraphGreedy(*mGraph, limit);

	/*if (doBetweenness)
	{
		initBetweenness();

		cout << "bulkbuilddist" << endl;
		BulkBuildShortestPathDist(*testgraph);
		openSpdIndexFile(spd_index_path, shortest_path_dist_path);

		cout << "brandesdisk" << endl;
		//BrandesDisk(testgraph->netWorkSet);
		Brandes(testgraph->netWorkSet);

		cout << "init" << endl;
		//InitCommunityShortDistanceDisk(testgraph->nodeCommunitySet);
		InitCommunityShortDistance();
	}*/

	nodeBlockIndex->bulkBuildIndex(*this);

	/*if (doBetweenness)
	{
		cout << "bulkbuildcommu" << endl;
		BulkBuildCommunityToNodeDist(*testgraph);

		cout << "write" << endl;
		write_community_message();

		spd_node_index.close_file();
		spd_index.close_file();
	}*/

	node_map_block.clear();

	setOpened(true);
	//Disconnect();

	return 0;
}

double GraphManager::store(string networkfile, string communityfile, int limit)
{
	//tempGraph = new GDBDataGraph();
	//Graph gra;

	int n, m;

	gLoader->readCommunity(*mGraph, communityfile, base_dir + db_name + "\\");
	gLoader->readNetworkFromFile(*mGraph, networkfile);

	storeAttributes(mGraph->nodeType);

	init();
	initialNew();

	// mGraph->initIdAlloter();

	double time_consumed = 0;

	cout << "Start to Write File" << endl;

	storeGraphGreedy(*mGraph, limit);

	/*if (doBetweenness)
	{
	initBetweenness();

	cout << "bulkbuilddist" << endl;
	BulkBuildShortestPathDist(*testgraph);
	openSpdIndexFile(spd_index_path, shortest_path_dist_path);

	cout << "brandesdisk" << endl;
	//BrandesDisk(testgraph->netWorkSet);
	Brandes(testgraph->netWorkSet);

	cout << "init" << endl;
	//InitCommunityShortDistanceDisk(testgraph->nodeCommunitySet);
	InitCommunityShortDistance();
	}*/

	nodeBlockIndex->bulkBuildIndex(*this);

	/*if (doBetweenness)
	{
	cout << "bulkbuildcommu" << endl;
	BulkBuildCommunityToNodeDist(*testgraph);

	cout << "write" << endl;
	write_community_message();

	spd_node_index.close_file();
	spd_index.close_file();
	}*/

	node_map_block.clear();

	// setNodenumInDisk(mGraph->nodeNum);
	// setCommnumInDisk(mGraph->communityNum);

	setOpened(true);
	//Disconnect();

	return 0;
}

void GraphManager::connect()
{
	cacheManager->getCache(cacheManager->getBlockMetaCache(), new_smeta, S_META_OFFSET);

	// OpenIndex
	//bigKeyIndex->open();

	if (doBetweenness)
	{
		//openSpdIndexFile(spd_index_path, shortest_path_dist_path);
		//openC2NIndexFile(c2n_index_path, c2n_dist_path);
		//read_community_message();
	}
	relDB->connect_sqlite();

	community_nodes_path = db_name + "_" + "communityNodes.db";
	gLoader->loadCommunityNodes(*mGraph, community_nodes_path);

	node_block_path = db_name + "_" + "nodeBlock.db";
	gLoader->loadNodeBlocks(*mGraph, node_block_path);

	setOpened(true);
}

void GraphManager::disconnect()
{
	if (doBetweenness)
	{
		//write_community_message();
		//c2n_node_index.unmapping(&c2n_node_index.emptyStart, OFFSET_EMPTY_START);
		//c2n_node_index.index_file.close();
		//spd_index.Clear_Cache();
		//spd_node_index.unmapping(&spd_node_index.emptyStart, OFFSET_EMPTY_START);
		//spd_node_index.index_file.close();
	}

// Tools / Files
	

// Cache
	clearCache();

// Index
	//bigKeyIndex->close();
	
	if (relDB->isOpen())
	{
		relDB->disconnect_sqlite();
	}

	gLoader->writeCommunityNodes(*mGraph, community_nodes_path);

	setOpened(false);
}

void GraphManager::initialNew()
{
	//StorageMeta* meta = new StorageMeta(0);
	//cacheManager->createCache(cacheManager->getBlockMetaCache(), new_smeta, S_META_OFFSET, meta);
	
	//db_alloc_new(meta);
}

void GraphManager::storeGraphGreedy(MemoryGraph& graph, int limit)
{
	int existCommunity = 1;
	int communityNum = graph.getCommunityNum();

	while (existCommunity < communityNum)
	{
		storeCommunityGreedyRelation(graph, existCommunity, limit);
		existCommunity++;
	}
}

int GraphManager::listNumofNode(int needNum, int list_edge_num)
{
	int count = needNum / list_edge_num;
	if (needNum % list_edge_num == 0)
		return count;
	else
		return count + 1;
}

void GraphManager::storeCommunityGreedyRelation(MemoryGraph& graph, int comid, int limit)
{
	GDBRegion* r_meta = &gRegion[comid];

	unordered_set<int> nodes;
	unordered_map<int, int> startEdge;

	int totalList = 0;//整个社区节点需要多少个list
	for (const auto& node : graph.communityNodes[comid])
	{
		int node_id = node;
		int nodeEdgeNumber = graph.nodeEdges[node_id];
		int listNumberOfNode = nodeEdgeNumber / list_edgenum;
		if (nodeEdgeNumber % list_edgenum != 0)
			++listNumberOfNode;
		totalList += listNumberOfNode;
		nodes.insert(node_id);
		startEdge[node_id] = 0;
	}

	int blockNum = totalList / block_listnum;
	if (totalList % block_listnum != 0)
		++blockNum;

	int block_count = 0;
	float lastCw = 0;
	float lastDw = 0;
	int nodenum = 0;
	int edgenum = 0;
	float recordCw = 0;
	float recordEdge = 0;
	//int maxrelation = 0;
	int recordListNum = 0;

	unordered_map<int, list<int>::iterator> relationIter;
	map<int, list<int>> relationNode;
	unordered_map<int, int> nodeRelation;

	for (const auto& n : nodes)
	{
		nodeRelation[n] = 0;
		relationNode[0].push_back(n);
		relationIter[n] = (--relationNode[0].end());
	}

	CacheNode<GDBBlock>* block = allotNewBlock(comid);
	int currentBlockIndex = block->offset;
	r_meta->blockIds.insert(currentBlockIndex);

	while (!nodes.empty())
	{
		float maxlocal = -1;
		int maxpos = 0;

		if (block->data->b_meta.ava_listnum == block_listnum)
		{
			block_count++;
			cacheManager->releaseCache(block, blockIdPool);
			
			block = allotNewBlock(comid);
			currentBlockIndex = block->offset;
			r_meta->blockIds.insert(currentBlockIndex);

			lastCw = 0;
			lastDw = 0;
			nodenum = 0;
			recordEdge = 0;
			edgenum = 0;
			recordListNum = 0;
			relationNode.clear();
			nodeRelation.clear();
			relationIter.clear();

			for (const auto& n : nodes)
			{
				nodeRelation[n] = 0;
				relationNode[0].push_back(n);
				relationIter[n] = (--relationNode[0].end());
			}
		}

		int insertnum = 0;
		int count = 0;

		bool full = false;

		map<int, list<int>>::reverse_iterator relationIt = relationNode.rbegin();
		while (relationIt != relationNode.rend())
		{
			if (count >= limit)
				break;

			for (const auto& node : relationIt->second)
			{
				count++;
				if (count >= limit)
				{
					break;
				}

				int edge_count = graph.nodeEdges[node] - startEdge[node];
				int needListNum = listNumofNode(edge_count, list_edgenum);
				int canListNum = block_listnum - block->data->b_meta.ava_listnum;
				int listNum = min(needListNum, canListNum);
				int edgeNum = min(edge_count, listNum * list_edgenum);

				if (!full)
					full = (edgeNum == graph.nodeEdges[node]);
				else
				{
					if (edgeNum != graph.nodeEdges[node])
						continue;
				}

				float newCw;
				if (graph.nodeEdges[node] == 0)
				{
					newCw = lastCw + 1;
				}
				else
				{
					newCw = lastCw + (float)edgeNum / graph.nodeEdges[node];
				}

				int tempedge = lastDw + nodeRelation[node];

				int newD = tempedge;
				if (nodenum == 0)
				{
					newD = 1;
				}

				float newlocal = newCw * newD;

				if (newlocal > maxlocal || (newlocal == maxlocal && listNum > insertnum))
				{
					maxpos = node;
					maxlocal = newlocal;
					insertnum = listNum;
					recordEdge = tempedge;
					recordCw = newCw;
					recordListNum = listNum;
				}

				//	if(full)
				//		break;
			}

			if (full)
				break;

			relationIt++;
		}

		lastCw = recordCw;
		lastDw = recordEdge;
		nodenum++;
		int tempStartCount = startEdge[maxpos];
		//unordered_map<int, int>::iterator tempIter = startIter[maxpos];

		assignNodeToBlockNew(graph, currentBlockIndex, block_count
			, block->data, maxpos, tempStartCount, recordListNum, true);//正式插入，改变block值

		int node_id = maxpos;

		node_map_block[node_id].push_back(currentBlockIndex);
		mGraph->nodeblock[node_id].insert(currentBlockIndex);

		if (tempStartCount < graph.nodeEdges[node_id])//若该节点没有存完，则保存下来，之后可能会存
		{
			startEdge[node_id] = tempStartCount;
			//startIter[node_id] = tempIter;
		}
		else
		{
			nodes.erase(node_id);
		}

		if (block->data->b_meta.ava_listnum != block_listnum)
		{
			int r = nodeRelation[node_id];
			
			relationNode[r].erase(relationIter[node_id]);
			nodeRelation.erase(node_id);
			
			if (relationNode[r].empty())
				relationNode.erase(r);

			for (const auto& n : nodes)
			{
				int c = 0;
				if (graph.netWorkSet[node_id].find(n) != graph.netWorkSet[node_id].end())
				{
					c++;
				}
				if (graph.netWorkSet[n].find(node_id) != graph.netWorkSet[n].end())
				{
					c++;
				}
				if (c > 0)
				{
					int r = nodeRelation[n];
					//int pos = lower_bound(relationNode[r].begin(), relationNode[r].end(), edgeit->first) - relationNode[r].begin();
					relationNode[r].erase(relationIter[n]);

					if (relationNode[r].empty())
						relationNode.erase(r);

					nodeRelation[n] += c;
					r += c;

					relationNode[r].push_back(n);
					relationIter[n] = (--relationNode[r].end());
				}
				//recordNeigh.insert(n);
			}
		}
	}

	float avalist = block->data->b_meta.ava_listnum;
	if (avalist / (float)block_listnum < ava_threshold)
		r_meta->avaBlock = block->offset;

	cacheManager->releaseCache(block, blockIdPool);
}

int GraphManager::assignNodeToBlockNew(MemoryGraph& graph, int thisoffset, int block_count, GDBBlock* block,
	int node, int& startEdgeCount, int listNum, bool real)
{
	int startListNum = block->b_meta.ava_listnum;
	
	for (int i = 0; i < listNum; i++, startListNum++)
	{
		block->lists[startListNum].l_meta.nodeid = node;
		
		int temp = startEdgeCount;
		for (int j = 0; j < list_edgenum && startEdgeCount < graph.nodeEdges[node]; j++, startEdgeCount++)
		{
			//int dest = graph.netWork[node][startEdgeCount].first;
			int dest = (*graph.destIter[node]).first;
			GDBEdge* edgej = &block->lists[startListNum].edge[j];
			edgej->dest_id = dest;
			//block->lists[startListNum].edge[j].type = graph.netWork[node][startEdgeCount].second;
			edgej->type = (*graph.typeIter[node]);

			if(getEdgeDestHead(dest, EDH_BLOCK_INDEX) == -1)
			{
				setEdgeDestHead(dest, thisoffset, startListNum, j);
				edgej->next.set(-1, -1, -1);
				edgej->pre.set(-1, -1, -1);
			}
			else
			{
				if (getEdgeDestHead(dest, EDH_BLOCK_INDEX) == thisoffset)
				{
					edgej->next.set(getEdgeDestHead(dest));
					edgej->pre.set(-1, -1, -1); 
					int list_index = getEdgeDestHead(dest, EDH_LIST_INDEX);
					int index = getEdgeDestHead(dest, EDH_EDGE_INDEX);
					EdgePos* bpre = &block->lists[list_index].edge[index].pre;
					bpre->block_pos = thisoffset;
					bpre->list_index = startListNum;
					bpre->edge_index = j;
					setEdgeDestHead(dest, thisoffset, startListNum, j);
				}
				else
				{
					EdgePos* ep = getEdgeDestHead(dest);
					int block_pos = ep->block_pos;
					CacheNode<GDBBlock>* b = nullptr;
					cacheManager->getCache(cacheManager->getBlockCache(), b, block_pos);

					int list_index = ep->list_index;
					int edge_index = ep->edge_index;
					EdgePos* bpre = &b->data->lists[list_index].edge[edge_index].pre;
					bpre->set(thisoffset, startListNum, j);

					cacheManager->releaseCache(b, blockIdPool);

					edgej->next.set(block_pos, list_index, edge_index);
					edgej->pre.set();
					setEdgeDestHead(dest, thisoffset, startListNum, j);
				}
			}

			graph.typeIter[node]++;
			if (graph.typeIter[node] == graph.destIter[node]->second.end())
			{
				graph.destIter[node]++;

				if (graph.destIter[node] != graph.netWorkSet[node].end())
				{
					graph.typeIter[node] = graph.destIter[node]->second.begin();
				}
			}
		}
		//block->lists[startListNum].edge[j] = graph.netWork[node][startEdgeCount];
		block->lists[startListNum].l_meta.edge_num = startEdgeCount - temp;
	}
	if (real)//如果确定插入，在该block可用的空间位置
		block->b_meta.ava_listnum = startListNum;
	return startListNum;
}

int GraphManager::getBlockIndex(int offset)
{
	return (offset - begin_of_block) / block_size;
}

CacheNode<GDBBlock>* GraphManager::allotNewBlock(int cid)
{
	CacheNode<GDBBlock>* block = nullptr;
	int blockIndex = blockIdPool->nextId();
	
	if (blockIdPool->newAlloted())
	{
		block = cacheManager->createBlockCache(block_listnum, list_edgenum, cid, blockIndex);
	}
	else
	{
		vector<int> p(1, cid);
		block = cacheManager->initCache(cacheManager->getBlockCache(), blockIndex, p);
	}

	return block;
}

void GraphManager::removeBlock(GDBBlock* block, int blockIndex, int comid, bool isAva)
{
	if (isAva)
	{
		gUpdater->removeRegionAvaBlock(*this, comid, block, blockIndex);
	}
	gRegion[comid].blockIds.erase(blockIndex);
	blockIdPool->removeId(blockIndex);
	cacheManager->getBlockCache().remove(blockIndex);
}

void GraphManager::clearCache()
{
	// All Cache defined in Graph should invoke function clear()
}

bool GraphManager::nodeHasCommunity(int node)
{
	return mGraph->nodeHasCommunity(node);
}

int GraphManager::getNodeFirstCommunity(int node)
{
	return mGraph->getNodeFirstCommunity(node);
}

int GraphManager::getEdgeDestHead(int destid, int type)
{
	if (type == 0)
		return mGraph->edge_dest_head[destid].block_pos;
	else if (type == 1)
		return mGraph->edge_dest_head[destid].list_index;
	else
		return mGraph->edge_dest_head[destid].edge_index;
}

EdgePos* GraphManager::getEdgeDestHead(int destid)
{
	return &(mGraph->edge_dest_head[destid]);
}

void GraphManager::setEdgeDestHead(int destid, int boff, int lidx, int eidx)
{
	mGraph->edge_dest_head[destid].set(boff, lidx, eidx);
}

void GraphManager::setEdgeDestHead(int destid, EdgePos* ep)
{
	mGraph->edge_dest_head[destid].set(ep);
}

void GraphManager::setInMemory() {
	mGraph = new MemoryGraph();
	loadMemoryGraphFromDisk();
}

void GraphManager::releaseInMemory() {
	delete mGraph;
}

void GraphManager::loadMemoryGraph(int type) {
	if (mGraph)
		delete mGraph;
	mGraph = new MemoryGraph();

	if (type == 0) {
		loadMemoryGraphFromFile();
	}
	else if (type == 1) {
		loadMemoryGraphFromDisk();
	}
}

void GraphManager::loadMemoryGraphFromFile() {
	string networkfile;
	string labelfile;

	gLoader->readGraphFromFile(*mGraph, networkfile, labelfile);
}

void GraphManager::loadMemoryGraphFromDisk() {
	mGraph->initNetwork(new_smeta->data->nodenum);

	GraphIO* blockIO = cacheManager->getBlockCache().getIO();
	GDBBlock* block = new GDBBlock(block_listnum, list_edgenum);
	vector<int> params;
	params.push_back(block_listnum);
	params.push_back(list_edgenum);

	unordered_set<int> nodeset;

	int startoff = begin_of_block;
	while (true) {
		blockIO->mapping(block, startoff, params);
		addBlockToGraph(block, nodeset);

		startoff += block_size;
		blockIO->file.seekg(startoff);
		if (blockIO->file.peek() == -1)
			break;
	}

	mGraph->nodes = vector<int>(nodeset.begin(), nodeset.end());
	sort(mGraph->nodes.begin(), mGraph->nodes.end());

	gLoader->initAfterReadNetwork(*mGraph, "");
}

void GraphManager::addBlockToGraph(GDBBlock* block) {
	int listnum = block->b_meta.ava_listnum;
	for (int i = 0; i < listnum; ++i) {
		int node1 = block->lists[i].l_meta.nodeid;
		int edgenum = block->lists[i].l_meta.edge_num;
		for (int j = 0; j < edgenum; ++j) {
			int node2 = block->lists[i].edge[j].dest_id;
			int type = block->lists[i].edge[j].type;
			
			mGraph->addEdge(node1, node2, type);
		}
	}
}

void GraphManager::addBlockToGraph(GDBBlock* block, unordered_set<int>& nodeset) {
	int listnum = block->b_meta.ava_listnum;
	for (int i = 0; i < listnum; ++i) {
		int node1 = block->lists[i].l_meta.nodeid;
		nodeset.insert(node1);
		int edgenum = block->lists[i].l_meta.edge_num;
		for (int j = 0; j < edgenum; ++j) {
			int node2 = block->lists[i].edge[j].dest_id;
			nodeset.insert(node2);
			int type = block->lists[i].edge[j].type;

			mGraph->addEdge(node1, node2, type);
		}
	}
}

int GraphManager::getNodenumFromDisk() {
	cacheManager->getCache(cacheManager->getBlockMetaCache(), new_smeta, S_META_OFFSET);
	int n = new_smeta->data->nodenum;
	IDPool* p = NULL;
	cacheManager->releaseCache(new_smeta, p);

	return n;
}

void GraphManager::setStorageMeta() {
	setNodenumInDisk(mGraph->nodeNum);
	setCommnumInDisk(mGraph->communityNum);

	new_smeta->data->idtype = mGraph->nodeIdAlloterType;
	new_smeta->data->commtype = mGraph->communityIdAlloterType;

	if (mGraph->nodeIdAlloterType == 0) {
		_itoa(mGraph->nodeIdAlloter.i2iAlloter->defaultval, new_smeta->data->iddefault, 10);
	}
	else {
		strcpy(new_smeta->data->iddefault, mGraph->nodeIdAlloter.s2iAlloter->defaultval.c_str());
	}

	if (mGraph->communityIdAlloterType == 0) {
		_itoa(mGraph->communityIdAlloter.i2iAlloter->defaultval, new_smeta->data->commdefault, 10);
	}
	else {
		strcpy(new_smeta->data->commdefault, mGraph->communityIdAlloter.s2iAlloter->defaultval.c_str());
	}
}

void GraphManager::setNodenumInDisk(int val) {
	new_smeta->data->nodenum = val;
}

void GraphManager::setCommnumInDisk(int val) {
	new_smeta->data->commnum = val;
}

void GraphManager::setGraphTime() {
	time_t rawtime;
	time(&rawtime);
	char tmp[256];
	strftime(tmp, sizeof(tmp), "%Y-%m-%d-%H-%M-%S", localtime(&rawtime));
	graph_create_time = string(tmp);
	strcpy(new_smeta->data->createtime, graph_create_time.c_str());
}

void GraphManager::setGraphSchema(GraphSchemaManager* gsm, string& schema) {
	if (gsm->hasSchema(schema)) {
		schemaid = schema;
		gSchema = gsm->schemas[schema];
		strcpy(new_smeta->data->schemaid, schemaid.c_str());
	}
	else {
		cout << "Schema not found" << endl;
	}
}
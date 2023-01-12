#include "GraphUpdater.h"

void GraphUpdater::buildTempGraph(GraphManager& g, TempGraph& d_graph)
{
	for (const auto& node : d_graph.stored)
	{
		if (d_graph.storedStarts.find(node) != d_graph.storedStarts.end())
		{
			int cid = g.getNodeFirstCommunity(node);
			d_graph.nodeCommunity[node] = cid;
			//d_graph.lpaCommunityNode[cid].insert(node);
		}
		else
		{
			if (g.nodeHasCommunity(node))
				d_graph.nodeCommunity[node] = g.getNodeFirstCommunity(node);
		}
	}
}

bool GraphUpdater::getNodeCommunity(GraphManager& g, TempGraph& d_graph)
{
	if (d_graph.unstored.empty())
	{
		for (const auto& n : d_graph.storedStarts)
		{
			int cid = g.getNodeFirstCommunity(n);
			d_graph.lpaCommunityNode[cid].insert(n);
		}
		return false;
	}

	//全部有监督的社区发现，得到所有节点的社区标签
	LPAT lpa(5);
	lpa.Update(d_graph.netWorkSet, d_graph.nodeCommunity);

	for (const auto& n : d_graph.unstored)
	{
		int cid = d_graph.nodeCommunity[n];
		int newcid = -1;
		if (g.mGraph->communityIdAlloterType == 0) {
			if (g.mGraph->communityIdAlloter.s2iAlloter->existId(cid)) {
				newcid = cid;
			}
			else {
				newcid = g.mGraph->communityIdAlloter.i2iAlloter->idAlloter(cid);
			}
		}
		else {
			if (g.mGraph->communityIdAlloter.s2iAlloter->existId(cid)) {
				newcid = cid;
			}
			else {
				newcid = g.mGraph->communityIdAlloter.s2iAlloter->idAlloter(to_string(cid));
			}
		}
		d_graph.nodeCommunity[n] = newcid;
		d_graph.maxNodeId = max(d_graph.maxNodeId, n);
		d_graph.maxCommId = max(d_graph.maxCommId, newcid);
	}

	g.mGraph->reAllotNodeSpace(d_graph.maxNodeId);
	g.mGraph->reAllotCommSpace(d_graph.maxCommId);

	for (const auto& n : d_graph.netWorkSet)
	{
		int nid = n.first;
		int cid = d_graph.nodeCommunity[nid];
		d_graph.lpaCommunityNode[cid].insert(nid);
	}

	for (const auto& n : d_graph.unstored)
	{
		int nid = insertNewNode(g, n, 0, vector<int>(1, d_graph.nodeCommunity[n]), vector<string>(), false);
	}

	return true;
}


// Insert Data

void GraphUpdater::insertDataV1(GraphManager& g, TempGraph& d_graph)
{
	buildTempGraph(g, d_graph);
	getNodeCommunity(g, d_graph);
	insertData(g, d_graph);
}


bool GraphUpdater::insertData(GraphManager& g, TempGraph& d_graph)
{
	g.node_map_block.clear();
	//updateBigIndex.clear();
	/*if (f_level == 0)
	{
	f_level++;
	db_file.open(path, ios::in | ios::out | ios::binary);
	mapping(&new_smeta, S_META_OFFSET);
	}*/
	unordered_map<int, unordered_map<int, vector<int>>>::iterator it = d_graph.netWorkSet.begin();

	//将已存储的节点存到已存的list中
	unordered_set<int>::iterator storelistIt = d_graph.storedStarts.begin();
	while (storelistIt != d_graph.storedStarts.end())
	{
		int node = *storelistIt;

		int startEdge = 0;
		int cid = d_graph.nodeCommunity[node];
		insertNodeToBlocksExistList(g, node, d_graph.netWorkSet[node], d_graph.nodeEdges[node], 
			startEdge, d_graph.destIter[node], d_graph.typeIter[node], g.mGraph->nodeblock[node]);//获取regionoffset

		if (startEdge != d_graph.nodeEdges[node])
		{
			d_graph.node_startEdge[node] = startEdge;
			storelistIt++;
		}
		else//如果装满了则删除
		{
			d_graph.storedStarts.erase(storelistIt++);
			d_graph.node_startEdge.erase(node);
		}
	}
	
	cout << "insert 1" << endl;
	//查看已存的Block中是否有空的list
	storelistIt = d_graph.storedStarts.begin();
	while (storelistIt != d_graph.storedStarts.end())
	{
		int node = *storelistIt;
		int startEdge = d_graph.node_startEdge[node];
		insertNodeToBlocksNewList(g, node, d_graph.nodeCommunity[node], d_graph.netWorkSet[node], d_graph.nodeEdges[node], 
			startEdge, d_graph.destIter[node], d_graph.typeIter[node], g.mGraph->nodeblock[node]);

		if (startEdge != d_graph.nodeEdges[node])
		{
			d_graph.node_startEdge[node] = startEdge;
			storelistIt++;
		}
		else//如果装满了则删除
		{
			d_graph.storedStarts.erase(storelistIt++);
			d_graph.node_startEdge.erase(node);
		}
	}
	//cout << "insert 2" << endl;
	//将剩余的节点按照block贪心方法添加到block中
	unordered_map<int, int>nodeEdgeNum;//贪心时统计的每个节点的边的剩余总数
	unordered_map<int, int>::iterator edgeNumit = d_graph.node_startEdge.begin();
	while (edgeNumit != d_graph.node_startEdge.end())
	{
		int node = edgeNumit->first;
		int tempStart = edgeNumit->second;
		nodeEdgeNum[node] = d_graph.nodeEdges[node] - tempStart;
		edgeNumit++;
	}

	unordered_map<int, unordered_set<int>>::iterator community_iter = d_graph.lpaCommunityNode.begin();
	while (community_iter != d_graph.lpaCommunityNode.end())
	{
		int cid = community_iter->first;

		unordered_set<int>::iterator nodes_it = community_iter->second.begin();//删除社区中已经存储完毕的节点
		while (nodes_it != community_iter->second.end())
		{
			int node = *nodes_it;

			d_graph.nodeCommunity[node] = cid;//存储所有节点的社区
			if (d_graph.node_startEdge.find(node) == d_graph.node_startEdge.end())
				community_iter->second.erase(nodes_it++);
			else
				nodes_it++;
		}
		//cout << "insert 3 " << cid << endl;
		if (!community_iter->second.empty())//i如果该社区还存在需要继续存储的节点
		{
			vector<int> nodes = vector<int>(community_iter->second.begin(), community_iter->second.end());
			unordered_map<int, unordered_set<int>> blockedges;
			unordered_map<int, int> blockedgenum;

			set<int> blocklist;
			for (const auto& n : nodes)
			{
				for (const auto& b : g.mGraph->nodeblock[n])
				{
					blocklist.insert(b);
				}
			}

			getNodeEdgesInBlocks(g, community_iter->second, blocklist, blockedgenum, blockedges);

			for(const auto& node_id : nodes)
			{
				blockedgenum[node_id] += d_graph.nodeEdges[node_id] - d_graph.node_startEdge[node_id];
			}

			std::sort(nodes.begin(), nodes.end());  //bug sort by degree

			if(!g.gRegion[cid].blockIds.empty())
			{
				int blockIndex = g.gRegion[cid].avaBlock;
				CacheNode<GDBBlock>* avaBlock = nullptr;

				/*while (blockIndex != -1 && !community_iter->second.empty())
				{
					//cout << regionOffset << endl;
					g.cacheManager->getCache(g.cacheManager->getBlockCache(), avaBlock, blockIndex);
					blockIndex = insertNodeToBlock(g, cid, nodes, d_graph.netWorkSet, d_graph.nodeEdges, 
						d_graph.destIter, d_graph.typeIter, d_graph.node_startEdge, blockedges, blockedgenum, blockIndex, avaBlock);
				}*/
				
				while (!nodes.empty())
				{
					avaBlock = g.allotNewBlock(cid);
					blockIndex = avaBlock->offset;

					insertNodeToBlock(g, cid, nodes, d_graph.netWorkSet, d_graph.nodeEdges, 
						d_graph.destIter, d_graph.typeIter, d_graph.node_startEdge, blockedges, blockedgenum, blockIndex, avaBlock);
					g.gRegion[cid].blockIds.insert(blockIndex);
				}
			}
			else
			{
				CacheNode<GDBBlock>* avaBlock = nullptr;

				while (!nodes.empty())
				{
					avaBlock = g.allotNewBlock(cid);
					int blockIndex = avaBlock->offset;
					insertNodeToBlock(g, cid, nodes, d_graph.netWorkSet, d_graph.nodeEdges, 
						d_graph.destIter, d_graph.typeIter, d_graph.node_startEdge, blockedges, blockedgenum, blockIndex, avaBlock);
					g.gRegion[cid].blockIds.insert(blockIndex);
				}
			}
		}
		community_iter++;
	}
	cout << "finish insert data" << endl;

	/*map<int, vector<int>>::iterator mit = newNetwork.begin();
	while(mit != newNetwork.end())
	{
	for(int i = 0; i < mit->second.size(); i++)
	{
	AddRel(mit->first, mit->second[i], 1);
	}
	mit++;
	}*/

	// insertIndex(node_blocknum, nodeCommunity);//更新插入的索引
											  
	return true;

}

int GraphUpdater::insertNewNode(GraphManager& g, int node_id, int type, vector<int>& comm_id, vector<string>& attributes, bool resize)
{
	g.mGraph->insertNode(node_id, comm_id, resize);
	
	if (!comm_id.empty())
	{
		comm_id.push_back(-1);
	}

	//openIndexFile(node_index_path.c_str(), big_node_index_path.c_str());

	set<int> blocks;
	blocks.clear();

	string node_s = to_string(node_id);

	//updateBigIndex[node_id] = -1;
	//node_index.insert_newkey(node_s.c_str(), comm_id[0], blocks);
	//node_index.set_bet_and_type(node_s.c_str(), 0, type);

	insertNewKey(g, node_id, type, attributes);

	//node_ids.insert(node_ids.begin() + pos, node_id);

	g.setEdgeDestHead(node_id, -1, -1, -1);

	//spd_node_index.index_file.close();
	//big_node_index.index_file.close();

	return node_id;
}

void GraphUpdater::insertNewKey(GraphManager& g, int node_id, int type, vector<string>& attributes)
{
	g.relDB->insertNewKey(type, attributes);
}

int GraphUpdater::insertNodeToBlock(GraphManager& g, int comid, vector<int>&nodes, unordered_map<int, unordered_map<int, vector<int>>>& newNetwork
	, unordered_map<int, int>& nodeedges, unordered_map<int, unordered_map<int, vector<int>>::iterator>& destIter
	, unordered_map<int, vector<int>::iterator>& typeIter, unordered_map<int, int>&node_startEdge, unordered_map<int, unordered_set<int>>& blockedges
	, unordered_map<int, int>& blockedgenum, int blockIndex, CacheNode<GDBBlock>* avaBlock)
{
	unordered_map<int, int> edges;
	
	for(const auto& node_id : nodes)
	{
		edges[node_id] = 0;
	}

	unordered_map<int, int> edgenums;
	vector<int> allnodes;
	unordered_set<int> ava_nodes;
	for (int i = 0; i < g.block_listnum; i++)
	{
		int nid = avaBlock->data->lists[i].l_meta.nodeid;
		if (nid != -1)
		{
			edgenums[nid] += avaBlock->data->lists[i].l_meta.edge_num;
			allnodes.push_back(nid);
			if (blockedges.find(nid) != blockedges.end())
				continue;
			ava_nodes.insert(nid);
		}
	}

	set<int> blocklist;
	for (const auto& n : ava_nodes)
	{
		for (const auto& b : g.mGraph->nodeblock[n])
		{
			blocklist.insert(b);
		}
	}

	getNodeEdgesInBlocks(g, ava_nodes, blocklist, blockedgenum, blockedges);
	for (const auto& n : ava_nodes)
	{
		if (newNetwork.find(n) != newNetwork.end())
		{
			blockedgenum[n] += nodeedges[n] - node_startEdge[n];
		}
	}

	int recordCw = 0;
	int recordEdge = 0;
	int lastCw = 0;
	int lastEdge = 0;

	for (int i = 0; i < allnodes.size(); i++)
	{
		int node_id = allnodes[i];
		int num = edgenums[i];
		//int allnum = blockedges[node_id].size();
		int allnum = blockedgenum[node_id];

		lastCw += (float)num / allnum;

		for (const auto& n : nodes)
		{
			if ((newNetwork.find(node_id) != newNetwork.end() && newNetwork[node_id].find(n) != newNetwork[node_id].end())
				|| (blockedges.find(node_id) != blockedges.end() && blockedges[node_id].find(n) != blockedges[node_id].end()))
			{
				edges[n]++;
			}
			if ((newNetwork.find(n) != newNetwork.end() && newNetwork[n].find(node_id) != newNetwork[n].end())
				|| (blockedges.find(n) != blockedges.end() && blockedges[n].find(node_id) != blockedges[n].end()))
			{
				edges[n]++;
			}
		}

		for (int j = i + 1; j < allnodes.size(); j++)
		{
			if ((newNetwork.find(node_id) != newNetwork.end() && newNetwork[node_id].find(allnodes[j]) != newNetwork[node_id].end())
				|| (blockedges.find(node_id) != blockedges.end() && blockedges[node_id].find(allnodes[j]) != blockedges[node_id].end()))
			{
				lastEdge++;
			}
			if ((newNetwork.find(allnodes[j]) != newNetwork.end() && newNetwork[allnodes[j]].find(node_id) != newNetwork[allnodes[j]].end())
				|| (blockedges.find(allnodes[j]) != blockedges.end() && blockedges[allnodes[j]].find(node_id) != blockedges[allnodes[j]].end()))
			{
				lastEdge++;
			}
		}
	}

	bool saved = false;

	while (!nodes.empty())
	{
		float maxlocal = -1;
		int maxpos = 0;
		saved = false;
		int limitNum = 200;
		int count = 0;

		int insertnum = 0;

		for (int i = 0; i < nodes.size() && i < limitNum; i++)
		{
			int edge_count = nodeedges[nodes[i]] - node_startEdge[nodes[i]];
			int needListNum = g.listNumofNode(edge_count, g.list_edgenum);
			int canListNum = g.block_listnum - avaBlock->data->b_meta.ava_listnum;
			int listNum = min(needListNum, canListNum);
			int edgeNum = min(edge_count, listNum * g.list_edgenum);

			float newCw = lastCw + (float)edgeNum / blockedgenum[nodes[i]];
			//float newC = newCw / (allnodes.size() + 1);

			int tempedge = lastEdge;
			tempedge += edges[nodes[i]];

			float newD = tempedge;
			if (allnodes.empty())
			{
				newD = 1;
			}

			float newlocal = newCw * newD;

			if (newlocal > maxlocal || (newlocal == maxlocal && listNum > insertnum))
			{
				maxpos = i;
				maxlocal = newlocal;
				insertnum = listNum;
				recordEdge = tempedge;
				recordCw = newCw;
			}
		}

		lastCw = recordCw;
		lastEdge = recordEdge;
		allnodes.push_back(nodes[maxpos]);
		int tempStartCount = node_startEdge[nodes[maxpos]];
		int lastpos = tempStartCount;

		assignNodeToBlock(g, nodes[maxpos], avaBlock->data, blockIndex, newNetwork, nodeedges, destIter[nodes[maxpos]], typeIter[nodes[maxpos]], tempStartCount);//正式插入，改变block

		g.node_map_block[nodes[maxpos]].push_back(blockIndex);
		g.mGraph->nodeblock[nodes[maxpos]].insert(blockIndex);

		edges.erase(nodes[maxpos]);

		for (const auto& n : nodes)
		{
			if (n == nodes[maxpos])
				continue;

			if ((newNetwork.find(nodes[maxpos]) != newNetwork.end() && newNetwork[nodes[maxpos]].find(n) != newNetwork[nodes[maxpos]].end())
				|| (blockedges.find(nodes[maxpos]) != blockedges.end() && blockedges[nodes[maxpos]].find(n) != blockedges[nodes[maxpos]].end()))
			{
				edges[n]++;
			}
			if ((newNetwork.find(n) != newNetwork.end() && newNetwork[n].find(nodes[maxpos]) != newNetwork[n].end())
				|| (blockedges.find(n) != blockedges.end() && blockedges[n].find(nodes[maxpos]) != blockedges[n].end()))
			{
				edges[n]++;
			}
		}

		if (tempStartCount < nodeedges[nodes[maxpos]])
		{
			//cout << tempStartCount << " " << nodeedges[mynodes[maxpos].id] << " " << mynodes[maxpos].id << " " << (*avaBlock)->db.b_meta.ava_listnum << endl;
			//system("pause");
			node_startEdge[nodes[maxpos]] = tempStartCount;
		}
		else
			nodes.erase(nodes.begin() + maxpos);

		if (avaBlock->data->b_meta.ava_listnum == g.block_listnum)
		{
			//block_offsets.insert(avaBlockOffset);

			int temprecord = avaBlock->data->b_meta.avaNext;
			avaBlock->data->b_meta.avaPre = -1;
			avaBlock->data->b_meta.avaNext = -1;
			g.cacheManager->releaseCache(avaBlock, g.blockIdPool);
			
			g.gRegion[comid].avaBlock = temprecord;
			
			saved = true;//该block已经保存过了

			break;
		}
	}

	if (nodes.empty() && saved == false)//当节点全部保存完毕，并且恰好最后一个block没有保存完毕
	{
		float ava = avaBlock->data->b_meta.ava_listnum;
		float all = g.block_listnum;
		float percent = ava / all;
		if (percent < g.ava_threshold)
		{
			g.gRegion[comid].avaBlock = blockIndex;
		}
		else
		{
			g.gRegion[comid].avaBlock = avaBlock->data->b_meta.avaNext;
			avaBlock->data->b_meta.avaPre = -1;
			avaBlock->data->b_meta.avaNext = -1;
		}

		g.cacheManager->releaseCache(avaBlock, g.blockIdPool);
	}

	return g.gRegion[comid].avaBlock;
}

void GraphUpdater::getNodeEdgesInBlocks(GraphManager& g, unordered_set<int>& nodes, set<int>& blocks, unordered_map<int, int>& edgecount, unordered_map<int, unordered_set<int>>& network)
{
	for (const auto& b : blocks)
	{
		CacheNode<GDBBlock>* block = nullptr;
		g.cacheManager->getCache(g.cacheManager->getBlockCache(), block, b);

		for (int i = 0; i < g.block_listnum; i++)
		{
			int nid = block->data->lists[i].l_meta.nodeid;
			if (nodes.find(nid) != nodes.end())
			{
				int edge_num = block->data->lists[i].l_meta.edge_num;
				edgecount[nid] += edge_num;
				for (int j = 0; j < edge_num; j++)
					network[nid].insert(block->data->lists[i].edge[j].dest_id);
			}

		}
		g.cacheManager->releaseCache(block, g.blockIdPool);
	}
}

void GraphUpdater::assignEdge(GraphManager& g, GDBBlock* block, int node, int dest_id, int list_index, int edge_index, int blockIndex)
{
	int i = list_index;
	int count = edge_index;

	if (g.getEdgeDestHead(dest_id, EDH_BLOCK_INDEX) == -1)
	{
		g.setEdgeDestHead(dest_id, blockIndex, i, count);
		block->lists[i].edge[count].next.set();
		block->lists[i].edge[count].pre.set(); 
	}
	else
	{
		EdgePos* ep = g.getEdgeDestHead(dest_id);
		if (ep->block_pos == blockIndex)
		{
			block->lists[i].edge[count].next.set(ep);
			block->lists[i].edge[count].pre.set();
			int list_index = ep->list_index;
			int edge_index = ep->edge_index;
			block->lists[list_index].edge[edge_index].pre.set(blockIndex, i, count);
			g.setEdgeDestHead(dest_id, blockIndex, i, count);
		}
		else
		{
			int p = ep->block_pos;
			CacheNode<GDBBlock>* newblock = nullptr;
			g.cacheManager->getCache(g.cacheManager->getBlockCache(), newblock, p);

			int list_index = ep->list_index;
			int edge_index = ep->edge_index;

			newblock->data->lists[list_index].edge[edge_index].pre.set(blockIndex, i, count);

			g.cacheManager->releaseCache(newblock, g.blockIdPool);
			//Write_Block(newblock, tempGraph->edge_dest_head[block->lists[i].edge[count].dest_id].block_pos, 6);

			block->lists[i].edge[count].next.set(ep);
			block->lists[i].edge[count].pre.set();
			g.setEdgeDestHead(dest_id, blockIndex, i, count);
		}
	}
}

int GraphUpdater::assignNodeToBlock(GraphManager& g, int node,GDBBlock* block, int blockIndex, unordered_map<int, unordered_map<int, vector<int>>>& newNetwork
	, unordered_map<int, int>& nodeedges, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, int&startEdge)
{
	for (int i = 0; i < g.block_listnum; i++)
	{
		if (startEdge == nodeedges[node])
			break;
		if (block->lists[i].l_meta.nodeid == -1)
		{
			int count = 0;
			block->lists[i].l_meta.nodeid = node;
			while (count < g.list_edgenum && startEdge < nodeedges[node])
			{
				block->lists[i].edge[count].dest_id = edgedest->first;
				block->lists[i].edge[count].type = *edgetype;
				int dest_id = block->lists[i].edge[count].dest_id;
				assignEdge(g, block, node, dest_id, i, count, blockIndex);

				startEdge++;
				count++;

				edgetype++;
				if (edgetype == edgedest->second.end())
				{
					edgedest++;

					if (edgedest != newNetwork[node].end())
					{
						edgetype = edgedest->second.begin();
					}
				}
			}

			block->b_meta.ava_listnum++;
			block->lists[i].l_meta.edge_num = count;
		}
	}
	return 0;
}

void GraphUpdater::insertNodeOneBlockExistList(GraphManager& g, int node, unordered_map<int, vector<int>>&edges, int &alledges, int& startEdge
	, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, int blockIndex)
{
	CacheNode<GDBBlock>* block = nullptr;
	g.cacheManager->getCache(g.cacheManager->getBlockCache(), block, blockIndex);
	
	for (int i = 0; i < g.block_listnum; i++)
	{
		//block.lists[i].l_meta.nodeid = -1;
		if (startEdge == alledges)
			break;
		if (block->data->lists[i].l_meta.nodeid == node)
		{
			int edge_num = block->data->lists[i].l_meta.edge_num;
			while (edge_num < g.list_edgenum && startEdge < alledges)
			{
				block->data->lists[i].edge[edge_num].dest_id = edgedest->first;
				block->data->lists[i].edge[edge_num].type = *edgetype;

				int dest_id = block->data->lists[i].edge[edge_num].dest_id;

				assignEdge(g, block->data, node, dest_id, i, edge_num, blockIndex);

				edge_num++;
				startEdge++;

				edgetype++;
				if (edgetype == edgedest->second.end())
				{
					edgedest++;

					if (edgedest != edges.end())
					{
						edgetype = edgedest->second.begin();
					}
				}
			}
			block->data->lists[i].l_meta.edge_num = edge_num;
		}

	}
	
	g.cacheManager->releaseCache(block, g.blockIdPool);
}

void GraphUpdater::insertNodeToBlocksExistList(GraphManager& g, int node, unordered_map<int, vector<int>>&edges, int& alledges, int& startEdge
	, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, unordered_set<int>&blocklist)
{
	for (const auto& block : blocklist)
	{
		if (startEdge == alledges)
			break;
		insertNodeOneBlockExistList(g, node, edges, alledges, startEdge, edgedest, edgetype, block);
	}
}

void GraphUpdater::insertNodeOneBlockNewList(GraphManager& g, int node, int cid, unordered_map<int, vector<int>>&edges, int& alledges, int& startEdge
	, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, int blockIndex)
{
	CacheNode<GDBBlock>* block = nullptr;
	g.cacheManager->getCache(g.cacheManager->getBlockCache(), block, blockIndex);
	
	if (block->data->b_meta.ava_listnum == g.block_listnum)
	{
		g.cacheManager->releaseCache(block, g.blockIdPool);
		return;
	}

	int totalSize = alledges;
	for (int i = 0; i < g.block_listnum; i++)
	{
		if (startEdge == alledges)
			break;
		if (block->data->lists[i].l_meta.nodeid == -1)
		{
			block->data->b_meta.ava_listnum++;
			block->data->lists[i].l_meta.nodeid = node;
			int edge_num = 0;
			if (totalSize - startEdge > g.list_edgenum)
				edge_num = g.list_edgenum;
			else
				edge_num = totalSize - startEdge;
			block->data->lists[i].l_meta.edge_num = edge_num;
			for (int j = 0; j < edge_num; j++)
			{
				block->data->lists[i].edge[j].dest_id = edgedest->first;
				block->data->lists[i].edge[j].type = *edgetype;
				int dest_id = block->data->lists[i].edge[j].dest_id;
				
				assignEdge(g, block->data, node, dest_id, i, j, blockIndex);

				startEdge++;

				edgetype++;
				if (edgetype == edgedest->second.end())
				{
					edgedest++;

					if (edgedest != edges.end())
					{
						edgetype = edgedest->second.begin();
					}
				}
			}
		}
	}

	if (block->data->b_meta.ava_listnum / g.block_listnum >= g.ava_threshold)
	{
		removeRegionAvaBlock(g, cid, block->data, blockIndex);
	}

	g.cacheManager->releaseCache(block, g.blockIdPool);
}

void GraphUpdater::insertNodeToBlocksNewList(GraphManager& g, int node, int cid, unordered_map<int, vector<int>>&edges, int& alledges, int& startEdge
	, unordered_map<int, vector<int>>::iterator& edgedest, vector<int>::iterator& edgetype, unordered_set<int>&blocklist)
{
	for (const auto& block : blocklist)
	{
		if (startEdge == alledges)
			break;
		insertNodeOneBlockNewList(g, node, cid, edges, alledges, startEdge, edgedest, edgetype, block);
	}
}

// Delete Data

void GraphUpdater::linkPreNext(GraphManager& g, GDBBlock* pre_block, GDBEdge* preEdge, GDBBlock* block, GDBEdge* delEdge, int blockIndex)
{
	if(preEdge != NULL)
		preEdge->next.set(delEdge->next);

	int next_list_index = delEdge->next.list_index;
	int next_edge_index = delEdge->next.edge_index;

	if (delEdge->next.block_pos != -1)
	{
		if (delEdge->next.block_pos == blockIndex)
		{
			block->lists[next_list_index].edge[next_edge_index].pre.set(delEdge->pre);
		}
		else if (pre_block != NULL && delEdge->next.block_pos == delEdge->pre.block_pos)
		{
			pre_block->lists[next_list_index].edge[next_edge_index].pre.set(delEdge->pre);
		}
		else
		{
			int nextpos = block->lists[next_list_index].edge[next_edge_index].next.block_pos;
			CacheNode<GDBBlock>* nextblock = nullptr;
			g.cacheManager->getCache(g.cacheManager->getBlockCache(), nextblock, nextpos);
			
			nextblock->data->lists[next_list_index].edge[next_edge_index].pre.set(delEdge->pre);

			g.cacheManager->releaseCache(nextblock, g.blockIdPool);
		}
	}
}

void GraphUpdater::adjustPre(GraphManager& g, GDBBlock* block, int i, int j, int blockIndex, int tar_i, int tar_j, int tar_blockIndex)
{
	int dest_id = block->lists[i].edge[j].dest_id;

	EdgePos* ep = g.getEdgeDestHead(dest_id);
	if (ep->block_pos == blockIndex
		&& ep->list_index == i
		&& ep->edge_index == j)
	{
		g.setEdgeDestHead(dest_id, tar_blockIndex, tar_i, tar_j);
	}
	else
	{
		if (block->lists[i].edge[j].pre.block_pos != blockIndex)
		{
			//new_db_block pre_block;
			int prepos = block->lists[i].edge[j].pre.block_pos;
			CacheNode<GDBBlock>* preblock = nullptr;
			g.cacheManager->getCache(g.cacheManager->getBlockCache(), preblock, prepos);

			int prelist = block->lists[i].edge[j].pre.list_index;
			int preedge = block->lists[i].edge[j].pre.edge_index;
			preblock->data->lists[prelist].edge[preedge].next.set(tar_blockIndex, tar_i, tar_j);

			g.cacheManager->releaseCache(preblock, g.blockIdPool);
		}
		else
		{
			int pre_list_index = block->lists[i].edge[j].pre.list_index;
			int pre_edge_index = block->lists[i].edge[j].pre.edge_index;
			block->lists[pre_list_index].edge[pre_edge_index].next.set(tar_blockIndex, tar_i, tar_j);
		}
	}
}

void GraphUpdater::insertRegionAvaBlock(GraphManager& g, GDBRegion* region, GDBBlock* block, int blockIndex)
{
	int next = region->avaBlock;
	if (next != -1)
	{
		CacheNode<GDBBlock>* nextblock = nullptr;
		g.cacheManager->getCache(g.cacheManager->getBlockCache(), nextblock, next);
		nextblock->data->b_meta.avaPre = blockIndex;
		g.cacheManager->releaseCache(nextblock, g.blockIdPool);
	}

	region->avaBlock = blockIndex;
	block->b_meta.avaNext = next;
}

void GraphUpdater::removeRegionAvaBlock(GraphManager& g, int cid, GDBBlock* block, int blockIndex)
{
	if (block->b_meta.avaPre != -1 && block->b_meta.avaNext != -1)
	{
		int prepos = block->b_meta.avaPre;
		CacheNode<GDBBlock>* preblock = nullptr;
		CacheNode<GDBBlock>* nextblock = nullptr;
		g.cacheManager->getCache(g.cacheManager->getBlockCache(), preblock, prepos);

		int nextpos = block->b_meta.avaNext;
		g.cacheManager->getCache(g.cacheManager->getBlockCache(), nextblock, nextpos);

		preblock->data->b_meta.avaNext = block->b_meta.avaNext;
		g.cacheManager->releaseCache(preblock, g.blockIdPool);

		nextblock->data->b_meta.avaPre = block->b_meta.avaPre;
		g.cacheManager->releaseCache(nextblock, g.blockIdPool);

		block->b_meta.avaPre = -1;
		block->b_meta.avaNext = -1;
	}
	else if (block->b_meta.avaPre != -1 && block->b_meta.avaNext == -1)
	{
		int prepos = block->b_meta.avaPre;
		CacheNode<GDBBlock>* preblock = nullptr;
		g.cacheManager->getCache(g.cacheManager->getBlockCache(), preblock, prepos);

		preblock->data->b_meta.avaNext = -1;
		g.cacheManager->releaseCache(preblock, g.blockIdPool);

		block->b_meta.avaPre = -1;
		block->b_meta.avaNext = -1;
	}
	else if (block->b_meta.avaNext != -1 && block->b_meta.avaPre == -1)
	{
		int nextpos = block->b_meta.avaNext;
CacheNode<GDBBlock>* nextblock = nullptr;
g.cacheManager->getCache(g.cacheManager->getBlockCache(), nextblock, nextpos);

nextblock->data->b_meta.avaPre = -1;

g.cacheManager->releaseCache(nextblock, g.blockIdPool);

g.gRegion[cid].avaBlock = block->b_meta.avaNext;

block->b_meta.avaPre = -1;
block->b_meta.avaNext = -1;
	}
	else
	{
		if (g.gRegion[cid].avaBlock == blockIndex)
		{
			g.gRegion[cid].avaBlock = -1;
		}
	}
}

void GraphUpdater::removeEdge(GraphManager& g, GDBBlock* block, int list_index, int edge_index, int blockIndex, int edge_num)
{
	int dest_id = block->lists[list_index].edge[edge_index].dest_id;
	EdgePos* ep = g.getEdgeDestHead(dest_id);
	if (ep->block_pos == blockIndex
		&& ep->list_index == list_index
		&& ep->edge_index == edge_index)
	{
		linkPreNext(g, NULL, NULL, block, &block->lists[list_index].edge[edge_index], blockIndex);
		g.setEdgeDestHead(dest_id, &block->lists[list_index].edge[edge_index].next);
	}
	else
	{
		int pre_list_index = block->lists[list_index].edge[edge_index].pre.list_index;
		int pre_edge_index = block->lists[list_index].edge[edge_index].pre.edge_index;

		if (block->lists[list_index].edge[edge_index].pre.block_pos != blockIndex)
		{
			int prepos = block->lists[list_index].edge[edge_index].pre.block_pos;
			CacheNode<GDBBlock>* preblock = nullptr;
			g.cacheManager->getCache(g.cacheManager->getBlockCache(), preblock, prepos);

			linkPreNext(g, preblock->data, &preblock->data->lists[pre_list_index].edge[pre_edge_index], block, &block->lists[list_index].edge[edge_index], blockIndex);

			g.cacheManager->releaseCache(preblock, g.blockIdPool);
		}
		else
		{
			linkPreNext(g, block, &block->lists[pre_list_index].edge[pre_edge_index], block, &block->lists[list_index].edge[edge_index], blockIndex);
		}
	}

	if (edge_index != edge_num - 1)
	{
		adjustPre(g, block, list_index, edge_num - 1, blockIndex, list_index, edge_index, blockIndex);
	}

	block->lists[list_index].edge[edge_index] = block->lists[list_index].edge[edge_num - 1];//list change
	block->lists[list_index].l_meta.edge_num--;
}

void GraphUpdater::deleteEdgeFromBlocksNodes(GraphManager& g, unordered_set<int>& nodes, unordered_map<int, unordered_map<int, vector<int>>>&newNetwork, unordered_set<int>& blocklist)
{
	for (const auto& blockIndex : blocklist)
	{
		if (newNetwork.empty())
			break;

		CacheNode<GDBBlock>* block = nullptr;
		g.cacheManager->getCache(g.cacheManager->getBlockCache(), block, blockIndex);

		bool isOrigin = false;
		float ava = block->data->b_meta.ava_listnum;
		float all = g.block_listnum;
		if (ava / all < g.ava_threshold)
		{
			isOrigin = true;
		}

		unordered_map<int, int> totalList;
		for (int i = 0; i < g.block_listnum; i++)
		{
			int node = block->data->lists[i].l_meta.nodeid;
			if (nodes.find(node) != nodes.end())
			{
				totalList[node]++;
				int num = block->data->lists[i].l_meta.edge_num;
				for (int j = 0; j < num; j++)
				{
					int edge_id = block->data->lists[i].edge[j].dest_id;
					int t = block->data->lists[i].edge[j].type;

					if (newNetwork[node].find(edge_id) != newNetwork[node].end())
					{
						bool status = false;
						int pos = -1;
						if (newNetwork[node][edge_id][0] == -1)
							status = true;
						else {
							pos = lower_bound(newNetwork[node][edge_id].begin(), newNetwork[node][edge_id].end(), t) - newNetwork[node][edge_id].begin();
							if (pos < newNetwork[node][edge_id].size() && newNetwork[node][edge_id][pos] == t) {
								status = true;
							}
						}
						
						if (status) {
							if (t != -1 && status) {
								newNetwork[node][edge_id].erase(newNetwork[node][edge_id].begin() + pos);
								if (newNetwork[node][edge_id].empty()) {
									newNetwork[node].erase(edge_id);
									if (newNetwork[node].empty())
									{
										newNetwork.erase(node);
										nodes.erase(node);
									}
								}
							}

							removeEdge(g, block->data, i, j, blockIndex, num);
							
							j--;
							num--;
						}
					}
				}
				if (num == 0)
				{
					block->data->b_meta.ava_listnum--;
					block->data->lists[i].l_meta.nodeid = -1;
					totalList[node]--;
				}
			}
		}
		for (const auto& n : totalList)
		{
			if (n.second == 0)
			{
				//修改索引
				g.node_map_block[n.first].push_back(blockIndex);
				g.mGraph->nodeblock[n.first].erase(blockIndex);
			}
		}

		ava = block->data->b_meta.ava_listnum;
		all = g.block_listnum;

		if (ava == 0)
		{
			g.removeBlock(block->data, blockIndex, block->data->b_meta.comm_id, isOrigin);
		}
		else
		{
			if (ava / all < g.ava_threshold && isOrigin == false)//加入到链表中
			{
				insertRegionAvaBlock(g, &g.gRegion[block->data->b_meta.comm_id], block->data, blockIndex);
			}
		}

		g.cacheManager->releaseCache(block, g.blockIdPool);
	}
}

void GraphUpdater::deleteData(GraphManager& g, unordered_map<int, unordered_map<int, vector<int>>>& newNetwork)
{
	g.node_map_block.clear();

	unordered_set<int> blocklist;
	unordered_set<int> nodes;

	for (const auto& n : newNetwork)
	{
		nodes.insert(n.first);
		for (const auto& b : g.mGraph->nodeblock[n.first])
		{
			blocklist.insert(g.mGraph->nodeblock[n.first].begin(), g.mGraph->nodeblock[n.first].end());
		}
	}

	deleteEdgeFromBlocksNodes(g, nodes, newNetwork, blocklist);

	//deleteIndex();
}

void GraphUpdater::deleteNodeEdges(GraphManager& g, int node_id)
{
	for (const auto& blockIndex : g.mGraph->nodeblock[node_id])
	{
		CacheNode<GDBBlock>* block = nullptr;
		g.cacheManager->getCache(g.cacheManager->getBlockCache(), block, blockIndex);

		bool isOrigin = false;
		float ava = block->data->b_meta.ava_listnum;
		float all = g.block_listnum;
		if (ava / all < g.ava_threshold)
		{
			isOrigin = true;
		}

		unordered_map<int, int> totalList;
		for (int i = 0; i < g.block_listnum; i++)
		{
			int node = block->data->lists[i].l_meta.nodeid;
			if (node == node_id)
			{
				totalList[node]++;
				int num = block->data->lists[i].l_meta.edge_num;
				for (int j = num - 1; j >= 0; --j)
				{
					removeEdge(g, block->data, i, j, blockIndex, num);
					num--;
				}

				if (num == 0)
				{
					block->data->b_meta.ava_listnum--;
					block->data->lists[i].l_meta.nodeid = -1;
					totalList[node]--;
				}
			}
			else if (node != -1)
			{
				totalList[node]++;
				int num = block->data->lists[i].l_meta.edge_num;
				for (int j = 0; j < num; j++)
				{
					int edge_id = block->data->lists[i].edge[j].dest_id;
					int t = block->data->lists[i].edge[j].type;

					if (edge_id != node_id)
						continue;

					removeEdge(g, block->data, i, j, blockIndex, num);

					j--;
					num--;
				}

				if (num == 0)
				{
					block->data->b_meta.ava_listnum--;
					block->data->lists[i].l_meta.nodeid = -1;
					totalList[node]--;
				}
			}
		}

		for (const auto& n : totalList)
		{
			if (n.first != node_id && n.second == 0)
			{
				//修改索引
				g.node_map_block[n.first].push_back(blockIndex);
				g.mGraph->nodeblock[n.first].erase(blockIndex);
			}
		}

		ava = block->data->b_meta.ava_listnum;
		all = g.block_listnum;

		if (ava == 0)
		{
			g.removeBlock(block->data, blockIndex, block->data->b_meta.comm_id, isOrigin);
		}
		else
		{
			if (ava / all < g.ava_threshold && isOrigin == false)//加入到链表中
			{
				insertRegionAvaBlock(g, &g.gRegion[block->data->b_meta.comm_id], block->data, blockIndex);
			}
		}

		g.cacheManager->releaseCache(block, g.blockIdPool);
	}
}

void GraphUpdater::deleteNodeInEdges(GraphManager& g, int node)
{
	EdgePos* ep = g.getEdgeDestHead(node);
	if (ep->block_pos == -1)
	{
		return;
	}

	//node_map_block.clear();

	while (ep->block_pos != -1)
	{
		int blockIndex = ep->block_pos;

		CacheNode<GDBBlock>* block = nullptr;
		g.cacheManager->getCache(g.cacheManager->getBlockCache(), block, blockIndex);

		int list_index = ep->list_index;
		int edge_index = ep->edge_index;

		g.setEdgeDestHead(node, &block->data->lists[list_index].edge[edge_index].next);

		int num = block->data->lists[list_index].l_meta.edge_num;

		removeEdge(g, block->data, list_index, edge_index, blockIndex, num);
		
		//通过限制边数表示删除边

		if (block->data->lists[list_index].l_meta.edge_num == 0)
		{
			int list_node_id = block->data->lists[list_index].l_meta.nodeid;

			block->data->b_meta.ava_listnum--;
			block->data->lists[list_index].l_meta.nodeid = -1;

			bool isExist = false;
			for (int j = 0; j < g.block_listnum; j++)
			{
				if (block->data->lists[j].l_meta.nodeid == list_node_id)
				{
					isExist = true;
					break;
				}
			}

			if (!isExist)
			{
				g.node_map_block[list_node_id].push_back(blockIndex);
				g.mGraph->nodeblock[list_node_id].erase(blockIndex);
			}

			float ava = block->data->b_meta.ava_listnum;
			float all = g.block_listnum;

			bool isOrigin = (ava / all < g.ava_threshold);
			if (ava == 0)
			{
				g.removeBlock(block->data, blockIndex, block->data->b_meta.comm_id, isOrigin);
			}
			else
			{
				if ((ava + 1) / all >= g.ava_threshold && isOrigin)//加入到链表中
				{
					insertRegionAvaBlock(g, &g.gRegion[block->data->b_meta.comm_id], block->data, blockIndex);
				}
			}
		}

		g.cacheManager->releaseCache(block, g.blockIdPool);

		ep = g.getEdgeDestHead(node);
	}

	// deleteIndex();
}

bool GraphUpdater::deleteNode(GraphManager& g, int node_id)
{
	if (!g.mGraph->existNode(node_id))
		return false;

	deleteNodeEdges(g, node_id);
	deleteNodeInEdges(g, node_id);

	g.mGraph->removeNode(node_id);

	int type = -1; // node_index.get_type(node_s.c_str());

	g.mGraph->nodeblock[node_id].clear();
	//node_index.remove(node_s.c_str());

	//int offset = 0;
	//GetNodeSpdOffset(node_s.c_str(), offset);
	//spd_node_index.Remove_Node_betrelated(offset);

	//spd_index.remove(node_s.c_str());

	if (g.updateBigIndex[node_id] != -1)
	{
		//g.bigKeyIndex->removeNode(g.updateBigIndex[node_id]);
		//updateBigIndex[node_id] = -1;
	}

	g.updateBigIndex[node_id] = -1;

	g.relDB->removeKey(node_id, type);

	return true;
}
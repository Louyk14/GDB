#include "GDBBlock.h"

GDBBlock::GDBBlock(int block_listnum, int list_edgenum, int cid, int anext, int apre, int alistnum)
{
	b_meta.comm_id = cid;
	b_meta.avaNext = anext;
	b_meta.avaPre = apre;
	b_meta.ava_listnum = alistnum;

	lists = new GDBList[block_listnum];
	for (int i = 0; i < block_listnum; i++)
	{
		lists[i].setEdges(list_edgenum);
		lists[i].l_meta.nodeid = -1;
		lists[i].l_meta.edge_num = 0;
	}
}

GDBBlock::GDBBlock(const GDBBlock& block)
{
	b_meta = block.b_meta;
	lists = block.lists;
}

GDBBlock::~GDBBlock()
{
	delete[] lists;
}
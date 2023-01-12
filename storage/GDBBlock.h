#ifndef GDBBLOCK_H
#define GDBBLOCK_H

#include "GDBList.h"

#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class BlockMeta {
public:
	BlockMeta() {};
	BlockMeta(const BlockMeta& bm)
	{
		comm_id = bm.comm_id;
		avaNext = bm.avaNext;
		avaPre = bm.avaPre;
		ava_listnum = bm.ava_listnum;
	}

	int comm_id;
	int avaNext;
	int avaPre;
	int ava_listnum;
};

class GDBBlock {
public:
	BlockMeta b_meta;
	GDBList* lists;

	GDBBlock() { }
	GDBBlock(int block_listnum, int list_edgenum, int cid = -1, int anext = -1, int apre = -1, int alistnum = 0);

// copy the pointer
	GDBBlock(const GDBBlock& block);
	~GDBBlock();

	void init(vector<int>& params)
	{
		int cid = params[0];
		b_meta.avaNext = -1;
		b_meta.avaPre = -1;
		b_meta.ava_listnum = 0;
		b_meta.comm_id = cid;
	}

	// block_listnum in params[0] and list_edgenum in params[1]
	void readFromFile(fstream& db_file, int offset, vector<int>& params) {
		int block_listnum = params[0];
		int list_edgenum = params[1];
		int list_edgesize = sizeof(GDBEdge) * list_edgenum;
		db_file.seekg(offset);
		db_file.read((char*)(&b_meta), sizeof(BlockMeta));

		if (lists == NULL) {
			lists = new GDBList[block_listnum];
			for (int i = 0; i < block_listnum; i++)
			{
				lists[i].setEdges(list_edgenum);
				lists[i].l_meta.nodeid = -1;
				lists[i].l_meta.edge_num = 0;
			}
		}

		for (int i = 0; i < block_listnum; ++i)
		{
			db_file.read((char*)(&lists[i].l_meta), sizeof(ListMeta));
			db_file.read((char*)(lists[i].edge), list_edgesize);
		}
	}

	void writeToFile(fstream& db_file, int offset, vector<int>& params) {
		int block_listnum = params[0];
		int list_edgenum = params[1];
		int list_edgesize = sizeof(GDBEdge) * list_edgenum;
		db_file.seekp(offset);
		db_file.write((char*)(&b_meta), sizeof(BlockMeta));

		for (int i = 0; i < block_listnum; ++i)
		{
			db_file.write((char*)(&lists[i].l_meta), sizeof(ListMeta));
			db_file.write((char*)(lists[i].edge), list_edgesize);
		}
	}
};

#endif
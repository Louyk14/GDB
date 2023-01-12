#pragma once

#ifndef GDBLIST_H
#define GDBLIST_H

#include "GDBEdge.h"

#include <iostream>
using namespace std;

class ListMeta {
public:
	ListMeta() {};
	ListMeta(const ListMeta& l)
	{
		nodeid = l.nodeid;
		edge_num = l.edge_num;
	}
	int nodeid;//存储的节点的id
	int edge_num;//list中存储的数量
};

class GDBList {
public:
	ListMeta l_meta;
	GDBEdge* edge;

	GDBList();
	GDBList(int list_edgenum);

// copy the pointer
	GDBList(const GDBList& list);
	~GDBList();
	void setEdges(int le);
};

#endif
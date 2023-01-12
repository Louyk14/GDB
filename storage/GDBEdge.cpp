#include "GDBEdge.h"

EdgePos::EdgePos()
{
	block_pos = -1;
	list_index = -1;
	edge_index = -1;
}

EdgePos::EdgePos(int b, int l, int e)
{
	block_pos = b;
	list_index = l;
	edge_index = e;
}

EdgePos::EdgePos(const EdgePos& p)
{
	block_pos = p.block_pos;
	list_index = p.list_index;
	edge_index = p.edge_index;
}

void EdgePos::set(int b, int l, int e)
{
	block_pos = b;
	list_index = l;
	edge_index = e;
}

void EdgePos::set(EdgePos& e)
{
	block_pos = e.block_pos;
	list_index = e.list_index;
	edge_index = e.edge_index;
}

void EdgePos::set(EdgePos* e)
{
	block_pos = e->block_pos;
	list_index = e->list_index;
	edge_index = e->edge_index;
}

GDBEdge::GDBEdge()
{
	dest_id = -1;
	type = -1;
	pre.block_pos = -1;
	pre.list_index = -1;
	pre.edge_index = -1;
	next.block_pos = -1;
	next.list_index = -1;
	next.edge_index = -1;
}

GDBEdge::GDBEdge(const GDBEdge& edge)
{
	dest_id = edge.dest_id;
	type = edge.type;
	pre = edge.pre;
	next = edge.next;
}
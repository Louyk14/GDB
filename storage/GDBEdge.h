#pragma once
#ifndef GDBEDGE_H
#define GDBEDGE_H

class EdgePos
{
public:
	int block_pos;
	int list_index;
	int edge_index;

	EdgePos();
	EdgePos(int b, int l, int e);
	EdgePos(const EdgePos& p);

	void set(int b = -1, int l = -1, int e = -1);
	void set(EdgePos& e);
	void set(EdgePos* e);

	bool operator == (const EdgePos& e) const
	{
		return (block_pos == e.block_pos) && (list_index == e.list_index) && (edge_index == e.edge_index);
	}

	
};

class GDBEdge {
public:
	int dest_id;
	int type;
	EdgePos pre;
	EdgePos next;

	GDBEdge();
	GDBEdge(const GDBEdge& edge);

	bool operator < (const GDBEdge& ei) const
	{
		return (dest_id < ei.dest_id) || (dest_id == ei.dest_id && type < ei.type);
	}
};

#endif
#include "GDBList.h"

GDBList::GDBList()
{
	edge = NULL;
}

GDBList::GDBList(int le)
{
	edge = new GDBEdge[le];
}

GDBList::GDBList(const GDBList& list)
{
	l_meta = list.l_meta;
	edge = list.edge;
}

GDBList::~GDBList()
{
	delete[] edge;
}

void GDBList::setEdges(int le)
{
	if (edge)
		delete[] edge;
	edge = new GDBEdge[le];
}
#pragma once
#ifndef GRAPHQUERY_H
#define GRAPHQUERY_H

#include "GraphManager.h"

#include <string>
#include <iostream>
using namespace std;

class GraphQuery {
public:
	GraphQuery();
	~GraphQuery();

// filter
	void getNodeById(GraphManager& g, int nid);
	void getNodeByAttributes(GraphManager& g, unordered_map<string, string>& attributes);

	void getEdgeById(GraphManager& g, string& eid);
	void getEdgeByAttributes(GraphManager& g, unordered_map<string, string>& attributes);

// Normal Queries
	void getKHopNeighbours(GraphManager& g, int nid);
	void getKNeighbours(GraphManager& g, int nid);
	int getDistance(GraphManager& g, int nid1, int nid2);
	void getPath(GraphManager& g, int nid1, int nid2);
	void isConnected(GraphManager& g, int nid1, int nid2);

// Special Queries
	int getBetweenness(GraphManager& g, int nid);
	void subgraphMatch(GraphManager& g, GDBDataGraph& sg);
};

#endif
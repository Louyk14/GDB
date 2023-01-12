#ifndef COMMGRAPHUTIL_H
#define COMMGRAPHUTIL_H

#include <algorithm>
#include "TemporalGraph.h"

using namespace std;

class CommGraphUtil {
public:
	void initCommunity(TemporalGraph& g);
	void buildCommGraph(TemporalGraph& g, TemporalGraph& c_graph);
	void convertCommGraph(TemporalGraph& g, TemporalGraph& c_graph);
};

#endif
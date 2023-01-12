#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <time.h>
#include <vector>
using namespace std;

class GraphGenerator {
public:
	GraphGenerator();
	void randomSplit();

	int comm_num;
	int node_num;
};

#endif
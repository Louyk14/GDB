#pragma once
#ifndef PROBABILITY_STRATEGY_HPP
#define PROBABILITY_STRATEGY_HPP

//#include "MatchGraph.h"
#include "../MemoryGraph.h"

class NodeProbabilityStrategy {
protected:
	double* degree; //Array of degree probability
	double* out_deg; //Array of "out" degree probability
	double* in_deg; //Array of "in" degree probability
	int degree_size;
	int out_deg_size;
	int in_deg_size;

	map<int, double> labels; //Map of labels probability

	virtual void evaluateProbabilities(MemoryGraph* g2);
	//virtual void evaluateProbabilities(TempMatchGraph* g2);

public:
	NodeProbabilityStrategy(MemoryGraph* g2) {
		evaluateProbabilities(g2);
	}
	//NodeProbabilityStrategy(TempMatchGraph* g2) {
	//	evaluateProbabilities(g2);
	//}

	~NodeProbabilityStrategy() {
		delete[] out_deg;
		delete[] in_deg;
		delete[] degree;
	}

	virtual double getProbability(MemoryGraph *g1, int id) = 0;
};

class SubIsoNodeProbability : public NodeProbabilityStrategy {
public:
	SubIsoNodeProbability(MemoryGraph* source) :NodeProbabilityStrategy(source) {}
	//SubIsoNodeProbability(TempMatchGraph* source) :NodeProbabilityStrategy(source) {}
	double getProbability(MemoryGraph* g, int id);
	virtual ~SubIsoNodeProbability() {}
};

#endif

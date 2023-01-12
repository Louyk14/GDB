#pragma once
#ifndef GRAPHAPPLICATION_H
#define GRAPHAPPLICATION_H

#include "GraphManager.h"
#include "GraphQuery.h"
//#include "GraphAnalyzer.h"

class GraphApplication {
public:
	GraphQuery* gQuery;
	//GraphAnalyzer* gAnalyzer;

	GraphApplication();
	~GraphApplication();
};

#endif
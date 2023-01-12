#include "GraphApplication.h"

GraphApplication::GraphApplication()
{
	gQuery = new GraphQuery();
	//gAnalyzer = new GraphAnalyzer();
}

GraphApplication::~GraphApplication()
{
	if (gQuery)
		delete gQuery;
	//if (gAnalyzer)
	//	delete gAnalyzer;
}
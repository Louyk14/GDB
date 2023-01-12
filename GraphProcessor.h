#pragma once
#ifndef GRAPHPROCESSOR_H
#define GRAPHPROCESSOR_H

#include "parser/definations.h"
#include "GraphDatabase.h"

class GraphDatabase;

class GraphProcessor {
public:
	GraphProcessor(GraphDatabase* db);

	GraphDatabase* gdb;

	void exec(Statement& stat);
	void exec_ddl(DDLStatement& stat);
	void exec_dml(DMLStatement& stat);
	void exec_drop_stat(DropStatement& stat);
	void exec_insert_stat(InsertStatement& stat);
	void exec_insert_into_graph_stat(InsertGraphStat& stat);
	void exec_remove_stat(RemoveStatement& stat);
	void exec_create_schema(CreateSchemaStatement& stat);

	void createGraph(string gname);
	void createGraphSet(Statement& stat);
};

#endif
#pragma once
#ifndef GRAPHPROCESSOR_H
#define GRAPHPROCESSOR_H

#include "parser/definations.h"
#include "GraphDatabase.h"
#include "ParserGraphs.h"

class GraphDatabase;
class WhereConditionGraph;
class FromConditionGraph;

class GraphProcessor {
public:
	GraphProcessor(GraphDatabase* db);

	GraphDatabase* gdb;
	WhereConditionGraph* wcg;
	FromConditionGraph* fcg;

	void exec(Statement& stat);
	void exec_ddl(DDLStatement& stat);
	void exec_dml(DMLStatement& stat);
	void exec_drop_stat(DropStatement& stat);
	void exec_insert_stat(InsertStatement& stat);
	void exec_insert_into_graph_stat(InsertGraphStat& stat);
	void exec_remove_stat(RemoveStatement& stat);
	void exec_remove_from_graph_stat(RemoveGraphStat& stat);
	void exec_create_schema(CreateSchemaStatement& stat);

	void createGraph(string gname);
	void createGraphSet(Statement& stat);

	void exec_query_stat(QueryStatement& stat);
	void exec_select_stat(SelectStatement& stat);

	void deal_with_first_order_stat(FirstOrderStat& stat);
	void deal_with_first_order_unit(FirstOrderUnit& stat);
};

#endif
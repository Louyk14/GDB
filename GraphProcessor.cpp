#include "GraphProcessor.h"

GraphProcessor::GraphProcessor(GraphDatabase* db) {
	gdb = db;
}

void GraphProcessor::exec(Statement& stat) {
	if (stat.type == DML_STATEMENT_TYPE) {
		exec_dml(*stat.dmlStatement);
	}
	else if (stat.type == DDL_STATEMENT_TYPE) {
		exec_ddl(*stat.ddlStatement);
	}
}

void GraphProcessor::exec_ddl(DDLStatement& stat) {
	if (stat.type == CREATE_GRAPH_TYPE) {
		string gid = stat.createGraph->gid;
		vector<string> filelist = stat.createGraph->filelist;
		for (int i = 0; i < filelist.size(); ++i) {
			filelist[i] = filelist[i].substr(1, (int)filelist[i].size() - 2);
		}

		bool hasfor = stat.createGraph->hasfor;
		string gsid = stat.createGraph->gsid;

		if (stat.createGraph->sitem->type == SCHEMA_ID_TYPE) {
			string schemaid = *stat.createGraph->sitem->schemaid;
			gdb->createGraph(gid, filelist, schemaid);
		}

		if (hasfor) {
			gdb->linkGraphToGraphSet(gid, gsid);
		}
	}
	else if (stat.type == CREATE_GSET_TYPE) {
		string gsid = stat.createGSet->gsid;
		vector<string> aliasgraph = stat.createGSet->gidlist;

		gdb->createGraphSet(gsid, aliasgraph);
	}
	else if (stat.type == CREATE_SCHEMA_TYPE) {
		exec_create_schema(*stat.createSchema);
	}
	else if (stat.type == LOAD_GSET_TYPE) {
		string gsid = stat.loadGSet->gsid;

		gdb->loadGraphSet(gsid);
	}
	else if (stat.type == LOAD_GRAPH_TYPE) {
		string gid = stat.loadGraph->gid;

		gdb->loadGraph(gid);
	}
	else if (stat.type == DROP_TYPE) {
		exec_drop_stat(*stat.dropStat);
	}
}

void GraphProcessor::exec_drop_stat(DropStatement& stat) {
	if (stat.type == DROP_GRAPH_TYPE) {
		gdb->dropGraph(stat.itemid);
	}
	else if (stat.type == DROP_GSET_TYPE) {
		gdb->dropGraphSet(stat.itemid);
	}
	else if (stat.type == DROP_SCHEMA_TYPE) {
		gdb->dropSchema(stat.itemid);
	}
}

void GraphProcessor::exec_insert_stat(InsertStatement& stat) {
	if (stat.type == INSERT_INTO_GSET_TYPE) {
		gdb->insertIntoGraphSet(stat.insertGSetStat->gsid, stat.insertGSetStat->gidlist);
	}
	else if (stat.type == INSERT_INTO_GRAPH_TYPE) {
		exec_insert_into_graph_stat(*stat.insertGraphStat);
	}
}

void GraphProcessor::exec_insert_into_graph_stat(InsertGraphStat& stat) {
	if (stat.type == INSERT_INTO_GRAPH_TUPLE_TYPE) {
		gdb->insertIntoGraph(*stat.gstat, stat.gid);
	}
	else if (stat.type == INSERT_INTO_GRAPH_TYPE) {

	}
	else if (stat.type == INSERT_INTO_GRAPH_TYPE) {

	}
}

void GraphProcessor::exec_remove_stat(RemoveStatement& stat) {
	if (stat.type == REMOVE_FROM_GSET_TYPE) {
		gdb->removeFromGraphSet(stat.removeGSetStat->gsid, stat.removeGSetStat->gidlist);
	}
	//else (stat.type == REMOVE_FROM_GRAPH_TYPE) {
	//	gdb->remove
	//}
}

void GraphProcessor::exec_create_schema(CreateSchemaStatement& stat) {
	if (stat.type == CREATE_SCHEMA_DESCRIBE_TYPE) {
		gdb->createSchema(stat.schemaname, stat.schemaStatement->nodeattrlist, stat.schemaStatement->edgeattrlist, stat.schemaStatement->edgelink);
	}
	else if (stat.type == CREATE_SCHEMA_FILE_TYPE) {
		gdb->createSchema((*stat.filepath).substr(1, (int)stat.filepath->size() - 2));
	}
}

void GraphProcessor::exec_dml(DMLStatement& stat) {
	if (stat.type == INSERT_TYPE) {
		exec_insert_stat(*stat.insertStatement);
	}
	else if (stat.type == REMOVE_TYPE) {
		exec_remove_stat(*stat.removeStatement);
	}
}

void GraphProcessor::createGraph(string gname) {
	gdb->loadGraph(gname);
}

void GraphProcessor::createGraphSet(Statement& stat) {

}
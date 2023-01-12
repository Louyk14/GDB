#include "RDBHandler.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++)
	{
		//attributes[nodeid][azColName[i]] = argv[i] ? argv[i] : "NULL";
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int RDBHandler::execute(sqlite3* &db, string& sql)
{
	char* zErrMsg = 0;
	int rc = sqlite3_exec(db, sql.c_str(), callback, 0, &zErrMsg);

	if (rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		//fprintf(stdout, "Table operation succeed\n");
	}

	return rc;
}

string RDBHandler::generateInsertSQL(string table, vector<string>& attributes, vector<string>& defaultVal)
{
	string insertsql = "INSERT INTO " + table + " values (";

	for (int i = 0; i < attributes.size(); i++)
	{
		insertsql += attributes[i];

		if (i != defaultVal.size() - 1)
		{
			insertsql += ", ";
		}
	}

	if (attributes.size() < defaultVal.size())
	{
		for (int i = attributes.size(); i < defaultVal.size(); i++)
		{
			insertsql += defaultVal[i];

			if (i != defaultVal.size() - 1)
			{
				insertsql += ", ";
			}
		}
	}

	insertsql += ");";

	return insertsql;
}

string RDBHandler::generateDeleteSQL(string table, int node_id)
{
	string deletesql = "DELETE FROM " + table + " where id = " + to_string(node_id);
	return deletesql;
}
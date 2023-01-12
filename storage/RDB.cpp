#include "RDB.h"

RDB::RDB(string base_dir, string& dbn)
{
	db = 0;
	dbname = base_dir + dbn + "//" + dbn + ".db";

	nodetype2tablename.push_back("UNDEFINED");
	tablename2nodetype["UNDEFINED"] = 0;
	edgetype2tablename.push_back("UNDEFINED");
	tablename2edgetype["UNDEFINED"] = 0;
}

RDB::~RDB() {
	
}

void RDB::connect_sqlite()
{
	int rc = sqlite3_open(dbname.c_str(), &db);
	if (rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		//exit(0);
	}
	else
	{
		fprintf(stderr, "Opened database successfully\n");
	}
}

void RDB::disconnect_sqlite()
{
	sqlite3_close(db);
}

string RDB::upper_str(string& str)
{
	string upperstr = str;
	transform(str.begin(), str.end(), upperstr.begin(), ::toupper);

	return upperstr;
}

void RDB::parseCreate(string& tablename, string& stmt, unordered_map<string, int>& attrType)
{
	int index = 0;
	for (index = 0; index < stmt.size(); index++)
	{
		if (stmt[index] == '(')
		{
			break;
		}
	}

	index++;

	for (; index < stmt.size();)
	{
		string attr = "";
		string type = "";

		while (index < stmt.size() && stmt[index] == ' ')
		{
			index++;
		}

		for (; index < stmt.size() && stmt[index] != ' '; index++)
		{
			attr += stmt[index];
		}

		while (index < stmt.size() && stmt[index] == ' ')
		{
			index++;
		}

		for (; index < stmt.size() && stmt[index] != ',' && stmt[index] != ' ' && stmt[index] != ')'; index++)
		{
			type += stmt[index];
		}

		while (index < stmt.size() && (stmt[index] == ' ' || stmt[index] == ',' || stmt[index] == ')'))
		{
			index++;
		}

		string key = tablename + "." + upper_str(attr);
		type = upper_str(type);

		RETURNTYPE returnType;

		if (type == "VARCHAR")
		{
			attrType[key] = returnType.STRING_TYPE;
		}
		else if (type == "INT")
		{
			attrType[key] = returnType.INT_TYPE;
		}
		else if (type == "FLOAT" || type == "REAL")
		{
			attrType[key] = returnType.DOUBLE_TYPE;
		}
		else if (type == "BIT")
		{
			attrType[key] = returnType.BOOL_TYPE;
		}
	}
}

void RDB::initNodeTable(string filename, unordered_map<int, int>& nodetypes)
{
	fstream infile;
	infile.open(filename, ios::in);
	if (infile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}

	int typenum = 0;
	string buff;
	getline(infile, buff);
	typenum = atoi(buff.c_str());

	unordered_map<int, int> typeattrnum;
	bool flag = true;

	char* zErrMsg = 0;
	int iRet = SQLITE_OK;
	iRet = sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);
	if (iRet != SQLITE_OK)
	{
		if (zErrMsg != NULL)
		{
			sqlite3_free(zErrMsg);
		}

		return;
	}

	for (int i = 0; i < typenum; i++)
	{
		int type, attrnum;
		string tablename;

		buff.clear();

		infile >> type >> tablename >> attrnum;

		nodetype2tablename[type] = tablename;
		tablename2nodetype[tablename] = type;
		typeattrnum[type] = attrnum - 1;//remove id as an attribute

		string s = "";
		infile.get();
		getline(infile, s);
		//continue;

		int rc = handler.execute(db, s);
		//int rc = sqlite3_exec(db, buff.c_str(), callback, 0, &zErrMsg);

		if (rc != SQLITE_OK)
		{
			cout << "Dropping table ... " << endl;
			string dropsql = "DROP TABLE " + tablename + ";";

			char* zErrMsg = 0;
			int rc = handler.execute(db, dropsql);
			if (rc != SQLITE_OK)
			{
				flag = false;
				break;
			}
			rc = handler.execute(db, s);
			if (rc != SQLITE_OK)
			{
				flag = false;
				break;
			}
			else
			{
				fprintf(stdout, "Table created successfully\n");
			}
		}
		else
		{
			fprintf(stdout, "Table created successfully\n");
		}

		parseCreate(tablename, s, attrType);

		string buff = "";

		while (true)
		{
			buff = "";
			getline(infile, buff);
			if (buff[0] == '#')
			{
				buff = "";
				getline(infile, buff);
				break;
			}

			// Create Index

			int rc = handler.execute(db, buff);

			if (rc != SQLITE_OK)
			{
				cout << "Create Index Failed! " << endl;
			}
			else
			{
				fprintf(stdout, "Index created successfully\n");
			}
		}

		string temp = "";
		for (int i = 0; i < buff.size(); i++)
		{
			if (buff[i] == ' ')
			{
				defaultval[tablename].push_back(temp);
				temp.clear();
			}
			else
			{
				temp += buff[i];
			}
		}

		if (!buff.empty())
		{
			defaultval[tablename].push_back(temp);
		}
		buff.clear();
	}

	if (!flag)
	{
		sqlite3_exec(db, "rollback", NULL, 0, 0);
		cout << "fail" << endl;
		infile.close();
		return;
	}
	//return;
	int node_id, type;
	string s = "";
	string current = "";
	int curIndex = 0;
	while (getline(infile, s))
	{
		for (curIndex = 0; curIndex < s.size(); curIndex++)
		{
			if (s[curIndex] == ' ')
				break;
			else
				current += s[curIndex];
		}
		node_id = atoi(current.c_str());
		curIndex++;
		current.clear();
		for (; curIndex < s.size(); curIndex++)
		{
			if (s[curIndex] == ' ')
				break;
			else
				current += s[curIndex];
		}
		type = atoi(current.c_str());
		curIndex++;
		current.clear();

		nodetypes[node_id] = type;
		int attrnum = typeattrnum[type];

		string sql = "INSERT INTO " + nodetype2tablename[type] + " values (" + to_string(node_id);
		if (attrnum != 0)
		{
			sql += ", ";
		}

		bool closed = true;
		for (int i = curIndex; i < s.size(); i++)
		{
			if (s[i] == '\'')
			{
				if (s[i - 1] == ',' || s[i - 1] == ' ' || i == s.size() - 1 || s[i + 1] == ' ')
				{
					closed = !closed;
				}
				else
				{
					s[i] = '_';
				}
			}
			else if (s[i] == ' ')
			{
				if (closed)
					s[i] = ',';
			}
		}
		sql += s.substr(curIndex);
		//cout << sql << endl;
		//for (int i = 0; i < attrnum; i++)
		//{				
		//infile >> s;
		//sql += s;

		//	if (i != attrnum - 1)
		//	{
		//		sql += ", ";
		//	}
		//}

		sql += ");";
		//cout << sql << endl;
		//system("pause");
		char* zErrMsg = 0;

		int rc = handler.execute(db, sql);

		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			flag = false;
			break;
		}
		else
		{
			//fprintf(stdout, "Insert successfully\n");
		}
	}

	if (!flag)
	{
		sqlite3_exec(db, "rollback", NULL, 0, 0);
		cout << "fail" << endl;
	}
	else
	{
		iRet = sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
		if (iRet != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: Commit fails\n");
		}

		if (zErrMsg != NULL)
		{
			sqlite3_free(zErrMsg);
		}
	}

	infile.close();
}

void RDB::initEdgeTable(string filename)
{
	fstream infile;
	infile.open(filename, ios::in);
	if (infile.fail())
	{
		cerr << "读取文件错误" << endl;
		return;
	}

	int typenum = 0;
	string buff;
	getline(infile, buff);
	typenum = atoi(buff.c_str());

	unordered_map<int, int> typeattrnum;
	bool flag = true;

	char* zErrMsg = 0;
	int iRet = SQLITE_OK;
	iRet = sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);
	if (iRet != SQLITE_OK)
	{
		if (zErrMsg != NULL)
		{
			sqlite3_free(zErrMsg);
		}

		return;
	}

	for (int i = 0; i < typenum; i++)
	{
		int type, attrnum;
		string tablename;

		buff.clear();

		infile >> type >> tablename >> attrnum;
		edgetype2tablename[type] = tablename;
		tablename2edgetype[tablename] = type;
		typeattrnum[type] = attrnum;

		string s = "";
		infile.get();
		getline(infile, s);
		//continue;

		char* zErrMsg = 0;

		int rc = handler.execute(db, s);
		//int rc = sqlite3_exec(db, buff.c_str(), callback, 0, &zErrMsg);

		if (rc != SQLITE_OK)
		{
			cout << "Dropping table ... " << endl;
			string dropsql = "DROP TABLE " + tablename + ";";

			char* zErrMsg = 0;
			int rc = handler.execute(db, dropsql);
			if (rc != SQLITE_OK)
			{
				flag = false;
				break;
			}
			rc = handler.execute(db, s);
			if (rc != SQLITE_OK)
			{
				flag = false;
				break;
			}
		}
		else
		{
			fprintf(stdout, "Table created successfully\n");
		}

		parseCreate(tablename, s, attrType);

		string buff = "";

		getline(infile, buff);
		string temp = "";
		for (int i = 0; i < buff.size(); i++)
		{
			if (buff[i] == ' ')
			{
				defaultval[tablename].push_back(temp);
				temp.clear();
			}
			else
			{
				temp += buff[i];
			}
		}

		if (!buff.empty())
		{
			defaultval[tablename].push_back(temp);
		}
		buff.clear();
	}
	//return;
	int startnode, endnode, type;
	while (infile >> startnode)
	{
		infile >> endnode >> type;
		int attrnum = typeattrnum[type];

		string sql = "INSERT INTO " + edgetype2tablename[type] + " values (";

		for (int i = 0; i < attrnum; i++)
		{
			string s = "";
			infile >> s;
			sql += s;

			if (i != attrnum - 1)
			{
				sql += ", ";
			}
		}

		sql += ");";

		char* zErrMsg = 0;

		int rc = handler.execute(db, sql);

		if (rc != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
			flag = false;
			break;
		}
		else
		{
			//fprintf(stdout, "Insert successfully\n");
		}
	}

	if (!flag)
	{
		sqlite3_exec(db, "rollback", NULL, 0, 0);
		cout << "fail" << endl;
	}
	else
	{
		iRet = sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
		if (iRet != SQLITE_OK)
		{
			fprintf(stderr, "SQL error: Commit fails\n");
		}

		if (zErrMsg != NULL)
		{
			sqlite3_free(zErrMsg);
		}
	}

	infile.close();
}

void RDB::insertNewKey(int type, vector<string>& attributes)
{
	string tablename = nodetype2tablename[type];
	string insertsql = handler.generateInsertSQL(tablename, attributes, defaultval[tablename]);
	handler.execute(db, insertsql);
}

void RDB::removeKey(int node_id, int type)
{	
	string tablename = nodetype2tablename[type];
	string deletesql = handler.generateDeleteSQL(tablename, node_id);
	handler.execute(db, deletesql);
}
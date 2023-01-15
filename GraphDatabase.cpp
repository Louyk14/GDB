#include "GraphDatabase.h"

GraphDatabase::GraphDatabase() {
	gsetdir = "gsets";
	gdir = "graphs";
	schemadir = "schemas";

	gParser = new GraphParser();
	gProcessor = new GraphProcessor(this);
	gschemaManager = new GraphSchemaManager(schemadir);
	gLoader = new GraphLoader();

	if (_access(gsetdir.c_str(), 0) != 0) {
		system(("mkdir " + gsetdir).c_str());
	}

	if (_access(gdir.c_str(), 0) != 0) {
		system(("mkdir " + gdir).c_str());
	}

	if (_access(schemadir.c_str(), 0) != 0) {
		system(("mkdir " + schemadir).c_str());
	}
}

GraphDatabase::~GraphDatabase() {
	if (gParser)
		delete gParser;
	if (gProcessor)
		delete gProcessor;
	if (gLoader)
		delete gLoader;
	for (auto& gset : gsetManager)
		delete gset.second;

	if (gschemaManager)
		delete gschemaManager;

	for (auto& g : graphs)
		delete g.second;
}

void GraphDatabase::run() {
	//auto start = std::chrono::high_resolution_clock::now();
	//GraphSet ans = parse(query);
	//auto end = std::chrono::high_resolution_clock::now();
	//end = clock();
	//std::fstream fout("message.log", std::ios::app);
	//fout << (double)(end - start) / CLOCKS_PER_SEC << endl;
	//double secs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
	//printf("%.4lf\n", secs / 1000000000);
	//cout << "TOTAL:"<<end<<"|"<<start<<"|"<< secs/(double)1000000000 <<"|"<<CLOCKS_PER_SEC<< endl;

	//return 0;

	while (true) {
		try {
			//        parse("query * as Graph1 from {v1, e1<v2->v3>, e2<{v3->v4}>, {v4->v2, v1->v4}}");
			//        parse("query * as Graph2 from {v1, e1<v2->v3>, {v1->v4}}");
			//        Graph ans = parse("Query * from Graph1 minus Graph2");
			string query;
			//cout << RED << "Please input your query: " BLACK;
			getline(cin, query);
			// CREATE GRAPH g100 schema1 from file 'dataset//storage//100//network.dat', 'dataset//storage//100//community.dat';
			// CREATE GRAPHSET gs1(g100) schema1;
			// CREATE GRAPH g100dup schema1 from file 'dataset//storage//100//network.dat', 'dataset//storage//100//community.dat' for gs1;
			// LOAD GRAPHSET gs1;
			// LOAD GRAPH g100dup;
			// query = "create schema schema1 {STUDENT (NAME STRING, DEPT_ID INTEGER),CLASS (NAME STRING),TAKE [STUDENT-CLASS] (TIME STRING)};";
			// query = "CREATE GRAPHSET gs1 (g100, g100fake) schema1;";
			// query = "CREATE GRAPH g1 schema1 FOR gs1";
			if (query == "quit") {
				break;
			}
			Statement ans = gParser->parse(query);
			gProcessor->exec(ans);
			//cout << ans.toString() << endl;
		}
		catch (const GraphException &msg) {
			cerr << msg.what() << endl;
		}
		catch (...) {
			cerr << "Parse error, please try again" << endl;
		}
	}
	
	//gParser->run();
}

void GraphDatabase::close() {
	// for (auto& gm : gsetManager) {
	//	delete gm.second;
	// }

	// for (auto& g : graphs) {
	// 	delete g.second;
	// }
}

void GraphDatabase::createGraph(string gname, vector<string>& filelist, string& schemaid) {
	string dbname = gname;
	int block_listnum = 15;
	int list_edgenum = 15;
	double ava_threshold = 0.5;
	int cachesize = 100;

	// BPlusTree Index for NodeBlockPos
	string leaf_file = dbname;
	string internal_file = dbname;
	int leaf_cache_size = 3;
	int internal_cache_size = 3;
	bool tree_empty = true;
	bool overwrite = true;
	bool firsttime = true;

	string big_key_file = dbname;
	int big_key_cache_size = 10;

	GraphManager* graph = new GraphManager(dbname, block_listnum, list_edgenum, ava_threshold, cachesize,
		leaf_file, internal_file, leaf_cache_size, internal_cache_size,
		big_key_file, big_key_cache_size, tree_empty, overwrite, firsttime);
	
	graph->setGraphSchema(gschemaManager, schemaid);

	if (filelist.size() == 2) {
		graph->store(filelist[0], filelist[1]);
	}
	else {
		graph->store(filelist[0], filelist[1], filelist[2], filelist[3]);
	}

	graph->setStorageMeta();
	graph->setGraphTime();

	graphs[gname] = graph;
}

void GraphDatabase::loadGraph(string gname) {
	string dbname = gname;
	int block_listnum = 15;
	int list_edgenum = 15;
	double ava_threshold = 0.5;
	int cachesize = 100;

	// BPlusTree Index for NodeBlockPos
	string leaf_file = dbname;
	string internal_file = dbname;
	int leaf_cache_size = 3;
	int internal_cache_size = 3;
	bool tree_empty = false;
	bool overwrite = false;
	bool firsttime = false;

	string big_key_file = dbname;
	int big_key_cache_size = 10;

	GraphManager* graph = new GraphManager(dbname, block_listnum, list_edgenum, ava_threshold, cachesize,
		leaf_file, internal_file, leaf_cache_size, internal_cache_size,
		big_key_file, big_key_cache_size, tree_empty, overwrite, firsttime);

	// graph->setGraphSchema(gschemaManager, graph->schemaid);
	
	graphs[gname] = graph;
}

bool GraphDatabase::dispatchGraph(string gname, string& gtime, GraphSetManager* gm, int auth) {
	if (gsetManager.find(gm->name) == gsetManager.end()) {
		cout << "Current graph set does not log in" << endl;
		return false;
	}
	if (!hasGraph(gname)) {
		cout << "Graph not exist" << endl;
		return false;
	}
	if (graphs.find(gname) == graphs.end()) {
		loadGraph(gname);
	}
	if (gtime != "" && graphs[gname]->graph_create_time > gtime) {
		cout << "Graph already removed" << endl;
		return false;
	}
	if (auth == 0) {
		if (readAuthority[gname].find(gm) != readAuthority[gname].end()) {
			cout << "Already has the read authority" << endl;
			return false;
		}
		readAuthority[gname].insert(gm);
		if (gtime == "")
			gtime = graphs[gname]->graph_create_time;
		return true;
	}
	else if (auth == 1) {
		if (writeAuthority[gname].find(gm) != writeAuthority[gname].end()) {
			cout << "Already has the write authority" << endl;
			return false;
		}
		writeAuthority[gname].insert(gm);
		if (gtime == "")
			gtime = graphs[gname]->graph_create_time;
		return true;
	}
	else {
		cout << "Unknown authority" << endl;
	}

	return false;
}

bool GraphDatabase::retrieveGraph(string gname, GraphSetManager* gm, int auth) {
	if (!hasGraph(gname)) {
		cout << "Graph not exist" << endl;
		return false;
	}
	if (auth == 0) {
		if (readAuthority[gname].find(gm) == readAuthority[gname].end()) {
			cout << "Do not has the read authority" << endl;
			return false;
		}
		readAuthority[gname].erase(gm);
		return true;
	}
	else if (auth == 1) {
		if (writeAuthority[gname].find(gm) == writeAuthority[gname].end()) {
			cout << "Do not has the write authority" << endl;
			return false;
		}
		writeAuthority[gname].erase(gm);
		return true;
	}
	else if (auth == -1) {
		if (readAuthority[gname].find(gm) != readAuthority[gname].end()) {
			readAuthority[gname].erase(gm);
		}
		if (writeAuthority[gname].find(gm) != writeAuthority[gname].end()) {
			writeAuthority[gname].erase(gm);
		}
		return true;
	}
	else {
		cout << "Unknown authority" << endl;
	}

	return false;
}

void GraphDatabase::callbackGraph(string gname) {
	for (const auto& gm : readAuthority[gname]) {
		gm->returnGraph(gname, 0);
	}

	for (const auto& gm : writeAuthority[gname]) {
		gm->returnGraph(gname, 1);
	}
}

void GraphDatabase::createGraphSet(string gsname, vector<string>& aliasgraph) {
	GraphSetManager* gsM = new GraphSetManager(gsname, this, aliasgraph);
}

bool GraphDatabase::loadGraphSet(string gsname) {
	GraphSetManager* gsM = new GraphSetManager(gsname, this);
	if (gsM->gIO == NULL) {
		delete gsM;
		return false;
	}

	return true;
}

void GraphDatabase::addGraphSet(GraphSetManager* gm) {
	if (gsetManager.find(gm->name) != gsetManager.end()) {
		cout << "Graph set " + gm->name + "already exists !" << endl;
	}
	else {
		gsetManager[gm->name] = gm;
	}
}

void GraphDatabase::removeGraphSet(GraphSetManager* gm, unordered_map<string, int>& graphAuth) {
	if (gsetManager.find(gm->name) != gsetManager.end()) {
		gsetManager.erase(gm->name);
		for (const auto& g : graphAuth) {
			if (g.second == 0) {
				readAuthority[g.first].erase(gm);
			}
			else if (g.second == 1) {
				writeAuthority[g.first].erase(gm);
			}
		}
	}
}

void GraphDatabase::linkGraphToGraphSet(string gname, string gsname) {
	GraphSetManager* gsm = NULL;

	if (!hasGraph(gname) || !getGraphSet(gsname, gsm)) {
		return;
	}
	
	gsm->registerGraphFirstTime(gname);
}

void GraphDatabase::dropGraphSet(string gsname) {
	GraphSetManager* gsm = NULL;
	if (!hasGraphSet(gsname)) {
		cout << "Graph set not exist !" << endl;
		return;
	}
	
	if (gsetManager.find(gsname) != gsetManager.end()) {
		delete gsetManager[gsname];
		gsetManager.erase(gsname);
	}

	system(("RMDIR /s/q " + gsetdir + "\\" + gsname).c_str());
}

void GraphDatabase::dropGraph(string gname) {
	GraphManager* gm = NULL;
	if (!hasGraph(gname)) {
		cout << "Graph not exist !" << endl;
		return;
	}
	
	if (graphs.find(gname) != graphs.end()) {
		delete graphs[gname];
		graphs.erase(gname);
	}

	system(("RMDIR /s/q " + gdir + "\\" + gname).c_str());

	callbackGraph(gname);
}

void GraphDatabase::dropSchema(string schemaname) {
	gschemaManager->dropSchema(schemaname);
}

bool GraphDatabase::getGraph(string gname, GraphManager*& gm) {
	if (!hasGraph(gname)) {
		gm = NULL;
		return false;
	}
	else {
		if (graphs.find(gname) != graphs.end()) {
			gm = graphs[gname];
		}
		else {
			loadGraph(gname);
			gm = graphs[gname];
		}
		return true;
	}
}

bool GraphDatabase::getGraphSet(string gsname, GraphSetManager*& gsm) {
	if (!hasGraphSet(gsname)) {
		gsm = NULL;
		return false;
	}
	else {
		if (gsetManager.find(gsname) != gsetManager.end()) {
			gsm = gsetManager[gsname];
		}
		else {
			loadGraphSet(gsname);
			gsm = gsetManager[gsname];
		}
		return true;
	}
}

bool GraphDatabase::hasGraph(string gname) {
	if (graphs.find(gname) != graphs.end()) {
		return true;
	}
	if (_access((gdir + "\\" + gname).c_str(), 0) != 0) {
		return false;
	}
	else {
		return true;
	}
}

bool GraphDatabase::hasGraphSet(string gsname) {
	if (gsetManager.find(gsname) != gsetManager.end()) {
		return true;
	}
	if (_access((gsetdir + "\\" + gsname).c_str(), 0) != 0) {
		return false;
	}
	else {
		return true;
	}
}

void GraphDatabase::createSchema(string schemaname, SchemaAttrMap& nodeAttrMap, SchemaAttrMap& edgeAttrMap, SchemaNetwork& schemaNetwork) {
	gschemaManager->createSchema(schemaname, nodeAttrMap, edgeAttrMap, schemaNetwork);
}

void GraphDatabase::createSchema(string filename) {
	gschemaManager->createSchema(filename);
}

void GraphDatabase::insertIntoGraphSet(string gsname, vector<string>& gidlist) {
	for (int i = 0; i < gidlist.size(); ++i) {
		linkGraphToGraphSet(gidlist[i], gsname);
	}
}

void GraphDatabase::removeFromGraphSet(string gsname, vector<string>& gidlist) {
	GraphSetManager* gsm = NULL;

	if (!getGraphSet(gsname, gsm)) {
		return;
	}

	for (int i = 0; i < gidlist.size(); ++i) {
		if (!hasGraph(gidlist[i]))
			continue;
		gsm->removeGraph(gidlist[i]);
	}
}

void GraphDatabase::insertIntoGraph(GraphStat& gs, string& gid) {
	GraphManager* gm;
	if (getGraph(gid, gm)) {
		TempGraph insertGraph(gs, gm);
		gm->gUpdater->insertDataV1(*gm, insertGraph);
	}
}

void GraphDatabase::removeFromGraph(GraphStat& gs, string& gid) {
	GraphManager* gm;
	if (getGraph(gid, gm)) {
		TempGraph removeGraph(gs, gm);
		gm->gUpdater->deleteData(*gm, removeGraph.netWorkSet);
	}
}
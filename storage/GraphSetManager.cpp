#include "GraphSetManager.h"

GraphSetManager::GraphSetManager(string gname, GraphDatabase* db) {
	// open an existing graph set
	name = gname;
	gdb = db;

	base_dir = "gsets\\";
	if (_access((base_dir + gname).c_str(), 0) != 0) {
		cout << "Graph set not exist!" << endl;
		gIO = NULL;
		return;
	}

	gIO = new GraphIO(base_dir + gname + "\\content.log", false, false);

	login();

	vector<int> params;
	gIO->mapping(this, 0, params);

	for (auto& g : gManagers) {
		if (!registerGraph(g.first, g.second)) {
			gManagers.erase(g.first);
		}
	}

	delete gIO;
	gIO = new GraphIO(base_dir + gname + "\\content.log", true, false);
}

GraphSetManager::GraphSetManager(string gname, GraphDatabase* db, vector<string>& aliasg) {
	// create a new graph set
	name = gname;
	gdb = db;

	if (_access(("gsets\\" + gname).c_str(), 0) != 0) {
		system(("mkdir gsets\\" + gname).c_str());
	}

	base_dir = "gsets\\";
	gIO = new GraphIO(base_dir + gname + "\\content.log", true, false);

	login();

	for (const auto& g : aliasg) {
		registerGraphFirstTime(g);
	}
}



GraphSetManager::~GraphSetManager() {
	close();
}

bool GraphSetManager::registerGraphFirstTime(string gname, int auth) {
	string gtime = "";
	if (gdb->dispatchGraph(gname, gtime, this, auth)) {
		gManagers[gname] = gtime;
		graphAuth[gname] = auth;
		return true;
	}
	else
		return false;
}

bool GraphSetManager::registerGraph(string gname, string gtime, int auth) {
	if (gdb->dispatchGraph(gname, gtime, this, auth)) {
		gManagers[gname] = gtime;
		graphAuth[gname] = auth;
		return true;
	}
	else
		return false;
}

bool GraphSetManager::returnGraph(string gname, int auth) {
	if (gdb->retrieveGraph(gname, this, auth)) {
		graphAuth.erase(gname);
		gManagers.erase(gname);
		return true;
	}
	else
		return false;
}

void GraphSetManager::removeGraph(string gname) {
	if (gdb->retrieveGraph(gname, this, -1)) {
		graphAuth.erase(gname);
		gManagers.erase(gname);
	}
}

bool GraphSetManager::login() {
	gdb->addGraphSet(this);
	return true;
}

bool GraphSetManager::logout() {
	gdb->removeGraphSet(this, graphAuth);
	return true;
}

void GraphSetManager::close() {
	vector<int> params;
	gIO->unmapping(this, 0, params);

	if (gIO)
		delete gIO;

	for (const auto& graph : graphAuth) {
		returnGraph(graph.first, graph.second);
	}

	logout();
}

GraphManager* GraphSetManager::getGraph(string gname) {
	return gdb->graphs[gname];
}
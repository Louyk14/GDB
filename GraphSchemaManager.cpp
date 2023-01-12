#include "GraphSchemaManager.h"

GraphSchemaManager::GraphSchemaManager(string dir) {
	base_dir = dir;

	loadAllSchema();
}

GraphSchemaManager::~GraphSchemaManager() {
	for (const auto& schema : schemas) {
		delete schema.second;
	}
}

bool GraphSchemaManager::loadSchema(string name) {
	GraphSchema* schema = new GraphSchema(base_dir + "\\" + name + ".sch");
	schemas[name] = schema;
	return true;
}

bool GraphSchemaManager::loadAllSchema() {
	vector<string> files;
	intptr_t hFile = 0;
	struct _finddata_t fileinfo;
	string path = base_dir;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
		do {
			if (fileinfo.attrib & _A_SUBDIR) {
				
			}
			else {
				files.push_back(fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}

	for (const auto& name : files) {
		string cur = "";
		for (int i = 0; i < name.size(); ++i) {
			if (name[i] == '.')
				break;
			else
				cur += name[i];
		}
		loadSchema(cur);
	}

	return true;
}

void GraphSchemaManager::createSchema(string schemaname, unordered_map<string, vector<pair<string, string>>>& nodeAttrMap, unordered_map<string, vector<pair<string, string>>>& edgeAttrMap, unordered_map<string, vector<pair<string, string>>>& schemaNetwork) {
	if (schemas.find(schemaname) != schemas.end()) {
		cout << "Duplicate schema ID" << endl;
		return;
	}
	GraphSchema* gs = new GraphSchema(base_dir + "\\" + schemaname + ".sch", schemaname, nodeAttrMap, edgeAttrMap, schemaNetwork);
	schemas[schemaname] = gs;
}

void GraphSchemaManager::createSchema(string filename) {
	bool succ = true;
	GraphSchema* gs = new GraphSchema(filename, base_dir, schemas, succ);
	if (succ) {
		schemas[gs->name] = gs;
	}
	else {
		cout << "Duplicate schema ID" << endl;
	}
}

void GraphSchemaManager::dropSchema(string& schemaname) {
	if (hasSchema(schemaname)) {
		delete schemas[schemaname];
		schemas.erase(schemaname);
		system(("DEL " + base_dir + "\\" + schemaname + ".sch").c_str());
	}
	else {
		cout << "Schema not found !" << endl;
	}
}

void GraphSchemaManager::dispatchSchema(string& schemaname, GraphSchema*& gschema, int type) {
	if (hasSchema(schemaname)) {
		gschema = schemas[schemaname];
		if (type == 0) {
			schemas[schemaname]->addRelatedGraph(schemaname);
		}
		else if (type == 1) {
			schemas[schemaname]->addRelatedGraphSet(schemaname);
		}
	}
	else {
		cout << "Schema not found !" << endl;
		gschema = NULL;
	}
}

bool GraphSchemaManager::hasSchema(string& schemaname) {
	if (schemas.find(schemaname) != schemas.end()) {
		return true;
	}
	else {
		return false;
	}
}
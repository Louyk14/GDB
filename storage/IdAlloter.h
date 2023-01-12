#pragma once
#ifndef IDALLOTER_H
#define IDALLOTER_H

#include "IDPool.h"

#include <iostream>
using namespace std;

template<class ID_TYPE>
class IdAlloter {
public:
	IdAlloter(string path, string n, ID_TYPE& dval, bool overwrite)
	{
		allotNew = false;
		name = n;
		defaultval = dval;

		pool = new IDPoolDisk(path + "_" + name + "IdPool.idx", false);
		storepath = path + "_" + name + "IdAlloter.idx";
		gIO = new GraphIO(storepath, overwrite);
		readFromFile(gIO->file, 0);
	};

	~IdAlloter() {
		if (pool)
			delete pool;

		delete gIO;
		gIO = new GraphIO(storepath, true);

		writeToFile(gIO->file, 0);

		if (gIO)
			delete gIO;
	}

	string name;
	string storepath;
	IDPoolDisk* pool;
	bool allotNew;
	unordered_map<ID_TYPE, int> o2nMapper;
	vector<ID_TYPE> n2oMapper;
	GraphIO* gIO;
	ID_TYPE defaultval;

	int allotId(ID_TYPE& id) {
		int nid = -1;
		// id is a outterId from user assigned before ?
		if (oidExist(id))
		{
			nid = mappedId(id);
			setAlloted(false);
		}
		else
		{
			nid = idAlloter(id);
			setAlloted(pool->newAlloted());
		}

		return nid;
	}

	bool oidExist(ID_TYPE& id) {
		return o2nMapper.find(id) != o2nMapper.end();
	}

	bool nidExist(int id) {
		return id <= pool->maxId && n2oMapper[id] != defaultval;
	}
	//bool isOuterId(int id);
	//bool isInnerId(int id);
	bool existId(int id) {
		return id <= pool->maxId && n2oMapper[id] != defaultval;
	}
	int mappedId(ID_TYPE& id) {
		return o2nMapper[id];
	}
	bool newAlloted() {
		return allotNew;
	}
	void setAlloted(bool s) {
		allotNew = s;
	}

	void idAlloter(vector<ID_TYPE>& nodes) {
		for (const auto& n : nodes)
		{
			int m = pool->nextId();
			o2nMapper[n] = m;

			if (pool->createNew)
				n2oMapper.push_back(n);
			else
				n2oMapper[m] = n;
		}
	}

	int idAlloter(ID_TYPE& node) {
		int newId = pool->nextId();
		o2nMapper[node] = newId;

		if (pool->createNew)
			n2oMapper.push_back(node);
		else
			n2oMapper[newId] = node;

		return newId;
	}
	// id is a newId
	void removenId(int id) {
		if (nidExist(id))
		{
			ID_TYPE oid = n2oMapper[id];
			n2oMapper[id] = defaultval;
			o2nMapper.erase(oid);
			pool->removeId(id);
		}
		else
		{
			cout << "ID not exist!" << endl;
		}
	}
	void removeoId(ID_TYPE& id) {
		int nid = -1;
		if (oidExist(id))
		{
			nid = mappedId(id);
			n2oMapper[nid] = defaultval;
			o2nMapper.erase(id);
			pool->removeId(nid);
		}
		else
		{
			cout << "ID not exist!" << endl;
		}
	}
	
	int getMaxId() { return pool->maxId; }
	int getIdNum() { return pool->idNum; }
	
	void set(int n) {
		n2oMapper = vector<int>(n + 1, defaultval);
		pool->set(n);
	}
	//void set(int n, vector<int>& existIds);
	void setDefault(ID_TYPE& dval) {
		defaultval = dval;
	}

	void readFromFile(fstream& db_file, int offset) {
		db_file.seekg(offset);		
		// start from 1
		n2oMapper.push_back(defaultval);
		ID_TYPE t;
		int counter = 1;
		while (db_file.read(reinterpret_cast<char*>(&t), sizeof(ID_TYPE))) {
			n2oMapper.push_back(t);
			if (t != defaultval) {
				o2nMapper[t] = counter;
			}		
			counter++;
		}
	}

	void writeToFile(fstream& db_file, int offset) {
		db_file.clear();
		db_file.seekp(offset);
		for (int i = 1; i < n2oMapper.size(); ++i) {
			db_file.write(reinterpret_cast<const char*>(&n2oMapper[i]), sizeof(ID_TYPE));
		}
	}
};

#endif
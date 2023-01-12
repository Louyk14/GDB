#pragma once

#include "GraphIO.h"
#include "../tools.h"

#include <vector>
#include <list>
#include <unordered_map>
#include <omp.h>
#include <fstream>
#include <iostream>
using namespace std;

template <typename T>
struct CacheNode {
public:
	CacheNode(int offset) : offset(offset), used(0), alive(true), data(nullptr) {}
	CacheNode(int offset, T& data) : offset(offset), data(data), alive(true), used(0) {}

public:
	void lock() {
		if(alive)
			++used;
	}
	void unlock() {
		if(alive)
			--used;
	}

	bool locked() {
		return used != 0;
	}

	void init(int off, vector<int>& params)
	{
		offset = off;
		used = 0;
		data->init(params);
		alive = true;
	}

public:
	int used;
	int offset;
	T* data; // 类型T须重载operator=或者拷贝构造函数，以及默认构造函数
	bool alive;
};

template <typename T>
class Cache
{
public:
	typedef list<CacheNode<T>*> CacheData;
	typedef typename CacheData::iterator CacheUnit;

public:
	Cache(string& dn, string& db_file, int cache_size, int dsize, bool offmap = false, int start_off = 0, bool is_parallel = false, vector<int>& p = vector<int>(), bool overwrite=false)
		: db_name(dn), is_parallel(is_parallel), data_size(dsize), offset_mapping(offmap), start_offset(start_off), cache_size(cache_size), params(p), lock() {
		gIO = new GraphIO(db_file, overwrite);
		omp_init_lock(&lock);
	}

	Cache() { };

	Cache(Cache* c, string newname) {
		db_name = newname;
		is_parallel = c->is_parallel;
		data_size = c->data_size;
		offset_mapping = c->offset_mapping;
		start_offset = c->start_offset;
		cache_size = c->cache_size;
		params = c->params;
		string path = c->gIO->filename;
		replacekmp(path, c->db_name, newname);
		gIO = new GraphIO(path, false);
		lock = c->lock;
		omp_init_lock(&lock);
	}

	void copyTo(Cache& c, string newname) {
		c.db_name = newname;

		c.is_parallel = is_parallel;
		c.data_size = data_size;
		c.offset_mapping = offset_mapping;
		c.start_offset = start_offset;
		c.cache_size = cache_size;
		c.params = params;

		string path = gIO->filename;
		replacekmp(path, db_name, newname);
		c.gIO = new GraphIO(path, false);
		c.lock = lock;
		omp_init_lock(&c.lock);
	}

	~Cache() {
		omp_destroy_lock(&lock);
		clear();

		if (gIO)
			delete gIO;
	}

public:
	void create(CacheNode<T>*& unit, int offset, T* data = nullptr) {
		if (is_parallel)
			omp_set_lock(&lock);

		if (cache_size != 0) {
			set(offset, false, data);
			unit = *(--cache_data.end());
		}

		if (is_parallel)
			omp_unset_lock(&lock);
	}

	CacheNode<T>*& get_and_init(int offset, vector<int>& init_params)
	{
		if (is_parallel)
			omp_set_lock(&lock);

		if (map.find(offset) != map.end()) {
			CacheData::iterator unit_it = map[offset];
			if ((*unit_it)->alive)
				cout << "Error in Cache: Try to init unremoved cache ! (alive = True)" << endl;				
			else
			{
				(*unit_it)->init(offset, init_params);
				
				if (unit_it != (--cache_data.end()))
					map[offset] = promote(map[offset]);
			}
		}
		else if (cache_size != 0) {
			set(offset, true);
			CacheNode<T>* unit = *(--cache_data.end());
			unit->init(offset, params);		
		}

		if (is_parallel)
			omp_unset_lock(&lock);
		
		return *map[offset];
	}

	void get(CacheNode<T>*& unit, int offset) {
		if (is_parallel)
			omp_set_lock(&lock);

		if (map.find(offset) != map.end()) {
			CacheData::iterator unit_it = map[offset];
			if (!(*unit_it)->alive)
			{
				cout << "Error in Cache: Try to get removed cache ! (alive = False)" << endl;
				return;
			}

			if (unit_it != (--cache_data.end())) {
				map[offset] = promote(map[offset]);
			}
			unit = *map[offset];
		}
		else if (cache_size != 0) {
			set(offset, true);
			unit = *(--cache_data.end());
		}

		if (is_parallel)
			omp_unset_lock(&lock);
	}

	void remove(int offset) {
		if (map.find(offset) != map.end()) {
			CacheData::iterator unit_it = map[offset];
			if (unit_it != (--cache_data.end())) {
				if ((*unit_it)->alive)
					(*unit_it)->alive = false;
			}
		}
	}

	void write(T& meta, int offset, int type) {
		if (map.find(offset) == map.end()) {
			set(offset, meta);
		}
	}

	void clear() {
		if (map.size() > 0) {
			unordered_map<int, CacheUnit>::iterator it = map.begin();
			while (it != map.end()) {
				writeBack(*(it->second));
				++it;
			}
			map.clear();
		}
		for (auto& u : cache_data) {
			delete u;
		}
		cache_data.clear();
	}

	void writeBackDirect(T* data, int offset) {
		gIO->unmapping(data, offsetMapper(offset), params);
	}

	int getSize() {
		return cache_size;
	}

	GraphIO* getIO() {
		return gIO;
	}

private:
	int offsetMapper(int offset) {
		if (offset_mapping)
			return start_offset + offset * data_size;
		else
			return offset;
	}

	CacheUnit promote(CacheUnit iter) {
		cache_data.splice(cache_data.end(), cache_data, iter);
		return (--cache_data.end());
	}

	void writeBack(CacheNode<T>* node, bool to_delete = true) {
		if (node->alive)
			gIO->unmapping(node->data, offsetMapper(node->offset), params);
		
		if (to_delete)
			delete node->data;
	}

	void set(int offset, T& data) {
		set(offset, false, &data);
	}

	void set(int offset, bool read, T* data = nullptr) {
		// 若read为true，则不管data是否为null均从文件读；若read为false，则根据data是否为空决定是否为新建

		if (cache_size == 0)
			return;

		if (cache_data.size() < cache_size) {
			CacheNode<T>* node = new CacheNode<T>(offset);
			if (read) {
				node->data = new T();
				gIO->mapping(node->data, offsetMapper(offset), params);
			}
			else if (data) {
				node->data = data; // cant use T(*data) 
			}
			map[offset] = cache_data.insert(cache_data.end(), node);
		}
		else {
			int pos = 0;
			int erase_unit = -1;
			CacheUnit to_erase = cache_data.begin();
			for (const auto& u : cache_data) {
				if (u->used == 0) {
					erase_unit = u->offset;
					break;
				}
				else if (u->used < 0) {
					cout << "Cache Error: Cache.h, L." << __LINE__ << endl;
				}
				++pos;
				++to_erase;
			}
			if (to_erase == cache_data.end()) {
				cout << "Cache Overflow!" << endl;
				return;
			}
			map.erase(erase_unit);
			writeBack(*to_erase, false);

			CacheNode<T>* c = *to_erase;
			c->offset = offset;
			if (read) {
				gIO->mapping(c->data, offsetMapper(offset), params);
			}
			else if (data) {
				c->data = data;
			}
			else {
				c->data = new T();
			}

			cache_data.splice(cache_data.end(), cache_data, to_erase);
			map[offset] = (--cache_data.end());
		}
	}

public:
	// 数据文件
	GraphIO* gIO;
	string db_name;

	// 缓存结构
	CacheData cache_data;
	unordered_map<int, CacheUnit> map;
	int cache_size;
	vector<int> params;
	int data_size;
	bool offset_mapping;
	int start_offset;

	// 并发控制
	bool is_parallel;
	omp_lock_t lock;
};

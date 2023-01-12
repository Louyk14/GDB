#pragma once
#ifndef BIGKEYINDEX_H
#define BIGKEYINDEX_H

#include "GraphIO.h"
#include "IDPool.h"
#include "BigKeyCacheManager.h"

#include <vector>
#include <unordered_set>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

// GetBigKey: 读取缓存结构
// WriteBigKey：把数据写入缓存结构

template <class BIG_KEY_VALUE_TYPE>
class BigKeyIndex {
public:
	GraphIO* gIO;
	IDPoolDisk* bigKeyIdPool;
	BigKeyCacheManager<BIG_KEY_VALUE_TYPE>* bigKeyCacheManager;

	CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* allotNewBigKey()
	{
		CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* new_node = nullptr;
		int nodeIndex = bigKeyIdPool->nextId();
		if (bigKeyIdPool->newAlloted())
		{
			new_node = bigKeyCacheManager->createBigKeyNodeNodeCache(nodeIndex);
		}
		else
		{
			new_node = bigKeyCacheManager->initCache(bigKeyCacheManager->getBigKeyNodeCache(), nodeIndex);
		}

		return new_node;
	}

	int getBigKeyNodeNum()
	{
		return bigKeyIdPool->idNum;
	}

	BigKeyIndex(string base_dir, string& big_key_file, int big_key_cache_size, int big_key_size, bool big_key_offmap, 
		int big_key_start_off, int meta_size, bool is_parallel = false, vector<int>& block_params = vector<int>(), bool overwrite = false)
	{
		if (overwrite) {
			// gIO = new GraphIO(big_key_file + "_nodeBlockBigKey.idx", true);
			string filename = base_dir + big_key_file + "//_pool_nodeBlockBigKeyIndex.idx";
			bigKeyIdPool = new IDPoolDisk(filename, overwrite, true);

			bigKeyCacheManager = new BigKeyCacheManager<BIG_KEY_VALUE_TYPE>(base_dir, big_key_file, big_key_file, big_key_cache_size, big_key_size, big_key_offmap,
				big_key_start_off, meta_size, is_parallel, block_params, overwrite);

			CacheNode<BigKeyMeta>* unit = new CacheNode<BigKeyMeta>(0);
			bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyMetaCache(), unit, 0);
		}
		else {
			// gIO = new GraphIO(big_key_file + "_nodeBlockBigKey.idx", false);
			string filename = base_dir + big_key_file + "//_pool_nodeBlockBigKeyIndex.idx";
			bigKeyIdPool = new IDPoolDisk(filename, overwrite, true);

			bigKeyCacheManager = new BigKeyCacheManager<BIG_KEY_VALUE_TYPE>(base_dir, big_key_file, big_key_file, big_key_cache_size, big_key_size, big_key_offmap,
				big_key_start_off, meta_size, is_parallel, block_params, overwrite);
		}
	}

	BigKeyIndex(BigKeyIndex* bki, string base_dir, string newname)
	{
		// gIO = new GraphIO(big_key_file + "_nodeBlockBigKey.idx", true);
		string filename = base_dir + newname + "//_pool_nodeBlockBigKeyIndex.idx";
		bigKeyIdPool = new IDPoolDisk(bki->bigKeyIdPool, filename);

		bigKeyCacheManager = new BigKeyCacheManager<BIG_KEY_VALUE_TYPE>(bki->bigKeyCacheManager, base_dir, newname);

		CacheNode<BigKeyMeta>* unit = new CacheNode<BigKeyMeta>(0);
		bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyMetaCache(), unit, 0);
	}

	~BigKeyIndex()
	{
		if (bigKeyIdPool)
			delete bigKeyIdPool;
		if (bigKeyCacheManager)
			delete bigKeyCacheManager;
		if (gIO)
			delete gIO;
	}

	void open()
	{
		gIO->open();
	}

	void close()
	{
		gIO->close();
	}

	int insertNewkey(const vector<BIG_KEY_VALUE_TYPE>& value)//创建新key，第一个块。
	{
		int nodeNum = value.size() / BIG_KEY_ORDER;
		if (value.size() % BIG_KEY_ORDER != 0)
			nodeNum++;

		int start = 0;
		int start_index = 0;

		CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* first_node = nullptr;
		CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* second_node = nullptr;

		for (int i = 0; i < nodeNum; ++i)
		{
			if (i == 0)
			{
				first_node = allotNewBigKey();
				insertValues(first_node->data, value, start);
				start_index = first_node->offset;
			}
			else
			{
				if(second_node != nullptr)
					bigKeyCacheManager->releaseCache(second_node, bigKeyIdPool);

				second_node = first_node;
				first_node = allotNewBigKey();
				insertValues(first_node->data, value, start);
				second_node->data->meta.next = first_node->offset;
			}
		}

		if(first_node != nullptr)
			bigKeyCacheManager->releaseCache(first_node, bigKeyIdPool);

		if(second_node != nullptr)
			bigKeyCacheManager->releaseCache(second_node, bigKeyIdPool);

		return start_index;
	}

	void insertNewkey(BigKeyNode<BIG_KEY_VALUE_TYPE>* last, const vector<BIG_KEY_VALUE_TYPE>& value, int start)//创建新key，第一个块。
	{
		int valNum = value.size() - start;
		int nodeNum = valNum / BIG_KEY_ORDER;
		if (valNum % BIG_KEY_ORDER != 0)
			nodeNum++;

		CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* first_node = nullptr;
		CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* second_node = nullptr;

		for (int i = 0; i < nodeNum; ++i)
		{
			if (i == 0)
			{
				first_node = allotNewBigKey();
				insertValues(first_node->data, value, start);
				last->meta.next = first_node->offset;
			}
			else
			{
				if (second_node != nullptr)
					bigKeyCacheManager->releaseCache(second_node, bigKeyIdPool);

				second_node = first_node;
				first_node = allotNewBigKey();
				insertValues(first_node->data, value, start);
				second_node->data->meta.next = first_node->offset;
			}
		}

		if (first_node != nullptr)
			bigKeyCacheManager->releaseCache(first_node, bigKeyIdPool);

		if (second_node != nullptr)
			bigKeyCacheManager->releaseCache(second_node, bigKeyIdPool);
	}

	// start should be initialzed with 0
	void insertValues(BigKeyNode<BIG_KEY_VALUE_TYPE>* node, const vector<BIG_KEY_VALUE_TYPE>& value, int start)
	{
		for (int i = 0; i < BIG_KEY_ORDER && start < value.size(); i++)
		{
			if (node->values[i].empty())
			{
				node->values[i] = value[start];
				start++;
				node->meta.used_count++;
			}
		}

		if (start != value.size())
		{
			int remainNum = value.size() - start;
			
			if (node->meta.next != 0)
			{
				CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* next_node = nullptr;
				bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyNodeCache(), next_node, node->meta.next);
				insertValues(next_node->data, value, start);
				bigKeyCacheManager->releaseCache(next_node, bigKeyIdPool);
			}
			else
			{
				insertNewkey(node, value, start);
			}
		}
	}

	void removeValue(BigKeyNode<BIG_KEY_VALUE_TYPE>* node, BIG_KEY_VALUE_TYPE& value)
	{
		bool find = false;
		for (int i = 0; i < BIG_KEY_ORDER; ++i)
		{
			if (node->values[i] == value)
			{
				node->values[i].clear();
				node->meta.used_count--;

				find = true;
				break;
			}
		}

		if (!find && node->meta.next != 0)
		{
			CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* next_node = nullptr;
			bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyNodeCache(), next_node, node->meta.next);
			removeValue(next_node, value);
			bigKeyCacheManager->releaseCache(next_node, bigKeyIdPool);
		}
	}

	void removeValues(BigKeyNode<BIG_KEY_VALUE_TYPE>* node, unordered_set<BIG_KEY_VALUE_TYPE>& value)
	{
		bool find = false;
		
		for (int i = 0; i < BIG_KEY_ORDER; ++i)
		{
			if (!node->values[i].empty() && value.find(node->values[i]) != value.end())
			{
				value.erase(node->values[i]);
				node->values[i].clear();
				node->meta.used_count--;
				
				if (value.empty())
				{
					find = true;
					break;
				}
			}
		}

		if (!find && node->meta.next != 0)
		{
			CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* next_node = nullptr;
			bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyNodeCache(), next_node, node->meta.next);
			removeValue(next_node, value);
			bigKeyCacheManager->releaseCache(next_node, bigKeyIdPool);
		}
	}

	void getValues(BigKeyNode<BIG_KEY_VALUE_TYPE>* node, vector<BIG_KEY_VALUE_TYPE>& values)
	{
		for (int i = 0; i < BIG_KEY_ORDER; ++i)
		{
			if (!node->values[i].empty())
				values.push_back(node->values[i]);
		}

		if (node->meta.next != 0)
		{
			CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* next_node = nullptr;
			bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyNodeCache(), next_node, node->meta.next);
			getValues(next_node, value);
			bigKeyCacheManager->releaseCache(next_node, bigKeyIdPool);
		}
	}

	// pos start from 1
	void modifyValue(BigKeyNode<BIG_KEY_VALUE_TYPE>* node, int pos, BIG_KEY_VALUE_TYPE& value)
	{
		if (BIG_KEY_ORDER < pos)
		{
			if (node->meta.next != 0)
			{
				CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* next_node = nullptr;
				bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyNodeCache(), next_node, node->meta.next);
				modifyValue(next_node, pos - BIG_KEY_ORDER, value);
				bigKeyCacheManager->releaseCache(next_node, bigKeyIdPool);
			}
			else
			{
				cout << "modify error" << endl;
			}

			return;
		}

		node->values[pos - 1] = value;
	}

	// startpos and endpos start from 1, count should be initialized with 0, endpos is included, i.e., [startpos, endpos]
	void modifyValues(BigKeyNode<BIG_KEY_VALUE_TYPE>* node, int startpos, int endpos, vector<BIG_KEY_VALUE_TYPE>& values, int start)
	{
		if (BIG_KEY_ORDER < startpos)
		{
			if (node->meta.next != 0)
			{
				CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* next_node = nullptr;
				bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyNodeCache(), next_node, node->meta.next);
				modifyValues(next_node, startpos - BIG_KEY_ORDER, endpos - BIG_KEY_ORDER, values, start);
				bigKeyCacheManager->releaseCache(next_node, bigKeyIdPool);
			}
			else
			{
				cout << "modify error" << endl;
			}

			return;
		}

		for (int i = startpos - 1; (i < BIG_KEY_ORDER) && (i < endpos) && (start < values.size()); i++, start++)
		{
			if (node->values[i].empty())
			{
				node->meta.used_count++;
			}

			node->values[i] = values[start];
		}

		if (start != values.size())
		{
			int remainNum = values.size() - start;
			if (node->meta.next != 0)
			{
				CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* next_node = nullptr;
				bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyNodeCache(), next_node, node->meta.next);
				modifyValues(next_node, 1, remainNum, values, start);
				bigKeyCacheManager->releaseCache(next_node, bigKeyIdPool);
			}
			else
			{
				insertNewkey(node, values, start);
			}
		}
	}

	// pos start from 1
	void getValue(BigKeyNode<BIG_KEY_VALUE_TYPE>* node, int pos, BIG_KEY_VALUE_TYPE& value)
	{
		if (BIG_KEY_ORDER < pos)
		{
			if (node->meta.next != 0)
			{
				CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* next_node = nullptr;
				bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyNodeCache(), next_node, node->meta.next);
				getValue(next_node, pos - BIG_KEY_ORDER, value);
				bigKeyCacheManager->releaseCache(next_node, bigKeyIdPool);
			}
			else
			{
				cout << "node not exist!" << endl;
			}

			return;
		}

		value = node->values[pos - 1];
		cout << "get value " << value << endl;
	}

	void removeNode(BigKeyNode<BIG_KEY_VALUE_TYPE>* node, int offset)
	{
		int nextoffset = node->meta.next;

		bigKeyCacheManager->getBigKeyNodeCache().remove(offset);

		if (nextoffset != 0)
		{
			CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* next_node = nullptr;
			bigKeyCacheManager->getCache(bigKeyCacheManager->getBigKeyNodeCache(), next_node, nextoffset);
			removeNode(next_node);
			bigKeyCacheManager->releaseCache(next_node, bigKeyIdPool);
		}
	}
};


#endif
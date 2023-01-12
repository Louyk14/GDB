#pragma once
#ifndef INDEXCACHEMANAGER_H
#define INDEXCACHEMANAGER_H

#include "BPlusTreeUtils.h"
#include "BPlusTreeNode.h"
#include "Cache.h"
#include "IDPool.h"

#include <algorithm>

template<class KEY_TYPE, class VALUE_TYPE>
class IndexCacheManager
{
public:
	IndexCacheManager(string base_dir, string& leaf_file, int leaf_cache_size, int leaf_size, bool leaf_offmap, int leaf_start_off,
		string& internal_file, int internal_cache_size, int internal_size, bool internal_offmap, int internal_start_off,
		int meta_size,
		bool is_parallel = false, vector<int>& block_params = vector<int>(), bool overwrite = false)
		: leaf_cache(leaf_file, base_dir + leaf_file + "//_nodeBlockLeafIndex.idx", leaf_cache_size, leaf_size, true, leaf_start_off, is_parallel, vector<int>(), overwrite),
		internal_cache(internal_file, base_dir + internal_file + "//_nodeBlockInternalIndex.idx", internal_cache_size, internal_size, internal_offmap, internal_start_off, is_parallel, vector<int>(), overwrite),
		meta_cache(internal_file, base_dir + internal_file + "//_meta_nodeBlockInternalIndex.idx", 1, meta_size, false, 0, false, vector<int>(), overwrite)
	{

	}

	IndexCacheManager(IndexCacheManager* icm, string base_dir, string newname) {
		icm->leaf_cache.copyTo(leaf_cache, newname);
		icm->internal_cache.copyTo(internal_cache, newname);
		icm->meta_cache.copyTo(meta_cache, newname);
	}

	~IndexCacheManager()
	{
		clear();
	}

public:
	Cache<LeafNode<KEY_TYPE, VALUE_TYPE>>& getNodeBlockLeafNodeCache()
	{
		return leaf_cache;
	}

	CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* createNodeBlockLeafNodeCache(int offset)
	{
		CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* node = nullptr;
		LeafNode<KEY_TYPE, VALUE_TYPE>* inode = new LeafNode<KEY_TYPE, VALUE_TYPE>();
		createCache(leaf_cache, node, offset, inode);
		return node;
	}

	Cache<InternalNode<KEY_TYPE>>& getNodeBlockInternalNodeCache()
	{
		return internal_cache;
	}

	CacheNode<InternalNode<KEY_TYPE>>* createNodeBlockInternalNodeCache(int offset)
	{
		CacheNode<InternalNode<KEY_TYPE>>* node = nullptr;
		InternalNode<KEY_TYPE>* inode = new InternalNode<int>();
		createCache(internal_cache, node, offset, inode);
		return node;
	}

	Cache<MetaT>& getTreeMetaCache()
	{
		return meta_cache;
	}

	void clear()
	{
		leaf_cache.clear();
		internal_cache.clear();
		meta_cache.clear();
	}

	template<class T>
	void createCache(Cache<T>& cache, CacheNode<T>*& unit, int offset, T* data = nullptr)
	{
		cache.create(unit, offset, data);
		unit->lock();
	}

	template<class T>
	void getCache(Cache<T>& cache, CacheNode<T>*& unit, int offset)
	{
		cache.get(unit, offset);
		unit->lock();
	}

	template<class T>
	void releaseCache(CacheNode<T>* unit, IDPool* pool)
	{
		unit->unlock();

		if (!unit->alive && !unit->locked())
		{
			pool->removeId(unit->offset);
		}
	}

	template<class T>
	CacheNode<T>*& initCache(Cache<T>& cache, int offset, vector<int>& params = vector<int>())
	{
		CacheNode<T>* unit = cache.get_and_init(offset, params);
		unit->lock();
		return unit;
	}

	template<class T>
	void bulkUploadNodes(Cache<T>& cache, vector<T*>& nodes, vector<int>& offsets)
	{
		int cache_size = cache.getSize();
		CacheNode<T>* unit = nullptr;
		
		int store_size = min(cache_size, (int)nodes.size());
		int index = 0;
		for (index = 0; index < store_size; ++index)
		{
			createCache(cache, unit, offsets[index], nodes[index]);
			unit->unlock();
		}

		for (; index < nodes.size(); ++index)
			cache.writeBackDirect(nodes[index], offsets[index]);
	}

//private:
	
	Cache<LeafNode<KEY_TYPE, VALUE_TYPE>> leaf_cache;
	Cache<InternalNode<KEY_TYPE>> internal_cache;
	Cache<MetaT> meta_cache;
};


#endif
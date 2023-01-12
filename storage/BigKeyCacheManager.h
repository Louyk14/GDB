#pragma once
#ifndef BIGKEYCACHEMANAGER_H
#define BIGKEYCACHEMANAGER_H

#include "BigKeyNode.h"
#include "Cache.h"
#include "IDPool.h"

template<class BIG_KEY_VALUE_TYPE>
class BigKeyCacheManager
{
public:
	BigKeyCacheManager(string base_dir, string dbn, string& big_key_file, int big_key_cache_size, int big_key_size, bool big_key_offmap, int big_key_start_off,
		int meta_size,
		bool is_parallel = false, vector<int>& block_params = vector<int>(), bool overwrite=false)
		: big_key_cache(dbn, base_dir + big_key_file + "//_nodeBlockBigKey.idx", big_key_cache_size, big_key_size, true, big_key_start_off, is_parallel, vector<int>(), overwrite),
		meta_cache(dbn, base_dir + big_key_file + "//_meta_nodeBlockBigKey.idx", 1, meta_size, false, 0, false, vector<int>(), overwrite)
	{

	}

	BigKeyCacheManager(BigKeyCacheManager* bkcm, string base_dir, string newname) {
		bkcm->big_key_cache.copyTo(big_key_cache, newname);
		bkcm->meta_cache.copyTo(meta_cache, newname);
	}

	~BigKeyCacheManager()
	{
		clear();
	}

public:
	Cache<BigKeyNode<BIG_KEY_VALUE_TYPE>>& getBigKeyNodeCache()
	{
		return big_key_cache;
	}

	CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* createBigKeyNodeNodeCache(int offset)
	{
		CacheNode<BigKeyNode<BIG_KEY_VALUE_TYPE>>* node = nullptr;
		BigKeyNode<BIG_KEY_VALUE_TYPE>* inode = new BigKeyNode<BIG_KEY_VALUE_TYPE>();
		createCache(big_key_cache, node, offset, inode);
		return node;
	}

	Cache<BigKeyMeta>& getBigKeyMetaCache()
	{
		return meta_cache;
	}

	void clear()
	{
		big_key_cache.clear();
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
	void releaseCache(CacheNode<T>* unit, IDPoolDisk* pool)
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

private:
	Cache<BigKeyNode<BIG_KEY_VALUE_TYPE >> big_key_cache;
	Cache<BigKeyMeta> meta_cache;
};


#endif
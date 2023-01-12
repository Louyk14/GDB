#pragma once

#include "StorageMeta.h"
#include "Cache.h"
#include "GDBBlock.h"
#include "IDPool.h"

class CacheManager
{
public:
	CacheManager(string base_dir, string& block_file, int block_size, int block_dsize, bool block_offmap, int block_start_off,
		int block_meta_dsize, bool is_parallel = false, vector<int>& block_params = vector<int>(), bool overwrite = false);
	CacheManager(CacheManager* cm, string base_dir, string newname);
	~CacheManager();

public:
	Cache<GDBBlock>& getBlockCache();
	CacheNode<GDBBlock>* createBlockCache(int block_listnum, int list_edgenum, int comid, int blockIndex);

	Cache<StorageMeta>& getBlockMetaCache();

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

	void clear();

private:
	Cache<GDBBlock> block_cache;
	Cache<StorageMeta> block_meta_cache;
};


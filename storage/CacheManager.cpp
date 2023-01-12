#include "CacheManager.h"

CacheManager::CacheManager(string base_dir, string& db_file, int size, int block_dsize, bool block_offmap, int block_start_off,
	int block_meta_dsize, bool is_parallel, vector<int>& block_params, bool overwrite)
	: block_cache(db_file, base_dir + db_file + "//_db.dat", size, block_dsize, block_offmap, block_start_off, is_parallel, block_params, overwrite), block_meta_cache(db_file, base_dir + db_file + "//_meta_db.dat", 1, block_meta_dsize, false, 0, is_parallel, vector<int>(), overwrite)
{
}

CacheManager::CacheManager(CacheManager* cm, string base_dir, string newname) {
	cm->block_cache.copyTo(block_cache, newname);
	cm->block_meta_cache.copyTo(block_meta_cache, newname);
	// block_meta_cache = cm->block_meta_cache;
}

CacheManager::~CacheManager()
{
	clear();
}

Cache<GDBBlock>& CacheManager::getBlockCache()
{
	return block_cache;
}

CacheNode<GDBBlock>* CacheManager::createBlockCache(int block_listnum, int list_edgenum, int comid, int blockIndex)
{
	CacheNode<GDBBlock>* block = nullptr;
	GDBBlock* iblock = new GDBBlock(block_listnum, list_edgenum, comid);
	createCache(block_cache, block, blockIndex, iblock);
	return block;
}

Cache<StorageMeta>& CacheManager::getBlockMetaCache()
{
	return block_meta_cache;
}

void CacheManager::clear()
{
	block_cache.clear();
	block_meta_cache.clear();
}

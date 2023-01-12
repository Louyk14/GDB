#ifndef BPT_H
#define BPT_H

#ifdef USE_OPEN_MP
#include <omp.h>
#endif

#include "BPlusTreeNode.h"
#include "IndexCacheManager.h"
#include "IDPool.h"
#include "BigKeyIndex.h"

#include <string>
#include <fstream>
#include <iostream>

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <list>
#include <unordered_map>
#include <algorithm>

#ifndef UNIT_TEST
#include "BPlusTreeUtils.h"
#else
#include "util/my_unit_test_predefined.h"
#endif

using namespace std;

/* offsets */
#define OFFSET_META 0
#define OFFSET_BLOCK OFFSET_META + sizeof(MetaT)
#define SIZE_NO_CHILDREN sizeof(LeafNode<KEY_TYPE, VALUE_TYPE>) - BP_ORDER * sizeof(record_t<KEY_TYPE, VALUE_TYPE>)


/* custom compare operator for STL algorithms */
template<class KEY_TYPE>
bool operator< (const KEY_TYPE &l, const index_t<KEY_TYPE> &r) {
	return l < r.key;
}
template<class KEY_TYPE>
bool operator< (const index_t<KEY_TYPE> &l, const KEY_TYPE &r) {
	return l.key < r;
}
template<class KEY_TYPE>
bool operator== (const KEY_TYPE &l, const index_t<KEY_TYPE> &r) {
	return l == r.key;
}
template<class KEY_TYPE>
bool operator== (const index_t<KEY_TYPE> &l, const KEY_TYPE &r) {
	return l.key == r;
}

template<class KEY_TYPE, class VALUE_TYPE>
bool operator< (const KEY_TYPE &l, const record_t<KEY_TYPE, VALUE_TYPE> &r) {
	return l < r.key;
}
template<class KEY_TYPE, class VALUE_TYPE>
bool operator< (const record_t<KEY_TYPE, VALUE_TYPE> &l, const KEY_TYPE &r) {
	return l.key < r;
}
template<class KEY_TYPE, class VALUE_TYPE>
bool operator== (const KEY_TYPE &l, const record_t<KEY_TYPE, VALUE_TYPE> &r) {
	return l == r.key;
}
template<class KEY_TYPE, class VALUE_TYPE>
bool operator== (const record_t<KEY_TYPE, VALUE_TYPE> &l, const KEY_TYPE &r) {
	return l.key == r;
}

/* helper iterating function */
template<class VALUE_TYPE>
inline typename VALUE_TYPE::child_t begin(VALUE_TYPE &node) {
	return node.children;
}
template<class VALUE_TYPE>
inline typename VALUE_TYPE::child_t end(VALUE_TYPE &node) {
	return node.children + node.n;
}

/* helper searching function */
template<class KEY_TYPE>
inline index_t<KEY_TYPE> *find(InternalNode<KEY_TYPE> &node, const KEY_TYPE &key) {
	if (key) {
		return upper_bound(begin(*node), end(*node) - 1, key);
	}
	if (node.n > 1) {
		return node.children + node.n - 2;
	}
	return begin(*node);
}
template<class KEY_TYPE, class VALUE_TYPE>
inline record_t<KEY_TYPE, VALUE_TYPE> *find(LeafNode<KEY_TYPE, VALUE_TYPE> &node, const KEY_TYPE &key) {
	return lower_bound(begin(*node), end(*node), key);
}

/* the encapulated B+ tree */
template<class KEY_TYPE, class VALUE_TYPE, class BIG_KEY_VALUE_TYPE>
class BPlusTree {
public:
	IndexCacheManager<KEY_TYPE, VALUE_TYPE>* indexCacheManager;
	IDPoolDisk* leafIdPool, *internalIdPool;
	BigKeyIndex<BIG_KEY_VALUE_TYPE>* bigKeyIndex;

	CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* allotNewLeaf()
	{
		CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* new_leaf = nullptr;
		int leafIndex = leafIdPool->nextId();
		if (leafIdPool->newAlloted())
		{
			 new_leaf = indexCacheManager->createNodeBlockLeafNodeCache(leafIndex);
		}
		else
		{
			new_leaf = indexCacheManager->initCache(indexCacheManager->getNodeBlockLeafNodeCache(), leafIndex);
		}

		return new_leaf;
	}

	int getLeafNodeNum()
	{
		return leafIdPool->idNum;
	}

	CacheNode<InternalNode<KEY_TYPE>>* allotNewInternal()
	{
		CacheNode<InternalNode<KEY_TYPE>>* new_internal = nullptr;
		int internalIndex = internalIdPool->nextId();
		if (internalIdPool->newAlloted())
		{
			new_internal = indexCacheManager->createNodeBlockInternalNodeCache(internalIndex);
		}
		else
		{
			new_internal = indexCacheManager->initCache(indexCacheManager->getNodeBlockInternalNodeCache(), internalIndex);
		}

		return new_internal;
	}

	int getInternalNodeNum()
	{
		return internalIdPool->idNum;
}

#ifdef USE_OPEN_MP
	mutable omp_lock_t leaf_lock;
	mutable omp_lock_t internal_lock;
#endif

	BPlusTree(string base_dir, string leaf_file, string internal_file, int leaf_cache_size, int internal_cache_size, 
		string big_key_file, int big_key_cache_size, bool force_empty = false, bool overwrite = false)
	{
#ifdef USE_OPEN_MP
		omp_init_lock(&leaf_lock);
		omp_init_lock(&internal_lock);
#endif
		indexCacheManager = new IndexCacheManager<KEY_TYPE, VALUE_TYPE>(base_dir, leaf_file, leaf_cache_size, sizeof(LeafNode<KEY_TYPE, VALUE_TYPE>), true, 0,
			internal_file, internal_cache_size, sizeof(InternalNode<KEY_TYPE>), true, sizeof(MetaT), 
			sizeof(MetaT), false, vector<int>(), overwrite);

		bigKeyIndex = new BigKeyIndex<BIG_KEY_VALUE_TYPE>(base_dir, big_key_file, big_key_cache_size, sizeof(BigKeyNode<BIG_KEY_VALUE_TYPE>), true, sizeof(BigKeyMeta),
			sizeof(BigKeyMeta), false, vector<int>(), overwrite);

		leafIdPool = new IDPoolDisk(base_dir + leaf_file + "//_pool_nodeBlockLeafIndex.idx", overwrite, true);
		internalIdPool = new IDPoolDisk(base_dir + internal_file + "//_pool_nodeBlockInternalIndex.idx", overwrite, true);

		if (!force_empty)
			indexCacheManager->getCache(indexCacheManager->getTreeMetaCache(), meta, OFFSET_META);		
		else
			init_from_empty();
	}

	BPlusTree(BPlusTree* bpt, string base_dir, string newname)
	{
#ifdef USE_OPEN_MP
		omp_init_lock(&leaf_lock);
		omp_init_lock(&internal_lock);
#endif
		indexCacheManager = new IndexCacheManager<KEY_TYPE, VALUE_TYPE>(bpt->indexCacheManager, base_dir, newname);

		bigKeyIndex = new BigKeyIndex<BIG_KEY_VALUE_TYPE>(bpt->bigKeyIndex, base_dir, newname);

		leafIdPool = new IDPoolDisk(bpt->leafIdPool, base_dir + newname + "//_pool_nodeBlockLeafIndex.idx");
		internalIdPool = new IDPoolDisk(bpt->internalIdPool, base_dir + newname + "//_pool_nodeBlockInternalIndex.idx");

		indexCacheManager->getCache(indexCacheManager->getTreeMetaCache(), meta, OFFSET_META);
	}

	~BPlusTree() {
		//  Cache should be cleared
		if (indexCacheManager)
			delete indexCacheManager;
		if (bigKeyIndex)
			delete bigKeyIndex;
		if (leafIdPool)
			delete leafIdPool;
		if (internalIdPool)
			delete internalIdPool;

#ifdef USE_OPEN_MP
		omp_destroy_lock(&leaf_lock);
		omp_destroy_lock(&internal_lock);
#endif
	}

	/* abstract operations */
	int search(const KEY_TYPE& key, VALUE_TYPE *value) const
	{
		CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* leaf = nullptr;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), leaf, search_leaf(key));

		// finding the record
		record_t<KEY_TYPE, VALUE_TYPE> *record = find(leaf->data, key);
		if (record != leaf->data->children + leaf->data->n) {
			// always return the lower bound
			*value = record->value;

			int res = keycmp(record->key, key);
			indexCacheManager->releaseCache(leaf, leafIdPool);
			return res;
		}
		else {
			indexCacheManager->releaseCache(leaf, leafIdPool);
			return -1;
		}
	}

	void print_tab(int n) const {
		for (int i = 0; i < n; i++)
			printf("\t");
	}

	void print_tree(LeafNode<KEY_TYPE, VALUE_TYPE>& leaf, int tab_num) const {
		print_tab(tab_num);
		printf("\t\t\tLEAF HAVE children number %d\n", leaf.n);
		for (int i = 0; i < leaf.n; i++) {
			print_tab(tab_num);
			printf("\t\t\t\tCHILD[%d]: %s\n", i, leaf.children[i].key.k);
		}
		print_tab(tab_num);
		printf("\t\t\tEND OF LEAF\n");
	}

	void print_tree(InternalNode<KEY_TYPE>& internal, int height, int tab_num) const {
		print_tab(tab_num);
		printf("\tINTERNAL HAVE children number %d\n", internal.n);
		for (int i = 0; i < internal.n; i++) {
			print_tab(tab_num);
			printf("\t\tCHILD[%d]:%s\n", i, internal.children[i].key.k);
			if (height > 1) {
				CacheNode<InternalNode<KEY_TYPE>>* tmp = nullptr;
				indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), tmp, internal.children[i].child);
				print_tree(tmp->data, height - 1, tab_num + 2);
				indexCacheManager->releaseCache(tmp, internalIdPool);
			}
			else {
				CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* tmp = nullptr;
				indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), tmp, internal.children[i].child);
				print_tree(tmp->data, tab_num);
				indexCacheManager->releaseCache(tmp, leafIdPool);
			}
		}
		print_tab(tab_num);
		printf("\tEND OF INTERNAL\n");
	}

	void print_tree() const {
		printf("\n\n==========================\nTREE:\n");
		CacheNode<InternalNode<KEY_TYPE>>* tmp = nullptr;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), tmp, search_leaf(meta->data->root_offset));
		print_tree(tmp, meta->data->height, 0);
		indexCacheManager->releaseCache(tmp, internalIdPool);
		printf("END_TREE\n");
	}

	int search_range(KEY_TYPE *left, const KEY_TYPE &right,
		VALUE_TYPE *values, size_t max, bool *next = NULL) const
	{
		if (left == NULL || keycmp(*left, right) > 0)
			return -1;

		int off_left = search_leaf(*left);
		int off_right = search_leaf(right);
		int off = off_left;
		size_t i = 0;
		record_t<KEY_TYPE, VALUE_TYPE> *b, *e;

		CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* leaf = nullptr;
		while (off != off_right && off != -1 && i < max) {
			indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), leaf, off);

			// start point
			if (off_left == off)
				b = find(leaf->data, *left);
			else
				b = begin(*leaf->data);

			// copy
			e = leaf->data->children + leaf->data->n;
			for (; b != e && i < max; ++b, ++i)
				values[i] = b->value;

			off = leaf->data->next;

			indexCacheManager->releaseCache(leaf, leafIdPool);
		}

		// the last leaf
		if (i < max) {
			indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), leaf, off_right);

			b = find(leaf->data, *left);
			e = upper_bound(begin(*leaf->data), end(*leaf->data), right);
			for (; b != e && i < max; ++b, ++i)
				values[i] = b->value;
			indexCacheManager->releaseCache(leaf, leafIdPool);
		}

		// mark for next iteration
		if (next != NULL) {
			if (i == max && b != e) {
				*next = true;
				*left = b->key;
			}
			else {
				*next = false;
			}
		}

		return i;
	}

	int remove(const KEY_TYPE& key)
	{
		CacheNode<InternalNode<KEY_TYPE>>* parent = nullptr;
		CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* leaf = nullptr;

		// find parent node
		int parent_off = search_index(key);
		indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), parent, parent_off);

		// find current node
		index_t<KEY_TYPE> *where = find(parent->data, key);
		int offset = where->child;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), leaf, offset);

		// verify
		if (!binary_search(begin(*leaf->data), end(*leaf->data), key))
		{
			indexCacheManager->releaseCache(parent, internalIdPool);
			indexCacheManager->releaseCache(leaf, leafIdPool);
			return -1;
		}

		size_t min_n = getLeafNodeNum() == 1 ? 0 : meta->data->order / 2;
		assert(leaf->data->n >= min_n && leaf->data->n <= meta->data->order);

		// delete the key
		record_t<KEY_TYPE, VALUE_TYPE> *to_delete = find(leaf->data, key);
		copy(to_delete + 1, end(leaf->data), to_delete);
		leaf->data->n--;

		// merge or borrow
		if (leaf->data->n < min_n) {
			// first borrow from left
			bool borrowed = false;
			if (leaf->data->prev != -1)
				borrowed = borrow_key(false, leaf->data);

			// then borrow from right
			if (!borrowed && leaf->data->next != -1)
				borrowed = borrow_key(true, leaf->data);

			// finally we merge
			if (!borrowed) {
				assert(leaf->data->next != -1 || leaf->data->prev != -1);

				KEY_TYPE index_key;

				if (where == end(parent->data) - 1) {
					// if leaf is last element then merge | prev | leaf |
					assert(leaf->data->prev != -1);
					CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* prev = nullptr;
					indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), prev, leaf->data->prev);
					index_key = begin(*prev->data)->key;

					merge_leafs(&prev->data, &leaf->data);
					node_remove(&prev->data, &leaf->data);
				}
				else {
					// else merge | leaf | next |
					assert(leaf->data->next != -1);
					CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* next = nullptr;
					indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), next, leaf->data->next);
					index_key = begin(*leaf->data)->key;  // 新的leaf的第一个的key，也就是merge过来的东西的第一个的key

					merge_leafs(&leaf->data, &next->data);
					node_remove(&leaf->data, &next->data);
				}

				indexCacheManager->releaseCache(leaf, leafIdPool);

				// remove parent's key
				remove_from_index(parent_off, parent->data, index_key, true);  // parent是当前leaf的parent
				
				indexCacheManager->releaseCache(parent, internalIdPool);
			}
			else {
				indexCacheManager->releaseCache(leaf, leafIdPool);
				indexCacheManager->releaseCache(parent, internalIdPool);
				//unmap(&leaf, offset);
			}
		}
		else {
			indexCacheManager->releaseCache(leaf, leafIdPool);
			indexCacheManager->releaseCache(parent, internalIdPool);
			//unmap(&leaf, offset);
		}

		return 0;
	}

	int insert(const KEY_TYPE& key, VALUE_TYPE value)
	{
		int parent = search_index(key);
		int offset = search_leaf(parent, key);
		CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* leaf = nullptr;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), leaf, offset);

		// check if we have the same key
		if (binary_search(begin(*leaf->data), end(*leaf->data), key))
		{
			indexCacheManager->releaseCache(leaf, leafIdPool);
			return 1;
		}

		if (leaf->data->n == meta->data->order) {
			// split when full

			// new sibling leaf
			CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* new_leaf = allotNewLeaf();
			node_create(offset, leaf->data, new_leaf->data, new_leaf->offset);

			// find even split point
			size_t point = leaf->data->n / 2;
			bool place_right = keycmp(key, leaf->data->children[point].key) > 0;
			if (place_right)
				++point;

			// split
			copy(leaf->data->children + point, leaf->data->children + leaf->data->n,
				new_leaf->data->children);
			new_leaf->data->n = leaf->data->n - point;
			leaf->data->n = point;

			// which part do we put the key
			if (place_right)
				insert_record_no_split(new_leaf->data, key, value);
			else
				insert_record_no_split(leaf->data, key, value);

			// save leafs
			//unmap(&leaf, offset);
			//unmap(&new_leaf, leaf.next);

			// insert new index key
			insert_key_to_index(parent, new_leaf->data->children[0].key,
				offset, leaf->data->next, true);
		}
		else {
			insert_record_no_split(leaf->data, key, value);
			//unmap(&leaf, offset);
		}

		indexCacheManager->releaseCache(leaf, leafIdPool);
		return 0;
	}

	int update(const KEY_TYPE& key, VALUE_TYPE value)
	{
		int offset = search_leaf(key);
		CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* leaf = nullptr;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), leaf, offset);

		record_t<KEY_TYPE, VALUE_TYPE> *record = find(leaf->data, key);
		if (record != leaf->data->children + leaf->data->n)
			if (keycmp(key, record->key) == 0) {
				record->value = value;
				//unmap(&leaf, offset);

				indexCacheManager->releaseCache(leaf, leafIdPool);
				return 0;
			}
			else {
				indexCacheManager->releaseCache(leaf, leafIdPool);
				return 1;
			}
		else
		{
			indexCacheManager->releaseCache(leaf, leafIdPool);
			return -1;
		}
	}

	MetaT get_meta() const {
		return meta->data;
	}

#ifndef UNIT_TEST
private:
#else
public:
#endif
	CacheNode<MetaT>* meta;

	/* init empty tree */
	void init_from_empty()
	{
		MetaT* temp_meta = new MetaT();
		// init default meta
		memset(temp_meta, 0, sizeof(MetaT));
		temp_meta->order = BP_ORDER;
		temp_meta->value_size = sizeof(VALUE_TYPE);
		temp_meta->key_size = sizeof(KEY_TYPE);
		temp_meta->height = 1;

		// init root node
		// CacheNode<InternalNode<int>>* root = allotNewInternal();
		temp_meta->root_offset = 0;

		// init empty leaf
		// CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* leaf = allotNewLeaf();
		// leaf->data->parent = temp_meta->root_offset;
		// temp_meta->leaf_offset = root->data->children[0].child = 0;

		// indexCacheManager->releaseCache(root);
		// indexCacheManager->releaseCache(leaf);

		indexCacheManager->createCache(indexCacheManager->getTreeMetaCache(), meta, OFFSET_META, temp_meta);
	}

	/* find index */
	int search_index(const KEY_TYPE &key) const
	{
		int org = meta->data->root_offset;
		int height = meta->data->height;
		while (height > 1) {
			CacheNode<InternalNode<KEY_TYPE>>* node = nullptr;
			indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), node, org);

			index_t<KEY_TYPE> *i = upper_bound(begin(*node->data), end(*node->data) - 1, key);
			org = i->child;
			indexCacheManager->releaseCache(node, internalIdPool);
			--height;
		}

		return org;
	}

	/* find leaf */
	int search_leaf(int index, const KEY_TYPE &key) const
	{
		CacheNode<InternalNode<KEY_TYPE>>* node = nullptr;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), node, index);

		index_t<KEY_TYPE> *i = upper_bound(begin(*node->data), end(*node->data) - 1, key);
		int res = i->child;
		indexCacheManager->releaseCache(node, internalIdPool);
		
		return res;
	}

	int search_leaf(const KEY_TYPE &key) const
	{
		return search_leaf(search_index(key), key);
	}

	/* remove internal node */
	void remove_from_index(int offset, InternalNode<KEY_TYPE> &node,
		const KEY_TYPE &key, bool is_leaf = false)
	{
		size_t min_n = meta->data->root_offset == offset ? 1 : meta->data->order / 2;
		assert(node.n >= min_n && node.n <= meta->data->order);

		// remove key
		KEY_TYPE index_key = begin(*node)->key;  // 但是当node的child的第一个被merge掉之后，就会导致这个找不到了
		index_t<KEY_TYPE> *to_delete = find(node, key);
		if (to_delete != end(node)) {
			(to_delete + 1)->child = to_delete->child;  // to_delete+1的内容里面放上了to_delete的内容，所以这样就不用专门处理to_delete+1的key了
			copy(to_delete + 1, end(node), to_delete);  // 要删除的其实是to_delete + 1，所以先把to_delete的东西放到后面一个。比如2 3 4 5里面要删除4，那就把3这个位置上面的东西放到4上面覆盖掉，然后把 4到最后 复制到 3到最后之前的一个位置上
		}
		node.n--;

		// remove to only one key
		if (node.n == 1 && meta->data->root_offset == offset 
			&& getInternalNodeNum() != 1)
		{
			unalloc(&node, meta->data->root_offset);
			meta->data->height--;
			meta->data->root_offset = node.children[0].child;
			//unmap_from_file(&meta, OFFSET_META);
			return;
		}

		// merge or borrow
		if (node.n < min_n) {
			CacheNode<InternalNode<KEY_TYPE>>* parent = nullptr;
			indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), parent, node.parent);

			// first borrow from left
			bool borrowed = false;
			if (offset != begin(*parent->data)->child)
				borrowed = borrow_key(false, node, offset, is_leaf);

			// then borrow from right
			if (!borrowed && offset != (end(*parent->data) - 1)->child)
				borrowed = borrow_key(true, node, offset, is_leaf);

			// finally we merge
			if (!borrowed) {
				assert(node.next != -1 || node.prev != -1);

				if (offset == (end(*parent->data) - 1)->child) {
					// if leaf is last element then merge | prev | leaf |
					assert(node.prev != -1);
					CacheNode<InternalNode<KEY_TYPE>>* prev = nullptr;
					indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), prev, node.prev);

					// merge
					index_t<KEY_TYPE> *where = find(parent->data, begin(*prev->data)->key);
					reset_index_children_parent(begin(*node), end(*node), node.prev, is_leaf);  // 只是把右边的节点的parent信息修改了，没有修改parent的孩子信息
					merge_keys(where, prev->data, node, true);  // 现在需要把parent的孩子改掉，同时需要把prev对应的key（也就是where的key）改掉
					//unmap(&prev, node.prev);  // 在这里parent的child的key也已经改掉了，但是还没有去掉最后一个
					indexCacheManager->releaseCache(prev, internalIdPool);
				}
				else {
					// else merge | leaf | next |
					assert(node.next != -1);
					CacheNode<InternalNode<KEY_TYPE>>* next = nullptr;
					indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), next, node.next);

					// merge
					index_t<KEY_TYPE> *where = find(parent->data, index_key);
					reset_index_children_parent(begin(*next->data), end(*next->data), offset, is_leaf);
					merge_keys(where, node, next->data);
					//unmap(&node, offset);
					indexCacheManager->releaseCache(next, internalIdPool);
				}

				// remove parent's key
				remove_from_index(node.parent, parent->data, index_key);
			}
			else {
				//unmap(&node, offset);
			}

			indexCacheManager->releaseCache(parent, internalIdPool);
		}
		else {
			//unmap(&node, offset);
		}
	}

	/* borrow one key from other internal node */
	bool borrow_key(bool from_right, InternalNode<KEY_TYPE> &borrower,
		int offset, bool is_leaf = false)
	{
		typedef typename InternalNode<KEY_TYPE>::child_t child_t;

		int lender_off = from_right ? borrower.next : borrower.prev;
		CacheNode<InternalNode<KEY_TYPE>>* lender = nullptr;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), lender, lender_off);

		assert(lender->data->n >= meta->data->order / 2);
		if (lender->data->n != meta->data->order / 2) {
			child_t where_to_lend, where_to_put;

			CacheNode<InternalNode<KEY_TYPE>>* parent = nullptr;

			// swap keys, draw on paper to see why
			if (from_right) {
				where_to_lend = begin(*lender->data);
				where_to_put = end(borrower);

				indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), parent, borrower.parent);
				child_t where = lower_bound(begin(*parent->data), end(*parent->data) - 1,
					(end(*borrower) - 1)->key);
				where->key = where_to_lend->key;
				//unmap(&parent, borrower.parent);
				indexCacheManager->releaseCache(parent, internalIdPool);
			}
			else {
				where_to_lend = end(*lender->data) - 1;
				where_to_put = begin(*borrower);

				indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), parent, lender->data->parent);
				child_t where = find(parent->data, begin(*lender->data)->key);
				// where_to_put->key = where->key;
				where->key = (where_to_lend - 1)->key;
				//unmap(&parent, lender.parent);
				indexCacheManager->releaseCache(parent, internalIdPool);
			}

			// store
			copy_backward(where_to_put, end(*borrower), end(*borrower) + 1);  // 因为要借前面的东西进来，所以现在已经有的往后移动一下挪个位置
			*where_to_put = *where_to_lend;
			borrower.n++;

			// erase
			reset_index_children_parent(where_to_lend, where_to_lend + 1, offset, is_leaf);
			copy(where_to_lend + 1, end(*lender->data), where_to_lend);
			lender->data->n--;		
			//unmap(&lender, lender_off);
			indexCacheManager->releaseCache(lender, internalIdPool);
			return true;
		}

		indexCacheManager->releaseCache(lender, internalIdPool);
		return false;
	}

	/* borrow one record from other leaf */
	bool borrow_key(bool from_right, LeafNode<KEY_TYPE, VALUE_TYPE> &borrower)
	{
		int lender_off = from_right ? borrower.next : borrower.prev;
		CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* lender = nullptr;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), lender, lender_off);

		assert(lender->data->n >= meta->data->order / 2);
		if (lender->data->n != meta->data->order / 2) {
			typename LeafNode<KEY_TYPE, VALUE_TYPE>::child_t where_to_lend, where_to_put;

			// decide offset and update parent's index key
			if (from_right) {
				where_to_lend = begin(*lender->data);
				where_to_put = end(borrower);
				change_parent_child(borrower.parent, begin(*borrower)->key,
					lender->data->children[1].key);
			}
			else {
				where_to_lend = end(lender->data) - 1;
				where_to_put = begin(*borrower);
				change_parent_child(lender->data->parent, begin(*lender->data)->key,
					where_to_lend->key);
			}

			// store
			copy_backward(where_to_put, end(*borrower), end(*borrower) + 1);
			*where_to_put = *where_to_lend;
			borrower.n++;

			// erase
			copy(where_to_lend + 1, end(lender->data), where_to_lend);
			lender->data->n--;
			//unmap(&lender, lender_off);
			indexCacheManager->releaseCache(lender, leafIdPool);
			return true;
		}

		indexCacheManager->releaseCache(lender, leafIdPool);
		return false;
	}

	/* change one's parent key to another key */
	void change_parent_child(int parent, const KEY_TYPE &o,
		const KEY_TYPE &n)
	{
		CacheNode<InternalNode<KEY_TYPE>>* node = nullptr;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), node, parent);

		index_t<KEY_TYPE> *w = find(node->data, o);
		assert(w != node->data->children + node->data->n);

		w->key = n;
		//unmap(&node, parent);
		if (w == node->data->children + node->data->n - 1) {
			change_parent_child(node->data->parent, o, n);
		}

		indexCacheManager->releaseCache(node, internalIdPool);
	}

	/* merge right leaf to left leaf */
	void merge_leafs(LeafNode<KEY_TYPE, VALUE_TYPE> *left, LeafNode<KEY_TYPE, VALUE_TYPE> *right)
	{
		std::copy(begin(*right), end(*right), end(*left));
		left->n += right->n;
	}

	void merge_keys(index_t<KEY_TYPE> *where,
		InternalNode<KEY_TYPE> &node, InternalNode<KEY_TYPE> &next, bool change_where_key = false)
	{
		//(end(node) - 1)->key = where->key;std::copy_backw
		if (change_where_key) {
			where->key = (end(next) - 1)->key;
		}
		std::copy(begin(*next), end(*next), end(*node));
		node.n += next.n;
		node_remove(&node, &next);
	}

	/* insert into leaf without split */
	void insert_record_no_split(LeafNode<KEY_TYPE, VALUE_TYPE> *leaf,
		const KEY_TYPE &key, const VALUE_TYPE &value)
	{
		record_t<KEY_TYPE, VALUE_TYPE> *where = upper_bound(begin(*leaf), end(*leaf), key);
		copy_backward(where, end(*leaf), end(*leaf) + 1);

		where->key = key;
		where->value = value;
		leaf->n++;
	}

	/* add key to the internal node */
	void insert_key_to_index(int offset, const KEY_TYPE &key,
		int old, int after, bool is_leaf = false)
	{
		if (offset == -1) {
			// create new root node
			CacheNode<InternalNode<KEY_TYPE>>* root = allotNewInternal();
			int rootIndex = root->offset;

			root->data->next = root->data->prev = root->data->parent = -1;
			meta->data->root_offset = rootIndex;
			meta->data->height++;

			// insert `old` and `after`
			root->data->n = 2;
			root->data->children[0].key = key;
			root->data->children[0].child = old;
			root->data->children[1].child = after;

			//unmap_from_file(&meta, OFFSET_META);
			//unmap(&root, meta->data->root_offset);

			// update children's parent
			reset_index_children_parent(begin(*root->data), end(*root->data),
				meta->data->root_offset);
			return;
		}

		CacheNode<InternalNode<KEY_TYPE>>* node = nullptr;
		indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), node, offset);
		assert(node->data->n <= meta->data->order);

		if (node->data->n == meta->data->order) {
			// split when full

			CacheNode<InternalNode<KEY_TYPE>>* new_node = allotNewInternal();
			node_create(offset, node->data, new_node->data, new_node->offset);

			// find even split point
			size_t point = (node->data->n - 1) / 2;
			bool place_right = keycmp(key, node->data->children[point].key) > 0;
			if (place_right)
				++point;

			// prevent the `key` being the right `middle_key`
			// example: insert 48 into |42|45| 6|  |
			if (place_right && keycmp(key, node->data->children[point].key) < 0)
				point--;

			KEY_TYPE middle_key = node->data->children[point].key;

			// split
			copy(begin(*node->data) + point + 1, end(*node->data), begin(*new_node->data));
			new_node->data->n = node->data->n - point - 1;
			node->data->n = point + 1;

			// put the new key
			if (place_right)
				insert_key_to_index_no_split(*new_node->data, key, after);
			else
				insert_key_to_index_no_split(*node->data, key, after);

			//unmap(&node, offset);
			//unmap(&new_node, node.next);

			// update children's parent
			reset_index_children_parent(begin(*new_node->data), end(*new_node->data), node->data->next, is_leaf);

			// give the middle key to the parent
			// note: middle key's child is reserved
			insert_key_to_index(node->data->parent, middle_key, offset, node->data->next);
		}
		else {
			insert_key_to_index_no_split(*node->data, key, after);
			//unmap(&node, offset);
		}

		indexCacheManager->releaseCache(node, internalIdPool);
	}

	void insert_key_to_index_no_split(InternalNode<KEY_TYPE> &node,
		const KEY_TYPE &key, int value)
	{
		index_t<KEY_TYPE> *where = upper_bound(begin(node), end(node) - 1, key);

		// move later index forward
		copy_backward(where, end(node), end(node) + 1);

		// insert this key
		where->key = key;
		where->child = (where + 1)->child;
		(where + 1)->child = value;

		node.n++;
	}

	// should be accomplish twice
	/* change children's parent */
	void reset_index_children_parent(index_t<KEY_TYPE> *begin, index_t<KEY_TYPE> *end,
		int parent, bool is_leaf = false)
	{
		// this function can change both InternalNode<KEY_TYPE> and LeafNode<KEY_TYPE, VALUE_TYPE>'s parent
		// field, but we should ensure that:
		// 1. sizeof(InternalNode<KEY_TYPE>) <= sizeof(LeafNode<KEY_TYPE, VALUE_TYPE>)
		// 2. parent field is placed in the beginning and have same size
		if (is_leaf) {
			CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* node = nullptr;
			while (begin != end) {
				indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), node, begin->child);
				node->data->parent = parent;
				//unmap_from_file(&node, begin->child, SIZE_NO_CHILDREN);
				//unmap(&node, begin->child);
				indexCacheManager->releaseCache(node, leafIdPool);
				++begin;
			}
		}
		else {
			CacheNode<InternalNode<KEY_TYPE>>* node = nullptr;
			while (begin != end) {
				indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), node, begin->child);
				node->data->parent = parent;
				//unmap_from_file(&node, begin->child, SIZE_NO_CHILDREN);
				//unmap(&node, begin->child);
				indexCacheManager->releaseCache(node, internalIdPool);
				++begin;
			}
		}
	}

	void node_create(int offset, LeafNode<KEY_TYPE, VALUE_TYPE> *node, LeafNode<KEY_TYPE, VALUE_TYPE> *next, int next_offset)
	{
		// new sibling node
		next->parent = node->parent;
		next->next = node->next;
		next->prev = offset;
		node->next = next_offset;
		// update next node's prev
		if (next->next != -1) {
			CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* old_next = nullptr;
			indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), old_next, next->next);
			old_next->data->prev = node->next;
			//unmap_from_file(&old_next, next->next, SIZE_NO_CHILDREN);
			//unmap(&old_next, next->next);
			indexCacheManager->releaseCache(old_next, leafIdPool);
		}
		//unmap_from_file(&meta, OFFSET_META);
	}

	void node_create(int offset, InternalNode<KEY_TYPE> *node, InternalNode<KEY_TYPE> *next, int next_offset)
	{
		// new sibling node
		next->parent = node->parent;
		next->next = node->next;
		next->prev = offset;
		node->next = next_offset;
		// update next node's prev
		if (next->next != -1) {
			CacheNode<InternalNode<KEY_TYPE>>* old_next = nullptr;
			indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), old_next, next->next);
			old_next->data->prev = node->next;
			//unmap_from_file(&old_next, next->next, SIZE_NO_CHILDREN);
			//unmap(&old_next, next->next);
			indexCacheManager->releaseCache(old_next, internalIdPool);
		}
		//unmap_from_file(&meta, OFFSET_META);
	}

	void node_remove(LeafNode<KEY_TYPE, VALUE_TYPE> *prev, LeafNode<KEY_TYPE, VALUE_TYPE> *node)
	{
		unalloc(node, prev->next);
		prev->next = node->next;
		if (node->next != -1) {
			CacheNode<LeafNode<KEY_TYPE, VALUE_TYPE>>* next = nullptr;
			indexCacheManager->getCache(indexCacheManager->getNodeBlockLeafNodeCache(), next, node->next);
			next->data->prev = node->prev;
			//unmap_from_file(&next, node->next, SIZE_NO_CHILDREN);
			//unmap(&next, node->next);
			indexCacheManager->releaseCache(next, leafIdPool);
		}
		//unmap_from_file(&meta, OFFSET_META);
	}

	void node_remove(InternalNode<KEY_TYPE> *prev, InternalNode<KEY_TYPE> *node)
	{
		unalloc(node, prev->next);
		prev->next = node->next;
		if (node->next != -1) {
			CacheNode<InternalNode<KEY_TYPE>>* next = nullptr;
			indexCacheManager->getCache(indexCacheManager->getNodeBlockInternalNodeCache(), next, node->next);
			next->data->prev = node->prev;
			//unmap_from_file(&next, node->next, SIZE_NO_CHILDREN);
			//unmap(&next, node->next);
			indexCacheManager->releaseCache(next, internalIdPool);
		}
		//unmap_from_file(&meta, OFFSET_META);
	}

	/* multi-level file open/close */

	void unalloc(LeafNode<KEY_TYPE, VALUE_TYPE> *leaf, int offset)
	{
		// leafIdPool.removeId(offset);
		indexCacheManager->getNodeBlockLeafNodeCache().remove(offset);
	}

	void unalloc(InternalNode<KEY_TYPE> *node, int offset)
	{
		// internalIdPool.removeId(offset);
		indexCacheManager->getNodeBlockInternalNodeCache().remove(offset);
	}

public:
	bool bulkBuildIndex(GraphManager& graph)
	{
		//Bigkey big_node_index(big_node_index_path.c_str(), true);//"Big_node_index.db"
		//big_node_index.init();

		int nodenum = graph.mGraph->nodeNum;
		int leafnum = max(1, nodenum / BULK_NUM);
		int leftnum = nodenum - BULK_NUM * leafnum;
		int myheight = 0;

		vector<int>::iterator it = graph.mGraph->initialNodes.begin();
		vector<LeafNode<KEY_TYPE, VALUE_TYPE>*> leaves;
		vector<int> leaf_offsets;

		for (int i = 0; i < leafnum; i++)
		{
			LeafNode<KEY_TYPE, VALUE_TYPE>* newleaf = new LeafNode<KEY_TYPE, VALUE_TYPE>();
			leaf_offsets.push_back(leafIdPool->nextId());

			int childnum = BULK_NUM;
			if (leftnum > 0)
			{
				childnum = childnum + min(BP_ORDER - BULK_NUM, leftnum);
				leftnum -= min(BP_ORDER - BULK_NUM, leftnum);
			}
			else if (leftnum < 0)
			{
				childnum = nodenum;
				leftnum = 0;
			}
			
			for (int j = 0; j < childnum; j++)
			{
				VALUE_TYPE new_record;
				int node = *it;

				if (graph.node_map_block[node].size() > VALUE_NUM - 1)
				{
					vector<BIG_KEY_VALUE_TYPE> pre_blocks, end_blocks;
					pre_blocks.resize(VALUE_NUM - 1);
					end_blocks.resize(graph.node_map_block[*it].size() - VALUE_NUM + 1);
					
					copy(graph.node_map_block[*it].begin(), graph.node_map_block[*it].begin() + VALUE_NUM - 1, pre_blocks.begin());
					copy(graph.node_map_block[*it].begin() + VALUE_NUM - 1, graph.node_map_block[*it].end(), end_blocks.begin());
					
					int big_offset = bigKeyIndex->insertNewkey(end_blocks);
					pre_blocks.push_back(big_offset);
					new_record.bptInit(graph.mGraph, node, VALUE_NUM, pre_blocks);
					insert_record_no_split(newleaf, node, new_record);
					graph.updateBigIndex[node] = big_offset;
				}
				else
				{
					new_record.bptInit(graph.mGraph, node, graph.node_map_block[*it].size(), graph.node_map_block[*it]);
					insert_record_no_split(newleaf, node, new_record);
				}

				it++;
			}
			
			if (!leaves.empty())
			{
				int last = leaves.size() - 1;
				leaves[last]->next = leaf_offsets[last + 1];
				newleaf->prev = leaf_offsets[last];
			}
			leaves.push_back(newleaf);
		}
		
		vector<int> internal_offsets;
		vector<InternalNode<KEY_TYPE>*> allinternodes;
		vector<InternalNode<KEY_TYPE>*> internodes;

		int lastlevelnum = leaves.size();

		int newlevelnum = max(1, lastlevelnum / BULK_NUM);
		int lastleft = lastlevelnum - newlevelnum * BULK_NUM;
		int leafindex = 0;
		int offset_index = 0;

		InternalNode<KEY_TYPE>* lastinternalnode = NULL;

		for (int i = 0; i < newlevelnum; i++)
		{
			InternalNode<KEY_TYPE>* newinternode = new InternalNode<KEY_TYPE>();
			internal_offsets.push_back(internalIdPool->nextId());

			int childnum = BULK_NUM;
			if (lastleft > 0)
			{
				childnum = childnum + min(BP_ORDER - BULK_NUM, lastleft);
				lastleft -= min(BP_ORDER - BULK_NUM, lastleft);
			}
			else if (lastleft < 0)
			{
				childnum = lastlevelnum;
				lastleft = 0;
			}

			newinternode->n = childnum;

			if (lastinternalnode != NULL)
			{
				newinternode->prev = internal_offsets[i - 1];
				lastinternalnode->next = internal_offsets[i];
			}
			
			for (int j = 0; j < childnum; j++)
			{
				if (leafindex + 1 < leaves.size())
				{
					KEY_TYPE max_key = leaves[leafindex + 1]->children[0].key;
					newinternode->children[j].key = max_key;
				}

				newinternode->children[j].child = leaf_offsets[leafindex];
				leaves[leafindex]->parent = internal_offsets[i];
				leafindex++;
			}

			lastinternalnode = newinternode;
			internodes.push_back(newinternode);
			allinternodes.push_back(newinternode);
		}

		myheight++;
		int lastindex = 0;
		
		while (internodes.size() > 1)
		{
			vector<InternalNode<KEY_TYPE>*> temp;

			lastlevelnum = internodes.size();
			newlevelnum = max(1, lastlevelnum / BULK_NUM);
			lastleft = lastlevelnum - newlevelnum * BULK_NUM;
			lastindex = 0;

			lastinternalnode = NULL;
			int start_offset_index = internal_offsets.size();

			for (int i = 0; i < newlevelnum; i++)
			{
				InternalNode<KEY_TYPE>* newinternode = new InternalNode<KEY_TYPE>();
				internal_offsets.push_back(internalIdPool->nextId());

				int childnum = BULK_NUM;
				if (lastleft > 0)
				{
					childnum = childnum + min(BP_ORDER - BULK_NUM, lastleft);
					lastleft -= min(BP_ORDER - BULK_NUM, lastleft);
				}
				else if (lastleft < 0)
				{
					childnum = lastlevelnum;
					lastleft = 0;
				}

				newinternode->n = childnum;

				for (int j = 0; j < childnum; j++)
				{
					if (lastindex + 1 < internodes.size())
					{
						int max_index = internodes[lastindex]->n - 1;
						KEY_TYPE max_key = internodes[lastindex]->children[max_index].key;
						newinternode->children[j].key = max_key;
					}
				
					newinternode->children[j].child = internal_offsets[offset_index + lastindex];
					internodes[lastindex]->parent = internal_offsets[start_offset_index + i];
					lastindex++;
				}

				lastinternalnode = newinternode;
				temp.push_back(newinternode);
				allinternodes.push_back(newinternode);
			}

			offset_index = start_offset_index;
			internodes = temp;
			myheight++;
		}

		meta->data->root_offset = *(--internal_offsets.end());
		meta->data->leaf_offset = *leaf_offsets.begin();
		meta->data->height = myheight;
		
		indexCacheManager->bulkUploadNodes(indexCacheManager->getNodeBlockLeafNodeCache(), leaves, leaf_offsets);
		indexCacheManager->bulkUploadNodes(indexCacheManager->getNodeBlockInternalNodeCache(), allinternodes, internal_offsets);

		return true;
	}
};


#endif /* end of BPT_H */
#pragma once
#ifndef BPLUSTREEUTILS_H
#define BPLUSTREEUTILS_H

//#include "../MemoryGraph.h"
#include "BigKeyNode.h"
#include <vector>
#include <deque>
#include <string.h>
using namespace std;
#define VALUE_NUM 1
//一个元素的key对应的value值的数量 4，最后一位存另一个index文件的offset
#define NODE_VALUE_NUM 1
#define value_t int

class MemoryGraph;

struct key_t {
	char k[16];

	key_t(const char *str = "")
	{
		memset(k, 0, sizeof(k));
		strcpy(k, str);
	}

	bool operator <(const key_t& b) const {
		int x = strlen(k) - strlen(b.k);
		return x < 0 || (x == 0 && strcmp(k, b.k) < 0);
	}

	bool operator ==(const key_t& b) const {
		int x = strlen(k) - strlen(b.k);
		return x == 0 && strcmp(k, b.k) == 0;
	}

	operator bool() const {
		return strcmp(k, "") != 0;
	}
};

struct key_t_int {
	int k;

	key_t_int(int kt = -1)
	{
		k = kt;
	}

	bool operator <(const key_t_int& b) const {
		return k < b.k;
	}

	bool operator ==(const key_t_int& b) const {
		return k == b.k;
	}

	operator bool() const {
		return k != -1;
	}
};

class nodeBlockPos {
public:
	double betweenness;
	int type;
	int cid;
	int count;//value中有数字的有几个
	value_t value[VALUE_NUM];
	nodeBlockPos(int comid = -1, int t = -1, int c = 0, int bet = 0) : count(c), betweenness(bet), type(t), cid(comid) { }

	void bptInit(MemoryGraph* g, int node, int valueNum, vector<value_t_int>& valuelist);
	void bptInit(MemoryGraph* g, int node, int valueNum, deque<value_t_int>& valuelist);
};


/* predefined B+ info */
#define BP_ORDER 20
#define BULK_NUM 12

template<class KEY_TYPE>
inline int keycmp(const KEY_TYPE &a, const KEY_TYPE &b) {
	if (a == b) {
		return 0;
	}
	if (a < b) {
		return -1;
	}
	return 1;
}


#endif /* end of PREDEFINED_H */
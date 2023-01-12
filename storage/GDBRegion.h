#pragma once
#ifndef GDBREGION_H
#define GDBREGION_H

#include <unordered_set>
#include <vector>
#include <iostream>
using namespace std;

class GDBRegion {
public:
	int avaBlock;
	unordered_set<int> blockIds;
	bool operator<(const GDBRegion &a)const//�Ӵ�С
	{
		return a.avaBlock < avaBlock;
	}
};

#endif